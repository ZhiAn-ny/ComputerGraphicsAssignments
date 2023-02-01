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
	for (unsigned int i = 0; i < this->meshes_.size(); i++)
	{
		if (this->meshes_[i].get_name()._Equal(name))
			return &this->meshes_[i];
	}
}

void gobj::Scene::transform_mesh(string name, vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
	AMesh* mesh = this->get_object(name);
	mesh->transform(tvec, svec, rvec, angle);
}

void gobj::Scene::transform_model(string name, vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
}

void gobj::Scene::add_object(mesh::Mesh mesh)
{
	mesh.bind();
	this->meshes_.push_back(mesh);
}

void gobj::Scene::add_object(mesh::Model model)
{
	model.bind();
	this->models_.push_back(model);
}

void gobj::Scene::render(Shader* shader)
{
	shader->use();
	for (int i = 0; i < this->meshes_.size(); i++)
	{
		this->meshes_[i].render(shader);
	}
	for (int i = 0; i < this->models_.size(); i++)
	{
		this->models_[i].render(shader);
	}
}
