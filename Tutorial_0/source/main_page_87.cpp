// Page:   87
// Capter: 4
// Time for action – creating the famous OpenGL teapot

#include <GL/glut.h>

#include <osg/Drawable>
#include <osg/Geode>
#include <osgViewer/Viewer>

#include <iostream>
#include <cstdint>

typedef float  float32_t;
typedef double float64_t;

class TeapotDrawable : public osg::Drawable
{
public:
    TeapotDrawable(float32_t size = 1.0f)
    : m_size (size)
    {}

    TeapotDrawable(const TeapotDrawable& copy, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY)
    : osg::Drawable (copy, copyOp)
    , m_size        (copy.m_size)
    {}

    META_Object(osg, TeapotDrawable);

    virtual osg::BoundingBox computeBoundingBox() const override
    {
        const osg::Vec3 min(-m_size, -m_size, -m_size);
        const osg::Vec3 max(m_size, m_size, m_size);

        return osg::BoundingBox(min, max);
    }

    virtual void drawImplementation(osg::RenderInfo& renderInfo) const override
    {
        glFrontFace(GL_CW);

        glutSolidTeapot(m_size);

        glFrontFace(GL_CCW);
    }

private:
    float32_t m_size;
};

int32_t main(int32_t argc, char** argv)
{
    glutInit(&argc, argv);

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(new TeapotDrawable(1.0f));

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}