#include "Lib.h"
#include "Scene.h"
#include "ShapeFactory.h"

class Mouse
{
private:
	bool isHolding;
	Scene* scene;

public:
	Mouse();
	~Mouse();

	void assignRefScene(Scene* refScene);

	void onMouseClick(int btn, int state, int x, int y);

	void onMouseRelease(int btn, int state, int x, int y);

};
