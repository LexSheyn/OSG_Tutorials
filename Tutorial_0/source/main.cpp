// Page:    158
// Chapter: 6
// Time for action – generating a Bezier curve

#include "base.h"

#include <osg/Program>
#include <osg/LineWidth>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgViewer/Viewer>

// OpenGL has provided functions to generate Bezier and NURBS and surfaces for
// years, but they are not as good as we wish. Today's geometry shader can do the same work
// in a more convenient and efficient way. Take the generation of a Cubic Bezier curve as an
// example. Given two endpoints, and two control points to the shader, it will then produce a
// smooth curve, with specific segments, that begins and ends at two different endpoints, and
// be pulled away towards the control points.

int32_t main(int32_t argc, char** argv)
{
    // The vertex shader is always required, But this time it only
    // transforms vertices to successive shaders.

    const std::string workingDirectory = osgDB::getCurrentWorkingDirectory();
    const std::string codeDirectory = workingDirectory.substr(0, workingDirectory.size() - 6);
    const std::string shaderDirectory  = codeDirectory + "/shaders/";

    osg::ref_ptr<osg::Shader> vertexShader = osgDB::readShaderFile(shaderDirectory + "cubic_bezier_curve_120.vert");
    osg::ref_ptr<osg::Shader> fragmentShader = osgDB::readShaderFile(shaderDirectory + "cubic_bezier_curve_120.geom");

    // We will create the input primitive of the geometry shader by using an
    // osg::Geometry class. It contains a new type of primitive, named
    // GL_LINES_ADJACENCY_EXT, which gives a dimension of four of the
    // shader's gl_PositionIn variable.

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    vertices->push_back(osg::Vec3(0.0f, 0.0f,  0.0f));
    vertices->push_back(osg::Vec3(1.0f, 1.0f,  1.0f));
    vertices->push_back(osg::Vec3(2.0f, 1.0f, -1.0f));
    vertices->push_back(osg::Vec3(3.0f, 0.0f,  0.0f));

    osg::ref_ptr<osg::DrawArrays> primitiveSet = new osg::DrawArrays(GL_LINES_ADJACENCY_EXT, 0, 4);

    osg::ref_ptr<osg::Geometry> controlPoints = new osg::Geometry();

    controlPoints->setVertexArray(vertices.get());
    controlPoints->addPrimitiveSet(primitiveSet.get());

    // TO DO

    return 0;
}