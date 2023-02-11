#include "mesh.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace gobj::mesh;

Mesh::Mesh() 
{ 
    this->add_texture("none", "res/textures/blank.jpg", false);
    this->set_diffuse_map("none");
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->verts = vertices;
    this->indices = indices;
    this->textures_ = textures;
}

Mesh::~Mesh() { }

vec3 gobj::mesh::Mesh::get_pos()
{
    return this->get_anchor();
}

void gobj::mesh::Mesh::set_speed(float speed)
{
    this->speed_ = speed;
}

void gobj::mesh::Mesh::set_ref_sys(vec3 front, vec3 up)
{
    this->front_ = front;
    this->up_ = up;
}

string Mesh::get_name()
{
    return this->name_;
}

void Mesh::set_name(string name)
{
    this->name_ = name;
}

void Mesh::add_vertex(Vertex v)
{
    this->verts.push_back(v);
}

void Mesh::set_color(vec4 color)
{
    for (unsigned int i = 0; i < this->verts.size(); i++)
    {
        this->verts[i].color = color;
    }
}

void Mesh::select()
{
    this->selected_ = true;
}

void Mesh::deselect()
{
    this->selected_ = false;
}

bool gobj::mesh::Mesh::is_selected()
{
    return this->selected_;
}

void Mesh::set_indices(vector<unsigned int> indices)
{
    this->indices = indices;
}

void Mesh::add_texture(Texture texture)
{
    for (int i = 0; i < this->textures_.size(); i++)
        if (this->textures_[i].path._Equal(texture.path)) return;

    texture.id = this->load_texture(texture.path.c_str(), 0);
    this->textures_.push_back(texture);
}

unsigned int Mesh::load_texture(char const* path, int vertical_flip)
{
    GLenum format;
    unsigned int tex_ID = 0;
    int width, height, nrChannels;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    stbi_set_flip_vertically_on_load(vertical_flip);

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &tex_ID);
        glBindTexture(GL_TEXTURE_2D, tex_ID);

        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;


        // GL_REPEAT | GL_MIRRORED_REPEAT | GL_CLAMP_TO_EDGE | GL_CLAMP_TO_BORDER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return tex_ID;
}

void Mesh::set_bounding_box()
{
    for (int i = 0; i < this->verts.size(); i++)
    {
        if (this->verts[i].pos.x > this->bb_top_right_.x) this->bb_top_right_.x = this->verts[i].pos.x;
        else if (this->verts[i].pos.x < this->bb_bottom_left_.x) this->bb_bottom_left_.x = this->verts[i].pos.x;
        
        if (this->verts[i].pos.y > this->bb_top_right_.y) this->bb_top_right_.y = this->verts[i].pos.y;
        else if (this->verts[i].pos.y < this->bb_bottom_left_.y) this->bb_bottom_left_.y = this->verts[i].pos.y;

        if (this->verts[i].pos.z > this->bb_top_right_.z) this->bb_top_right_.z = this->verts[i].pos.z;
        else if (this->verts[i].pos.z < this->bb_bottom_left_.z) this->bb_bottom_left_.z = this->verts[i].pos.z;
    }
}

vec3 Mesh::bb_top_right()
{
    return this->model * vec4(this->bb_top_right_, 1.0);
}

vec3 Mesh::bb_bottom_left()
{
    return this->model * vec4(this->bb_bottom_left_, 1.0);
}

vec3 Mesh::get_anchor()
{
    vec3 distance = abs(this->bb_bottom_left_ - this->bb_top_right_);

    vec3 anchor = vec3(0);
    anchor.x = this->bb_bottom_left_.x + distance.x / 2;
    anchor.y = this->bb_bottom_left_.y + distance.y / 2;
    anchor.z = this->bb_bottom_left_.z + distance.z / 2;

    return this->model * vec4(anchor, 1.0);
}

float Mesh::ray_intersection(vec3 origin, vec3 direction)
{
    vec3 dirfrac = vec3(0);

    dirfrac.x = 1.0f / direction.x;
    dirfrac.y = 1.0f / direction.y;
    dirfrac.z = 1.0f / direction.z;

    float t1 = (this->bb_bottom_left().x - origin.x) * dirfrac.x;
    float t2 = (this->bb_top_right().x - origin.x) * dirfrac.x;
    float t3 = (this->bb_bottom_left().y - origin.y) * dirfrac.y;
    float t4 = (this->bb_top_right().y - origin.y) * dirfrac.y;
    float t5 = (this->bb_bottom_left().z - origin.z) * dirfrac.z;
    float t6 = (this->bb_top_right().z - origin.z) * dirfrac.z;

    float tmin = max({ max({ min({ t1, t2 }), min({ t3, t4 }) }), min({ t5, t6 }) });
    float tmax = min({ min({ max({ t1, t2 }), max({ t3, t4 }) }), max({ t5, t6 }) });

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0) return -1;

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax) return -1;

    return tmin;
}

