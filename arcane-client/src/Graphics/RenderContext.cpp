#include "RenderContext.h"

namespace Graphics
{
    RenderContext::RenderContext(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept : 
        WorldMatrix(),
        ViewMatrix(viewMatrix),
        ProjectionMatrix(projectionMatrix),
        ViewProjectionMatrix(viewMatrix * projectionMatrix),
        WorldViewProjectionMatrix()
    {}
}
