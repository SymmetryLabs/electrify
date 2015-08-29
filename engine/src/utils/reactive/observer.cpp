#include "observer.h"

Observer::Observer(rxcpp::subscription&& subscription)
: subscription(std::move(subscription))
{
}

void Observer::unsubscribe()
{
    subscription.unsubscribe();
}
