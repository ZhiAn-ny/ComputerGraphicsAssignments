#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ShaderMaker.h"
#include "lib.h"
#include "ShapeFactory.h"
#include "Scene.h"


static unsigned int MatMod, MatProj;
mat4 Projection;

RECT window;
Scene scene;

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
	
	shape = shf.getButterfly(0.0, 0.0, 1, 1);
	scene.addObject(&shape);
	name = shape.name;
	scene.transformObject(name, vec3(200.0, 200.0, 0.0), vec3(0.0), vec3(100.0), 0);

	shape = shf.getHeart(0.0, 0.0, 1, 1);
	scene.addObject(&shape);
	name = shape.name;
	scene.transformObject(name, vec3(100.0, 150.0, 0.0), vec3(0.0), vec3(100.0), 0);


	// Passo variabili uniform a shader
	// Specifico le coordinate del mondo in riferimento al dominio d'uso (es. se parlo di temperature potrei avere l'origine sotto zero)
	Projection = ortho(0.0f, float(window.right), 0.0f, float(window.bottom));
	MatProj = glGetUniformLocation(scene.getProgramID(), "Projection"); // secondo argomento � il nome della variabile definita nello shader
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

void updateAngolo(int value)
{
	int angolo = 20;

	vec3 tv = vec3(-1.0, -1.0, 0.0);
	vec3 rv = vec3(1.0, 0.0, 0.0);
	vec3 sv = vec3(1.0, 1.0, 0.0);

	//scene.transformObject("butterfly_0", tv, rv, sv, angolo);
	
	/*if (s > 3 || s < 0.5)
	{
		factor = 1 / factor;
	}
	s *= factor;*/

	glutTimerFunc(50, updateAngolo, 0);
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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	createWindow("MyGameApp");

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(myKey);
	glutTimerFunc(50, updateAngolo, 0); // 1� parametro -> millisec
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	scene.setShaders((char*)"vertexShader_M.glsl", (char*)"fragmentShader_S.glsl");
	INIT_VAO();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


