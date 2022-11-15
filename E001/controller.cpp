#include "controller.h"


gctrl::GameController::GameController()
{
}

gctrl::GameController::~GameController()
{
}

void gctrl::GameController::init_game(gscene::Scene* scene)
{
	this->scene_ = scene;
}

void gctrl::GameController::action(GameAction action)
{
	switch (action) {
	case GameAction::kFire:

		break;
	case GameAction::kMoveUp:

		break;
	case GameAction::kMoveDown:

		break;
	}
}

void gctrl::GameController::game_loop()
{


}
