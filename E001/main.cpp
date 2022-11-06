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
	// shape = shf.getButterfly(0.0, 0.0, 1, 1);
	// scene.addObject(&shape);
	// name = shape.name;
	// scene.transformObject(name, vec3(200.0, 200.0, 0.0), vec3(100.0), 0);
	// 
	// shape = shf.getHeart(0.0, 0.0, 1, 1);
	// scene.addObject(&shape);
	// name = shape.name;
	// scene.transformObject(name, vec3(100.0, 150.0, 0.0), vec3(100.0), 0);


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
	float angolo = 0.1;

	vec3 tv = vec3(0.0);
	vec3 sv = vec3(1.0, 1.0, 1.0); // Leave z axis untouched

	scene.transformObject("butterfly_0", tv, sv, angolo);

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

	if (state == GLUT_UP) mouse.onMouseRelease(btn, state, x, y);
	if (state == GLUT_DOWN) mouse.onMouseClick(btn, state, x, y);

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
	//glutTimerFunc(50, timeRefresh, 0);
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	scene.setShaders((char*)"vertexShader.glsl", (char*)"fragmentShader.glsl");
	INIT_VAO();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


