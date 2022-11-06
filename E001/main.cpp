#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ShaderMaker.h"
#include "lib.h"
#include "ShapeFactory.h"
#include "Scene.h"


#define  PI   3.14159265358979323846

static unsigned int programId, MatMod, MatProj;
mat4 Projection;

int width = 800;
int height = 800;

float angolo = 0.0f;
float s = 1.0f;
float factor = 1.1f;
float dxc = 0, dyc = 0, dxf = 0, dyf = 0;

Scene scene;


void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();

	// CAMBIA RIFERIMENTO A SHADER
	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_S.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	ShapeFactory shf;
	SceneObject shape;
	std::string name;
	
	shape = shf.getButterfly(0.0, 0.0, 1, 1);
	scene.addObject(&shape);
	name = shape.name;
	scene.transformObject(name, vec3(600.0, 200.0, 0.0), vec3(0.0), vec3(100.0), 0);

	shape = shf.getHeart(0.0, 0.0, 1, 1);
	scene.addObject(&shape);
	name = shape.name;
	scene.transformObject(name, vec3(400.0, 400.0, 0.0), vec3(0.0), vec3(100.0), 0);


	// Passo variabili uniform a shader
	// Specifico le coordinate del mondo in riferimento al dominio d'uso (es. se parlo di temperature potrei avere l'origine sotto zero)
	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programId, "Projection"); // secondo argomento è il nome della variabile definita nello shader
	MatMod = glGetUniformLocation(programId, "Model");

}

void drawScene(void)
{
	
	vector<SceneObject> Scena = scene.getScene();
	int k;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	scene.drawScene(&MatMod, &MatProj, &Projection);

	glutSwapBuffers();

}

void updateAngolo(int value)
{
	angolo = 1;

	//vec3 tv = vec3(600.0, 200.0, 0.0);
	//vec3 rv = vec3(1.0,0,0);
	//vec3 sv = vec3(1.0);

	//scene.transformObject("butterfly_0", tv, rv, sv, angolo);
	
	if (s > 3 || s < 0.5)
	{
		factor = 1 / factor;
	}
	s *= factor;

	glutTimerFunc(50, updateAngolo, 0);
	glutPostRedisplay();
}

void myKey(unsigned char key, int x, int y)
{
	switch (key)
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
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Farfalla OpenGL");
	glutDisplayFunc(drawScene);

	glutKeyboardFunc(myKey);

	glutTimerFunc(10, updateAngolo, 0); // 1° parametro -> millisec
	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


