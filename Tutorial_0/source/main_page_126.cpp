// Page:   126
// Capter: 6
// Time for action – setting polygon modes of different nodes

// We are going to select the polygon raterization mode of a loaded model. The
// osg::PolygonMode class, which is derived from the osg::StateAttribute base class,
// will be used to achieve this goal. It simply encapsulates OpenGL's glPolygonMode() function and implements interfaces for specifying face and drawing mode parameters, and
// thus changes the final rasterization of the attached node.

#include "base.h"

#include <osg/PolygonMode>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

// We will work on the bases of the transformation example in the last chapter. We
// create two osg::MatrixTrnsform nodes and make them share the same
// loaded cessna model. The two transformation nodes are placed at different
// positions in the 3D world, which will display two cessna models as the result.

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> transform0 = new osg::MatrixTransform();

    transform0->setMatrix(osg::Matrix::translate(-25.0f, 0.0f, 0.0f));
    transform0->addChild(model.get());

    osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform();

    transform1->setMatrix(osg::Matrix::translate(25.0f, 0.0f, 0.0f));
    transform1->addChild(model.get());

    // Now, we wull add an osg::PolygonMode rendering attrubute to the associated
    // state set of the node transform0, It has a setMode() method which
    // accepts two parameters: the face that the mode applied to, and the mode should
    // be in which polygons will be rasterized.

    osg::ref_ptr<osg::PolygonMode> polygonMode = new osg::PolygonMode();

    polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

    osg::StateSet* stateSet0 = transform0->getOrCreateStateSet();

    stateSet0->setAttribute(polygonMode.get());

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(transform0.get());
    root->addChild(transform1.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}