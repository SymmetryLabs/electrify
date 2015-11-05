#pragma once

#include "observable_vector.h"
#include "proxy_slave_visitor.h"
#include "on_release.h"

template <typename T>
void performOnObjects(ProxySlaveVisitor& visitor, ObservableVector<T>& master, ObservableVector<T>& slave)
{
    auto visitorPtr = visitor.shared_from_this();

    slave.clear();
    for (const auto& obj : master.v) {
        auto created = visitor.constructionStrategy(obj);
        visitor(obj, created);
        slave.push_back(created);
    }

    auto scopedObservers = std::make_shared<std::vector<ScopedObserver>>();
    scopedObservers->push_back(ScopedObserver{master.valueAdded.observe(
        [visitorPtr, &slave] (const std::pair<size_t, std::reference_wrapper<T>>& p) {
            size_t pos = p.first;
            auto created = visitorPtr->constructionStrategy(p.second.get());
            (*visitorPtr)(p.second.get(), created);
            visitorPtr->dataProxy.sendEvent([=, &slave] {
                slave.insert(slave.begin() + pos, created);
            });
        }
    )});
    scopedObservers->push_back(ScopedObserver{master.willRemoveValue.observe(
        [visitorPtr] (const std::reference_wrapper<T>& p) {
            visitorPtr->remove(p.get());
        }
    )});
    scopedObservers->push_back(ScopedObserver{master.valueRemoved.observe([visitorPtr, &slave] (size_t pos) {
        visitorPtr->dataProxy.sendEvent([=, &slave] {
            slave.erase(slave.begin() + pos);
        });
    })});

    slave.retainFork(master.retain(ScopedPtr{new OnRelease{[visitorPtr, &master] {
        visitorPtr->remove(master);
    }}}));
    visitor.addRemoveFunction(&master, [scopedObservers] (RemoveProxySlaveVisitor& visitor) {
        for (ScopedObserver so : *scopedObservers) {
            so.release();
        }
    });
}

template <typename T>
void performOnObjects(RemoveProxySlaveVisitor& visitor, ObservableVector<T>& master)
{
    visitor.removeForIndex(&master);
    for (auto& t : master) {
        visitor(t);
    }
}
