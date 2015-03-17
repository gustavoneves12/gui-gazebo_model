#ifndef gazebo_model_GazeboModelVisualization_H
#define gazebo_model_GazeboModelVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <vizkit3d/RobotModel.h>
#include <base/samples/RigidBodyState.hpp>
#include <osg/Group>
#include <map>

namespace vizkit3d
{
    class GazeboVisualization
        : public vizkit3d::Vizkit3DPlugin<base::samples::RigidBodyState>
        , boost::noncopyable
    {
    Q_OBJECT
    Q_PROPERTY(QString modelFile READ modelFile WRITE setModelFile)
    public:
        GazeboVisualization();
        ~GazeboVisualization();

    Q_INVOKABLE void updateData(base::samples::RigidBodyState const &sample)
    {vizkit3d::Vizkit3DPlugin<base::samples::RigidBodyState>::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(base::samples::RigidBodyState const& plan);
        
    private:

        void setModelFile(QString modelFile);
        QString modelFile() const;

        osg::Node* getNode(std::string name);

        osg::ref_ptr<osg::Group> root;

        std::map<std::string, osg::Node*> nameToNode;

    };
}
#endif
