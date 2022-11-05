#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

vector<SceneObject> Scene::getScene()
{
    return this->_scene;
}

void Scene::addObject(SceneObject* fig)
{
	this->createVertexArray(fig);
	this->bindVerticesGeometry(fig);
	this->bindVerticesColor(fig);

	this->_scene.push_back(*fig);
}

void Scene::drawScene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection)
{
	vector<SceneObject> Scena = this->_scene;
	int length = this->getSceneLength();
	int k;

	float angolo = 0.0f;
	float s = 1.0f;
	float factor = 1.1f;
	float dxc = 0, dyc = 0, dxf = 0, dyf = 0;

	// fuori dal ciclo perché non cambia, sempre lei
	glUniformMatrix4fv(*MatProj, 1, GL_FALSE, value_ptr(*Projection));

	for (k = 0; k < length; k++)
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
		glUniformMatrix4fv(*MatMod, 1, GL_FALSE, value_ptr(Scena[k].Model));

		glBindVertexArray(Scena[k].VertexArrayObject);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLE_FAN, 0, Scena[k].nVertices);
	}
}

void Scene::createVertexArray(SceneObject* fig)
{
	glGenVertexArrays(1, &fig->VertexArrayObject);
	glBindVertexArray(fig->VertexArrayObject);
}

void Scene::bindVerticesGeometry(SceneObject* fig)
{
	glGenBuffers(1, &fig->VertexBufferObject_Geometry);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VertexBufferObject_Geometry);
	glBufferData(GL_ARRAY_BUFFER, fig->vertices.size() * sizeof(vec3), fig->vertices.data(), GL_STATIC_DRAW); // .data() usato per ottenere l'indirizzo di partenza del vettore (come &)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

void Scene::bindVerticesColor(SceneObject* fig)
{
	glGenBuffers(1, &fig->VertexBufferObject_Colors);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VertexBufferObject_Colors);
	glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

int Scene::getSceneLength()
{
	return this->_scene.size();
}
