// Page:   112
// Capter: 5
// Have a go hero – working with the PagedLOD class

#include "base.h"

#include <osg/PagedLOD>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

struct LODNodeCreateInfo
{
    osg::Vec3        position;
    const osg::Vec2* ranges;
    const char**     filePaths;
    uint32_t         LODCount;
};

osg::Node* createLODNode(const LODNodeCreateInfo& LODNodeCreateInfo)
{
    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD();
    
    for (uint32_t i = 0; i < LODNodeCreateInfo.LODCount; ++i)
    {
        pagedLOD->setFileName(i, std::string(LODNodeCreateInfo.filePaths[i]));
        pagedLOD->setRange(i, LODNodeCreateInfo.ranges[i].x(), LODNodeCreateInfo.ranges[i].y());
    }

    osg::ref_ptr<osg::MatrixTransform> matrixTransform = new osg::MatrixTransform();

    matrixTransform->setMatrix(osg::Matrix::translate(LODNodeCreateInfo.position));
    matrixTransform->addChild(pagedLOD.get());

    return matrixTransform.release();
}

int32_t main(int32_t argc, char** argv)
{
    osg::Vec2 LODRanges[] = { osg::Vec2(0.0f, 100.0f), osg::Vec2(100.0f, 200.0f) };

    const char* filePaths[] = { MODEL_DIR"cessna.osg", MODEL_DIR"cow.osg" };

    LODNodeCreateInfo lodNodeCreateInfo;

    lodNodeCreateInfo.position  = osg::Vec3(0.0f, -20.0f, 0.0f);
    lodNodeCreateInfo.ranges    = LODRanges;
    lodNodeCreateInfo.filePaths = filePaths;
    lodNodeCreateInfo.LODCount  = 2;

    osg::ref_ptr<osg::Node> LODNode = createLODNode(lodNodeCreateInfo);

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(model.get());
    root->addChild(LODNode.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}