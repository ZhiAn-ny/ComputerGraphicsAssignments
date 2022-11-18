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
		kRight = 2,
		kNone = 0
	};

	class SceneObject {
	private:
		int nTriangles = default_triangle_number;
		int nVertices = 0;

		glm::vec4 pos_ = {};
		gso::Direction dir_ = gso::Direction::kUp;
		gso::Direction basc_dir_ = {};

		// Bottom left corner in the object's coordinates.
		glm::vec4 obj_bottom_left_ = {};
		// Top right corner in the object's coordinates.
		glm::vec4 obj_top_right_ = {};

		glm::vec4 bottomLeft = {};
		glm::vec4 topRight = {};

		GLuint VertexArrayObject;
		GLuint VertexBufferObject_Geometry;
		GLuint VertexBufferObject_Colors;

		// Model matrix: translation * rotation * scale
		glm::mat4 Model = glm::mat4(1.0);

		GLenum render_mode_ = GL_TRIANGLE_FAN;


		void createVertexArray();
		void bindVerticesGeometry();
		void bindVerticesColor();

		void update_object_corners();


	protected:
		std::string name_ = {};

		std::vector<glm::vec3> vertices_ = {};
		std::vector<glm::vec4> colors_ = {};
		
	public:
		SceneObject();
		SceneObject(std::string name);
		~SceneObject();

		std::string get_name();

		int get_triangles();

		void add_vertex(glm::vec3 pos, glm::vec4 color);

		void set_color(glm::vec4 center, glm::vec4 others);

		void set_render_mode(GLenum mode);

		void set_basculation_direction(gso::Direction dir);

		gso::Direction get_basculation_direction();

		glm::vec4 get_position();

		float get_height();

		float get_width();

		glm::mat4 get_model();

		void set_model(glm::mat4 model_matrix);

		/**
		 * @returns width/height ratio
		 */
		float get_ratio();

		float get_original_ratio();

		bool is_colliding(glm::vec3 pos);

		bool is_colliding(gso::SceneObject other);

		void bind();

		void change_direction(gso::Direction new_dir);

		void update_position();

		void move(float distance);

		void transform(glm::vec3 tVector, glm::vec3 sVector, GLfloat angle);

		void render(unsigned int* MatMod);

	};

}

#endif // !GAME_SCENE_OBJECT_H_
