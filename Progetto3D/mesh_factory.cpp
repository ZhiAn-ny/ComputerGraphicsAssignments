#include "mesh_factory.h"

using namespace gobj::mesh;

MeshFactory::MeshFactory() { }
MeshFactory::~MeshFactory() { }

Mesh MeshFactory::create_cube()
{
    Mesh mesh;
    mesh.set_name("cube_" + std::to_string(this->cube_number));

    // front
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, -0.5f), color::white, vec2(0.0f, 0.0f), vec3(0,0,-1)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, -0.5f), color::white , vec2(1.0f, 0.0f), vec3(0,0,-1)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f), vec3(0,0,-1)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, -0.5f), color::white , vec2(0.0f, 1.0f), vec3(0,0,-1)));

    // back
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f), vec3(0,0,1)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, 0.5f), color::white , vec2(1.0f, 0.0f), vec3(0,0,1)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 1.0f), vec3(0,0,1)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, 0.5f), color::white , vec2(0.0f, 1.0f), vec3(0,0,1)));
    
    // left
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f), vec3(-1,0,0)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 0.0f), vec3(-1,0,0)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f), vec3(-1,0,0)));
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, -0.5f), color::white , vec2(0.0f, 1.0f), vec3(-1,0,0)));
    
    // right
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f), vec3(1,0,0)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 0.0f), vec3(1,0,0)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f), vec3(1,0,0)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, -0.5f), color::white , vec2(0.0f, 1.0f), vec3(1,0,0)));
    
    // bottom
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f), vec3(0,-1,0)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, 0.5f), color::white , vec2(1.0f, 0.0f), vec3(0,-1,0)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, -0.5f), color::white , vec2(1.0f, 1.0f), vec3(0,-1,0)));
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, -0.5f), color::white , vec2(0.0f, 1.0f), vec3(0,-1,0)));
    
    // top
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, 0.5f), color::white , vec2(0.0f, 0.0f), vec3(0,1,0)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 0.0f), vec3(0,1,0)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f), vec3(0,1,0)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, -0.5f), color::white , vec2(0.0f, 1.0f), vec3(0,1,0)));

    mesh.set_indices({
        0,1,3,
        3,1,2,

        4,5,7,
        7,5,6,

        8,9,11,
        11,9,10,

        12,13,15,
        15,13,14,

        16,17,19,
        19,17,18,

        20,21,23,
        23,21,22
    });

    this->cube_number = this->cube_number + 1;
    return mesh;
}
