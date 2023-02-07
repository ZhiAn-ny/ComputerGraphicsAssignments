#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "lib.h"

namespace util
{
	unsigned int check_error(string message);
	bool is_in_range(double a, double b, double x);
	vec3 distance(vec3 a, vec3 b);

	const int mouse_wheel_up = 4;
	const int mouse_wheel_down = 3;

	namespace dir {
		enum class Directions {
			front,
			back,
			up,
			down,
			left,
			right
		};

	} // !dir

} // !util

namespace gobj
{
	namespace mesh
	{
		class Vertex {
		public:
			vec3 pos = vec3(0);
			vec4 color = vec4(1);
			vec2 tex = vec2(0);
			vec3 normal = vec3(0);

			Vertex() {};
			Vertex(vec3 pos_, vec4 col_, vec2 tex_, vec3 normal_)
			{
				this->pos = pos_;
				this->color = col_;
				this->tex = tex_;
				this->normal = normal_;
			}
		};

		enum class TexType {
			diffuse,
			specular,
			undefined
		};

		class Texture {
		public:
			unsigned int id = 0;
			TexType type = TexType::undefined;
			string path = "";  // we store the path of the texture to compare with other textures
			string name = "";

			Texture() {}

			static Texture* find_first(TexType type, vector<Texture>& list);
		};

	} // !mesh
} // !gobj

#endif // !GAME_UTILS_H_
