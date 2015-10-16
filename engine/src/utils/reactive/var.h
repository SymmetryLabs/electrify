#pragma once

#include <boost/utility/base_from_member.hpp>
#include <rxcpp/rx.hpp>

#include "token_source.h"

template<typename T>
class Var : protected boost::base_from_member<rxcpp::subjects::behavior<T>>, public TokenSource<T> {

public:
    Var();
    Var(const T& f);
    Var(T&& f);

    T getValue() const;

    operator T() const;

};

#include "var.hpp"
