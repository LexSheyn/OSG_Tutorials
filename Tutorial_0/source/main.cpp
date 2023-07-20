// Page:    148
// Chapter: 6
// Time for action – achieving the translucent effect

// We are going to implement a common translucent effect that treats a model as glass. Any
// other scene objects can be displayed though the glass object. This can be done with the
// OpenGL blending mechanism, but it is important to calculate the corrent rendering order of
// scene objects in this case.

#include "base.h"

#include <osg/BlendFunc>
#include <osg/Texture2D>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    // We will continue using the quad geometry with a predefined texture coordinate
    // array. It should be treated as translucent object and the blending attribute
    // and modes should be applied later.

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    vertices->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
    vertices->push_back(osg::Vec3( 0.5f, 0.0f, -0.5f));
    vertices->push_back(osg::Vec3( 0.5f, 0.0f,  0.5f));
    vertices->push_back(osg::Vec3(-0.5f, 0.0f,  0.5f));

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();

    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array();

    texCoords->push_back(osg::Vec2(0.0f, 0.0f));
    texCoords->push_back(osg::Vec2(1.0f, 0.0f));
    texCoords->push_back(osg::Vec2(1.0f, 1.0f));
    texCoords->push_back(osg::Vec2(0.0f, 1.0f));

    // Be careful to set the color array of the quad. To blend it with other scene
    // objects, we have to set the alpha component to a value of less than 1.0 here.

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();

    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 0.5f));

    osg::ref_ptr<osg::DrawArrays> primitiveSet = new osg::DrawArrays(osg::DrawArrays::QUADS, 0, 4);

    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry();

    quad->setVertexArray(vertices.get());
    quad->setNormalArray(normals.get());
    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setColorArray(colors.get());
    quad->setColorBinding(osg::Geometry::BIND_OVERALL);
    quad->setTexCoordArray(0, texCoords.get());
    quad->addPrimitiveSet(primitiveSet.get());

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    geode->addDrawable(quad.get());

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(IMAGE_DIR"lz.rgb");

    texture->setImage(image.get());

    // Use the osg::BlendFunc class to implement the blending effect.
    // It works exactly the same as OpenGL's glBlendFunc().

    osg::ref_ptr<osg::BlendFunc> blendFunction = new osg::BlendFunc();

    blendFunction->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    osg::StateSet* stateSet = geode->getOrCreateStateSet();

    stateSet->setTextureAttributeAndModes(0, texture.get());
    stateSet->setAttributeAndModes(blendFunction.get());
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    osg::ref_ptr<osg::Group> root = new osg::Group();

    root->addChild(geode.get());
    root->addChild(osgDB::readNodeFile(MODEL_DIR"glider.osg"));

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}
