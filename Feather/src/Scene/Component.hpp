#pragma once


#include "Scene/Scene.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"

namespace Feather {    
    class Scene::Component {
    public:
        class Transform;


        template<typename T> static std::size_t TypeOf() {
            static const std::size_t type = next++;
            return type;
        }


        virtual void OnAdd() {}
        virtual void OnRemove() {}

        // TODO: Serialize
    private:
        inline static std::size_t next = 0;
    };


    class Scene::Component::Transform: public Component {
    public:
        Math::Float3 translation, scale;
        Math::Quaternion rotation;

        Transform(const Math::Float3& translation = Math::Float3(), const Math::Quaternion& rotation = Math::Quaternion::Identity(), const Math::Float3& scale = Math::Float3(1.0f))
        : translation(translation), rotation(rotation), scale(scale) {}

        operator Math::Matrix4() const { return Math::Matrix4::Translate(translation) * Math::Matrix4::Rotate(rotation) * Math::Matrix4::Scale(scale); }
    };
}
