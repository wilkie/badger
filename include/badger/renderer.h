#ifndef BADGER_RENDERER_H
#define BADGER_RENDERER_H

namespace Badger {
	class Renderer {
	public:
		Renderer();
		bool initializeViewport(unsigned int width, unsigned int height);
		void setProjection(unsigned int width, unsigned int height, 
			double rotation, double translationX, double translationZ, double zoom);
		void drawSquare(float x, float y, float width, float height);
		void drawCube(float x, float y, float z, float width, float height, float depth);
		void drawArrays(const float vertices[], const float normals[], const float colors[], const unsigned char indices[], unsigned int num);

		void clear();
	
	private:
	};
}

#endif
