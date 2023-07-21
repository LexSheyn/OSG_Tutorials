// Page:    176
// Chapter: 7
// Time for action – rendering more scenes at one time

// Multi-viewer are practical in representing complex scenes, for instance, to render a
// wire area with a main view and an eagle eye view, or to display the front, side, top
// and perspective views of the same scene. Here we will create three separate windows,
// containing three different models, each of which can be independently manipulated.

#include "base.h"

#include <osgDB/ReadFile>
#include <osgViewer/CompositeViewer>

// We design a function to create a new osgViewer::View object and apply an
// existing node to it. The setUpViewInWindow() method is used here to produce
// non-full screen views.

struct ViewCreateInfo
{
    int32_t       x;
    int32_t       y;
    int32_t       width;
    int32_t       height;
    int32_t       screenNumber;
    osg::Node*    p_scene;
};

osgViewer::View* createView(const ViewCreateInfo& createInfo)
{
    osg::ref_ptr<osgViewer::View> view = new osgViewer::View();

    view->setSceneData(createInfo.p_scene);
    view->setUpViewInWindow(createInfo.x, createInfo.y, createInfo.width, createInfo.height, createInfo.screenNumber);

    return view.release();
}

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> models[3];

    models[0] = osgDB::readNodeFile(MODEL_DIR"cessna.osg");
    models[1] = osgDB::readNodeFile(MODEL_DIR"cow.osg");
    models[2] = osgDB::readNodeFile(MODEL_DIR"glider.osg");

    ViewCreateInfo viewCreateInfos[3];

    osg::ref_ptr<osgViewer::View> views[3];

    viewCreateInfos[0].x            = 50;
    viewCreateInfos[0].y            = 50;
    viewCreateInfos[0].width        = 320;
    viewCreateInfos[0].height       = 240;
    viewCreateInfos[0].screenNumber = 0;
    viewCreateInfos[0].p_scene      = models[0].get();

    views[0] = createView(viewCreateInfos[0]);

    viewCreateInfos[1].x            = 370;
    viewCreateInfos[1].y            = 50;
    viewCreateInfos[1].width        = 320;
    viewCreateInfos[1].height       = 240;
    viewCreateInfos[1].screenNumber = 0;
    viewCreateInfos[1].p_scene      = models[1].get();

    views[1] = createView(viewCreateInfos[1]);

    viewCreateInfos[2].x            = 185;
    viewCreateInfos[2].y            = 310;
    viewCreateInfos[2].width        = 320;
    viewCreateInfos[2].height       = 240;
    viewCreateInfos[2].screenNumber = 0;
    viewCreateInfos[2].p_scene      = models[2].get();

    views[2] = createView(viewCreateInfos[2]);

    osgViewer::CompositeViewer viewer;

    viewer.addView(views[0].get());
    viewer.addView(views[1].get());
    viewer.addView(views[2].get());

    return viewer.run();
}