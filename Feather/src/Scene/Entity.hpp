#pragma once


#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Scene/Pool.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Component.hpp"


namespace Feather {
    class Scene::Entity {
    public:
        friend class Scene;
        template<typename... Args> friend class Viewer;


        template<typename... Args> bool Has() const {
            Assert(scene->Has(entity), "Scene does not have entity %lu!", entity);
            Assert(sizeof...(Args) > 0, "No components specified!");

            std::size_t types[] = { 0, Component::TypeOf<Args>()... };

            for (std::size_t i = 1; i <= sizeof...(Args); i++) if (types[i] >= scene->pools.size() || !scene->pools[types[i]] || !scene->pools[types[i]]->Has(entity)) return false;
            return true;
        }

        template<typename T> T& Get() const {
            Assert(scene->Has(entity), "Scene does not have entity %lu!", entity);
            Assert(Has<T>(), "Entity %lu does not have component %lu!", entity, Component::TypeOf<T>());

            std::size_t type = Component::TypeOf<T>();
            return scene->pools[type]->Get<T>(entity);
        }


        template<typename T, typename... Args> T& Add(Args&&... args) {
            Assert(scene->Has(entity), "Scene does not have entity %lu!", entity);
            Assert(!Has<T>(), "Entity %lu already has component %lu!", entity, Component::TypeOf<T>());

            std::size_t type = Component::TypeOf<T>();

            if (type >= scene->pools.size()) scene->pools.resize(type + 1);
            if (!scene->pools[type]) scene->pools[type] = std::make_unique<Pool>(sizeof(T));

            return scene->pools[type]->Add<T>(entity, std::forward<Args>(args)...);
        }

        template<typename T> void Remove() {
            Assert(scene->Has(entity), "Scene does not have entity %lu!", entity);
            Assert(Has<T>(), "Entity %lu does not have component %lu!", entity, Component::TypeOf<T>());

            std::size_t type = Component::TypeOf<T>();
            scene->pools[type]->Remove(entity);
        }


        bool operator==(const Entity& other) const { return entity == other.entity && scene == other.scene; }
        bool operator!=(const Entity& other) const { return !(*this == other); }

        operator std::size_t() const { return entity; }
    private:
        std::size_t entity;
        std::shared_ptr<Scene> scene;


        Entity(std::shared_ptr<Scene> scene, std::size_t entity): scene(scene), entity(entity) {}
    };
}
