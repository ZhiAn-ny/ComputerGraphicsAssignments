#include "polygonal_mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



using namespace gobj::mesh;

PolygonalMesh::PolygonalMesh() { }

PolygonalMesh::~PolygonalMesh() { }

void PolygonalMesh::add_vertex(vec3 pos, vec2 tex)
{
	this->vertices_.push_back(pos);
    this->tex_coords_.push_back(tex);
}

void PolygonalMesh::add_index(unsigned int index)
{
    this->indices_.push_back(index);
}

void PolygonalMesh::set_indices(vector<unsigned int> indices)
{
    this->indices_ = indices;
}

void gobj::mesh::PolygonalMesh::load_texture(char const* path, int vertical_flip)
{
    GLenum format;
    int width, height, nrChannels;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    stbi_set_flip_vertically_on_load(vertical_flip);

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;


        // GL_REPEAT | GL_MIRRORED_REPEAT | GL_CLAMP_TO_EDGE | GL_CLAMP_TO_BORDER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void PolygonalMesh::bind()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_G);
    glGenBuffers(1, &VBO_C);
    glGenBuffers(1, &VBO_T);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
     
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
    glEnableVertexAttribArray(2);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
    //glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vec3), vertices_.data(), GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(0);
    //
    //glBindBuffer(GL_ARRAY_BUFFER, VBO_C);
    //glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(vec3), colors_.data(), GL_STATIC_DRAW);
    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(1);
    //
    //glBindBuffer(GL_ARRAY_BUFFER, VBO_T);
    //glBufferData(GL_ARRAY_BUFFER, tex_coords_.size() * sizeof(vec2), tex_coords_.data(), GL_STATIC_DRAW);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

    // unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PolygonalMesh::render()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    util::check_error("ERROR::MESH_TEXTURE::LOADING_FAILED");
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, this->indices_.size(), GL_UNSIGNED_INT, 0);
}
