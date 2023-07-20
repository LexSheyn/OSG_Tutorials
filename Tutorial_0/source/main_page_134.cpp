// Page:    134
// Chapter: 6
// Time for action – applying simple fog to models

// We will tage the fog effect as an ideal example of working with various rendering attributes
// and modes. OpenGL accepts one linear and two exponential for equations, which are
// supported by the osg::For class as well.

#include "base.h"

#include <osg/Fog>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    // We would like to first create the for attribute. Using the linear mode, we have to
    // set the near and far distances by using setStart() and setEnd() methods.
    // We will also set the for color, in order to generate a dust fog-like effect.

    osg::ref_ptr<osg::Fog> fog = new osg::Fog();

    fog->setMode(osg::Fog::LINEAR);
    fog->setStart(500.0f);
    fog->setEnd(2500.0f);
    fog->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));

    // We are going to load an example terrain model named lz.osg, which can
    // be located in the data directory indicated by the environment variable
    // OSG_FILE_PATH. The only work to do is to set the fog attribute and the
    // associated mode to the node's state set.

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"lz.osg");

    osg::StateSet* stateSet = model->getOrCreateStateSet();

    stateSet->setAttributeAndModes(fog.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(model.get());

    return viewer.run();
}