// Page:    183
// Chapter: 7
// Time for action – rendering anaglyph stereo scenes

#include "base.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    osg::DisplaySettings* displaySettings = osg::DisplaySettings::instance();

    displaySettings->setStereoMode(osg::DisplaySettings::ANAGLYPHIC);
    displaySettings->setEyeSeparation(0.05f);
    //displaySettings->setStereo(true);

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osgViewer::Viewer viewer;

    osg::ColorMask* colorMask = new osg::ColorMask();

    colorMask->setMask(true, false, false, false);

    osg::StateSet* stateSet = model->getOrCreateStateSet();

    stateSet->setAttribute(colorMask);

    viewer.setUpViewInWindow(0, 0, 1920, 1080, 0);
    viewer.setSceneData(model.get());

    return viewer.run();
}