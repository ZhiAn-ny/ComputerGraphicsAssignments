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

void gso::SceneObject::set_color(glm::vec4 center, glm::vec4 others)
{
	this->colors_[0] = center;
	for (int i = 1; i < this->colors_.size() - 1; i++) {
		this->colors_[i] = others;
	}
}

void gso::SceneObject::transform(vec3 tVector, vec3 sVector, GLfloat angle)
{

	vec3 rotationVector = vec3(0.0, 0.0, 1.0); // Always rotate along z axis
	sVector.z = 1.0; // Leave z dimension untouched
	tVector.z = 0.0; // Can't move along z axis

	// Update position
	this->pos_.x += tVector.x;
	this->pos_.y += tVector.y;

	mat4 T = translate(mat4(1.0), tVector);
	mat4 S = scale(mat4(1.0), sVector);
	mat4 R = rotate(mat4(1.0), angle, rotationVector);

	this->Model = this->Model * T * R * S;
}
