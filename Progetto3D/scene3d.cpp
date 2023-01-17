#include "scene3d.h"

gobj::Scene::Scene()
{
}

gobj::Scene::~Scene()
{
}

void gobj::Scene::add_object(mesh::PolygonalMesh mesh)
{
	mesh.bind();
	this->objs_.push_back(mesh);
}

void gobj::Scene::render(Shader* shader)
{
	shader->use();
	for (int i = 0; i < this->objs_.size(); i++)
	{
		this->objs_[i].render(shader);
	}
}
