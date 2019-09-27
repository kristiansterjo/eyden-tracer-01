// //Kristian Sterjo & Albrit Bendo

#pragma once
#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 * @param color Color of the primitive
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---

		//finding the intersections of the rays and the sphere
		//relating to the hw by finding the root/s of the ray and sphere equations
		float x1, x2;
		float var_a = ray.dir.dot(ray.dir);
		float var_b = 2 * ray.dir.dot(ray.org - m_center);
		float var_c = (ray.org - m_center).dot(ray.org - m_center) - m_radius*m_radius;


		//first the discriminant has to be calculated
		float d = var_b*var_b - 4*var_a*var_c;
		//There is an intersection iff discriminant >=0
		if(d < 0){
			return false;
		}

		 x1 = (-0.5) * (var_b - sqrt(d)) / var_a;
		 x2 = (-0.5) * (var_b + sqrt(d)) / var_a;

		if(x1 > x2){
			float kot = x1;
			x1 = x2;
			x2 = kot;
		}
		if( x1 < Epsilon || x1 > ray.t){
			x1 = x2;
			if(x1 < Epsilon || x1 > ray.t) return false;
		}


		ray.t = x1;
		return true;
		
	}
		
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};
