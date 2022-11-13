#include "shape_factory.h"

gsf::ShapeFactory::ShapeFactory() { }

gsf::ShapeFactory::~ShapeFactory() { }

gso::SceneObject gsf::ShapeFactory::getShape(float centerX, float centerY,
	float rayX, float rayY, float (*xFunc)(float, float, float),
	float (*yFunc)(float, float, float), std::string name)
{
	gso::SceneObject fig = gso::SceneObject(name);
	float step = (2 * pi) / fig.get_triangles();
	float theta, x, y;

	// Add central vertex to the figure
	fig.add_vertex(glm::vec3(centerX, centerY, 0.0), color::cyan);

	// Add all the other vertices on the perimeter
	for (int i = 0; i <= fig.get_triangles(); i++)
	{
		theta = i * step;
		x = xFunc(centerX, rayX, theta);
		y = yFunc(centerY, rayY, theta);

		fig.add_vertex(glm::vec3(x, y, 0.0), color::cyan);
	}
	
	return fig;
}

gso::SceneObject gsf::ShapeFactory::getShape(float centerX, float centerY,
								   float rayX, float rayY,
								   float (*xFunc)(float, float, float),
								   float (*yFunc)(float, float, float))
{
	return this->getShape(centerX, centerY, rayX, rayY, xFunc, yFunc, "");
}

gso::SceneObject gsf::ShapeFactory::getHeart(float centerX, float centerY, float rayX, float rayY)
{
	std::string name = "heart_" + std::to_string(this->heartCounter);

	gso::SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (16 * pow(sin(t), 3)) / 16);},
		[](float y, float r, float t) {return y + r * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16);},
		name);

	fig.set_color(color::cyan, glm::vec4(0.54, 0.32, 0.87, 1.0));

	this->heartCounter++;
	return fig;
}

gso::SceneObject gsf::ShapeFactory::getButterfly(float centerX, float centerY, float rayX, float rayY)
{
	std::string name = "butterfly_" + std::to_string(this->butterflyCounter);

	gso::SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); },
		[](float y, float r, float t) {return (float)(y + r * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); },
		name);

	fig.set_color(color::cyan, glm::vec4(0.54, 0.32, 0.87, 1.0));

	this->butterflyCounter++;
	return fig;
}

gso::SceneObject gsf::ShapeFactory::getCircle(float centerX, float centerY, float rayX, float rayY)
{
	std::string name = "circle_" + std::to_string(this->circleCounter);

	gso::SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * cos(t)); },
		[](float y, float r, float t) {return (float)(y + r * sin(t)); },
		name);

	fig.set_color(color::cyan, glm::vec4(0.54, 0.32, 0.87, 1.0));

	this->circleCounter++;
	return fig;
}
