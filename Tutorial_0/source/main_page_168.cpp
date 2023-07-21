// Page:    168
// Chapter: 7
// Time for action – creating a HUD camera

// A head-up display (HUD) can render data without requiring users to look away from their
// usual viewpoints. It is widely used in 3D scenes, for displaying important 2D texts, computer
// game statistics, and flight and cockpit instruments. This time, we are going to design a
// HUD camera, which contains a model that should be placed in front of tohter scene objects
// at any time.

#include "base.h"

#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    // Two models are loaded from disk files. lz.osg is used as a demo terrain, and
    // glider.osg will be put under a HUD camera. Which means, it will always be visible to
    // viewers who are looking ahead; no matter other parts of the scene graph are
    // changing.

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"lz.osg");
    osg::ref_ptr<osg::Node> hud_model = osgDB::readNodeFile(MODEL_DIR"glider.osg");

    // The HUD camera and its choldren must be rendered after the regular scene
    // is finished being drawn on the screen. It will overwrite all present pixel data,
    // regardless of its location and depth. That is why we use GL_DEPTH_BUFFER_BIT to
    // clear the depth buffer. The GL_COLOR_BUFFER_BIT is not set here, to ensure that
    // the color buffer is correctly reserved.

    osg::ref_ptr<osg::Camera> camera = new osg::Camera();

    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);

    // The HUD camera should not be affected by the viewer or any other parent nodes,
    // so it needs to be changed to the absolute reference frame, and be set as a custom
    // fixed view matrix. The glider is also added to the camera node, used as content
    // to be displayed.

    camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    camera->setViewMatrixAsLookAt(osg::Vec3(0.0f, -5.0f, 5.0f), osg::Vec3(), osg::Vec3(0.0f, 1.0f, 1.0f));
    camera->addChild(hud_model.get());

    // We will add HUD camera, along with a regular loaded model, the the root node.

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(model.get());
    root->addChild(camera.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}