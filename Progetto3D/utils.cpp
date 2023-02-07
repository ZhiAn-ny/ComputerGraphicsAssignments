#include "utils.h"

using namespace gobj::mesh;

unsigned int util::check_error(string message)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << message << "(CODE: " << error << ")" << std::endl;
		return error;
	}
	return 0;
}

bool util::is_in_range(double a, double b, double x)
{
	return x >= a && x <= b;
}

vec3 util::distance(vec3 a, vec3 b)
{
	return abs(b - a);
}

bool util::is_same_material(res::mat::Material a, res::mat::Material b)
{
	return a.ambient == b.ambient && a.diffuse == b.diffuse
		&& a.specular == b.specular && a.shininess == b.shininess;
}

Texture* Texture::find_first(TexType type, vector<Texture>& list)
{
	for (int i = 0; i < list.size(); i++)
		if (list[i].type == type) return &list[i];
	return nullptr;
}
