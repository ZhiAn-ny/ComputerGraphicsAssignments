#include "Scene.h"




void gscene::Scene::createVertexArray(gso::SceneObject* fig)
{
	glGenVertexArrays(1, &fig->VertexArrayObject);
	glBindVertexArray(fig->VertexArrayObject);
}

void gscene::Scene::bindVerticesGeometry(gso::SceneObject* fig)
{
	glGenBuffers(1, &fig->VertexBufferObject_Geometry);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VertexBufferObject_Geometry);
	glBufferData(GL_ARRAY_BUFFER, fig->vertices_.size() * sizeof(vec3), fig->vertices_.data(), GL_STATIC_DRAW); // .data() usato per ottenere l'indirizzo di partenza del vettore (come &)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

void gscene::Scene::bindVerticesColor(gso::SceneObject* fig)
{
	glGenBuffers(1, &fig->VertexBufferObject_Colors);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VertexBufferObject_Colors);
	glBufferData(GL_ARRAY_BUFFER, fig->colors_.size() * sizeof(vec4), fig->colors_.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}



void gscene::Scene::transformObject(std::string name, vec3 tVector, vec3 sVector, GLfloat angle)
{
	vec3 rotationVector = vec3(0.0, 0.0, 1.0); // Always rotate along z axis
	sVector.z = 1.0; // Leave z dimension untouched
	tVector.z = 0.0; // Can't move along z axis

	gso::SceneObject* fig = this->get_object(name);

	// Update position
	fig->pos_.x += tVector.x;
	fig->pos_.y += tVector.y;

	mat4 T = translate(mat4(1.0), tVector);
	mat4 S = scale(mat4(1.0), sVector);
	mat4 R = rotate(mat4(1.0), angle, rotationVector);

	(*fig).Model = (*fig).Model * T * R * S;
}



gscene::Scene::Scene() { }

gscene::Scene::~Scene() { }

unsigned int gscene::Scene::get_id()
{
	return this->program_id_;
}

void gscene::Scene::set_shaders(char * vertsh, char * fragsh)
{
	GLenum ErrorCheckValue = glGetError();

	this->program_id_ = ShaderMaker::createProgram(vertsh, fragsh);
	glUseProgram(this->program_id_);
}

int gscene::Scene::add_object(gso::SceneObject* fig)
{
	this->createVertexArray(fig);
	this->bindVerticesGeometry(fig);
	this->bindVerticesColor(fig);

	this->scene_objs_.push_back(*fig);

	if (this->scene_objs_[this->scene_objs_.size() - 1].get_name() == fig->get_name())
		return this->scene_objs_.size() - 1;

	return -1;
}

gso::SceneObject* gscene::Scene::get_object(std::string name)
{
	for (int i = 0; i < this->scene_objs_.size(); i++)
	{
		if (this->scene_objs_[i].get_name()._Equal(name))
		{
			return &(this->scene_objs_[i]);
		}
	}
	return NULL;
}

void gscene::Scene::draw_scene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection)
{
	vector<gso::SceneObject> Scena = this->scene_objs_;
	int length = this->scene_objs_.size();
	int index;

	glUniformMatrix4fv(*MatProj, 1, GL_FALSE, value_ptr(*Projection));

	for (index = 0; index < length; index++)
	{
		// Create object's uniform matrix
		glUniformMatrix4fv(*MatMod, 1, GL_FALSE, value_ptr(Scena[index].Model));
		glBindVertexArray(Scena[index].VertexArrayObject);
		glDrawArrays(GL_TRIANGLE_FAN, 0, Scena[index].nVertices);

		if (this->wf_mode_)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
}




//vec3 Scene::getObjectPosition(std::string name)
//{
//	SceneObject* fig = this->getObject(name);
//	return fig->pos;
//}
//
//Direction Scene::getObjectDirection(std::string name)
//{
//	SceneObject* fig = this->getObject(name);
//	return fig->dir;
//}
//
//void Scene::changeObjectDirection(std::string name, Direction newDir)
//{
//	SceneObject* fig = this->getObject(name);
//	fig->dir = newDir;
//}
