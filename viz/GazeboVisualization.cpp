#include <iostream>
#include <vizkit3d/OsgVisitors.hpp>
#include "GazeboVisualization.hpp"

using namespace vizkit3d;

class Data : public osg::Referenced
{

public:
    base::samples::RigidBodyState pos;
};

class OSGUpdatePositionCallback : public osg::NodeCallback
{
public:

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {

        Data* data = dynamic_cast<Data*>(node->getUserData());

        if (data){
            osg::PositionAttitudeTransform *pat = node->asTransform()->asPositionAttitudeTransform();
            pat->setPosition(osg::Vec3d(data->pos.position[0], data->pos.position[1], data->pos.position[2]));
            pat->setAttitude(osg::Quat(data->pos.orientation.x(), data->pos.orientation.y(), data->pos.orientation.z(), data->pos.orientation.w()));
        }

        traverse(node, nv);
    }
};


void findNamedNodes(const std::string& searchName, osg::Node* currNode, std::vector<osg::Node*>& nodes)
{
    osg::Group* currGroup;

    if (!currNode){
        return;
    }

    if (currNode->getName() == searchName){
        std::cout << "found node: " << currNode->getName() << std::endl;
        nodes.push_back(currNode);
    }

    currGroup = currNode->asGroup();

    if (currGroup){
        for (unsigned int i = 0 ; i < currGroup->getNumChildren(); i ++){
            findNamedNodes(searchName, currGroup->getChild(i), nodes);
        }
    }
}

GazeboVisualization::GazeboVisualization() :
      root(new osg::Group)
{
}

GazeboVisualization::~GazeboVisualization()
{
}

osg::ref_ptr<osg::Node> GazeboVisualization::createMainNode()
{
    return root;
}

void GazeboVisualization::updateMainNode( osg::Node* node ) { }

void GazeboVisualization::updateDataIntern(base::samples::RigidBodyState const& sample)
{
    osg::Node *node = getNode(sample.sourceFrame);

    if (node){
        Data* data = dynamic_cast<Data*>(node->getUserData());
        data->pos = sample;
    }
}


void GazeboVisualization::setModelFile(QString modelFile)
{

    RobotModel robotModel;

    osg::Node *first = robotModel.load(QString(modelFile));
    std::vector<std::string> segments = robotModel.getSegmentNames();

    for (unsigned int i = 0; i < segments.size(); i++){
        std::vector<osg::Node*> nodes;

        findNamedNodes(segments[i], first, nodes);

        if (nodes.size() > 0){
            osg::PositionAttitudeTransform *pat = new osg::PositionAttitudeTransform();
            pat->setUpdateCallback(new OSGUpdatePositionCallback);
            pat->setUserData(new Data);
            pat->setName(segments[i]);

            for (unsigned int j = 0; j < nodes.size(); j++){
                pat->addChild(nodes[j]);
            }

            nameToNode.insert(std::make_pair<std::string, osg::Node*>(segments[i], pat));
            root->addChild(pat);
        }
    }

    setPluginName(QString::fromStdString(robotModel.getModelName()));

}

QString GazeboVisualization::modelFile() const
{
    return QString("");
}

osg::Node* GazeboVisualization::getNode(std::string name)
{
    std::map<std::string, osg::Node*>::iterator it = nameToNode.find(name);

    if (it != nameToNode.end()){
        return it->second;
    }

    return NULL;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(GazeboVisualization)

