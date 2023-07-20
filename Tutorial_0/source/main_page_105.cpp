// Page:   105
// Capter: 5
// Time for action – switching between the normal and damaged Cessna

#include "base.h"

#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model0 = osgDB::readNodeFile(MODEL_DIR"cessna.osg");
    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile(MODEL_DIR"cessnafire.osg");

    osg::ref_ptr<osg::Switch> root = new osg::Switch();

    root->addChild(model0.get(), false);
    root->addChild(model1.get(), true);

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());\

    return viewer.run();
}