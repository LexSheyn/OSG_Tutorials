// Page:    180
// Chapter: 7
// Time for action – enabling global multisampling

// Multisampling is a type of anti-aliasing technique. It can improve the final result's quality
// without much performance hit. User applications should set a sampling number for
// implementing multisample rasterization. Note that no all graphics cards support the
// multisampling extension, thus this example may fail on some systems and platforms.

#include "base.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    // Set the number of multisamples. Available values often include 2, 4, and 6,
    // depending on specific graphics devices.

    osg::DisplaySettings* displaySettings = osg::DisplaySettings::instance();

    displaySettings->setNumMultiSamples(4);

    // Load a model and render it with a standard viewer. The global multisampling
    // attribute managed bu the osg::DistplaySettings singletorn has already
    // come into effect now.

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osgViewer::Viewer viewer;

    viewer.setUpViewInWindow(0, 0, 1920, 1080, 0);
    viewer.setSceneData(model.get());

    return viewer.run();
}
