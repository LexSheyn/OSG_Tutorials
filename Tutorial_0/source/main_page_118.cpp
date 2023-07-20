// Page:   118
// Capter: 5
// Time for action – analyzing the Cessna structure

// User applications may always search the loaded scene graph for nodes of interest after
// loading a model file. For expmaple, we might like to take charge of the transformation or
// visibility of the loaded model if the root node is osg::Transform or osg::Switch. We
// Might also be interested in collecting all transformation nodes at the joints of a skeleton,
// which can be used to perform character animations later.
// The analysis of the loaded model structure is importatnt in that case. We will implemement an
// information pringing visitor here, which prints the basic information of visited nodes and
// arranges them in a tree structure.

#include "base.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <iostream>

// Declare the InfoVisitor class, and define the necessary virtual methods. We only
// handle leaf nodes and common osg::Node objects. The inline function spaces()
// is used for pringint spaces before node information, to indicate its level in the tree
// structure.

class InfoVisitor : public osg::NodeVisitor
{
public:
    InfoVisitor()
    : m_level (0)
    {
        this->setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    }

    std::string spaces() const
    {
        return std::string(m_level * 2, ' ');
    }

    virtual void apply(osg::Node& node) override
    {
        std::cout << this->spaces() << node.libraryName() << "::" << node.className() << std::endl;

        m_level++;

        this->traverse(node);

        m_level--;
    }

    virtual void apply(osg::Geode& geode) override
    {
        std::cout << this->spaces() << geode.libraryName() << "::" << geode.className() << std::endl;

        m_level++;

        for (uint32_t i = 0; i < geode.getNumDrawables(); ++i)
        {
            osg::Drawable* drawable = geode.getDrawable(i);

            std::cout << this->spaces() << drawable->libraryName() << "::" << drawable->className() << std::endl;
        }

        this->traverse(geode);

        m_level--;
    }

private:
    uint32_t m_level;
};

// We will introduce two methods className() and libraryName(), both of
// which return const char* values, for instance, "Node" as the class name and "osg"
// as the library name. There is no trick in re-implementing these two methods for
// different classes. The META_Object and META_Node macro definitions will do the
// work internally.

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile(MODEL_DIR"cessnafire.osg");

    if (!root)
    {
        OSG_FATAL << ": Failed to load model!" << std::endl;

        return -1;
    }

    InfoVisitor infoVisitor;

    root->accept(infoVisitor);

    

    return 0;
}