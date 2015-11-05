#pragma once

#include <functional>
#include <map>
#include <memory>
#include <type_traits>

#include "visitor_base.h"
#include "data_proxy.h"
#include "default_construct_strategy.h"

class RemoveProxySlaveVisitor : public VisitorBase<RemoveProxySlaveVisitor> {

public:

    void removeForIndex(const void* index)
    {
        auto iter = removeFunctions.find(index);
        if (iter != removeFunctions.end()) {
            iter->second(*this);
            removeFunctions.erase(index);
        }
    }

    template <typename T>
    void performOnObjects(std::shared_ptr<T> t)
    {
        if (t) {
            (*this)(*t);
        }
    }

    template <typename T>
    auto performOnObjects(T)
        -> typename std::enable_if<std::is_fundamental<T>::value>::type
    {
    }

private:
    std::map<const void*, std::function<void(RemoveProxySlaveVisitor&)>> removeFunctions;

    friend class ProxySlaveVisitor;

};

class ProxySlaveVisitor : public VisitorBase<ProxySlaveVisitor>,
    public std::enable_shared_from_this<ProxySlaveVisitor> {

public:
    explicit ProxySlaveVisitor(DataProxy& dataProxy_)
    : dataProxy(dataProxy_)
    {
    }

    DataProxy& dataProxy;
    DefaultConstructStrategy constructionStrategy;
    RemoveProxySlaveVisitor remove;

    void addRemoveFunction(const void* index,
        const std::function<void(RemoveProxySlaveVisitor&)>& func)
    {
        remove.removeFunctions[index] = func;
    }

    template <typename T1, typename T2>
    void performOnObjects(std::shared_ptr<T1> master, std::shared_ptr<T2> slave)
    {
        if (master && slave) {
            (*this)(*master, *slave);
        }
    }

    template <typename T1, typename T2>
    auto performOnObjects(T1&& master, T2&& slave)
        -> typename std::enable_if<std::is_fundamental<typename std::decay<T1>::type>::value
            && std::is_fundamental<typename std::decay<T2>::type>::value>::type
    {
        slave = master;
    }

};
