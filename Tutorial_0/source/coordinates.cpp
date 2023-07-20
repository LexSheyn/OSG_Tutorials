#include "coordinates.h"

osg::Vec3 polarCoordToCartesianCoord_OpenSceneGraph(float32_t latitude, float32_t longitude, float32_t altitude, float32_t sphereRadius)
{
    const osg::Vec3 point;

    const osg::Vec3 axisX(1.0f, 0.0f, 0.0f);
    const osg::Vec3 axisZ(0.0f, 0.0f, 1.0f);

    const osg::Matrix translation       = osg::Matrix::translate(0.0f, sphereRadius + altitude, 0.0f);
    const osg::Matrix rotationLatitude  = osg::Matrix::rotate(latitude, axisX);
    const osg::Matrix rotationLongitude = osg::Matrix::rotate(longitude, axisZ);

    const osg::Vec3 pointInSpace = point * translation * rotationLatitude * rotationLongitude;

    return pointInSpace;
}

osg::Vec3 polarCoordToCartesianCoord_OpenGL(float32_t latitude, float32_t longitude, float32_t altitude, float32_t sphereRadius)
{
    const osg::Vec3 point;

    const osg::Vec3 axisX(1.0f, 0.0f, 0.0f);
    const osg::Vec3 axisY(0.0f, 1.0f, 0.0f);

    const osg::Matrix translation       = osg::Matrix::translate(0.0f, 0.0f, sphereRadius + altitude);
    const osg::Matrix rotationLatitude  = osg::Matrix::rotate(latitude, axisX);
    const osg::Matrix rotationLongitude = osg::Matrix::rotate(longitude, axisY);

    const osg::Vec3 pointInSpace = point * translation * rotationLatitude * rotationLongitude;

    return pointInSpace;
}