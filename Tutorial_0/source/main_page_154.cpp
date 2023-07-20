// Page:    154
// Chapter: 6
// Time for action – implementing a cartoon cow

// The cartoon shading is a simple non-photorealistic effect which changes abruptly between
// tones. To achieve a cartoon shader, we only have to transform the vertex to built-in
// gl_Position variables in the vertex shader, and then calculate and select a tone by
// using the normal and light direction in the fragment shader. After that, we may apply it
// to a loaded model, for instance, a petty cow.

#include "base.h"

#include <osg/Program>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgViewer/Viewer>

int32_t main(int32_t argc, char** argv)
{
    const std::string workingDirectory = osgDB::getCurrentWorkingDirectory();
    const std::string codeDirectory = workingDirectory.substr(0, workingDirectory.size() - 6);
    const std::string shaderDirectory  = codeDirectory + "/shaders/";

    std::cout << workingDirectory << '\n';
    std::cout << codeDirectory    << '\n';
    std::cout << shaderDirectory  << '\n';

    osg::ref_ptr<osg::Shader> vertexShader = osgDB::readShaderFile(shaderDirectory + "cartoon_110.vert");
    osg::ref_ptr<osg::Shader> fragmentShader = osgDB::readShaderFile(shaderDirectory + "cartoon_110.frag");

    osg::ref_ptr<osg::Program> program = new osg::Program();

    program->addShader(vertexShader.get());
    program->addShader(fragmentShader.get());

    // Read a cow model, and apply the attribute and modes to its state set. There are
    // four uniform variables to be defined in the user application, so we must use the
    // addUniform() method four times in order to bind values to uniforms here.

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(MODEL_DIR"cow.osg");

    osg::ref_ptr<osg::Uniform> color0 = new osg::Uniform("color0", osg::Vec4(1.0f, 0.5f, 0.5f, 1.0f));
    osg::ref_ptr<osg::Uniform> color1 = new osg::Uniform("color1", osg::Vec4(0.5f, 0.2f, 0.2f, 1.0f));
    osg::ref_ptr<osg::Uniform> color2 = new osg::Uniform("color2", osg::Vec4(0.2f, 0.1f, 0.1f, 1.0f));
    osg::ref_ptr<osg::Uniform> color3 = new osg::Uniform("color3", osg::Vec4(0.1f, 0.05f, 0.05f, 1.0f));

    osg::StateSet* stateSet = model->getOrCreateStateSet();

    stateSet->setAttributeAndModes(program.get());
    stateSet->addUniform(color0.get());
    stateSet->addUniform(color1.get());
    stateSet->addUniform(color2.get());
    stateSet->addUniform(color3.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(model.get());

    return viewer.run();
}