#pragma once


#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Scene/Scene.hpp"
#include "Scene/Component.hpp"


namespace Feather {
    class Scene::Vector {
    public:
        Vector(std::size_t width): width(width) {
            data = reinterpret_cast<uint8_t*>(malloc(capacity * width));
            Assert(data, "Failed to create component vector!");
        }

        ~Vector() {
            for (std::size_t i = 0; i < size; i++) Get<Component>(i).OnRemove();
            free(data);
        }


        template<typename T> T& Get(std::size_t index) const {
            Assert(index < size, "Invalid component vector index: ", index);
            return *reinterpret_cast<T*>(data + index * width);
        }


        template<typename T, typename... Args> T& Add(Args&&... args) {
            if (size == capacity) {
                capacity *= 2;
                data = reinterpret_cast<uint8_t*>(realloc(data, capacity * width));
                Assert(data, "Failed to resize component vector!");
            }

            T* component = new (data + size * width) T(std::forward<Args>(args)...);
            component->OnAdd();
            size++;

            return *component;
        }

        void Remove(std::size_t index) {
            Assert(index < size, "Invalid component vector index: ", index);
            Get<Component>(index).OnRemove();

            size--;
            if (index != size) memcpy(data + index * width, data + size * width, width);
        }
    private:
        uint8_t* data = nullptr;
        std::size_t width, size = 0, capacity = 10;
    };


    class Scene::Pool {
    public:
        template<typename... Args> friend class Viewer;


        Pool(std::size_t width): components(width) {}


        bool Has(std::size_t entity) const {
            return entity < indices.size() && indices[entity] != NONE;
        }

        template<typename T> T& Get(std::size_t entity) const {
            Assert(Has(entity), "Entity ", entity, " does not have component: ", Component::TypeOf<T>());
            return components.Get<T>(indices[entity]);
        }


        template<typename T, typename... Args> T& Add(std::size_t entity, Args&&... args) {
            Assert(!Has(entity), "Entity ", entity, " already has component: ", Component::TypeOf<T>());

            if (entity >= indices.size()) indices.resize(entity + 1, NONE);
            indices[entity] = entities.size();

            entities.push_back(entity);
            return components.Add<T>(std::forward<Args>(args)...);
        }

        void Remove(std::size_t entity) {
            Assert(Has(entity), "Entity ", entity, " does not have component!");

            std::size_t temporary = entities[entities.size() - 1];
            entities[indices[entity]] = temporary;
            entities.pop_back();

            components.Remove(indices[entity]);

            indices[temporary] = indices[entity];
            indices[entity] = NONE;
        }
    private:
        Vector components;
        std::vector<std::size_t> indices;
        std::vector<std::size_t> entities;

        inline static const std::size_t NONE = SIZE_MAX;
    };
}
