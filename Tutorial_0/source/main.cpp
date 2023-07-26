// Page:    245
// Chapter: 9
// Time for action – clicking and selecting geometries

// Our task this time is to implement a very common task in 3D software - clicking to select
// an object in the world and showing a selection box around the object. The bounding
// box of the selected geometry sould be good for representing a selection box, and the
// osg::ShapeDrawable class can quickly generate a simple box for display purposes.
// The osg::PolygonMode attribute will then make the rendering pipeline only draw the
// wireframe of the box, which helps to show the selection box as brackets. These are all we
// need to produce practical picking object functionalities.

#include "base.h"

#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osgUtil/LineSegmentIntersector>
#include <osgViewer/Viewer>

// The PickHandler will do everything required fro our task, including an
// intersection test of the mouse cursor and the scene graph, creating and returning
// the selection box node (the m_selectionBox variable in this example), and
// transforming the box around the selected object when pressing the mouse button.

class PickHandler : public osgGA::GUIEventHandler
{
public:

    void createSelectionBox()
    {
        osg::Box* box = new osg::Box(osg::Vec3(), 1.0f);

        osg::ShapeDrawable* boxDrawable = new osg::ShapeDrawable(box);

        osg::ref_ptr<osg::Geode> geode = new osg::Geode();

        geode->addDrawable(boxDrawable);

        m_switch = new osg::Switch();

        m_selectionBox = new osg::MatrixTransform();

        m_switch->addChild(m_selectionBox.get());
        
        m_selectionBox->setNodeMask(0x1);
        m_selectionBox->addChild(geode.get());

        osg::PolygonMode* polygonMode = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

        osg::StateSet* stateSet = m_selectionBox->getOrCreateStateSet();

        stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        stateSet->setAttributeAndModes(polygonMode);
    }

    osg::Node* getSelectionBox()
    {
        return m_switch;
    }

    // In the following method, we will allocate and return a valid selection box
    // node to the main function. There are several points to note here: firstly, the
    // osg::Box object will not be changed at runtime, but a parent transformation
    // node will be used and modified instead, for the reason of simplifying
    // operations; secondly, the GL_LIGHTING mode and the osg::PolygonMode
    // attribute should be used to make the selection box more natural; finally, there
    // is also a confusing setNodeMask() call, which will be explained later.
    osg::Node* getOrCreateSelectionBox()
    {
        if (!m_selectionBox)
        {
            osg::Box* box = new osg::Box(osg::Vec3(), 1.0f);

            osg::ShapeDrawable* boxDrawable = new osg::ShapeDrawable(box);

            osg::ref_ptr<osg::Geode> geode = new osg::Geode();

            geode->addDrawable(boxDrawable);

            m_selectionBox = new osg::MatrixTransform();
            
            m_selectionBox->setNodeMask(0x1);
            m_selectionBox->addChild(geode.get());

            osg::PolygonMode* polygonMode = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

            osg::StateSet* stateSet = m_selectionBox->getOrCreateStateSet();

            stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
            stateSet->setAttributeAndModes(polygonMode);
        }

        return m_selectionBox.get();
    }

    // We are going to strictly limit the occasional of picking scene objects to make
    // sure camera manipulator operations can work. It will only be called when
    // the user is holding the Ctrl key and releasing the left mouse button. After
    // that, we obtain the viewer by converting the osgGA::GUIActionAdapter
    // object, and create an intersection visitor to find a node that can possibly be
    // picked by the mouse cursor (be aware of the setTraversalMask() method here, which
    // will be introduced along with the setNodeMask() method).
    // Then the resulting drawable object and its parent node path can be used
    // to describe the world position and scale of the bounding selection box.
    virtual bool handle(const osgGA::GUIEventAdapter& eventAdapter, osgGA::GUIActionAdapter& actionAdapter) override
    {
        const osgGA::GUIEventAdapter::EventType eventType = eventAdapter.getEventType();
        const int32_t mouseButton                         = eventAdapter.getButton();
        const int32_t modKeyMask                          = eventAdapter.getModKeyMask();

        const bool b_buttonReleased = (eventType == osgGA::GUIEventAdapter::RELEASE);
        const bool b_leftButton     = (mouseButton == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON);
        const bool b_ctrlPressed    = (modKeyMask & osgGA::GUIEventAdapter::MODKEY_CTRL);

        if (!b_buttonReleased || !b_leftButton || !b_ctrlPressed)
        {
            return false;
        }

        m_switch->setValue(0, false);

        osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&actionAdapter);

        if (viewer)
        {
            const float32_t x = eventAdapter.getX();
            const float32_t y = eventAdapter.getY();

            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, x, y);

            osgUtil::IntersectionVisitor intersectionVisitor(intersector.get());

            intersectionVisitor.setTraversalMask(~0x1);

            viewer->getCamera()->accept(intersectionVisitor);

            if (intersector->containsIntersections())
            {
                osgUtil::LineSegmentIntersector::Intersections& intersections = intersector->getIntersections();

                const osgUtil::LineSegmentIntersector::Intersection& intersection = *(intersections.begin());

                const osg::BoundingBox boundingBox = intersection.drawable->getBoundingBox();

                const osg::Matrix localToWorldMatrix = osg::computeLocalToWorld(intersection.nodePath);

                const osg::Vec3 worldCenter = boundingBox.center() * localToWorldMatrix;

                const float32_t x = boundingBox.xMax() - boundingBox.xMin();
                const float32_t y = boundingBox.yMax() - boundingBox.yMin();
                const float32_t z = boundingBox.zMax() - boundingBox.zMin();

                const osg::Matrix scale       = osg::Matrix::scale(x, y, z);
                const osg::Matrix translation = osg::Matrix::translate(worldCenter);

                const osg::Matrix worldMatrix = scale * translation;

                m_selectionBox->setMatrix(worldMatrix);

                m_switch->setValue(0, true);
            }
        }

        return false;
    }

private:
    osg::ref_ptr<osg::Switch>          m_switch;
    osg::ref_ptr<osg::MatrixTransform> m_selectionBox;
};

int32_t main(int32_t argc, char** argv)
{
    // We will first construct the scene graph by adding two models to the root node.

    osg::ref_ptr<osg::Node> model0 = osgDB::readNodeFile(MODEL_DIR"cessna.osg");
    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile(MODEL_DIR"cow.osg");

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(model0.get());
    root->addChild(model1.get());

    // We create the picking handler, and add the value of getSelectionBox()
    // to the root node, too. This will make the selection box visible in the scene graph.

    osg::ref_ptr<PickHandler> pickHandler = new PickHandler();

    pickHandler->createSelectionBox();

    root->addChild(pickHandler->getSelectionBox());

    osgViewer::Viewer viewer;

    viewer.setUpViewInWindow(0, 0, 1920, 1080, 0);
    viewer.setSceneData(root.get());
    viewer.addEventHandler(pickHandler.get());

    return viewer.run();
}