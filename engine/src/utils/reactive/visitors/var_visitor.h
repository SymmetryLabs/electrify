#pragma once

#include <tuple>

#include "visitor_base.h"
#include "proxy_slave_visitor.h"
#include "on_release.h"
#include "scoped_ptr.h"

template <typename T>
void performOnObjects(ProxySlaveVisitor& visitor, Var<T>& master, Var<T>& slave)
{
    auto visitorPtr = visitor.shared_from_this();

    if (master.hasValue()) {
        T originalVal = master.getValue();
        T created = visitor.constructionStrategy(originalVal);
        visitor(originalVal, created);
        slave.emit(created);
    } else {
        slave.removeValue();
    }

    auto scopedObservers = std::make_shared<std::vector<ScopedObserver>>();
    scopedObservers->push_back(ScopedObserver{master.previous().observe(
        [visitorPtr, &slave] (T prev) {
            visitorPtr->remove(prev);
        }
    )});

    scopedObservers->push_back(ScopedObserver{master.observe(
        [visitorPtr, &slave] (T next) {
            auto created = visitorPtr->constructionStrategy(next);
            (*visitorPtr)(next, created);
            visitorPtr->dataProxy.sendEvent([=, &slave] {
                slave.emit(created);
            });
        }
    )});

    slave.retainFork(master.retain(ScopedPtr{new OnRelease{[=, &master] {
        visitorPtr->remove(master);
    }}}));
    visitor.addRemoveFunction(&master, [=] (RemoveProxySlaveVisitor& visitor) {
        for (ScopedObserver so : *scopedObservers) {
            so.release();
        }
    });
}

template <typename T>
void performOnObjects(RemoveProxySlaveVisitor& visitor, Var<T>& master)
{
    visitor.removeForIndex(&master);
    visitor(master.getValue());
}
