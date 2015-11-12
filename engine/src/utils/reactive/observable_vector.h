#pragma once

#include <functional>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include "observes.h"
#include "template_utils.h"
#include "type_traits_ext.h"
#include "event.h"
#include "data_proxy.h"
#include "var.h"
#include "object_owner.h"

class ProxySlaveVisitor;

template<typename T, typename Alloc = std::allocator<T>>
class ObservableVector : public Observes, public ObjectOwner {

    std::vector<T, Alloc> v;

public:
    // Member types
    typedef typename std::vector<T, Alloc>::value_type value_type;
    typedef typename std::vector<T, Alloc>::allocator_type allocator_type;
    typedef typename std::vector<T, Alloc>::reference reference;
    typedef typename std::vector<T, Alloc>::const_reference const_reference;
    typedef typename std::vector<T, Alloc>::pointer pointer;
    typedef typename std::vector<T, Alloc>::const_pointer const_pointer;
    typedef typename std::vector<T, Alloc>::iterator iterator;
    typedef typename std::vector<T, Alloc>::const_iterator const_iterator;
    typedef typename std::vector<T, Alloc>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T, Alloc>::const_reverse_iterator const_reverse_iterator;
    typedef typename std::vector<T, Alloc>::difference_type difference_type;
    typedef typename std::vector<T, Alloc>::size_type size_type;

    explicit ObservableVector(const allocator_type& alloc = allocator_type()) : v(alloc), sizeVar(v.size()) {}
    explicit ObservableVector(size_type n) : v(n), sizeVar(v.size()) {}
    ObservableVector(size_type n, const value_type& val, const allocator_type& alloc = allocator_type()) : v(n, val, alloc), sizeVar(v.size()) {}
    template <class InputIterator>
    ObservableVector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : v(first, last, alloc), sizeVar(v.size()) {}
    ObservableVector(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type()) : v(il, alloc), sizeVar(v.size()) {}

    ~ObservableVector();

    Event<std::pair<size_t, std::reference_wrapper<T>>> valueAdded;
    Event<std::reference_wrapper<T>> willRemoveValue;
    Event<size_t> valueRemoved;
    Var<size_t> sizeVar;

    ObservableVector& operator=(const std::vector<T, Alloc>& x);
    ObservableVector& operator=(std::initializer_list<value_type> il);

    // Iterators
    const_iterator begin() const noexcept { return v.begin(); }
    const_iterator end() const noexcept { return v.end(); }
    const_reverse_iterator rbegin() const noexcept { return v.rbegin(); }
    const_reverse_iterator rend() const noexcept { return v.rend(); }
    const_iterator cbegin() const noexcept { return v.cbegin(); }
    const_iterator cend() const noexcept { return v.cend(); }
    const_reverse_iterator crbegin() const noexcept { return v.crbegin(); }
    const_reverse_iterator crend() const noexcept { return v.crend(); }

    // Capacity
    size_type size() const noexcept { return v.size(); }
    size_type max_size() const noexcept { return v.max_size(); }
    size_type capacity() const noexcept { return v.capacity(); }
    bool empty() const noexcept { return v.empty(); }

    // Element access
    const_reference operator[] (size_type n) const { return v[n]; }
    const_reference at(size_type pos) const { return v.at(pos); }
    const_reference front() const { return v.front(); }
    const_reference back() const { return v.back(); }
    const value_type* data() const noexcept { return v.data(); }

    // Modifiers
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    void clear();

    // Allocator
    allocator_type get_allocator() const noexcept { return v.get_allocator(); }

    void makeProxySlave(ObservableVector<T, Alloc>& slave, DataProxy& dataProxy) const;
    template<typename SlaveType, typename SlaveAlloc = std::allocator<SlaveType>>
    void makeProxySlave(ObservableVector<std::shared_ptr<SlaveType>, SlaveAlloc>& slave, DataProxy& dataProxy) const;

    template<typename SlaveType, typename... ArgN, typename SlaveAlloc = std::allocator<SlaveType>>
    auto makeSlave(ObservableVector<std::shared_ptr<SlaveType>, SlaveAlloc>& slave, ArgN&&... args) const
        -> typename std::enable_if<!is_callable<typename std::tuple_element<0, std::tuple<ArgN...> >::type, T>::value>::type;
    template<typename SlaveType, typename FCreate, typename FDestr = VoidNoOp, typename SlaveAlloc = std::allocator<SlaveType>>
    auto makeSlave(ObservableVector<std::shared_ptr<SlaveType>, SlaveAlloc>& slave, FCreate&& createFunc, FDestr&& destructFunc = VoidNoOp()) const
        -> typename std::enable_if<is_callable<FCreate, T>::value && is_callable<FDestr, std::shared_ptr<SlaveType>>::value>::type;

private:
    template<typename t>
    friend std::ostream& operator<<(std::ostream& os, const ObservableVector<t>& ov);

    template<typename Archive, typename t>
    friend void serialize(Archive& archive, ObservableVector<t>& ov);

    template <typename t>
    friend void performOnObjects(ProxySlaveVisitor& visitor, ObservableVector<t>& master, ObservableVector<t>& slave);

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const ObservableVector<T>& ov) {
    return os << ov.v;
}

#include "observable_vector.hpp"
