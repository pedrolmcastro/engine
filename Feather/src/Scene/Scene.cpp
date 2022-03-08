#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Scene/Pool.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"

using namespace std;
using namespace Feather;


bool Scene::Has(size_t entity) const {
    return entity < next && !removed.contains(entity);
}

Scene::Entity Scene::Get(size_t entity) {
    Assert(Has(entity), "Scene does not have entity: ", entity);
    return Entity(shared_from_this(), entity);
}

Scene::Entity Scene::Add() {
    return Entity(shared_from_this(), next++);
}

void Scene::Remove(size_t entity) {
    Assert(Has(entity), "Scene does not have entity: ", entity);

    for (unique_ptr<Pool>& pool : pools) if (pool->Has(entity)) pool->Remove(entity);
    removed.insert(entity);
}
