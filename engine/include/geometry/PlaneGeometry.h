#ifndef PLANEGEOMETRY_H
#define PLANEGEOMETRY_H

#include <geometry/BufferGeometry.h>

namespace Shine {
	class PlaneGeometry : public BufferGeometry {
	public:
		PlaneGeometry();
		PlaneGeometry(float width = 1.0, float height = 1.0, float wSegment = 1.0, float hSegment = 1.0);
		~PlaneGeometry();
	};
}

#endif  // PLANEGEOMETRY_H