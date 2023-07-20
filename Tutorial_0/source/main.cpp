// Page:    137
// Chapter: 6
// Time for action – creating light sources in the scene

// By default, OSG automatically turns on the first light (GL_LIGHT0) and gives the scene a soft,
// directional light. However, this time we will create multiple lights by ourselves, and move
// them with transformation parent nodex. Be aware: only position lights can be translated.
// A directional light has no origin and cannot be placed anywhere.
// OpenGL and OSG both use the fourth component of the position parameter to decide if
// a light is a point light. That is to say, if the fourth component is 0, the light is treated as a
// directional source; otherwise it is positional.

#include "base.h"

#include <osg/MatrixTransform>
#include <osg/LightSource>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

// We create a function to create light sources for the scene graph. A light source
// should have a number (rangin from 0 to 7), a translation position, and a color
// paremeter. A point light is created because the fourth part of the position vector
// is 1.0. After that, we assign the light to a wenly-created osg::LightSource
// node, and add the light source to a translated osg::MatrixTransform node,
// which is then returned.

osg::Node* createLightSource(
    uint32_t         number,
    const osg::Vec3& translation,
    const osg::Vec4& color
)
{
    osg::ref_ptr<osg::Light> light = new osg::Light();

    light->setLightNum(number);
    light->setDiffuse(color);
    light->setPosition(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();

    lightSource->setLight(light.get());

    osg::ref_ptr<osg::MatrixTransform> sourceTransform = new osg::MatrixTransform();

    sourceTransform->setMatrix(osg::Matrix::translate(translation));
    sourceTransform->addChild(lightSource.get());

    return sourceTransform.release();
}

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cessna.osg");

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(model.get());

    // No it's time to construct two light source nodes and put them at different
    // positions in the scene.

    osg::Node* lightSource0 = createLightSource(0, osg::Vec3(-20.0f, 0.0f, 0.0f), osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
    osg::Node* lightSource1 = createLightSource(1, osg::Vec3(0.0f, -20.0f, 0.0f), osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f));

    // The light numbers 0 and 1 used here. So we will turn on modes GL_LIGHT0
    // and GL_LIGHT1 of the root node, which means that all nodes in the scene graph
    // could benefit from the two warm light sources.

    osg::StateSet* rootStateSet = root->getOrCreateStateSet();

    rootStateSet->setMode(GL_LIGHT0, osg::StateAttribute::ON);
    rootStateSet->setMode(GL_LIGHT1, osg::StateAttribute::ON);

    root->addChild(lightSource0);
    root->addChild(lightSource1);

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}