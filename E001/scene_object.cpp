#include "scene_object.h"

gso::SceneObject::SceneObject() { }

gso::SceneObject::~SceneObject() { }

gso::SceneObject::SceneObject(std::string name)
{
	this->name_ = name;
}
