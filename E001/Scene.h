#pragma once
#include "Lib.h"
#include "SceneObject.h"
#include "ShaderMaker.h"

class Scene
{
private:
	unsigned int programId;
	vector<SceneObject> _scene;
	bool isWireframeActive;

	void createVertexArray(SceneObject* fig);

	void bindVerticesGeometry(SceneObject* fig);

	void bindVerticesColor(SceneObject* fig);

	int getSceneLength();

public:
	Scene();
	~Scene();

	vector<SceneObject> getScene();
	unsigned int getProgramID();

	void addObject(SceneObject* fig);

	void drawScene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection);

	void setShaders(char* vertexShader, char* fragmentShader);

	void transformObject(std::string name, vec3 tVector, vec3 sVector, GLfloat angle);

	SceneObject* getObject(std::string name);

	vec3 getObjectPosition(std::string name);

	Direction getObjectDirection(std::string name);

	void changeObjectDirection(std::string name, Direction newDir);
};
