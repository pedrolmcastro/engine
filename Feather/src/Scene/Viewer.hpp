#pragma once


#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Scene/Pool.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Component.hpp"


namespace Feather {
    template<typename... Args> class Scene::Viewer {
    public:
        friend class Scene;


        std::vector<Entity>::iterator begin() { return entities.begin(); }
		std::vector<Entity>::iterator end() { return entities.end(); }
    private:
        std::shared_ptr<Scene> scene;
        std::vector<Entity> entities;


        Viewer(std::shared_ptr<Scene> scene): scene(scene) {
            Assert(scene->pools.size() > 0, "Scene does not have components!");
            Assert(sizeof...(Args) > 0, "No components specified!");

            std::size_t types[] = { 0, Component::TypeOf<Args>()... };
            std::size_t minimum = 0;

            for (std::size_t i = 1; i <= sizeof...(Args); i++) {
                Assert(scene->pools.contains(types[i]), "Scene does not have component: ", types[i]);
                if (scene->pools[types[i]]->entities.size() < scene->pools[minimum]->entities.size()) minimum = types[i];
            }

            for (const std::size_t& index : scene->pools[minimum]->entities) {
                Entity entity(scene, index);
                if (entity.Has<Args...>()) entities.push_back(entity);
            }
        }
    };
}
