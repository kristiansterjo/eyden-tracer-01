//Kristian Sterjo & Albrit Bendo

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
	 * @param color Color of the primitive
	 */
	CPrimPlane(Vec3f color, Vec3f origin, Vec3f normal)
		: CPrim(color)
		, m_normal(normal)
		, m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray& ray) override
	{	
		// --- PUT YOUR CODE HERE ---

		float aux1 = m_origin.dot(m_normal)-ray.org.dot(m_normal);
		float aux2 = ray.dir.dot(m_normal);
		float t;
		
		//the value of t is found iff the ray is not parallel to the plane
		//otherwise it return false 
		if(m_normal.dot(ray.dir) != 0){
			t = (aux1/aux2);
		}
		else{ 
			return false;
		}
		
		if(t<Epsilon || t>ray.t){
		 	return false;
		}
		
		ray.t = t;
		return true;
	}
	
	
private:
	Vec3f m_normal;	///< Normal on the plane
	Vec3f m_origin;	///< Point to the plane
};