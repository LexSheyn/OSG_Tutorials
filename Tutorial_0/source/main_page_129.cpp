// Page:    129
// Chapter: 6
// Time for action – lighting the glider or not

// We will show the usage of the OVERRIDE and PROTECTED flags in the following short
// example. The root node will be set to OVERRIDE, in order to force all choldren to inherit
// its attribute or mode. Meanwhile, the choldren will try to change their inheritance with or
// without a PROTECTED flag, which will lead to different results.

#include "base.h"

#include <osg/PolygonMode>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    // Create two osg::MatrixTransform nodes and make them both share a glider
    // model. After all, we don't want to use the well-known cessna all the time. The glider
    // is small in size, so only a small distance is required for the setMatrix() method.

    //osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"glider.osg");
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> transform0 = new osg::MatrixTransform();

    transform0->setMatrix(osg::Matrix::translate(-0.5, 0.0f, 0.0f));
    transform0->addChild(model.get());

    osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform();

    transform1->setMatrix(osg::Matrix::translate(0.5f, 0.0f, 0.0f));
    transform1->addChild(model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(transform0);
    root->addChild(transform1);

    // Now we are going to set the rendering mode of each node's state sett. The
    // GL_LIGHTING mode is a famous OpenGL enumeration which can be used to
    // enable or disable global lighting of the scene. Note that OVERRIDE and
    // PROTECTED flags are set to root and transformation1 separately, along
    // with an ON or OFF switch value.

    osg::StateSet* stateSet0 = transform0->getOrCreateStateSet();
    osg::StateSet* stateSet1 = transform1->getOrCreateStateSet();
    osg::StateSet* rootStateSet = root->getOrCreateStateSet();

    stateSet0->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateSet1->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE);
    rootStateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}