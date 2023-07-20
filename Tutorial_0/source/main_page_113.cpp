// Page:   113
// Capter: 5
// Time for action – animating the switch node

#include "base.h"

#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

// Declare the AnimationSwitch class. This wukk be deruved from the osg::Switch
// class to taje advantage of the setValue() method. We also make use of an
// OSG macro definition, META_Node, which is a little similar to the META_Object
// introduced in the last chapter, to define basic properties (library and clas name)
// of a node.

class AnimationSwitch : public osg::Switch
{
public:
    AnimationSwitch()
    : osg::Switch()
    , m_count(0)
    {}
    AnimationSwitch(const AnimationSwitch& copy, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY)
    : osg::Switch(copy, copyOp)
    , m_count(copy.m_count)
    {}

    META_Node(osg, AnimationSwitch);

    virtual void traverse(osg::NodeVisitor& nodeVisitor) override
    {
        if (!((++m_count)%60))
        {
            this->setValue(0, !this->getValue(0));
            this->setValue(1, !this->getValue(1));
        }

        osg::Switch::traverse(nodeVisitor);
    }

private:
    uint32_t m_count;
};

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model0 = osgDB::readNodeFile(MODEL_DIR"cessna.osg");
    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile(MODEL_DIR"cessnafire.osg");

    osg::ref_ptr<AnimationSwitch> root = new AnimationSwitch();

    root->addChild(model0.get(), true);
    root->addChild(model1.get(), false);

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}