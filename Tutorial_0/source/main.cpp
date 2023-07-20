// Page:    143
// Chapter: 6
// Time for action – loading and applying 2D textures

// The most common texture mapping technique is 2D texture mapping. This accepts a 2D image
// as the texture and maps it onto one or more geonetry surfaces. The osg::Texture2D class is
// used here as a texture attribute of a specific texture mapping unit.

#include "base.h"

#include <osg/Texture2D>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    // We will quickly create a quad and call the setTextCoordArray() method to
    // bind texture coordinates per vertex. The texture coordinate array only affects the
    // texture unit 0 in the example, but it is always possible to share arrays among units.

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

    osg::ref_ptr<osg::DrawArrays> primitiveSet = new osg::DrawArrays(GL_QUADS, 0, 4);

    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry();

    quad->setVertexArray(vertices.get());
    quad->setNormalArray(normals.get());
    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setTexCoordArray(0, texCoords.get());
    quad->addPrimitiveSet(primitiveSet.get());

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(IMAGE_DIR"lz.rgb");
    //osg::ref_ptr<osg::Image> image = osgDB::readImageFile(IMAGE_DIR"winter_house.jpg");

    texture->setImage(image.get());

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(quad.get());
    
    osg::StateSet* rootStateSet = root->getOrCreateStateSet();

    rootStateSet->setTextureAttributeAndModes(0, texture.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}