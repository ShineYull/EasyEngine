#ifndef SPHEREGEOMETRY_H
#define SPHEREGEOMETRY_H

#include <geometry/BufferGeometry.h>

namespace Shine {
	class SphereGeometry : public BufferGeometry {
	public:
		SphereGeometry();
		SphereGeometry(float radius = 1.0f, float widthSegments = 8.0f, float heightSegments = 6.0f, float phiStart = 0.0f, float phiLength = PI * 2.0f, float thetaStart = 0.0f, float thetaLength = PI);
		~SphereGeometry();

	private:
	};
}

#endif  // SPHEREGEOMETRY_H
