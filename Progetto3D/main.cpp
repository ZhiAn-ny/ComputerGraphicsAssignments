#include "view3d.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	gview::GameView3D view;

	view.init();
	view.start();
}