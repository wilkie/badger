#ifndef BADGER_RENDERER_H
#define BADGER_RENDERER_H

namespace Badger {
  class Renderer {
  public:
    Renderer();
    bool initializeViewport(unsigned int width, unsigned int height);
    void setProjection(unsigned int width, unsigned int height, double zoom);
    void drawSquare(double x, double y,
                    double width, double height,
                    double tu, double tv,
                    double tw, double th,
                    double depth);
    void drawCube(double x, double y,
                  double z, double width,
                  double height, double depth);
    void drawArrays(const double vertices[],
                    const double normals[],
                    const unsigned char indices[],
                    unsigned int num);
    void drawArrays(const double vertices[],
                    const double normals[],
                    const unsigned char indices[],
                    const double texture_coords[],
                    unsigned int num);
    void drawArrays(const double vertices[],
                    const double normals[],
                    const double colors[],
                    const unsigned char indices[],
                    unsigned int num);
    void drawArrays(const double vertices[],
                    const double normals[],
                    const double colors[],
                    const unsigned char indices[],
                    const double texture_coords[],
                    unsigned int num);
    void clear();
    void bindTexture(unsigned int texture);
  
  private:
  };
}

#endif