void Mesh::transform(vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
    mat4 T = translate(mat4(1), tvec);
    mat4 S = scale(mat4(1), svec);
    mat4 R = rotate(mat4(1), radians(angle), normalize(rvec));

    this->model = model * T * R * S;
}

void gobj::mesh::Mesh::move(Directions dir)
{
    this->move(dir, this->speed_);
}

void gobj::mesh::Mesh::move(Directions dir, float speed)
{
    vec3 tvec = vec3(0);
    switch (dir)
    {
    case util::dir::Directions::front:
        tvec += speed * this->front_;
        break;
    case util::dir::Directions::back:
        tvec -= speed * this->front_;
        break;
    case util::dir::Directions::left:
        tvec -= normalize(cross(this->front_, this->up_)) * speed;
        break;
    case util::dir::Directions::right:
        tvec += normalize(cross(this->front_, this->up_)) * speed;
        break;
    case util::dir::Directions::up:
        tvec += speed * this->up_;
        break;
    case util::dir::Directions::down:
        tvec -= speed * this->up_;
        break;
    default:
        break;
    }
    this->transform(tvec, vec3(1), vec3(1,0,0), 0);
}

void gobj::mesh::Mesh::turn(EulerAngle dir)
{
    this->turn(dir, 1);
}

void gobj::mesh::Mesh::turn(EulerAngle dir, float angle)
{
    vec3 rvec;

    switch (dir)
    {
    case util::dir::EulerAngle::yaw_right:
    case util::dir::EulerAngle::yaw_left:

        if (dir == EulerAngle::yaw_right) 
            angle = -angle;

        rvec = vec3(0, 0, 1); // fix z axis

        front_.x = front_.x * cos(radians(angle)) + front_.z * sin(radians(angle));
        front_.z = -front_.x * sin(radians(angle)) + front_.z * cos(radians(angle));
        up_.x = up_.x * cos(radians(angle)) + up_.z * sin(radians(angle));
        up_.z = -up_.x * sin(radians(angle)) + up_.z * cos(radians(angle));
        front_ = normalize(front_);
        up_ = normalize(up_);

        break;
    case util::dir::EulerAngle::pitch_up: 
    case util::dir::EulerAngle::pitch_down:

        if (dir == EulerAngle::pitch_down)
            angle = -angle;

        rvec = vec3(1, 0, 0);

        front_.y = front_.y * cos(radians(angle)) - front_.z * sin(radians(angle));
        front_.z = front_.y * sin(radians(angle)) + front_.z * cos(radians(angle));
        up_.y = up_.y * cos(radians(angle)) - up_.z * sin(radians(angle));
        up_.z = up_.y * sin(radians(angle)) + up_.z * cos(radians(angle));
        front_ = normalize(front_);
        up_ = normalize(up_);
        break;
    case util::dir::EulerAngle::roll_left:
    case util::dir::EulerAngle::roll_right:

        if (dir == EulerAngle::roll_right)
            angle = -angle;

        rvec = vec3(0, 1, 0); 
        front_.x = front_.x * cos(radians(angle)) - front_.y * sin(radians(angle));
        front_.y = front_.x * sin(radians(angle)) + front_.y * cos(radians(angle));
        up_.x = up_.x * cos(radians(angle)) - up_.y * sin(radians(angle));
        up_.y = up_.x * sin(radians(angle)) + up_.y * cos(radians(angle));
        front_ = normalize(front_);
        up_ = normalize(up_);
        break;
    default:
        break;
    }

    this->transform(vec3(0), vec3(1), rvec, angle);
    std::cout << front_.x << "," << front_.y << "," << front_.z << std::endl;

    
     /*Rx = mat3({ vec3(1, 0, 0),
                vec3(0, cos(ax), -sin(ax)),
                vec3(0, sin(ax), cos(ax)) });

     Ry = mat3({ vec3(0, cos(ay), sin(ay)),
                vec3(0, 1, 0),
                vec3(0, -sin(ay), cos(ay)) });

     Rz = mat3({ vec3(cos(az), -sin(az), 0),
                vec3(sin(az), cos(az), 0),
                vec3(0, 0, 1) });

    std::cout << front_.x << "," << front_.y << "," << front_.z << std::endl;
    mat3 R = mat3(Rx * Ry * Rz);

    mat3 R = rotate(angle, rvec);

    this->front_ = vec3((vec4(this->front_,1) * R));
    this->up_ = vec3((vec4(this->up_,1) * R));*/


 /*   this->front_ = vec3(vec4(this->front_, 1.0) * R);
    this->model = this->model * R;*/

    /*switch (dir)
    {
    case util::dir::Directions::up:
        rvec = vec3(1, 0, 0);
        break;
    case util::dir::Directions::down:
        rvec = vec3(1, 0, 0);
        angle = -angle;
        break;
    case util::dir::Directions::left:
        rot = vec3(0, 0, 1);
        rvec = vec3(0, 1, 0);
        R = rotate(mat4(1), radians(angle), normalize(rot));
        this->front_ = front * R;
        break;
    case util::dir::Directions::right:
        rot = vec3(0, 0, 1);
        rvec = vec3(0, 1, 0);
        angle = -angle;
        R = rotate(mat4(1), radians(angle), normalize(rot));
        this->front_ = front * R;
        break;
    case util::dir::Directions::front:
        rot = vec3(1, 0, 0);
        rvec = vec3(0, 0, 1);
        angle = -angle;
        break;
    case util::dir::Directions::back:
        rot = vec3(1, 0, 0);
        rvec = vec3(0, 0, 1);
        angle = -angle;
        break;
    default:
        break;
    }*/
    //this->transform(vec3(0), vec3(1), rvec, angle);
}

