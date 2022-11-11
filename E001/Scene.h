#ifndef GAME_SCENE_H_
#define GMAE_SCENE_H_

#include "Lib.h"
#include "SceneObject.h"
#include "ShaderMaker.h"

namespace gscene {


	class Scene {
	private:
		unsigned int program_id_ = 0;
		std::vector<SceneObject> scene_objs_ = {};
		bool wf_mode_ = false;

		void createVertexArray(SceneObject* fig);
		void bindVerticesGeometry(SceneObject* fig);
		void bindVerticesColor(SceneObject* fig);

	public:
		Scene();
		~Scene();

		unsigned int get_id();

		void set_shaders(char * vertsh, char * fragsh);

		/** 
		 * @return The new object's index.
		 */
		int add_object(SceneObject* fig);

		SceneObject* get_object(std::string name);

		void draw_scene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection);

		void transformObject(std::string name, vec3 tVector, vec3 sVector, GLfloat angle);
	};

}

#endif // !GAME_SCENE_H_




//
//class Scene
//{
//private:
//	unsigned int programId;
//	vector<SceneObject> _scene;
//	bool isWireframeActive;
//
//	void createVertexArray(SceneObject* fig);
//
//	void bindVerticesGeometry(SceneObject* fig);
//
//	void bindVerticesColor(SceneObject* fig);
//
//	int getSceneLength();
//
//public:
//
//	vector<SceneObject> getScene();
//	unsigned int getProgramID();
//
//	void addObject(SceneObject* fig);
//
//	void drawScene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection);
//
//	void setShaders(char* vertexShader, char* fragmentShader);
//
//
//	SceneObject* getObject(std::string name);
//
//	//vec3 getObjectPosition(std::string name);
//
//	//Direction getObjectDirection(std::string name);
//
//	//void changeObjectDirection(std::string name, Direction newDir);
//};
