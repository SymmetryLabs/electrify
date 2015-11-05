template <typename F>
void DataProxy::sendEvent(F&& eventFunc)
{
    if (hasEventQueue()) {
        queueEvent(std::forward<F>(eventFunc));
    } else {
        eventFunc();
    }
}

template<typename F, typename T1>
void DataProxy::sendEvent(F&& eventFunc, std::weak_ptr<T1> t1)
{
    sendEvent([=] {
        if (auto strongT1 = t1.lock()) {
            eventFunc(strongT1);
        }
    });
}

template<typename F, typename T1, typename T2>
void DataProxy::sendEvent(F&& eventFunc, std::weak_ptr<T1> t1, std::weak_ptr<T2> t2)
{
    sendEvent([=] {
        if (auto strongT1 = t1.lock()) {
            if (auto strongT2 = t2.lock()) {
                eventFunc(strongT1, strongT2);
            }
        }
    });
}

template<typename F, typename T1>
void DataProxy::sendEvent(F&& eventFunc, const T1& t1)
{
    sendEvent([=] {
        eventFunc(t1);
    });
}

template<typename F, typename T1, typename T2>
void DataProxy::sendEvent(F&& eventFunc, const T1& t1, const T2& t2)
{
    sendEvent([=] {
        eventFunc(t1, t2);
    });
}
