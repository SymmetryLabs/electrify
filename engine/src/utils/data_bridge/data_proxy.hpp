template <typename F>
void DataProxy::sendEvent(F&& eventFunc)
{
    if (hasEventQueue()) {
        queueEvent(std::forward<F>(eventFunc));
    } else {
        eventFunc();
    }
}
