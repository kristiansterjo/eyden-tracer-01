// //Kristian Sterjo & Albrit Bendo


#pragma once

#include "ICamera.h"
#include <math.h>

// Helpful cotang function
double cotan(double i) { return(1 / tan(i)); }

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_up(up)
	{	

		// --- PUT YOUR CODE HERE ---

		m_dir = normalize(dir);	

		//yAxis is the same vector as up but in the inverted direction
		m_yAxis = (-1)*m_up;

		//From the right hand rule the xaxis is the cross product of up and focus direction
		m_xAxis = m_dir.cross(m_up);

		//The situation is best represented by an isoscele rectangular triangle just as in the theoretical hw
		//Knowing this, the focus will be the cotangent of the half of the angle
		//Also getting the angle in degrees by dividing pi by 180
		m_focus = (float)1/tan ((angle/2) * (Pif / 180));
		
		m_aspect =  (float) resolution.width / resolution.height;

		
						
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---


		//Applying the code given in the slides
		float ndcx = (x + 0.5) / getResolution().width;  
		float ndcy = (y + 0.5) / getResolution().height;
		float sscx = (2 * ndcx - 1) * m_aspect;  
		float sscy = (2 * ndcy - 1);

		ray.org = m_pos;
		ray.dir =  m_dir * m_focus + sscx * m_xAxis + sscy * m_yAxis;
		
		
		//Here the numeric_limits<float>::max() function should be put 
		//but I was facing problems with it so I put it manually
		ray.t   = 340282e+38;

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};

