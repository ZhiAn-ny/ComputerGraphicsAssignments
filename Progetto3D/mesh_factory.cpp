#include "mesh_factory.h"

using namespace gobj::mesh;

MeshFactory::MeshFactory() { }
MeshFactory::~MeshFactory() { }

PolygonalMesh MeshFactory::create_cube()
{
    PolygonalMesh mesh;

    // front
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, -0.5f), color::white, vec2(0.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, -0.5f), color::white , vec2(1.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, -0.5f), color::white , vec2(0.0f, 1.0f)));

    // back
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, 0.5f), color::white , vec2(1.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 1.0f)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, 0.5f), color::white , vec2(0.0f, 1.0f)));
    
    // left
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f)));
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, -0.5f), color::white , vec2(0.0f, 1.0f)));
    
    // right
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, -0.5f), color::white , vec2(0.0f, 1.0f)));
    
    // bottom
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, 0.5f), color::white , vec2(0.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, 0.5f), color::white , vec2(1.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, -0.5f, -0.5f), color::white , vec2(1.0f, 1.0f)));
    mesh.add_vertex(Vertex(vec3(-0.5f, -0.5f, -0.5f), color::white , vec2(0.0f, 1.0f)));
    
    // top
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, 0.5f), color::white , vec2(0.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, 0.5f), color::white , vec2(1.0f, 0.0f)));
    mesh.add_vertex(Vertex(vec3(0.5f, 0.5f, -0.5f), color::white , vec2(1.0f, 1.0f)));
    mesh.add_vertex(Vertex(vec3(-0.5f, 0.5f, -0.5f), color::white , vec2(0.0f, 1.0f)));

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

    return mesh;
}
