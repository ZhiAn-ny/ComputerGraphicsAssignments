#include "hermite.h"

gso::HermiteShape::HermiteShape() {}

gso::HermiteShape::HermiteShape(std::string name)
{
	this->name_ = name;
}

gso::HermiteShape::~HermiteShape() {}


float gso::HermiteShape::phi0(float t)
{
	return 2.0 * pow(t, 3) - 3.0 * pow(t, 2) + 1;
}

float gso::HermiteShape::phi1(float t)
{
	return pow(t, 3) - 2.0 * pow(t, 2) + t;
}

float gso::HermiteShape::psi0(float t)
{
	return -2.0 * pow(t, 3) + 3.0 * pow(t, 2);
}

float gso::HermiteShape::psi1(float t)
{
	return pow(t, 3) - pow(t, 2);
}

float gso::HermiteShape::dx(int i, float* t, float T, float B, float C)
{
	if (i == 0) 
		return 0.5 * (1 - T) * (1 - B) * (1 - C) *
		(this->cp_[i+1].x - this->cp_[i].x) / (t[i+1] - t[i]);

	if (i == this->cp_.size() - 1)
		return 0.5 * (1 - T) * (1 - B) * (1 - C) *
		(this->cp_[i].x - this->cp_[i-1].x) / (t[i] - t[i-1]);

	if (i % 2 == 0)
		return  0.5 * (1 - T) * (1 + B) * (1 + C) *
		(this->cp_[i].x - this->cp_[i-1].x) / (t[i] - t[i-1])
		+ 0.5 * (1 - T) * (1 - B) * (1 - C) * 
		(this->cp_[i+1].x - this->cp_[i].x) / (t[i+1] - t[i]);

	return  0.5 * (1 - T) * (1 + B) * (1 - C) *
		(this->cp_[i].x - this->cp_[i - 1].x) / (t[i] - t[i - 1])
		+ 0.5 * (1 - T) * (1 - B) * (1 + C) *
		(this->cp_[i + 1].x - this->cp_[i].x) / (t[i + 1] - t[i]);
}

float gso::HermiteShape::dy(int i, float* t, float T, float B, float C)
{
	if (i == 0)
		return 0.5 * (1 - T) * (1 - B) * (1 - C) *
		(this->cp_[i + 1].y - this->cp_[i].y) / (t[i + 1] - t[i]);

	if (i == this->cp_.size() - 1)
		return 0.5 * (1 - T) * (1 - B) * (1 - C) *
		(this->cp_[i].y - this->cp_[i - 1].y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1 - T) * (1 + B) * (1 + C) *
		(this->cp_[i].y - this->cp_[i - 1].y) / (t[i] - t[i - 1])
		+ 0.5 * (1 - T) * (1 - B) * (1 - C) *
		(this->cp_[i + 1].y - this->cp_[i].y) / (t[i + 1] - t[i]);

	return  0.5 * (1 - T) * (1 + B) * (1 - C) *
		(this->cp_[i].y - this->cp_[i - 1].y) / (t[i] - t[i - 1])
		+ 0.5 * (1 - T) * (1 - B) * (1 + C) *
		(this->cp_[i + 1].y - this->cp_[i].y) / (t[i + 1] - t[i]);
}

float gso::HermiteShape::DX(int i, float* t)
{
	float T, B, C;
	T = B = C = 0;

	if (this->derivates_[i].x != 0)
		return this->derivates_[i].x;

	if (this->tbc_.size() == 0)
		return dx(i, t, T, B, C);

	return dx(i, t, this->tbc_[i].x, this->tbc_[i].y, this->tbc_[i].z);



	//if (this->derivates_[i].x == 0) {
	//	if (this->tbc_.size() == this->derivates_.size()) {
	//		return dx(i, t, T, B, C);
	//	}
	//	return dx(i, t, T, B, C);
	//}

	//return this->derivates_[i].x;
}

float gso::HermiteShape::DY(int i, float* t)
{
	float T, B, C;
	T = B = C = 0;

	if (this->derivates_[i].y != 0)
		return this->derivates_[i].y;
		
	if (this->tbc_.size() == 0)
		return dy(i, t, T, B, C);

	return dy(i, t, this->tbc_[i].x, this->tbc_[i].y, this->tbc_[i].z);
}

void gso::HermiteShape::interpolation(float* t)
{
	float tens = 0, bias = 0, cont = 0;
	float x, y;

	float pval = 140;
	float tg_step = 1.0 / (pval - 1);

	float tg_map, amp; 
	int i = 0, is = 0;

	this->vertices_.clear();
	this->colors_.clear();

	// Add central vertex
	this->add_vertex(glm::vec3(0.0), color::white);

	for (float tg = 0; tg <= 1; tg += tg_step) {
		// Locate interval
		if (tg > t[is + 1]) is++;

		amp = t[is + 1] - t[is];
		tg_map = (tg - t[is]) / amp;

		x = this->cp_[is].x * phi0(tg_map) + DX(is, t) * phi1(tg_map) * amp + this->cp_[is + 1].x * psi0(tg_map) + DX(is + 1, t) * psi1(tg_map) * amp;
		y = this->cp_[is].y * phi0(tg_map) + DY(is, t) * phi1(tg_map) * amp + this->cp_[is + 1].y * psi0(tg_map) + DY(is + 1, t) * psi1(tg_map) * amp;

		this->add_vertex(glm::vec3(x, y, 0.0), color::green);
	}
}

void gso::HermiteShape::build_curve()
{
	if (this->cp_.size() < 2) return;

	// Create even distributed points in int[0,1]
	float* t = new float[this->cp_.size()];
	float step = 1.0 / (this->cp_.size() - 1);

	for (int i = 0; i < this->cp_.size(); i++) {
		t[i] = (float)i * step;
	}

	this->interpolation(t);
}

void gso::HermiteShape::add_control_point(glm::vec3 cp)
{
	this->cp_.push_back(cp);
	this->colors_.push_back(color::white);
	this->derivates_.push_back(glm::vec3(0.0));

	this->build_curve();
	this->bind();
}

void gso::HermiteShape::add_control_point(glm::vec3 cp, glm::vec3 tbc)
{
	this->cp_.push_back(cp);
	this->colors_.push_back(color::white);
	this->derivates_.push_back(glm::vec3(0.0));
	this->tbc_.push_back(tbc);

	this->build_curve();
	this->bind();
}
