#ifndef GAME_OBJECT_MESH_INTERFACE_H_
#define GAME_OBJECT_MESH_INTERFACE_H_

#include "lib.h"
#include "shader.h"

namespace gobj
{
	namespace mesh
	{
		class Vertex {
		public:
			vec3 pos = vec3(0);
			vec4 color = vec4(1);
			vec2 tex = vec2(0);

			Vertex() {};
			Vertex(vec3 pos_, vec4 col_, vec2 tex_)
			{
				this->pos = pos_;
				this->color = col_;
				this->tex = tex_;
			}
		};

		class AMesh {
		private:
			string name_ = "";

		public:
			string get_name() { return this->name_; }
			void set_name(string name) { this->name_ = name; }

			virtual void add_vertex(Vertex v) = 0;
			virtual void add_index(unsigned int v) = 0;
			virtual void bind() = 0;
			virtual void render(Shader* sh) = 0;
			virtual void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) = 0;
			virtual void set_color(vec4 color) = 0;
		};
	}
}

#endif // !GAME_OBJECT_MESH_INTERFACE_H_
