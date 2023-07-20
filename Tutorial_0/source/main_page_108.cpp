// Page:   108
// Capter: 5
// Time for action – constructing a LOD Cessna

// We will create a discrete LOD node with a set of predefined objects to represent the
// sane nidel. These objects are used as child nodes of the osg::LOD node and displayed
// at different distances. We will use the internal polygon reduction technique class
// osgUtil::Simplifier to generate various detaled objects from an original model. You
// may also read low-polygon and high-polygon models from disk files.

#include "base.h"

#include <osg/LOD>
#include <osgDB/ReadFile>
#include <osgUtil/Simplifier>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> modelL0 = osgDB::readNodeFile(MODEL_DIR"cessna.osg");
    osg::ref_ptr<osg::Node> modelL1 = (osg::Node*)modelL0->clone(osg::CopyOp::DEEP_COPY_ALL);
    osg::ref_ptr<osg::Node> modelL2 = (osg::Node*)modelL0->clone(osg::CopyOp::DEEP_COPY_ALL);
    osg::ref_ptr<osg::Node> modelL3 = (osg::Node*)modelL0->clone(osg::CopyOp::DEEP_COPY_ALL);
    osg::ref_ptr<osg::Node> modelL4 = (osg::Node*)modelL0->clone(osg::CopyOp::DEEP_COPY_ALL);

    osgUtil::Simplifier simplifier;

    simplifier.setSampleRatio(0.8f);

    modelL1->accept(simplifier);

    simplifier.setSampleRatio(0.6f);

    modelL2->accept(simplifier);

    simplifier.setSampleRatio(0.4f);

    modelL3->accept(simplifier);

    simplifier.setSampleRatio(0.2f);

    modelL4->accept(simplifier);

    osg::ref_ptr<osg::LOD> root = new osg::LOD();

    root->addChild(modelL0.get(), 0.0f, 50.0f);
    root->addChild(modelL1.get(), 50.0f, 100.0f);
    root->addChild(modelL2.get(), 100.0f, 150.0f);
    root->addChild(modelL3.get(), 150.0f, 200.0f);
    root->addChild(modelL4.get(), 200.0f, FLT_MAX);

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}