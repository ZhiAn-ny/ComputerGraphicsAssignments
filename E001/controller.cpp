#include "controller.h"

gctrl::GameController::GameController()
{
}

gctrl::GameController::~GameController()
{
}

bool gctrl::GameController::is_outside_window(gso::SceneObject* fig)
{
	glm::vec4 pos = fig->get_position();
	if (pos.x < 0 || pos.x > this->window.right 
		|| pos.y < 0 || pos.y > this->window.bottom)
		return true;

	return false;
}

void gctrl::GameController::move_dragon(gso::Direction dir)
{
	std::vector<std::string> parts = { "head", "body", "tail", "wing" };
	for (int i = 0; i < parts.size(); i++) {
		gso::SceneObject* part = this->scene_->get_object(parts[i]);
		part->change_direction(dir);
		part->move(0.5);
	}
}

void gctrl::GameController::fire()
{
	gso::SceneObject shape = this->shape_factory.get_circle(0.0, 0.0, 1, 1);
	gso::SceneObject head = *this->scene_->get_object("head");
	glm::vec4 pos = head.get_position();

	shape.transform(glm::vec3(pos.x, pos.y, 0.0),
		glm::vec3(15), 0);
 	shape.set_color(color::dark_yellow, color::dark_orange);
	shape.change_direction(gso::Direction::kRight);

	this->scene_->add_object_at(&shape, 0);
}

void gctrl::GameController::init_game(gscene::Scene* scene)
{
	this->scene_ = scene;
}

void gctrl::GameController::action(GameAction action)
{
	switch (action) {
	case GameAction::kFire:
		this->fire();
		break;
	case GameAction::kMoveUp:
		this->move_dragon(gso::Direction::kUp);
		break;
	case GameAction::kMoveDown:
		this->move_dragon(gso::Direction::kDown);
		break;
	}
}

void gctrl::GameController::set_window(RECT window)
{
	this->window = window;
}

void gctrl::GameController::game_loop()
{
	std::vector<gso::SceneObject*> fireballs = this->scene_->get_starts_with("circle");
	std::vector<gso::SceneObject*>::iterator it;

	for (int i = 0; i < fireballs.size(); i++) {
		fireballs[i]->move(2);
	}

	for (int i = 0; i < fireballs.size(); i++) {

		if (this->is_outside_window(fireballs[i])) {
 			this->scene_->remove_object(fireballs[i]->get_name());
		}
	}
	

}
