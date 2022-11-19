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
	if (pos.x < 0 || pos.x > this->window_.right 
		|| pos.y < 0 || pos.y > this->window_.bottom)
		return true;

	return false;
}

void gctrl::GameController::check_collisions()
{
	std::vector<gso::SceneObject*> fireballs = this->scene_->get_starts_with("circle");
	std::vector<gso::SceneObject*> targets = this->scene_->get_starts_with("butterfly");

	for (int i = 0; i < targets.size(); i++) {
		for (int j = 0; j < fireballs.size(); j++) {
			if (fireballs[j]->is_colliding(*targets[i])) {
				this->logic_.kill(targets[i]->get_name());
				this->scene_->remove_object(fireballs[j]->get_name());

				j = fireballs.size();
				std::cout << "New score: " << this->logic_.get_score() << std::endl;
				std::cout << "--------" << std::endl;
			}
		}
	}
}

void gctrl::GameController::move_dragon(gso::Direction dir)
{
	std::vector<gso::SceneObject*> dragon = this->scene_->get_starts_with(actors::dragon);

	for (int i = 0; i < dragon.size(); i++) {
		dragon[i]->change_direction(dir);
		dragon[i]->move(0.5);
	}
}

void gctrl::GameController::flap_wing()
{
	int orig_scale = 7;
	static float s = orig_scale;
	gso::SceneObject* wing = this->scene_->get_object(actors::dragon + "_" + body::wing);

	static float orig_h = -1.0;
	static glm::vec3 pos;

	if (orig_h < 0) {
		orig_h = wing->get_height();
		pos = wing->get_position();
	}
	pos.y = this->scene_->get_object(actors::dragon + "_" + body::body)
						->get_position().y + 115;

	float offset;

	glm::mat4 T = glm::mat4(0);
	glm::mat4 M = glm::mat4(1);
	glm::mat4 S = glm::mat4(1);

	switch (wing->get_basculation_direction())
	{
	case gso::Direction::kNone:
		wing->set_basculation_direction(gso::Direction::kDown);
		break;

	case gso::Direction::kDown:
		s = s - 0.7;
		offset = (orig_h - orig_h / orig_scale * s) / 2;

		T = translate(mat4(1), vec3(pos.x, pos.y-offset, 0));
		S = scale(mat4(1), vec3(orig_scale, s, orig_scale));
		if (s < -orig_scale) 
			wing->set_basculation_direction(gso::Direction::kUp);
		break;
		
	case gso::Direction::kUp:
		s = s + 0.7;
		offset = (orig_h / orig_scale * s - orig_h) / 2;

		T = translate(mat4(1), vec3(pos.x, pos.y+offset, 0));
		S = scale(mat4(1), vec3(orig_scale, s, orig_scale));
		if (s > orig_scale)
			wing->set_basculation_direction(gso::Direction::kDown);
		break;
	}

	wing->set_model(M * T * S);
	wing->update_position();
}

void gctrl::GameController::update_fireballs()
{
	std::vector<gso::SceneObject*> fireballs = this->scene_->get_starts_with("circle");

	for (int i = 0; i < fireballs.size(); i++) {
		fireballs[i]->move(2);
	}
}

void gctrl::GameController::update_butterflies()
{
	std::vector<gso::SceneObject*> butterflies = this->scene_->get_starts_with("butterfly");
	glm::vec3 pos = glm::vec3(0.0);
	float scale_factor;

	for (int i = 0; i < butterflies.size(); i++) {

		if (butterflies[i]->get_ratio() > butterflies[i]->get_original_ratio() * 1.1) {
			butterflies[i]->set_basculation_direction(gso::Direction::kLeft);
		}
		else if (butterflies[i]->get_ratio() < butterflies[i]->get_original_ratio() / 2) {
			butterflies[i]->set_basculation_direction(gso::Direction::kRight);
		}

		pos.y = (((int)butterflies[i]->get_position().x % 200) - 100) / 1000.0;

		pos.y = sin(pos.y);
		scale_factor = (butterflies[i]->get_basculation_direction() 
						== gso::Direction::kLeft) ? 0.8 : 1.2;

		butterflies[i]->transform(pos, glm::vec3(scale_factor, 1, 1), 0);
		butterflies[i]->move(0.3);
	}
}

void gctrl::GameController::remove_out_of_sight()
{
	std::vector<gso::SceneObject*> objs = this->scene_->get_starts_with("circle");
	for (int i = 0; i < objs.size(); i++) {

		if (this->is_outside_window(objs[i])) {
			this->scene_->remove_object(objs[i]->get_name());
		}
	}

	objs = this->scene_->get_starts_with("butterfly");
	for (int i = 0; i < objs.size(); i++) {

		if (this->is_outside_window(objs[i])) {
			this->scene_->remove_object(objs[i]->get_name());
		}
	}
}

void gctrl::GameController::replenish_butterflies()
{
	int butterflies = this->scene_->get_starts_with("butterfly").size();

	while (butterflies < logic_.get_min_butterflies()) {
		this->add_enemy(glm::vec2(window_.right, rand() % (window_.bottom - 50) + 25));
		butterflies++;
	}
}

void gctrl::GameController::add_enemy(glm::vec2 pos)
{
	gso::SceneObject shape = this->shape_factory.get_butterfly(0, 0, 1, 1);

	shape.transform(glm::vec3(pos.x, this->window_.bottom - pos.y, 0.0),
		glm::vec3((rand() % 30) + 20), 0);
	shape.set_color(color::crimson, color::transparent);
	shape.set_basculation_direction(gso::Direction::kLeft);
	shape.change_direction(gso::Direction::kLeft);

	this->scene_->add_object(&shape);
}

void gctrl::GameController::fire()
{
	gso::SceneObject shape = this->shape_factory.get_circle(0.0, 0.0, 1, 1);
	gso::SceneObject head = *this->scene_->get_object(actors::dragon + "_" + body::head);
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
	this->logic_.init_logic(scene);
}

void gctrl::GameController::action(GameAction action, glm::vec2 pos)
{
	switch (action) {
	case GameAction::kFire:
		this->fire();
		break;
	case GameAction::kMoveDragonUp:
		if (this->logic_.can_move(actors::dragon, gso::Direction::kUp))
			this->move_dragon(gso::Direction::kUp);
		break;
	case GameAction::kMoveDragonDown:
		if (this->logic_.can_move(actors::dragon, gso::Direction::kDown))
			this->move_dragon(gso::Direction::kDown);
		break;
	case GameAction::kAddEnemy:
		this->add_enemy(pos);
		break;
	}
}

void gctrl::GameController::set_window(RECT window)
{
	this->window_ = window;
	this->logic_.set_world_boundaries(window);
}

void gctrl::GameController::game_loop()
{
	this->flap_wing();

	this->update_fireballs();
	
	this->update_butterflies();
	this->replenish_butterflies();
	
	this->check_collisions();


	this->remove_out_of_sight();
}
