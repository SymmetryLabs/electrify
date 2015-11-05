#pragma once

#include <functional>
#include <map>
#include <utility>

#include <prettyprint.hpp>

#include "observes.h"
#include "event.h"
#include "data_proxy.h"
#include "object_owner.h"

template<typename KeyT, typename ValueT>
class ObservableMap : public Observes, public ObjectOwner {

public:
    // Member types
    typedef typename std::map<KeyT, ValueT>::key_type key_type;
    typedef typename std::map<KeyT, ValueT>::mapped_type mapped_type;
    typedef typename std::map<KeyT, ValueT>::value_type value_type;
    typedef typename std::map<KeyT, ValueT>::key_compare key_compare;
    typedef typename std::map<KeyT, ValueT>::value_compare value_compare;
    typedef typename std::map<KeyT, ValueT>::allocator_type allocator_type;
    typedef typename std::map<KeyT, ValueT>::reference reference;
    typedef typename std::map<KeyT, ValueT>::const_reference const_reference;
    typedef typename std::map<KeyT, ValueT>::pointer pointer;
    typedef typename std::map<KeyT, ValueT>::const_pointer const_pointer;
    typedef typename std::map<KeyT, ValueT>::iterator iterator;
    typedef typename std::map<KeyT, ValueT>::const_iterator const_iterator;
    typedef typename std::map<KeyT, ValueT>::reverse_iterator reverse_iterator;
    typedef typename std::map<KeyT, ValueT>::const_reverse_iterator const_reverse_iterator;
    typedef typename std::map<KeyT, ValueT>::difference_type difference_type;
    typedef typename std::map<KeyT, ValueT>::size_type size_type;

    Event<std::pair<const KeyT, ValueT>> valueAdded;
    Event<const KeyT> valueRemoved;

    // Iterators
    const_iterator begin() const noexcept { return m.begin(); }
    const_iterator cbegin() const noexcept { return m.cbegin(); }
    const_reverse_iterator rbegin() const noexcept { return m.rbegin(); }
    const_reverse_iterator rend() const noexcept { return m.rend(); }
    const_iterator end() const noexcept { return m.end(); }
    const_iterator cend() const noexcept { return m.cend(); }
    const_reverse_iterator crbegin() const noexcept { return m.crbegin(); }
    const_reverse_iterator crend() const noexcept { return m.crend(); }

    // Capacity
    bool empty() const noexcept { return m.empty(); }
    size_type size() const noexcept { return m.size(); }
    size_type max_size() const noexcept { return m.max_size(); }

    // Element access
    const mapped_type& at (const key_type& k) const { return m.at(k); }

    // Modifiers
    std::pair<iterator,bool> insert (const value_type& val);
    template<class P> std::pair<iterator,bool> insert (P&& val);
    iterator erase (const_iterator position);
    size_type erase (const key_type& k);
    void clear() noexcept;

    // Observers
    key_compare key_comp() const { return m.key_comp(); }
    value_compare value_comp() const { return m.value_comp(); }

    // Operations
    const_iterator find (const key_type& k) const { return m.find(k); }
    size_type count (const key_type& k) const { return m.count(k); }
    const_iterator lower_bound (const key_type& k) const { return m.lower_bound(k); }
    const_iterator upper_bound (const key_type& k) const { return m.upper_bound(k); }
    std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return m.equal_range(k); }

    // Allocator
    allocator_type get_allocator() const noexcept { return m.get_allocator(); }

    void makeProxySlave(ObservableMap<KeyT, ValueT>& slave, DataProxy& dataProxy) const;

private:
    std::map<KeyT, ValueT> m;

    friend std::ostream &operator<<(std::ostream& os, const ObservableMap<KeyT, ValueT>& om);

    template<typename Archive, typename t1, typename t2>
    friend void serialize(Archive& archive, ObservableMap<t1, t2>& om);
};

template<typename KeyT, typename ValueT>
std::ostream& operator<<(std::ostream& os, const ObservableMap<KeyT, ValueT>& om) { 
    return os << om.m;
}

#include "observable_map.hpp"
