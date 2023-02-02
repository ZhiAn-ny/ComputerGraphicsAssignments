#include "scene3d.h"

using namespace gobj::mesh;

gobj::Scene::Scene()
{
}

gobj::Scene::~Scene()
{
}

IMesh* gobj::Scene::get_object(string name)
{
	for (unsigned int i = 0; i < this->meshes_.size(); i++)
	{
		if (this->meshes_[i].get_name()._Equal(name))
			return &this->meshes_[i];
	}
	for (unsigned int i = 0; i < this->models_.size(); i++)
	{
		if (this->models_[i].get_name()._Equal(name))
			return &this->models_[i];
	}
}

void gobj::Scene::transform_object(string name, vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
	IMesh* mesh = this->get_object(name);
	mesh->transform(tvec, svec, rvec, angle);
}

void gobj::Scene::select_nearest(vec3 origin, vec3 direction)
{
	double distance = INFINITE;
	mesh::IMesh* selected;
	/*for (int i = 0; i < this->meshes_.size(); i++)
	{
		double d = this->meshes_.ray_intersection(origin, direction);
		if (d > -1 && d < distance)
		{
			distance = d;
			selected = &this->meshes_[i];
		}
	}
	for (int i = 0; i < this->models_.size(); i++)
	{
		double d = this->models_.ray_intersection(origin, direction);
		if (d > -1 && d < distance) 
		{
			distance = d;
			selected = &this->models_[i];
		}
	}*/
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
