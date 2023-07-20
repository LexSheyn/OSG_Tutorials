// Page:   110
// Capter: 5
// Time for action – loading a model at runtime

// We are going to demonstrate the loading of a model file by using the osg::ProxyNode.
// The proxy will record the filename of the original model, and defer loading it until the viewer is
// running and sending corresponding requests.

#include "base.h"

#include <osg/ProxyNode>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::ProxyNode> root = new osg::ProxyNode();

    root->setFileName(0, MODEL_DIR"cessna.osg");

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}