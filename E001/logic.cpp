#include "logic.h"
#include "actors.h"

glog::GameLogic::GameLogic()
{
}

glog::GameLogic::~GameLogic()
{
}

bool glog::GameLogic::can_move(std::string name, gso::Direction dir)
{
	gso::SceneObject* fig = this->scene_->get_object(name);
	if (name._Equal(actors::dragon)) {
		fig = this->scene_->get_object(name + "_" + body::body);

		if (dir == gso::Direction::kUp || dir == gso::Direction::kRight)
			fig = this->scene_->get_object(name + "_" + body::head);
	}

	glm::vec3 pos = fig->get_position();

	switch (dir) {
	case gso::Direction::kUp:
		pos.y = this->world_boundary_.bottom;
		break;
	case gso::Direction::kDown:
		pos.y = this->world_boundary_.top;
		break;
	case gso::Direction::kLeft:
		pos.x = this->world_boundary_.left;
		break;
	case gso::Direction::kRight:
		pos.x = this->world_boundary_.right;
		break;
	}

	if (fig->is_colliding(pos)) return false;

	return true;
}

void glog::GameLogic::kill(std::string name)
{
	this->scene_->remove_object(name);
}

void glog::GameLogic::init_logic(gscene::Scene* scene)
{
	this->scene_ = scene;
}

void glog::GameLogic::set_world_boundaries(RECT boundaries)
{
	this->world_boundary_ = boundaries;
}
