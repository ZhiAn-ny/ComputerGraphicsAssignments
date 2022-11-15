#ifndef HERMITE_CURVES_H_
#define HERMITE_CURVES_H_

#include "scene_object.h"
#include "colors.h"

namespace gso {

	class HermiteShape : public SceneObject {
		std::vector<glm::vec3> cp_ = {};
		std::vector<glm::vec3> derivates_ = {};

		static float phi0(float t);
 		static float phi1(float t);
 		static float psi0(float t);
 		static float psi1(float t);
 
 		float dx(int i, float* t, float tens, float bias, float cont);
 		float dy(int i, float* t, float tens, float bias, float cont);
 		float DX(int i, float* t);
 		float DY(int i, float* t);

 	    void interpolation(float* t);

		// Requires minimum 2 control points
		void build_curve();

	public:
		HermiteShape();
 		HermiteShape(std::string name);
 		~HermiteShape();

		void add_control_point(glm::vec3 cp);

	};

}

#endif // !HERMITE_CURVES_H_
