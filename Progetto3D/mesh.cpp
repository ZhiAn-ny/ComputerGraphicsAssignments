#include "mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace gobj::mesh;

Mesh::Mesh() 
{ 
    this->add_texture("none", "res/textures/blank.jpg", false);
    this->set_diffuse_map("none");
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

void Mesh::set_indices(vector<unsigned int> indices)
{
    this->indices = indices;
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

void gobj::mesh::Mesh::transform(vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
    mat4 T = translate(mat4(1), tvec);
    mat4 S = scale(mat4(1), svec);
    mat4 R = rotate(mat4(1), radians(angle), normalize(rvec));

    this->model = model * T * R * S;
}

void gobj::mesh::Mesh::add_texture(string name, char const* path, bool vflip)
{
    auto search = this->textures_.find(name);
    if (search == this->textures_.end()) {
        unsigned int tex_ID = this->load_texture(path, vflip ? 1 : 0);
        this->textures_.insert_or_assign(name, tex_ID);
    }
}

void gobj::mesh::Mesh::set_diffuse_map(string name)
{
    auto search = this->textures_.find(name);
    if (search != this->textures_.end()) {
        this->diffuse_map = search->second;
    }
}

void gobj::mesh::Mesh::set_specular_map(string name)
{
    auto search = this->textures_.find(name);
    if (search != this->textures_.end()) {
        this->specular_map = search->second;
    }
}

void gobj::mesh::Mesh::set_material(res::mat::Material mat)
{
    this->material = mat;
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
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
