// Page:    172
// Chapter: 7
// Time for action – customizing the simulation loop

// We are already very familiar with the run() method of the osgViewer::Viewer class. It
// was used many timer to start a default simulation loop that loads the scene graph into the
// viewer and performs update, cull, and draw traversals on each frame.
//
// But what does the run() method actually do? Is it possible to add some pre- and
// post-frame events for certain purposed? In this example, we are going to customize the
// simulation loop with a C++ while statement, as well as display the frame number after
// advancing one frame at a time.
//
// Note that, the customized sumulation loop cannot benefit from the on-demand rendering
// scheme and the maximum frame rate setting. They are only available when using the
// run() method.

#include "base.h"

#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>

#include <iostream>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"lz.osg");

    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator();

    osgViewer::Viewer viewer;

    viewer.setUpViewInWindow(0, 0, 1920, 1080, 0);
    viewer.setSceneData(model.get());

    // We have to set a manipulator to hte viewer; otherwise we will be unable to
    // navigate the scene, including zoom, pan, orbit, and other controlling operations.
    // Here, a new trakcball manipulator is set to the viewer. It allows the user to
    // click and drap a point on the screen, having the object rotate to follow it. The
    // osgGA::TrackballManipulator is the default manipulator used internally in
    // the run() method.

    viewer.setCameraManipulator(manipulator.get());

    // We then run the viewer in a while loop. Its condition is tested every time to see if
    // the viewer is finished, by using the done() method. The body of the loop includes
    // the frame() method, which executes one frame to update, cull, and render the\
    // scene graph, and std::cout statement to ouptut the current frame nubmer.

    while (!viewer.done())
    {
        viewer.frame();

        osg::FrameStamp* frameStamp = viewer.getFrameStamp();

        std::cout << "Frame number: \t"    << frameStamp->getFrameNumber() << '\n';
        std::cout << "Reference time: \t"  << frameStamp->getReferenceTime() << '\n';
        std::cout << "Simulation time: \t" << frameStamp->getSimulationTime() << std::endl;
    }

    return 0;
}