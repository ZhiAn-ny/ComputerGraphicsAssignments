#include "ShapeFactory.h"

ShapeFactory::ShapeFactory()
{
	this->heartCounter = 0;
	this->butterflyCounter = 0;
	this->circleCounter = 0;
}

ShapeFactory::~ShapeFactory()
{
}

gso::SceneObject ShapeFactory::getShape(float centerX, float centerY,
								   float rayX, float rayY,
								   float (*xFunc)(float, float, float),
								   float (*yFunc)(float, float, float))
{
	gso::SceneObject fig = {};
	int index;
	float step;
	float theta, x, y;

	fig.nTriangles = 180;
	step = (2 * PI) / fig.nTriangles;

	// Add central vertex to the figure
	fig.add_vertex(glm::vec3(centerX, centerY, 0.0), color::cyan);

	// Add all the other vertices on the perimeter
	for (index = 0; index <= fig.nTriangles; index++)
	{
		theta = (float)index * step;
		x = xFunc(centerX, rayX, theta);
		y = yFunc(centerY, rayY, theta);

		fig.add_vertex(vec3(x, y, 0.0), color::cyan);
	}
	fig.nVertices = fig.vertices_.size();

	// set center as reference for object's position
	fig.pos_ = fig.vertices_[0];
	fig.Model = mat4(1.0);
	return fig;
}

void ShapeFactory::setColor(gso::SceneObject* fig, vec4 center, vec4(*colorFunc)(gso::SceneObject, int))
{
	int index = 0;

	fig->colors_[index] = center;

	// Add all the other vertices on the perimeter
	for (index = 1; index < fig->colors_.size(); index++)
	{
		fig->colors_[index] = colorFunc(*fig, index);
	}
}

void ShapeFactory::setCorners(gso::SceneObject* fig)
{
	vec3 lastVertex = fig->vertices_[fig->vertices_.size() - 1];

	if (lastVertex.x <= fig->bottomLeft.x && lastVertex.y <= fig->bottomLeft.y)
	{
		fig->bottomLeft = lastVertex;
	}
	else if (lastVertex.x >= fig->topRight.x && lastVertex.y >= fig->topRight.y)
	{
		fig->topRight = lastVertex;
	}
}

gso::SceneObject ShapeFactory::getHeart(float centerX, float centerY, float rayX, float rayY)
{
	vec4 darkYellow = vec4(255.0 / 255.0, 75.0 / 255.0, 0.0, 1.0);
	gso::SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (16 * pow(sin(t), 3)) / 16);},
		[](float y, float r, float t) {return y + r * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16);});

	fig.name_ = "heart_";
	fig.name_ += std::to_string(this->heartCounter);

	this->setColor(&fig, darkYellow,
		[](gso::SceneObject f, int i) {return vec4(1.0, 204.0 / 255.0, 0.0, 1.0);});

	this->heartCounter++;
	return fig;
}

gso::SceneObject ShapeFactory::getButterfly(float centerX, float centerY, float rayX, float rayY)
{
	vec4 darkOrange = vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0);
	gso::SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); },
		[](float y, float r, float t) {return (float)(y + r * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); });

	fig.name_ = "butterfly_";
	fig.name_ += std::to_string(this->butterflyCounter);

	this->setColor(&fig, darkOrange,
		[](gso::SceneObject f, int i) {return vec4(1.0, 0.0, 0.0, 0.0); });

	this->butterflyCounter++;
	return fig;
}

gso::SceneObject ShapeFactory::getCircle(float centerX, float centerY, float rayX, float rayY)
{
	vec4 color = vec4(0.0, 75 / 255, 1, 1);
	gso::SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * cos(t)); },
		[](float y, float r, float t) {return (float)(y + r * sin(t)); });

	fig.name_ = "circle_";
	fig.name_ += std::to_string(this->circleCounter);

	this->setColor(&fig, color,
		[](gso::SceneObject f, int i) {return vec4(0, 125/255.0, 1.0, 1.0); });

	this->circleCounter++;
	return fig;
}
