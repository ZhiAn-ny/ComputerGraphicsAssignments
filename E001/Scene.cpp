#include "Scene.h"


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
	fig->bind();

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

void gscene::Scene::draw_scene(unsigned int* MatMod, unsigned int* MatProj, glm::mat4* Projection)
{
	int length = this->scene_objs_.size();

	glUniformMatrix4fv(*MatProj, 1, GL_FALSE, value_ptr(*Projection));

	for (int i = 0; i < length; i++)
	{
		this->scene_objs_[i].render(MatMod);

		if (this->wf_mode_)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
}
