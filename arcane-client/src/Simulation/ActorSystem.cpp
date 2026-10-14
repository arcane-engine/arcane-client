#include "Simulation/ActorSystem.h"

namespace Simulation
{
    Actor& ActorSystem::CreateActor(std::uint32_t id, const Math::Vector3& position, const Math::Quaternion& rotation, const Math::Vector3& scale)
    {
        auto [it, inserted] = _actors.try_emplace(id, id, position, rotation, scale);
        return it->second;
    }

    void ActorSystem::RemoveActor(const std::uint32_t id)
    {
        _actors.erase(id);
    }

    Actor* ActorSystem::GetActor(const std::uint32_t id)
    {
        const auto it = _actors.find(id);

        return it != _actors.end() ? &it->second : nullptr;
    }

    const std::unordered_map<std::uint32_t, Actor>& ActorSystem::GetActors()
    {
        return _actors;
    }
}
