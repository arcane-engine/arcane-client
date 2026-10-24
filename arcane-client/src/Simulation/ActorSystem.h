#pragma once

#include <unordered_map>

#include "Simulation/Actor.h"

namespace Math
{
    struct Quaternion;
    struct Vector3;
}

namespace Simulation
{
    class ActorSystem
    {
    public:
        ActorSystem() = default;

        Actor& CreateActor(std::uint32_t id, const Math::Vector3& position, const Math::Quaternion& rotation, const Math::Vector3& scale, bool primary);

        void RemoveActor(std::uint32_t id);

        [[nodiscard]] std::unordered_map<std::uint32_t, Actor>& GetActors();
        [[nodiscard]] Actor* GetActor(std::uint32_t id);
        [[nodiscard]] std::uint32_t GetPrimaryActorId() const;

    private:
        std::uint32_t _primaryActorId;
        std::unordered_map<std::uint32_t, Actor> _actors;
    };
}
