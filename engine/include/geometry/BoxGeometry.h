#ifndef BOXGEOMETRY_H
#define BOXGEOMETRY_H

#include <geometry/BufferGeometry.h>

namespace Shine {
	class BoxGeometry : public BufferGeometry {
	public:
		float width;
		float height;
		float widthSegments;
		float heightSegments;
		float depthSegments;

		BoxGeometry();
		BoxGeometry(float width = 1.0f, float height = 1.0f, float depth = 1.0, float widthSegments = 1.0f, float heightSegments = 1.0f, float depthSegments = 1.0f);
		~BoxGeometry();

	private:
		int numberOfVertices = 0;
		float groupStart = 0;

		/**
		 * vec3(u, v, w)
		 * x y z | 0, 1, 2
		 * z y x | 2, 1, 0
		 * x z y | 0, 2, 1
		 */
		void buildPlane(int u, int v, int w, float udir, float vdir, float width, float height, float depth, float gridX, float gridY, float materialIndex);
	};
}

#endif  // BOXGEOMETRY_H