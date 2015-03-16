#ifndef gazebo_model_GazeboModelVisualization_H
#define gazebo_model_GazeboModelVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include </base/samples/RigidBodyState.hpp>

namespace vizkit3d
{
    class GazeboModelVisualization
        : public vizkit3d::Vizkit3DPlugin<base::samples::RigidBodyState>
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        GazeboModelVisualization();
        ~GazeboModelVisualization();

    Q_INVOKABLE void updateData(base::samples::RigidBodyState const &sample)
    {vizkit3d::Vizkit3DPlugin<base::samples::RigidBodyState>::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(base::samples::RigidBodyState const& plan);
        
    private:
        struct Data;
        Data* p;
    };
}
#endif
