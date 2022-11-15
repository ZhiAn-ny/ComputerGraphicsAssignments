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

int gso::SceneObject::get_triangles()
{
	return this->nTriangles;
}

void gso::SceneObject::update_object_corners()
{
	glm::vec3 last = this->vertices_[this->vertices_.size() - 1];

	if (last.x <= this->obj_bottom_left_.x && last.y <= this->obj_bottom_left_.y) {
		this->obj_bottom_left_ = glm::vec4(last.x, last.y, 0.0, 1.0);
	}
	if (last.x >= this->obj_top_right_.x && last.y >= this->obj_top_right_.y) {
		this->obj_top_right_ = glm::vec4(last.x, last.y, 0.0, 1.0);
	}
}

void gso::SceneObject::update_position()
{
	this->pos_ = glm::vec4(0.0);
	this->bottomLeft = this->obj_bottom_left_;
	this->topRight = this->obj_top_right_;

	this->bottomLeft = this->Model * this->bottomLeft;
	this->topRight = this->Model * this->topRight;
	this->pos_ = this->Model * this->pos_;

}

void gso::SceneObject::add_vertex(glm::vec3 pos, glm::vec4 color)
{
	this->vertices_.push_back(vec3(pos.x, pos.y, 0.0));
	this->colors_.push_back(color);
	this->nVertices++;
	this->update_object_corners();
}

void gso::SceneObject::set_color(glm::vec4 center, glm::vec4 others)
{
	this->colors_[0] = center;
	for (int i = 1; i < this->colors_.size() - 1; i++) {
		this->colors_[i] = others;
	}
}

float gso::SceneObject::get_height()
{
	return abs(this->bottomLeft.y - this->topRight.y);
}

float gso::SceneObject::get_width()
{
	return abs(this->bottomLeft.x - this->topRight.x);
}

float gso::SceneObject::get_original_ratio()
{
	float w = abs(this->obj_bottom_left_.x - this->obj_top_right_.x);
	float h = abs(this->obj_bottom_left_.y - this->obj_top_right_.y);
	return w / h;
}

bool gso::SceneObject::is_colliding(glm::vec3 pos)
{
	if (pos.x >= this->bottomLeft.x && pos.x <= this->topRight.x &&
		pos.y >= this->bottomLeft.y && pos.y <= this->topRight.y) 
			return true;

	return false;
}

bool gso::SceneObject::is_colliding(gso::SceneObject other)
{
	bool xcol = (this->bottomLeft.x <= other.topRight.x 
				&& this->topRight.x >= other.bottomLeft.x);

	bool ycol = (this->bottomLeft.y <= other.topRight.y
				&& this->topRight.y >= other.bottomLeft.y);

	return xcol && ycol;
}

void gso::SceneObject::createVertexArray()
{
	glGenVertexArrays(1, &this->VertexArrayObject);
	glBindVertexArray(this->VertexArrayObject);
}

void gso::SceneObject::bindVerticesGeometry()
{
	glGenBuffers(1, &this->VertexBufferObject_Geometry);
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject_Geometry);
	glBufferData(GL_ARRAY_BUFFER, this->vertices_.size() * sizeof(vec3), this->vertices_.data(), GL_STATIC_DRAW); // .data() usato per ottenere l'indirizzo di partenza del vettore (come &)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

void gso::SceneObject::bindVerticesColor()
{
	glGenBuffers(1, &this->VertexBufferObject_Colors);
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject_Colors);
	glBufferData(GL_ARRAY_BUFFER, this->colors_.size() * sizeof(vec4), this->colors_.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void gso::SceneObject::bind()
{
	this->createVertexArray();
	this->bindVerticesGeometry();
	this->bindVerticesColor();
}

void gso::SceneObject::change_direction(gso::Direction new_dir)
{
	this->dir_ = new_dir;
}

void gso::SceneObject::move(float distance)
{
	int dir_value = (int) this->dir_;
	glm::vec3 tVector = glm::vec3((dir_value / 2), (dir_value % 2), 0.0);
	glm::vec3 sVector = glm::vec3(1.0);

	tVector *= distance;

	this->transform(tVector, sVector, 0);
}

void gso::SceneObject::transform(vec3 tVector, vec3 sVector, GLfloat angle)
{

	vec3 rotationVector = vec3(0.0, 0.0, 1.0); // Always rotate along z axis
	sVector.z = 1.0; // Leave z dimension untouched
	tVector.z = 0.0; // Can't move along z axis

	mat4 T = translate(mat4(1.0), tVector);
	mat4 S = scale(mat4(1.0), sVector);
	mat4 R = rotate(mat4(1.0), angle, rotationVector);

	this->Model = this->Model * T * R * S;

	this->update_position();
}

void gso::SceneObject::render(unsigned int* MatMod)
{
	// Create object's uniform matrix
	glUniformMatrix4fv(*MatMod, 1, GL_FALSE, value_ptr(this->Model));
	glBindVertexArray(this->VertexArrayObject);
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->nVertices);
}
