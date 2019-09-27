// Kristian Sterjo & Albrit Bendo
// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition

#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 * @param color Color of the primitive
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---

		//also getting reference from the webpage that the TA sent
		//us via e-mail we first calculate the normal(=N) of the triangle

		Vec3f N = (m_b-m_a).cross(m_c-m_a);

		//conditioning the parallel case as before
		if(N.dot(ray.dir) == 0){
			return false;
		}
		
		//finding first the edge vectors so that later we can calculate the lambda values
		Vec3f edge_ab = (m_b-ray.org).cross(m_a-ray.org);
		Vec3f edge_bc = (m_c-ray.org).cross(m_b-ray.org);
		Vec3f edge_ca = (m_a-ray.org).cross(m_c-ray.org);

		float l1  = edge_ab.dot(ray.dir) /((edge_ca + edge_ab + edge_bc).dot(ray.dir));
		float l2  = edge_bc.dot(ray.dir) /((edge_ca + edge_ab + edge_bc).dot(ray.dir));
		float l3  = edge_ca.dot(ray.dir) /((edge_ca + edge_ab + edge_bc).dot(ray.dir));

		if(l1 < 0 || l2 < 0 || l3 < 0){
			return false;
		}
		

		float t = ((-1)*N.dot(ray.org - m_a)) / N.dot(ray.dir);
		if(t < Epsilon || t > ray.t)
			return false;

		ray.t = t;
		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};

