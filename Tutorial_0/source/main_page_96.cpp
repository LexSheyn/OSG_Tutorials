// Page:   96
// Capter: 5
// Time for action – adding models to the scene graph

#include "coordinates.h"

#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    const float32_t latitude     = 41.9028f;
    const float32_t longitude    = 12.4964f;
    const float32_t altitude     = 0.0f;
    const float32_t sphereRadius = 1.0f;

    std::cout << "Polar point: \t[ " << latitude << "* " << longitude << "* " << altitude << " ]" << std::endl;

    osg::Vec3 cartesianPoint = polarCoordToCartesianCoord_OpenSceneGraph(latitude, longitude, altitude, sphereRadius);

    std::cout << "Cartesian point: \t[ " << cartesianPoint.x() << ' ' << cartesianPoint.y() << ' ' << cartesianPoint.z() << " ]" << std::endl;

    osg::ref_ptr<osg::Node> model0 = osgDB::readNodeFile(MODEL_DIR"cessna.osg");
    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile(MODEL_DIR"cow.osg");

    osg::ref_ptr<osg::Transform> transform = new osg::Transform();

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(model0.get());
    root->addChild(model1.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}