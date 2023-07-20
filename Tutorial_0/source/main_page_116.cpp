// Page:   116
// Capter: 5
// Have a go hero – creating a tracker node

#include "base.h"

#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

float32_t lerp(float32_t start, float32_t finish, float32_t ratio)
{
    return (finish * ratio) + (start * (1.0f - ratio));
}

class CustomTransform : public osg::PositionAttitudeTransform
{
public:
    CustomTransform()
    : osg::PositionAttitudeTransform ()
    {}

    CustomTransform(const CustomTransform& copy, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY)
    : osg::PositionAttitudeTransform (copy, copyOp)
    {}

    META_Node(osg, CustomTransform);

    virtual void traverse(osg::NodeVisitor& nodeVisitor) override
    {
        static float32_t x = 0.0f;
        static float32_t y = 0.0f;
        static float32_t z = 0.0f;

        x += 0.01f;
        y -= 0.01f;
        z -= 0.01f;

        const osg::Vec3 scale = this->getScale();
        const osg::Vec3 newScale = osg::Vec3(scale.x() + x, scale.y() + y, scale.z() + z);

        //this->setScale(newScale);

        this->setPosition(osg::Vec3(x, y, z));

        osg::PositionAttitudeTransform::traverse(nodeVisitor);
    }
};

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model0 = osgDB::readNodeFile(MODEL_DIR"cow.osg");
    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> matrixTransform0 = new osg::MatrixTransform();
    osg::ref_ptr<CustomTransform> matrixTransform1 = new CustomTransform();

    matrixTransform0->addChild(model1.get());
    matrixTransform0->setMatrix(osg::Matrix::translate(-30.0f, 0.0f, 0.0f));

    matrixTransform1->addChild(model0.get());

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(matrixTransform0);
    root->addChild(matrixTransform1);

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}