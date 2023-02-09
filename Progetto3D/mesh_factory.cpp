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

Mesh gobj::mesh::MeshFactory::create_torus()
{
    Mesh mesh;
    mesh.set_name("toro_" + std::to_string(this->toro_number));
    int Stacks = 30;  //numero di suddivisioni sull'asse x
    int Slices = 30;  // numero di suddivisioni sull'asse y
    float R = 1, r = 0.1;
    float s, t;
    vector<unsigned int> indices = {};

    for (int i = 0; i <= Stacks; ++i) 
    {
        float V = i / (float)Stacks;
        float phi = V * glm::pi <float>() * 2;

        // Loop Through Slices
        for (int j = 0; j <= Slices; ++j)
        {
            float U = j / (float)Slices;
            float theta = U * (glm::pi <float>() * 2);

            float x = (R + r * cosf(phi)) * cosf(theta);
            float y = r * sinf(phi);
            float z = (R + r * cosf(phi)) * sinf(theta);
        
            mesh.add_vertex(Vertex(
                vec3(x, y, z),
                color::white,
                vec2(U, V),
                vec3(normalize(vec3(sin(phi) * cos(theta), cos(phi), sin(theta) * sin(phi))))
            ));
        }
    }
    for (int i = 0; i < Slices * Stacks + Slices; ++i)
    {
        indices.push_back(i);
        indices.push_back(i + Slices + 1);
        indices.push_back(i + Slices);

        indices.push_back(i + Slices + 1);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    mesh.set_indices(indices);

    this->toro_number++;
    return mesh;
}

Model gobj::mesh::MeshFactory::create_dolphin()
{
    Model dolphin = Model("res/meshes/dolphin/dolphin.obj");
    dolphin.set_name("dolphin_" + std::to_string(this->dolphin_number));

    this->dolphin_number++;
    return dolphin;
}

Model gobj::mesh::MeshFactory::create_manta()
{
    Model manta = Model("res/meshes/manta_ray/manta_ray.obj");
    manta.set_name("manta_" + std::to_string(this->manta_number));

    this->manta_number++;
    return manta;
}


Model gobj::mesh::MeshFactory::create_whale()
{
    Model whale = Model("res/meshes/whale/whale.obj");
    whale.set_name("whale_" + std::to_string(this->whale_number));

    this->whale_number++;
    return whale;
}

Model gobj::mesh::MeshFactory::create_fish()
{
    Model fish = Model("res/meshes/fish/12990_Black_Moor_Goldfish_v1_l2.obj");
    fish.set_name("fish_" + std::to_string(this->fish_number));

    this->fish_number++;
    return fish;
}

Model gobj::mesh::MeshFactory::create_jellyfish()
{
    Model jelly = Model("res/meshes/jellyfish/jellyfish.obj");
    jelly.set_name("jellyfish_" + std::to_string(this->jelly_number));

    this->jelly_number++;
    return jelly;
}
