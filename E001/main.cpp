#include "view.h"


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	gview::GameView game = gview::GameView();

	game.init_view();
}
