#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Graphics/RenderObject.h"
#include "Math/Vector3.h"

namespace Scene
{
    class SceneObject
    {
    public:
        explicit SceneObject(Graphics::RenderObject renderObject);

        const Graphics::RenderObject& GetRenderObject();
        const std::vector<DirectX::XMMATRIX>& GetWorldMatrixInstances();

        void AddInstance(const DirectX::XMMATRIX& worldMatrix);

        void ClearInstances();

    private:
        Graphics::RenderObject _renderObject;
        std::vector<DirectX::XMMATRIX> _worldMatrixInstances;
        std::vector<Math::Vector3> _worldPositionsInstances;
    };
}
