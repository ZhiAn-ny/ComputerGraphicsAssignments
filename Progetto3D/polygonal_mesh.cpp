#include "polygonal_mesh.h"

using namespace gobj::mesh;

PolygonalMesh::PolygonalMesh() { }

PolygonalMesh::~PolygonalMesh() { }

void PolygonalMesh::add_vertex(vec3 pos)
{
	this->vertices_.push_back(pos);
}

void PolygonalMesh::add_index(unsigned int index)
{
    this->indices_.push_back(index);
    this->colors_.push_back(color::white);
}

void PolygonalMesh::set_indices(vector<unsigned int> indices)
{
    for (int i = 0; i < indices.size(); i++)
    {
        this->add_index(indices[i]);
    }
}

void PolygonalMesh::bind()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_G);
    glGenBuffers(1, &VBO_C);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vec3), vertices_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_C);
    glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(vec3), colors_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

    // unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PolygonalMesh::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, this->indices_.size(), GL_UNSIGNED_INT, 0);
}
