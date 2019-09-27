//Kristian Sterjo & Albrit Bendo
// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief The Plane Geaometrical Primitive class
 */
class CPrimPlane : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param origin Point on the plane
	 * @param normal Normal to the plane
	 */
	CPrimPlane(Vec3f origin, Vec3f normal)
		: CPrim()
		, m_normal(normal)
		, m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		if(ray.dir.dot(m_normal)==0){
			//the case of dividing by 0
			exit(2);
		}

		float t = ((m_origin - ray.org).dot(m_normal)) / (ray.dir.dot(m_normal));
		if(t<Epsilon || t > ray.t){
			//listing all cases for which there is no intersection
			return false;
		}

		else{
			ray.t = t;
			return true;
		}
	}
	
	
private:
	Vec3f m_normal;	///< Point on the plane
	Vec3f m_origin;	///< Normal to the plane
};

// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
