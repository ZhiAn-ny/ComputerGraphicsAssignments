#include "controller.h"


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	gctrl::GameController controller = gctrl::GameController();

	controller.init_game();

}
