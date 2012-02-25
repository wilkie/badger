#include <badger/renderer.h>

#ifndef NO_GL
  #ifdef _WIN32
  #include <windows.h>
  #endif

  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include <math.h>
#include <stdio.h>
#include <glut.h>

Badger::Renderer::Renderer() {
}

void Badger::Renderer::bindTexture(unsigned int texture) {
  glBindTexture(GL_TEXTURE_2D, texture);
}

void Badger::Renderer::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glColor3d(1.0, 1.0, 1.0);
}

bool Badger::Renderer::initializeViewport(unsigned int width, unsigned int height) {
  glClearColor(1, 1, 1, 1);
  glClearDepth(1.0f);

  glViewport(0, 0, width, height);

  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

void Badger::Renderer::setProjection(unsigned int width, unsigned int height, double zoom) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, width, 0, height, -100, 100);
  glScaled(zoom, zoom, zoom);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Badger::Renderer::drawArrays(const float vertices[],
                                  const float normals[],
                                  const float colors[],
                                  const unsigned char indices[],
                                  unsigned int num) {

  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  glNormalPointer(GL_FLOAT, 0, normals);
  glColorPointer(3, GL_FLOAT, 0, colors);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glDrawElements(GL_QUADS, num, GL_UNSIGNED_BYTE, indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}

void Badger::Renderer::drawArrays(const float vertices[],
                                  const float normals[],
                                  const float colors[],
                                  const unsigned char indices[],
                                  const double texture_coords[],
                                  unsigned int num) {

  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glNormalPointer(GL_FLOAT, 0, normals);
  glColorPointer(3, GL_FLOAT, 0, colors);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_DOUBLE, 0, texture_coords);

  glDrawElements(GL_QUADS, num, GL_UNSIGNED_BYTE, indices);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}

void Badger::Renderer::drawSquare(float x, float y, float width, float height,
                                  double tu, double tv, double tw, double th) {
  // square ////////////////////////////////////////////////////////////////////
  //  v1------v0
  //  |       |
  //  |       |
  //  |       |
  //  v2------v3

  // vertex coords array
  static const float vertices[] = {
    1, 1, 0, -1, 1, 0, -1, -1, 0, 1, -1, 0}; // v0-v1-v2-v3

  // normal array
  static const float normals[] = {
    0, 0, 1,  0, 0, 1,  0,  0, 1, 0,  0, 1}; // v0-v1-v2-v3

  // color array
  static const float colors[] = {
    0.7f, 0.5f, 0, 0.7f, 0.5f, 0, 0.5f, 0.4f, 0, 0.7f, 0.4f, 0}; // v0-v1-v2-v3

  double texture_coords[] = {
    tu+tw, tv, tu, tv, tu, tv+th, tu+tw, tv+th}; // v0-v1-v2-v3

  static const unsigned char indices[] = {0, 1, 2, 3};

  glCullFace(GL_BACK);

  float half_width = width / 2.0f;
  float half_height = height / 2.0f;

  glPushMatrix();
  glTranslatef(x, y, 0);
  glScalef(half_width, half_height, 1.0);

  drawArrays(vertices, normals, colors, indices, texture_coords, 4);

  glPopMatrix();
}

void Badger::Renderer::drawCube(float x,     float y,      float z,
                                float width, float height, float depth) {
  // cube //////////////////////////////////////////////////////////////////////
  //    v6----- v5
  //   /|      /|
  //  v1------v0|
  //  | |     | |
  //  | |v7---|-|v4
  //  |/      |/
  //  v2------v3

  // vertex coords array
  static const float vertices[] = {
     1,  1,  1, -1,  1,  1, -1, -1,  1,  1, -1,  1,   // v0-v1-v2-v3
     1,  1,  1,  1, -1,  1,  1, -1, -1,  1,  1, -1,   // v0-v3-v4-v5
     1,  1,  1,  1,  1, -1, -1,  1, -1, -1,  1,  1,   // v0-v5-v6-v1
    -1,  1,  1, -1,  1, -1, -1, -1, -1, -1, -1,  1,   // v1-v6-v7-v2
    -1, -1, -1,  1, -1, -1,  1, -1,  1, -1, -1,  1,   // v7-v4-v3-v2
     1, -1, -1, -1, -1, -1, -1,  1, -1,  1,  1, -1};  // v4-v7-v6-v5

  // normal array
  static const float normals[] = {
     0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,   // v0-v1-v2-v3
     1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,   // v0-v3-v4-v5
     0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,   // v0-v5-v6-v1
    -1,  0,  0, -1,  0,  0, -1,  0,  0, -1,  0,  0,   // v1-v6-v7-v2
     0, -1,  0,  0, -1,  0,  0, -1,  0,  0, -1,  0,   // v7-v4-v3-v2
     0,  0, -1,  0,  0, -1,  0,  0, -1,  0,  0, -1};  // v4-v7-v6-v5

  // color array
  static const float colors[] = {
    0.7f, 0.5f, 0, 0.7f, 0.5f, 0, 0.52f, 0.4f, 0, 0.7f, 0.4f, 0, // v0-v1-v2-v3
    0.7f, 0.5f, 0, 0.7f, 0.5f, 0, 0.52f, 0.4f, 0, 0.7f, 0.4f, 0, // v0-v3-v4-v5
       1,    1, 1,    0,    1, 1,     0,    1, 0,    1,    1, 0, // v0-v5-v6-v1
    0.7f, 0.5f, 0, 0.7f, 0.5f, 0, 0.52f, 0.4f, 0, 0.7f, 0.4f, 0, // v1-v6-v7-v2
       0,    0, 0,    0,    0, 1,     1,    0, 1,    1,    0, 0, // v7-v4-v3-v2
    0.7f, 0.5f, 0, 0.7f, 0.5f, 0, 0.52f, 0.4f, 0, 0.7f, 0.4f, 0};// v4-v7-v6-v5

  static const unsigned char indices[] = {
     0,  1,  2,  3,
     4,  5,  6,  7,
     8,  9, 10, 11,
    12, 13, 14, 15,
    16, 17, 18, 19,
    20, 21, 22, 23};

  glCullFace(GL_BACK);

  float half_width = width / 2.0f;
  float half_height = height / 2.0f;
  float half_depth = depth / 2.0f;

  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(half_width, half_height, half_depth);

  drawArrays(vertices, normals, colors, indices, 24);

  glPopMatrix();
}
