#include "logic.h"
#include "actors.h"

glog::GameLogic::GameLogic()
{
}

glog::GameLogic::~GameLogic()
{
}

void glog::GameLogic::add_score(double points)
{
	this->score_ += points;
	std::cout << "+" << points << " points!" << std::endl;
}

int glog::GameLogic::get_min_butterflies()
{
	return this->n_butterflies_;
}

double glog::GameLogic::get_score()
{
	return this->score_;
}

double glog::GameLogic::get_dragon_speed()
{
	return this->dragon_speed_;
}

void glog::GameLogic::increase_dragon_speed()
{
	this->dragon_speed_ += 0.1;
}

void glog::GameLogic::decrease_dragon_speed()
{
	this->dragon_speed_ -= 0.1;
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
	gso::SceneObject* target = this->scene_->get_object(name);

	this->add_score(target->get_model().operator[](1).y);

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
