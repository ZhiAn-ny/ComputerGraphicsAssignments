#include "shape_factory.h"


gsf::ShapeFactory::ShapeFactory() { }

gsf::ShapeFactory::~ShapeFactory() { }

gso::SceneObject gsf::ShapeFactory::new_shape(float centerX, float centerY,
	float rayX, float rayY, float (*xFunc)(float, float, float),
	float (*yFunc)(float, float, float), std::string name)
{
	gso::SceneObject fig = gso::SceneObject(name);
	float step = (2 * M_PI) / fig.get_triangles();
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

gso::SceneObject gsf::ShapeFactory::new_shape(float centerX, float centerY,
								   float rayX, float rayY,
								   float (*xFunc)(float, float, float),
								   float (*yFunc)(float, float, float))
{
	return this->new_shape(centerX, centerY, rayX, rayY, xFunc, yFunc, "");
}

gso::HermiteShape gsf::ShapeFactory::new_hermite(std::vector<glm::vec3> cp, std::string name)
{
	gso::HermiteShape fig = gso::HermiteShape(name);

	for (int i = 0; i < cp.size(); i++)
	{
		fig.add_control_point(cp[i]);
	}

	return fig;
}

gso::HermiteShape gsf::ShapeFactory::new_hermite(std::vector<glm::vec3> cp, std::vector<glm::vec3> tbc, std::string name)
{
	if (cp.size() != tbc.size()) return this->new_hermite(cp, name);

	gso::HermiteShape fig = gso::HermiteShape(name);

	for (int i = 0; i < cp.size(); i++)
	{
		fig.add_control_point(cp[i], tbc[i]);
	}

	return fig;
}

gso::SceneObject gsf::ShapeFactory::get_heart(float centerX, float centerY, float rayX, float rayY)
{
	std::string name = "heart_" + std::to_string(this->heartCounter);

	gso::SceneObject fig = this->new_shape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (16 * pow(sin(t), 3)) / 16);},
		[](float y, float r, float t) {return y + r * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16);},
		name);

	fig.set_color(color::cyan, glm::vec4(0.54, 0.32, 0.87, 1.0));

	this->heartCounter++;
	return fig;
}

gso::SceneObject gsf::ShapeFactory::get_butterfly(float centerX, float centerY, float rayX, float rayY)
{
	std::string name = "butterfly_" + std::to_string(this->butterflyCounter);

	gso::SceneObject fig = this->new_shape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); },
		[](float y, float r, float t) {return (float)(y + r * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); },
		name);

	fig.set_color(color::cyan, glm::vec4(0.54, 0.32, 0.87, 1.0));

	this->butterflyCounter++;
	return fig;
}

gso::SceneObject gsf::ShapeFactory::get_circle(float centerX, float centerY, float rayX, float rayY)
{
	std::string name = "circle_" + std::to_string(this->circleCounter);

	gso::SceneObject fig = this->new_shape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * cos(t)); },
		[](float y, float r, float t) {return (float)(y + r * sin(t)); },
		name);

	fig.set_color(color::cyan, glm::vec4(0.54, 0.32, 0.87, 1.0));

	this->circleCounter++;
	return fig;
}

gso::SceneObject gsf::ShapeFactory::get_dragon_wing()
{
	std::string name = "wing";

	std::vector<glm::vec3> cps = {
		glm::vec3(-1.0, -16.0, 0.0),
		glm::vec3(-2.0, -12.0, 0.0),
		glm::vec3(-9.0, -10.0, 0.0),
		glm::vec3(-6.0, -6.0, 0.0),
		glm::vec3(-14.0, -1.0, 0.0),
		glm::vec3(-7.0, 1.0, 0.0),
		glm::vec3(-10.0, 11.0, 0.0),
		glm::vec3(-1.0, 10.0, 0.0),
		glm::vec3(-1.0, 17.0, 0.0),
		glm::vec3(11.0, 0.0, 0.0),
		glm::vec3(5.0, -7.0, 0.0),
		glm::vec3(7.0, -15.0, 0.0),
		glm::vec3(7.0, -17.0, 0.0),
		glm::vec3(-1.0, -16.0, 0.0)
	};

	std::vector<glm::vec3> tbc = {
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 1.0, -1.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0)
	};

	gso::HermiteShape h = this->new_hermite(cps, tbc, name);

	return h;
}

