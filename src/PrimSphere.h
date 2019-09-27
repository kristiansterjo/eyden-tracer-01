//Kristian Sterjo & Albrit Bendo
// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
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
	 */
	CPrimSphere(Vec3f center, float radius)
		: CPrim()
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---
		//applying the theoretical hw 1.2
		Vec3f v = ray.org - m_center;
		float var1 = ray.dir.dot(ray.dir);
		float var2 = 2*ray.dir.dot(v);
		float var3 = v.dot(v) - m_radius*m_radius;
		//the discriminant
		float d = var2*var2 - 4*var1*var3;
		//no solutions when there are no intersection
		if(d<0){
			return false;
		}
		
		float t = ((-1)*var2 - sqrt(d)/var1);
		if(t<Epsilon){
			t = (-1)*var2 + sqrt(d)/var1;
		}
		if(t>ray.t || t < Epsilon){
			return false;
		}

		//initializing ray.t only when intersects
		ray.t = t;

		return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

