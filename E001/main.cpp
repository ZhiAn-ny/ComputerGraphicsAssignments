#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ShaderMaker.h"
#include "lib.h"
#include "ShapeFactory.h"
#include "Scene.h"
#include "Mouse.h"


static unsigned int MatMod, MatProj;
mat4 Projection;

RECT window;
Scene scene;
Mouse mouse;

void createWindow(const char* name)
{
	int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	int SCREEN_HEIGHT= glutGet(GLUT_SCREEN_HEIGHT);
	
	window = {};
	window.right = SCREEN_WIDTH / 3;
	window.bottom = SCREEN_HEIGHT / 2;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window.right, window.bottom);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(name);
}

void INIT_VAO()
{
	ShapeFactory shf;
	SceneObject shape;
	std::string name;
	
	// Add scene objects to render on start
	 shape = shf.getButterfly(0.0, 0.0, 1, 1);
	 // Set initial direction
	 shape.dir = Direction::UP;
	 scene.addObject(&shape);
	 name = shape.name;
	 // Set initial position and scale
	 scene.transformObject(name, vec3(100.0, window.bottom - 200.0, 0.0), 
								 vec3(window.bottom/10), 0);

	 {
		 shape = shf.getButterfly(0.0, 0.0, 1, 1);
		 shape.dir = Direction::UP;
		 scene.addObject(&shape);
		 name = shape.name;
		 // Set initial position and scale
		 scene.transformObject(name, vec3(100.0, window.bottom / 4, 0.0),
			 vec3(window.bottom / 10), 0);

		 shape = shf.getButterfly(0.0, 0.0, 1, 1);
		 shape.dir = Direction::UP;
		 scene.addObject(&shape);
		 name = shape.name;
		 // Set initial position and scale
		 scene.transformObject(name, vec3(100.0, window.bottom /4*3, 0.0),
			 vec3(window.bottom / 10), 0);
	 }


	// Pass uniform variables to the shader
	// Coordinates are specified in relation to the usage domain
	// (i.e. when dealing w/ temperature, the origin could be below zero)
	Projection = ortho(0.0f, float(window.right), 0.0f, float(window.bottom));
	MatProj = glGetUniformLocation(scene.getProgramID(), "Projection");
	MatMod = glGetUniformLocation(scene.getProgramID(), "Model");

}

void drawScene(void)
{
	vector<SceneObject> Scena = scene.getScene();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	scene.drawScene(&MatMod, &MatProj, &Projection);

	glutSwapBuffers();
}

void timeRefresh(int value)
{
	float angolo = 0.0;
	float trasFactor;
	float minObjY = window.bottom / 4;
	float maxObjY = window.bottom - minObjY;
	float ray = window.bottom / 10;
	std::string moving = "butterfly_0";

	vec3 objPos = scene.getObjectPosition(moving);
	Direction dir = scene.getObjectDirection(moving);

	float y = (ray * 2 * (dir / abs((int)dir))) + objPos.y;

	// Change direction
	if (y < minObjY) 
		scene.changeObjectDirection(moving, Direction::UP);
	if (y > maxObjY) 
		scene.changeObjectDirection(moving, Direction::DOWN);


	// Create base translation vector
	vec3 tVector = vec3((dir / 2), (dir % 2), 0.0);

	// trasFactor = (dir / abs((int) dir));
	// 
	// tVector.x *= trasFactor;
	// tVector.y *= trasFactor;

	vec3 sv = vec3(1.0, 1.0, 1.0); // Leave z axis untouched

	scene.transformObject(moving, tVector, sv, angolo);

	glutTimerFunc(50, timeRefresh, 0);
	glutPostRedisplay();
}

void myKey(unsigned char key, int x, int y)
{
	/*switch (key)
	{
		case 'a':
			dxc--;
			break;
		case 'd':
			dxc++;
			break;
		case 's':
			dyc--;
			break;
		case 'w':
			dyc++;
			break;
	}*/

	glutPostRedisplay();
}

void mouseClick(int btn, int state, int x, int y)
{
	// Get y in window system
	y = window.bottom - y;

	// if (state == GLUT_UP) mouse.onMouseRelease(btn, state, x, y);
	// if (state == GLUT_DOWN) mouse.onMouseClick(btn, state, x, y);

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	createWindow("MyGameApp");

	glutDisplayFunc(drawScene);

	// Handle mouse inputs
	mouse.assignRefScene(&scene);
	glutMouseFunc(mouseClick);

	glutKeyboardFunc(myKey);
	glutTimerFunc(50, timeRefresh, 0);
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	scene.setShaders((char*)"vertexShader.glsl", (char*)"fragmentShader.glsl");
	INIT_VAO();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


