#include "Mouse.h"

Mouse::Mouse()
{
	this->isHolding = false;
}

Mouse::~Mouse()
{
}

void Mouse::assignRefScene(gscene::Scene* refScene)
{
	this->scene = refScene;
}

void Mouse::onMouseClick(int btn, int state, int x, int y)
{
	if (state != GLUT_DOWN) return;

	ShapeFactory shf;
	SceneObject shape;

	switch (btn)
	{
	case GLUT_LEFT_BUTTON:
		shape = shf.getCircle(x, y, 5, 5);
		(*this->scene).add_object(&shape);
		break;

	case GLUT_RIGHT_BUTTON:
		// shape = shf.getHeart(x, y, 50, 50);
		// (*this->scene).addObject(&shape);

		break;
	}

	this->isHolding = true;
}

void Mouse::onMouseRelease(int btn, int state, int x, int y)
{
	if (state != GLUT_UP) return;
	this->isHolding = false;
}
