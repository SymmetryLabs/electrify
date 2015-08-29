#pragma once

#include <boost/utility/base_from_member.hpp>
#include <rxcpp/rx.hpp>

#include "token_source.h"

template<typename T = void*>
class Event : protected boost::base_from_member<rxcpp::subjects::subject<T>>, public TokenSource<T> {

public:
    Event();

    void operator()() const;
    
    void operator()(const T& value) const;
    void operator()(T&& value) const;

};

#include "event.hpp"
