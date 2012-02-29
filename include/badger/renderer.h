#ifndef BADGER_RENDERER_H
#define BADGER_RENDERER_H

namespace Badger {
  class Renderer {
  public:
    Renderer();
    bool initializeViewport(unsigned int width, unsigned int height);
    void setProjection(unsigned int width, unsigned int height, double zoom);
    void drawSquare(float x, float y, float width, float height, double tu, double tv, double tw, double th);
    void drawCube(float x, float y, float z, float width, float height, float depth);
    void drawArrays(const float vertices[],
                    const float normals[],
                    const unsigned char indices[],
                    unsigned int num);
    void drawArrays(const float vertices[],
                    const float normals[],
                    const unsigned char indices[],
                    const double texture_coords[],
                    unsigned int num);
    void drawArrays(const float vertices[],
                    const float normals[],
                    const float colors[],
                    const unsigned char indices[],
                    unsigned int num);
    void drawArrays(const float vertices[],
                    const float normals[],
                    const float colors[],
                    const unsigned char indices[],
                    const double texture_coords[],
                    unsigned int num);
    void clear();
    void bindTexture(unsigned int texture);
  
  private:
  };
}

#endif
