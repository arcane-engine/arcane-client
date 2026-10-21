#include "SceneNode.h"

void Scene::SceneNode::SetSceneObject(SceneObject* sceneObject)
{
    _sceneObject = sceneObject;
}

Scene::SceneObject* Scene::SceneNode::GetSceneObject()
{
    return _sceneObject;
}

DirectX::XMMATRIX Scene::SceneNode::GetWorldMatrix()
{
    return DirectX::XMMatrixIdentity();
}
