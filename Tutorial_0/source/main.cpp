// Page:    234
// Chapted: 9
// Time for action – driving the Cessna

// We have lernt how to change the transformation matrix of a model with the
// osg::MatrixTransform nodex. With the help of the osg::AnimationPath class and the
// osgAnimation namespace, we can event create animation effects on these transformable
// objects. But this is not enough for an interactive scene. Our further requirement is to control
// scene graph nodes with user input devices. Imagine that we have a submarine, a tank, or a
// familiar cessna in a modern warface game. It will be really exicting if we can simulate driving
// it with the keyboard, mouse, or event joysticks.

#include "base.h"

#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>

// TO DO

class KeyEventHandler : public osgGA::GUIEventHandler
{
public:

    KeyEventHandler()
    {}

    KeyEventHandler(const KeyEventHandler& copy, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY)
    : osgGA::GUIEventHandler(copy, copyOp)
    {}

    META_Object(test, KeyEventHandler);

    // osgGA::GUIEventHandler.

    virtual bool handle(osgGA::Event* event, osg::Object* object, osg::NodeVisitor* nodeVisitor) override
    {
        return osgGA::GUIEventHandler::handle(event, object, nodeVisitor);
    }

    virtual bool handle(const osgGA::GUIEventAdapter& eventAdapter, osgGA::GUIActionAdapter& actionAdapter, osg::Object* object, osg::NodeVisitor* nodeVisitor) override
    {
        return osgGA::GUIEventHandler::handle(eventAdapter, actionAdapter, object, nodeVisitor);
    }

    virtual bool handle(const osgGA::GUIEventAdapter& eventAdapter, osgGA::GUIActionAdapter& actionAdapter) override
    {
        return osgGA::GUIEventHandler::handle(eventAdapter, actionAdapter);
    }

protected:

    virtual ~KeyEventHandler()
    {}
};

int32_t main(int32_t argc, char** argv)
{
    return 0;
}