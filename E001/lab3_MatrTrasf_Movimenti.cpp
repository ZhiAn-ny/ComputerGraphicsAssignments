#include <iostream>
#include "ShaderMaker.h"
#include "lib.h"

#include <GL/glew.h>
#include <GL/freeglut.h>



#define  PI   3.14159265358979323846

static unsigned int programId, MatMod, MatProj;
mat4 Projection;

int width = 800;
int height = 800;

float angolo = 0.0f;
float s = 1.0f;
float factor = 1.1f;
float dxc = 0, dyc = 0, dxf = 0, dyf = 0;

typedef struct {
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	int nTriangles;

	// Vertici
	// vec3 e vec4 sono formiti in glm
	vector<vec3> vertici;
	vector<vec4> colors;

	// Numero vertici
	int nv;
	
	//Matrice di Modellazione: Traslazione*Rotazione*Scala
	mat4 Model;
} Figura;

vector<Figura> Scena;

Figura  Farf = {};
Figura Cuore = {};


void crea_VAO_Vector(Figura* fig)
{

	glGenVertexArrays(1, &fig->VAO);
	glBindVertexArray(fig->VAO);
	//Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &fig->VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_G);
	glBufferData(GL_ARRAY_BUFFER, fig->vertici.size() * sizeof(vec3), fig->vertici.data(), GL_STATIC_DRAW); // .data() usato per ottenere l'indirizzo di partenza del vettore (come &)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &fig->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

}

void costruisci_cuore(float cx, float cy, float raggiox, float raggioy, Figura* fig) {

	int i;
	float stepA = (2 * PI) / fig->nTriangles;
	float t;

	// riempio il vettore mettendo prima il centro
	fig->vertici.push_back(vec3(cx, cy, 0.0));

	fig->colors.push_back(vec4(255.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
		fig->vertici.push_back(vec3(cx + raggiox*(16 * pow(sin(t), 3)) / 16, cy+raggioy*( (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16), 0.0));
		//Colore 
		fig->colors.push_back(vec4(1.0, 204.0 / 255.0, 0.0, 1.0));


	}
	fig->nv = fig->vertici.size();

}

void costruisci_farfalla(float cx, float cy, float raggiox, float raggioy, Figura* fig) {

	int i;
	float stepA = (2 * PI) / fig->nTriangles;
	float t;


	fig->vertici.push_back(vec3(cx, cy, 0.0));

	fig->colors.push_back(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
		fig->vertici.push_back(vec3(cx+raggiox*(sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4, cy+raggioy*(cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4, 0.0));
		//Colore 
		fig->colors.push_back(vec4(1.0, 0.0, 0.0, 0.0));


	}
	fig->nv = fig->vertici.size();

}

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
	Farf.nTriangles = 180;
	costruisci_farfalla(0.0, 0.0, 1, 1, &Farf);
	crea_VAO_Vector(&Farf);
	Scena.push_back(Farf);
	
	Cuore.nTriangles = 180;
	costruisci_cuore(0.0, 0.0, 1, 1, &Cuore);
	crea_VAO_Vector(&Cuore);
	
	// metto la figura creata nella scena
	Scena.push_back(Cuore);

	// Passo variabili uniform a shader
	// Specifico le coordinate del mondo in riferimento al dominio d'uso (es. se parlo di temperature potrei avere l'origine sotto zero)
	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programId, "Projection"); // secondo argomento è il nome della variabile definita nello shader
	MatMod = glGetUniformLocation(programId, "Model");

}

void drawScene(void)
{
	int k;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// fuori dal ciclo perché non cambia, sempre lei
	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));

	for (k = 0; k < Scena.size(); k++)
	{
		// Costruisco matrici di modellazione
		if (k == 0)
		{
			Scena[k].Model = mat4(1.0); // inizializzo a identità
			Scena[k].Model = translate(Scena[k].Model, vec3(600.0f + dxc, 200.0f + dyc, 0.0f)); // traslazione
			Scena[k].Model = scale(Scena[k].Model, vec3(100.0f * s, 100.0f * s, 1.0f));     // (lascio z inalterata)
			Scena[k].Model = rotate(Scena[k].Model, radians(angolo*30), vec3(0.0f, 0.0f, 1.0f)); // ruoto lungo l'asse z
		}
		if (k == 1)
		{
			Scena[k].Model = mat4(1.0); // inizializzo a identità
			Scena[k].Model = translate(Scena[k].Model, vec3(400.0f + dxf, 400.0f + dyf, 0.0f));
			Scena[k].Model = scale(Scena[k].Model, vec3(100.0f * (-s/2), 100.0f * (-s/2), 1.0f));
			Scena[k].Model = rotate(Scena[k].Model, radians(-angolo), vec3(0.0f, 0.0f, 1.0f)); // ruoto lungo l'asse z
		}

		// location, # matrici, normalizzare(t/f), puntatore alla matrice
		glUniformMatrix4fv(MatMod, 1, GL_FALSE, value_ptr(Scena[k].Model));

		glBindVertexArray(Scena[k].VAO);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLE_FAN, 0, Scena[k].nv);
	}

	glutSwapBuffers();

}

void updateAngolo(int value)
{
	angolo += 1;
	
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


