#include "scene3d.h"

using namespace gobj::mesh;

gobj::Scene::Scene()
{
}

gobj::Scene::~Scene()
{
}

AMesh* gobj::Scene::get_object(string name)
{
	for (unsigned int i = 0; i < this->objs_.size(); i++)
	{
		if (this->objs_[i].get_name()._Equal(name))
			return &this->objs_[i];
	}
}

void gobj::Scene::transform_object(string name, vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
	AMesh* mesh = this->get_object(name);
	mesh->transform(tvec, svec, rvec, angle);
}

void gobj::Scene::add_object(mesh::Mesh mesh)
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
