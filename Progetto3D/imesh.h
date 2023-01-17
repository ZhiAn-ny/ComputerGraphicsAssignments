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
			vec3 pos;
			vec4 color;
			vec2 tex;

			Vertex() {};
			Vertex(vec3 pos_, vec4 col_, vec2 tex_)
			{
				this->pos = pos_;
				this->color = col_;
				this->tex = tex_;
			}
		};

		class Mesh {
			virtual void add_vertex(Vertex v) = 0;
			virtual void add_index(unsigned int v) = 0;
			virtual void bind() = 0;
			virtual void render(Shader* sh) = 0;
		};
	}
}

#endif // !GAME_OBJECT_MESH_INTERFACE_H_
