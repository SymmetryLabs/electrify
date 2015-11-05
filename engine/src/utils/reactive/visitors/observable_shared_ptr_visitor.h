#pragma once

#include "observable_shared_ptr.h"
#include "proxy_slave_visitor.h"
#include "on_release.h"

template <typename T>
void performOnObjects(ProxySlaveVisitor& visitor, ObservableSharedPtr<T>& master, ObservableSharedPtr<T>& slave)
{
    auto visitorPtr = visitor.shared_from_this();

    if (master) {
        auto created = visitor.constructionStrategy(master.get());
        (*visitorPtr)(*master, *created);
        slave = created;
    } else {
        slave.reset();
    }

    auto scopedObservers = std::make_shared<std::vector<ScopedObserver>>();

    scopedObservers->push_back(ScopedObserver{master.observe(
        [=, &slave] (const std::shared_ptr<T>& t) {
            if (t) {
                auto created = visitorPtr->constructionStrategy(t);
                (*visitorPtr)(*t, *created);
                visitorPtr->dataProxy.sendEvent([=, &slave] {
                    slave = created;
                });
            }
        }
    )});

    slave.retainFork(master.retain(ScopedPtr{new OnRelease{[=, &master] {
        visitorPtr->remove(master);
    }}}));
    scopedObservers->push_back(ScopedObserver{master.previous().observe(
        [=, &slave] (const std::shared_ptr<T>& prev) {
            if (prev) {
                visitorPtr->remove(*prev);
            }
        }
    )});

    visitor.addRemoveFunction(&master, [=] (RemoveProxySlaveVisitor& visitor) {
        for (ScopedObserver so : *scopedObservers) {
            so.release();
        }
    });
}

template <typename T>
void performOnObjects(RemoveProxySlaveVisitor& visitor, ObservableSharedPtr<T>& master)
{
    visitor.removeForIndex(&master);
    if (master) {
        visitor(*master);
    }
}
