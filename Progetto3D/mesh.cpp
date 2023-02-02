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

gobj::mesh::Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<tex::Texture> textures)
{
    this->verts = vertices;
    this->indices = indices;
    this->textures_ = textures;
}

Mesh::~Mesh() { }

void Mesh::add_vertex(Vertex v)
{
    this->verts.push_back(v);
}

void Mesh::add_index(unsigned int index)
{
    this->indices.push_back(index);
}

void gobj::mesh::Mesh::set_color(vec4 color)
{
    for (unsigned int i = 0; i < this->verts.size(); i++)
    {
        this->verts[i].color = color;
    }
}

void gobj::mesh::Mesh::select()
{
    this->selected_ = true;
}

void gobj::mesh::Mesh::deselect()
{
    this->selected_ = false;
}

void Mesh::set_indices(vector<unsigned int> indices)
{
    this->indices = indices;
}

void gobj::mesh::Mesh::add_texture(tex::Texture texture)
{
    for (int i = 0; i < this->textures_.size(); i++)
    {
        if (this->textures_[i].path._Equal(texture.path)) return;
    }
    this->textures_.push_back(texture);
}

unsigned int gobj::mesh::Mesh::load_texture(char const* path, int vertical_flip)
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

void gobj::mesh::Mesh::set_bounding_box()
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

vec3 gobj::mesh::Mesh::bb_top_right()
{
    return this->model * vec4(this->bb_top_right_, 1.0);
}

vec3 gobj::mesh::Mesh::bb_bottom_left()
{
    return this->model * vec4(this->bb_bottom_left_, 1.0);
}

vec3 gobj::mesh::Mesh::get_anchor()
{
    vec3 distance = abs(this->bb_bottom_left_ - this->bb_top_right_);

    vec3 anchor = vec3(0);
    anchor.x = this->bb_bottom_left_.x + distance.x / 2;
    anchor.y = this->bb_bottom_left_.y + distance.y / 2;
    anchor.z = this->bb_bottom_left_.z + distance.z / 2;

    return this->model * vec4(anchor, 1.0);
}

float gobj::mesh::Mesh::ray_intersection(vec3 origin, vec3 direction)
{
    std::cout << "SELECTION::SCENE::MESHES::" << this->get_name() << std::endl;
    vec3 dist_sph = origin - this->get_anchor();

    float b = dot(dist_sph, direction);

    vec3 dims = abs(this->get_anchor() - this->bb_top_right());
    float shpere_ray = sqrt(pow(sqrt(pow(dims.x, 2) + pow(dims.y, 2)), 2) + pow(dims.z, 2));
    std::cout << "SELECTION::SCENE::MESHES::" << this->get_name() << "::SPHERE_RAY: " << shpere_ray << std::endl;
    
    float cc = dot(dist_sph, dist_sph) - shpere_ray * shpere_ray;
	float delta = b * b - cc;
    std::cout << "SELECTION::SCENE::MESHES::" << this->get_name() << "::DELTA: " << delta << std::endl;
 
    if (delta < 0) return -1;
    if (delta > 0)
    {
        // calcola le due intersezioni
        float t_a = -b + sqrt(delta);
        float t_b = -b - sqrt(delta);

        if (t_a < 0 && t_b < 0) return -1;
        std::cout << "SELECTION::SCENE::MESHES::" << this->get_name() << "::INTERSECTION_FOUND " << std::endl;
        return t_b;
    }

    float t = -b + sqrt(delta);
    if (t < 0) return -1;
    std::cout << "SELECTION::SCENE::MESHES::" << this->get_name() << "::INTERSECTION_FOUND " << std::endl;
    return t;
}

void gobj::mesh::Mesh::transform(vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
    mat4 T = translate(mat4(1), tvec);
    mat4 S = scale(mat4(1), svec);
    mat4 R = rotate(mat4(1), radians(angle), normalize(rvec));

    this->model = model * T * R * S;
}

void gobj::mesh::Mesh::add_texture(string name, char const* path, bool vflip)
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

    tex::Texture texture = tex::Texture();
    texture.id = this->load_texture(path, vflip ? 1 : 0);
    texture.path = path;
    texture.type = tex::TexType::undefined;
    texture.name = name;

    this->textures_.push_back(texture);
    
}

void gobj::mesh::Mesh::set_diffuse_map(string name)
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

void gobj::mesh::Mesh::set_specular_map(string name)
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

void gobj::mesh::Mesh::set_material(res::mat::Material mat)
{
    this->material = mat;
}

//bool gobj::mesh::Mesh::is_colliding(vec4 pos)
//{
//    bool xCollision = util::is_in_range(bb_bottom_left().x, bb_top_right().x, pos.x);
//    bool yCollision = util::is_in_range(bb_bottom_left().y, bb_top_right().y, pos.y);
//    bool zCollision = util::is_in_range(bb_bottom_left().z, bb_top_right().z, pos.z);
//
//    return xCollision && yCollision && zCollision;
//}

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
