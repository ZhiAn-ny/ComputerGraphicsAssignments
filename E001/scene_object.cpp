#include "scene_object.h"

gso::SceneObject::SceneObject() { }

gso::SceneObject::~SceneObject() { }

gso::SceneObject::SceneObject(std::string name)
{
	this->name_ = name;
}

std::string gso::SceneObject::get_name()
{
	return this->name_;
}

void gso::SceneObject::update_corners()
{
	glm::vec3 last = this->vertices_[this->vertices_.size() - 1];

	if (last.x <= this->bottomLeft.x && last.y <= this->bottomLeft.y) {
		this->bottomLeft = last;
	}
	if (last.x >= this->topRight.x && last.y >= this->topRight.y) {
		this->topRight = last;
	}
}

void gso::SceneObject::add_vertex(glm::vec3 pos, glm::vec4 color)
{
	this->vertices_.push_back(vec3(pos.x, pos.y, 0.0));
	this->colors_.push_back(color);
	this->nVertices++;
	this->update_corners();
}
