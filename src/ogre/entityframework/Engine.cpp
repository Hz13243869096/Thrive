#include <vector>

#include "Engine.h"

Engine::Engine()
{
    nodeMap;
}

void Engine::addEntity(Entity* entity)
{
    entityList.insert(entityList.end(),entity);
    //Here we have to see what components the entity contains, create nodes
    //containing them and add the nodes to the nodeLists
    //For now, just create a MoveNode. This should be done dinamically
    //MessageBox( NULL,/*boost::lexical_cast<char*>(*/"adding Entity"/*+node)*/, "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        MoveNode* moveNode = new MoveNode();
    moveNode->ogreNode = (OgreNodeComponent*) entity->get(typeid(OgreNodeComponent).name());
    moveNode->velocity = (VelocityComponent*) entity->get(typeid(VelocityComponent).name());
    std::vector<Node*>* nodeList = getNodeList(typeid(MoveNode).name());
    nodeList->push_back(moveNode);
}

void Engine::removeEntity(Entity* entity)
{
    //This code is just horrible. A different implementation of entityList is needed
    for (std::vector<Entity*>::iterator i = entityList.begin();i!=entityList.end();i++){
        if ((*i) == entity)
            entityList.erase(i);
            break;
    }
    
}

void Engine::addSystem(ISystem* system)
{
    systemList.insert(systemList.end(),system);
}

void Engine::removeSystem(ISystem* system)
{
    //This code is just horrible. A different implementation of systemList is needed
    for (std::vector<ISystem*>::iterator i = systemList.begin();i!=systemList.end();i++){
        if ((*i) == system)
            systemList.erase(i);
            break;
    }
}

std::vector<Node*>* Engine::getNodeList(std::string node)
{
    if (nodeMap.count(node)==0)
    {
        std::pair<std::string,std::vector<Node*>*> p = std::pair<std::string,std::vector<Node*>*>(node,new std::vector<Node*>());
        nodeMap.insert(p);
    }
    return nodeMap[node];
}

void Engine::update(Ogre::Real deltaTime)
{
    for (std::vector<ISystem*>::iterator i = systemList.begin(); i!=systemList.end(); i++)
    {
        (*i)->update(deltaTime);
    }
}