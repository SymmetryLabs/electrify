#pragma once

#include <rxcpp/rx.hpp>

class Observer {

public:
    explicit Observer(rxcpp::subscription&& subscription);
    virtual ~Observer() = default;

    void unsubscribe();

private:
    rxcpp::subscription subscription;

};
