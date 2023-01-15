#include "utils.h"

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
