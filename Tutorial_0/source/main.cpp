// Page:    186
// Chapter: 7
// Time for action – drawing aircrafts on a loaded terrain

// In this section, we are going to integrate what we learned before to create a slightly
// complex exmaple, which identifies all texture objects in a scene graph by using the
// osg::NodeVisitor utility, replaces them with a newly created shared texture, and binds
// the new texture to a render-to-texture camera. The texture is expected to represent more
// than a static image, so a customized simulation loop will be used to animate the sub-scene
// graph before calling the frame() method.

#include "base.h"

#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>

// The first task is to look for any textures applied to a loaded model. We have to
// derive a FindTextureVisitor from the osg::NodeVisitor base class. This
// Manages a texture object, which will be used for render-to-texture operation later.
// Every time we find an existing texture in the scene graph, we replace it with the
// managed one. This is implemented in the replaceTexture() method.
//
// In apply() method, call replaceTexture() on each node and drawable to
// see if there are any textures stored. Remember to call traverse() at the end of
// each method body to continue going though the scene graph.
//
// The user method uses getTextureAttribute() to obtain the texture in unit
// 0 from the input stat set, and replace it with the managed one. Because the
// state set is obtained via the getStateSet() method of node or drawable, not
// getOrCreateStateSet() which is sure to return an existin or new state set
// object, the input pointer may be null here.

class FindTextureVisitor : public osg::NodeVisitor
{
public:
    FindTextureVisitor(osg::Texture* p_texture)
    : m_texture (p_texture)
    {
        this->setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    }

    virtual void apply(osg::Node& node) override
    {
        this->replaceTexture(node.getStateSet());

        this->traverse(node);
    }

    virtual void apply(osg::Geode& geode) override
    {
        this->replaceTexture(geode.getStateSet());

        for (uint32_t i = 0; i < geode.getNumDrawables(); ++i)
        {
            this->replaceTexture(geode.getDrawable(i)->getStateSet());
        }

        this->traverse(geode);
    }

private:
    void replaceTexture(osg::StateSet* p_stateSet)
    {
        if (p_stateSet)
        {
            osg::Texture* p_oldTexture = dynamic_cast<osg::Texture*>(p_stateSet->getTextureAttribute(0, osg::StateAttribute::TEXTURE));

            if (p_oldTexture)
            {
                p_stateSet->setTextureAttribute(0, m_texture.get());
            }
        }
    }

private:
    osg::ref_ptr<osg::Texture> m_texture;
};

int32_t main(int32_t argc, char** argv)
{
    // Load two models as scene graphs. The lz.osg model is used as the main scene,
    // and the glider will be treated as a sub-graph that will be rendered to a texture,
    // and presented on the surfaces of models in the main scene.

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"lz.osg");
    osg::ref_ptr<osg::Node> subModel= osgDB::readNodeFile(MODEL_DIR"glider.osg");

    // Create a new texture object. This differs from the previous example that creates
    // 2D textures and applies an image to it. This time we should specify the texture size,
    // the internal format, and other attributes by ourselves.

    constexpr int32_t textureWidth  = 1024;
    constexpr int32_t textureHeight = 1024;

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();

    texture->setTextureSize(textureWidth, textureHeight);
    texture->setInternalFormat(GL_RGBA);
    texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
    texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

    // Use FintTextureVisitor to locate all textures used in the lz.osg model,
    // and replace them with the new, empty texture object.

    FindTextureVisitor findTextureVisitor(texture.get());

    if (model.valid())
    {
        model->accept(findTextureVisitor);
    }

    // Now it's time to create the render-to-textures camera. We set it up to have the
    // same viewport as the texture size scpecified, and clear the bakcground color and
    // buffer then starting to render sub-scene.

    osg::ref_ptr<osg::Camera> camera = new osg::Camera();

    camera->setViewport(0, 0, textureWidth, textureHeight);
    camera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f, 0.0f));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Force the camera to be rendered before the main scene, and use the high
    // efficency FBO to implement the render-to-textures technique. The key statement
    // in this example is to bind the color buffer with the texture object, whoch leads to
    // continuous updates of the texture object, redrawing the sub-scene graph again
    // and again.

    camera->setRenderOrder(osg::Camera::PRE_RENDER);
    camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
    camera->attach(osg::Camera::COLOR_BUFFER, texture.get());
    
    // Set the camera to be absolute, and set the loaded glider to be its sub-scene graph.

    camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    camera->addChild(subModel.get());

    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator();

    osgViewer::Viewer viewer;

    viewer.setUpViewInWindow(0, 0, 1920, 1080, 0);
    viewer.setSceneData(model.get());
    viewer.setCameraManipulator(manipulator.get());

    // The last step is to animate the glider. We haven't learnt any animation
    // functionalities in OSG, but we already known that the simulation loop can be
    // customized to add some pre- and post-frame events. We will simply modify
    // the view matrix of the render-to-textures canera during each frame, as if
    // making the glider swing. This is done by altering the up direction of the
    // "look-at" view matrix, as shown.

    float32_t delta = 0.1f;
    float32_t bias  = 0.0f;
    
    osg::Vec3 eye(0.0f, -5.0f, 5.0f);

    while (!viewer.done())
    {
        if (bias < -1.0f)
        {
            delta = 0.1f;
        }
        else if (bias > 1.0f)
        {
            delta = -0.1f;
        }

        bias += delta;

        camera->setViewMatrixAsLookAt(eye, osg::Vec3(), osg::Vec3(bias, 1.0f, 1.0f));

        viewer.frame();
    }

    // TO DO:
    // Model loaded into variable model is pitch black, nothing gets rendered on it!!!
    // What happened???
    // In the tutorial the root variable appears from nowhere...
    // What parts of code are missing?

    return 0;
}