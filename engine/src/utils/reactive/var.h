#pragma once

#include <boost/utility/base_from_member.hpp>
#include <rxcpp/rx.hpp>

#include "token_source.h"

template<typename T>
class Var : protected boost::base_from_member<rxcpp::subjects::behavior<T>>, public TokenSource<T> {

public:
    Var();
    explicit Var(const T& f);
    explicit Var(T&& f);

    T getValue() const;

};

#include "var.hpp"
