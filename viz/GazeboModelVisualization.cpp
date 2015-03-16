#include <iostream>
#include "GazeboModelVisualization.hpp"

using namespace vizkit3d;

struct GazeboModelVisualization::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
    base::samples::RigidBodyState data;
};


GazeboModelVisualization::GazeboModelVisualization()
    : p(new Data)
{
}

GazeboModelVisualization::~GazeboModelVisualization()
{
    delete p;
}

osg::ref_ptr<osg::Node> GazeboModelVisualization::createMainNode()
{
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return new osg::Geode();
}

void GazeboModelVisualization::updateMainNode ( osg::Node* node )
{
    osg::Geode* geode = static_cast<osg::Geode*>(node);
    // Update the main node using the data in p->data
}

void GazeboModelVisualization::updateDataIntern(base::samples::RigidBodyState const& value)
{
    p->data = value;
    std::cout << "got new sample data" << std::endl;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(GazeboModelVisualization)

