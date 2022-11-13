#ifndef GAME_SCENE_OBJECT_H_
#define GAME_SCENE_OBJECT_H_

#include <string>

#include "Lib.h"

namespace gso {

	const int default_triangle_number = 180;

	enum class Direction {
		kUp = 1,
		kDown = -1,
		kLeft = -2,
		kRight = 2
	};

	class SceneObject {
	private:
		std::string name_ = {};

		GLuint VertexArrayObject;
		GLuint VertexBufferObject_Geometry;
		GLuint VertexBufferObject_Colors;

		std::vector<glm::vec3> vertices_ = {};
		std::vector<glm::vec4> colors_ = {};

		int nTriangles = default_triangle_number;
		int nVertices = 0;

		glm::vec3 pos_ = {};
		gso::Direction dir_ = gso::Direction::kUp;

		glm::vec3 bottomLeft = {};
		glm::vec3 topRight = {};

		// Model matrix: translation * rotation * scale
		glm::mat4 Model = glm::mat4(1.0);


		void update_corners();

		void createVertexArray();
		void bindVerticesGeometry();
		void bindVerticesColor();
		
	public:
		SceneObject();
		SceneObject(std::string name);
		~SceneObject();

		std::string get_name();

		int get_triangles();

		void add_vertex(glm::vec3 pos, glm::vec4 color);

		void set_color(glm::vec4 center, glm::vec4 others);

		gso::Direction get_direction();

		glm::vec3 get_position();

		void bind();

		void change_direction(gso::Direction new_dir);

		void move(float distance);

		void transform(vec3 tVector, vec3 sVector, GLfloat angle);

		void render(unsigned int* MatMod);

	};

}

#endif // !GAME_SCENE_OBJECT_H_
