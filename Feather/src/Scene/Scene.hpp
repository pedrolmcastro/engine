#pragma once


#include "Precompiled.hpp"

namespace Feather {
    class Scene : public std::enable_shared_from_this<Scene> {
    public:
        class Pool;
        class Vector;
        class Entity;
        class Component;
        template<typename... Args> class Viewer;


        bool Has(std::size_t entity) const;
        Entity Get(std::size_t entity);

        // TODO: Recycle
        Entity Add();
        void Remove(std::size_t entity);


        template<typename... Args> Viewer<Args...> View() { return Viewer<Args...>(shared_from_this()); }
    private:
        std::size_t next = 0;
        std::unordered_set<std::size_t> removed;
        std::vector<std::unique_ptr<Pool>> pools;
    };
}
