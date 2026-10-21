#include "SceneObject.h"

namespace Scene
{
    SceneObject::SceneObject(Graphics::RenderObject renderObject)
        : _renderObject(std::move(renderObject))
    {}

    const Graphics::RenderObject& SceneObject::GetRenderObject()
    {
        return _renderObject;
    }

    const std::vector<DirectX::XMMATRIX>& SceneObject::GetWorldMatrixInstances()
    {
        return _worldMatrixInstances;
    }

    void SceneObject::AddInstance(const DirectX::XMMATRIX& worldMatrix)
    {
        _worldMatrixInstances.push_back(worldMatrix);
    }

    void SceneObject::ClearInstances()
    {
        _worldMatrixInstances.clear();
        _worldPositionsInstances.clear();
    }
}