void Mesh::add_texture(string name, char const* path, bool vflip)
{
    for (int i = 0; i < this->textures_.size(); i++)
    {
        if (this->textures_[i].path._Equal(path)) {
            std::cout << "ADD_TEXTURE::PATH_ALREADY_LOADED" << std::endl;
            return;
        }
        if (this->textures_[i].name._Equal(name)) {
            std::cout << "ADD_TEXTURE::NAME_UNAVAIABLE" << std::endl;
            return;
        }
    }

    Texture texture = Texture();
    texture.id = this->load_texture(path, vflip ? 1 : 0);
    texture.path = path;
    texture.type = TexType::undefined;
    texture.name = name;

    this->textures_.push_back(texture);
    
}

void Mesh::set_diffuse_map(string name)
{
    int index = -1;
    for (int i = 0; i < this->textures_.size(); i++)
    {
        if (this->textures_[i].name._Equal(name)) 
        {
            index = i; break;
        }
    }
    if (index < 0) return;
    this->diffuse_map = this->textures_[index].id;
}

void Mesh::set_specular_map(string name)
{
    int index = -1;
    for (int i = 0; i < this->textures_.size(); i++)
    {
        if (this->textures_[i].name._Equal(name))
        {
            index = i; break;
        }
    }
    if (index < 0) return;
    this->specular_map = this->textures_[index].id;
}

void Mesh::set_material(res::mat::Material mat, bool orig)
{
    this->material = mat;
    if (orig && res::mat::is_equal(this->orig_material_, { vec3(-1), vec3(-1), vec3(-1), 0 }))
        this->orig_material_ = mat;
}

void gobj::mesh::Mesh::set_shading(int type)
{
    this->shading_ = type;
}

bool Mesh::is_colliding(vec4 pos)
{
    bool xCollision = util::is_in_range(bb_bottom_left().x, bb_top_right().x, pos.x);
    bool yCollision = util::is_in_range(bb_bottom_left().y, bb_top_right().y, pos.y);
    bool zCollision = util::is_in_range(bb_bottom_left().z, bb_top_right().z, pos.z);

    return xCollision && yCollision && zCollision;
}

void gobj::mesh::Mesh::reset_material()
{
    this->material = this->orig_material_;
}

void Mesh::bind()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
     
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->set_bounding_box();
}

void Mesh::render(Shader* sh)
{
    sh->setMatrix4f("Model", this->model);
    sh->setMatrix3f("NormalMatrix", mat3(transpose(inverse(this->model))));

    sh->setBool("useTexture", res::mat::is_equal(material, orig_material_));
    sh->setInt("shadingType", this->shading_);

    sh->setVec3("base.ambient", this->material.ambient);
    sh->setVec3("base.diffuse", this->material.diffuse);
    sh->setVec3("base.specular", this->material.specular);
    sh->setFloat("base.shininess", this->material.shininess);

    sh->setFloat("material.shininess", this->material.shininess);
    sh->setInt("material.diffuse", 0);
    sh->setInt("material.specular", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse_map);
    util::check_error("ERROR::MESH::DIFFUSE_MAP::LOADING_FAILED");

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specular_map);
    util::check_error("ERROR::MESH::SPECULAR_MAP::LOADING_FAILED");

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}
