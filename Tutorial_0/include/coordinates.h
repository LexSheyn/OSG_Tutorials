#include "base.h"

#include <osg/Matrix>
#include <osg/Vec3>

osg::Vec3 polarCoordToCartesianCoord_OpenSceneGraph(float32_t latitude, float32_t longitude, float32_t altitude, float32_t sphereRadius);
osg::Vec3 polarCoordToCartesianCoord_OpenGL(float32_t latitude, float32_t longitude, float32_t altitude, float32_t sphereRadius);