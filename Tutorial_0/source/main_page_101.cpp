// Page:   101
// Capter: 5
// Time for action – performing translations of child nodes

#include "base.h"

#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> transform0 = new osg::MatrixTransform();

    transform0->setMatrix(osg::Matrix::translate(-25.0f, 0.0f, 0.0f));
    transform0->addChild(model.get());

    osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform();
    
    transform1->setMatrix(osg::Matrix::translate(25.0f, 0.0f, 0.0f));
    transform1->addChild(model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(transform0.get());
    root->addChild(transform1.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}