gso::SceneObject gsf::ShapeFactory::get_dragon_head()
{
	std::string name = "head";

	std::vector<glm::vec3> cps = {
		glm::vec3(-1.0, 2.5, 0.0),
		glm::vec3(1.0, 2.5, 0.0),
		glm::vec3(2.0, 1.5, 0.0),
		glm::vec3(5.0, 1.5, 0.0),
		glm::vec3(4.3, -0.5, 0.0),
		glm::vec3(1.0, -0.5, 0.0),
		glm::vec3(3.5, -1.3, 0.0),
		glm::vec3(3.0, -2.0, 0.0),
		glm::vec3(0.0, -1.5, 0.0),
		glm::vec3(-2.0, -2.5, 0.0),
		glm::vec3(-1.5, -1.5, 0.0),
		glm::vec3(-4.0, -0.5, 0.0),
		glm::vec3(-2.0, 0.0, 0.0),
		glm::vec3(-4.0, 1.5, 0.0),
		glm::vec3(-2.0, 1.5, 0.0),
		glm::vec3(-6.0, 4.5, 0.0),
		glm::vec3(-1.0, 2.5, 0.0),
	};

	std::vector<glm::vec3> tbc = {
		glm::vec3(0.0),
		glm::vec3(0.0),
		glm::vec3(0.0),
		glm::vec3(0.5, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(0.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(0.0)
	};

	gso::HermiteShape h = this->new_hermite(cps, tbc, name);
	return h;
}

gso::SceneObject gsf::ShapeFactory::get_dragon_tail()
{
	std::string name = "tail";

	std::vector<glm::vec3> cps = {
		glm::vec3(-18.0, 5.0, 0.0),
		glm::vec3(-5.0, 2.0, 0.0),
		glm::vec3(2.0, 5.0, 0.0),
		glm::vec3(7.0, 8.0, 0.0),
		glm::vec3(15.0, 10.0, 0.0),
		glm::vec3(12.0, 4.0, 0.0),
		glm::vec3(-2.0, -1.0, 0.0),
		glm::vec3(-9.0, 0.0, 0.0),
		glm::vec3(-18.0 ,5.0, 0.0),
	};

	//std::vector<glm::vec3> tbc = {
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//	glm::vec3(0.0, 1.0, -1.0),
	//};

	gso::HermiteShape h = this->new_hermite(cps, name);
	return h;

}

gso::SceneObject gsf::ShapeFactory::get_dragon_body()
{
	std::string name = "body";

	std::vector<glm::vec3> cps = {
		glm::vec3(-13.0, -2.0, 0.0),
		glm::vec3(-10.0, -3.0, 0.0),
		glm::vec3( -8.0, -5.0, 0.0),
		glm::vec3( -4.0, -6.0, 0.0),
		glm::vec3(  1.0, -5.0, 0.0),
		glm::vec3(  4.0, -1.0, 0.0),
		glm::vec3(  9.0,  2.0, 0.0),
		glm::vec3( 10.0,  2.0, 0.0),
		glm::vec3( 13.0,  3.0, 0.0),
		glm::vec3( 13.0,  7.0, 0.0),
		glm::vec3(  8.0,  7.0, 0.0),
		glm::vec3(  5.0,  5.0, 0.0),
		glm::vec3( -1.0,  3.0, 0.0),
		glm::vec3(-15.0,  4.0, 0.0),
		glm::vec3(-13.0, -2.0, 0.0),
	};

	gso::HermiteShape h = this->new_hermite(cps, name);
	return h;
}
