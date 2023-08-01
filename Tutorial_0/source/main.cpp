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

// Our task is to take control of cessna model with some keys. To handle these user
// events, we have to declare a ModelController class, which is derived from the
// osgGA::GUIEventHandler base class, and override the handle() method to
// make sure that all user events are pressed in as an osgGA::GUIEventAdapter
// osbject. The model pointer is also included in the handler class, otherwise
// there is no way to tell which model is going to be controlled.

class ModelController : public osgGA::GUIEventHandler
{
public:

    ModelController()
    {}

    void setTransform(osg::MatrixTransform* transform)
    {
        m_transform = transform;
    }

    const osg::MatrixTransform* getTransform() const
    {
        return m_transform.get();
    }

    // In the implementation of the handle() method, we will modify the Euler
    // angles of the member variable m_transform, which can be a transformation node
    // reresenting a cessna or other models. The character keys W, S, A, and D can
    // easily describe the heading and pitch rotations of the aircraft via a common
    // KEYDOWN event. Of course, function keys and navigation keys, including
    // KEY_Left, KEY_Right, and so on, are also available for use here.
    virtual bool handle(const osgGA::GUIEventAdapter& eventAdapter, osgGA::GUIActionAdapter& actionAdapter) override
    {
        osg::Matrix matrix = m_transform->getMatrix();

        const osgGA::GUIEventAdapter::EventType eventType = eventAdapter.getEventType();

        if (eventType == osgGA::GUIEventAdapter::KEYDOWN)
        {
            const int32_t key = eventAdapter.getKey();

            if (key == 'w' || key == 'W')
            {
                matrix *= osg::Matrix::rotate(-0.1f, osg::X_AXIS);
            }

            if (key == 's' || key == 'S')
            {
                matrix *= osg::Matrix::rotate(0.1f, osg::X_AXIS);
            }

            if (key == 'a' || key == 'A')
            {
                matrix *= osg::Matrix::rotate(-0.1f, osg::Z_AXIS);
            }

            if (key == 'd' || key == 'D')
            {
                matrix *= osg::Matrix::rotate(0.1f, osg::Z_AXIS);
            }

            m_transform->setMatrix(matrix);
        }
        
        return false;
    }

protected:

    virtual ~ModelController() override
    {}

    osg::ref_ptr<osg::MatrixTransform> m_transform;
};

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> matrixTransform = new osg::MatrixTransform();

    matrixTransform->addChild(model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(matrixTransform.get());

    osg::ref_ptr<ModelController> modelController = new ModelController();

    modelController->setTransform(matrixTransform.get());

    // We don's want the camera manipulator to work in this example, because it may also
    // affect the model-view matrix of the viewer when using keyboard and mouse,
    // and confuse the result of handling GUI events. Therefore, in addition to adding
    // the created event handler, we will prevent the main camera from receiving any
    // user event with the setAllowEventFocus() method, and set a suitable view
    // matrix by ourselves (because manipulator can't contact the camera now).

    osgViewer::Viewer viewer;

    viewer.setUpViewInWindow(0, 0, 1920, 1080, 0);
    viewer.addEventHandler(modelController.get());

    osg::Camera* camera = viewer.getCamera();

    camera->setViewMatrixAsLookAt(osg::Vec3(0.0f, -100.0f, 0.0f), osg::Vec3(), osg::Z_AXIS);
    camera->setAllowEventFocus(false);

    viewer.setSceneData(root.get());

    return viewer.run();
}