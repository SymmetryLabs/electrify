template <typename T>
DataTransmitter::DataTransmitter(const std::shared_ptr<T>& destination_)
: destination(destination_)
{
}

template <typename T>
void DataTransmitter::setDestination(const std::shared_ptr<T>& destination_)
{
    destination = destination_;
}

template<typename T>
void DataTransmitter::bind(Observable<T>& masterSignal, TokenSource<T>& slaveSignal)
{
    observe(masterSignal, [&, this] (T object) {
        sendFunction([=, &slaveSignal] {
            slaveSignal << object;
        });
    });
}

template<typename MasterType, typename SlaveType>
void DataTransmitter::bind(ObservableVector<MasterType>& masterVector, ObservableVector<SlaveType>& slaveVector)
{
    masterVector.makeProxySlave(slaveVector, masterDataProxy);
}

template<typename C, typename F>
void DataTransmitter::sendCommand(F&& func)
{
    WeakAnyPtr localWeakMaster = destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            func(strongMaster.template get<C>());
        }
    });
}

template<typename C, typename R, typename F, typename FResp>
void DataTransmitter::sendCommand(F&& func, FResp&& response)
{
    WeakAnyPtr localWeakMaster = destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            R rtn = func(strongMaster.template get<C>());

            slaveDataProxy.sendEvent([=] {
                response(rtn);
            });
        }
    });
}

template<typename C, typename S1, typename F, typename T1>
void DataTransmitter::sendCommand(F&& func, std::weak_ptr<T1> t1)
{
    WeakAnyPtr localWeakMaster = destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = t1.lock()) {
                func(strongMaster.template get<C>(),
                    std::dynamic_pointer_cast<S1>(strongT1));
            }
        }
    });
}

template<typename C, typename S1, typename S2, typename F, typename T1, typename T2>
void DataTransmitter::sendCommand(F&& func, std::weak_ptr<T1> t1, std::weak_ptr<T2> t2)
{
    WeakAnyPtr localWeakMaster = destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = t1.lock()) {
                if (auto strongT2 = t2.lock()) {
                    func(strongMaster.template get<C>(),
                        std::dynamic_pointer_cast<S1>(strongT1),
                        std::dynamic_pointer_cast<S2>(strongT2));
                }
            }
        }
    });
}

template<typename C, typename F, typename T1>
void DataTransmitter::sendCommand(F&& func, std::weak_ptr<T1> t1)
{
    WeakAnyPtr localWeakMaster = destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = t1.lock()) {
                func(strongMaster.template get<C>(), strongT1);
            }
        }
    });
}

template<typename C, typename F, typename T1, typename T2>
void DataTransmitter::sendCommand(F&& func, std::weak_ptr<T1> t1, std::weak_ptr<T2> t2)
{
    WeakAnyPtr localWeakMaster = destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = t1.lock()) {
                if (auto strongT2 = t2.lock()) {
                    func(strongMaster.template get<C>(), strongT1, strongT2);
                }
            }
        }
    });
}

template<typename F, typename T1>
void DataTransmitter::sendCommand(F&& func, std::weak_ptr<T1> t1)
{
    sendFunction([=] {
        if (auto strongT1 = t1.lock()) {
            func(strongT1);
        }
    });
}

template<typename F, typename T1, typename T2>
void DataTransmitter::sendCommand(F&& func, std::weak_ptr<T1> t1, std::weak_ptr<T2> t2)
{
    sendFunction([=] {
        if (auto strongT1 = t1.lock()) {
            if (auto strongT2 = t2.lock()) {
                func(strongT1, strongT2);
            }
        }
    });
}

template<typename C, typename S1, typename F, typename T1>
void DataTransmitter::sendCommand(F&& func, T1 t1)
{
    WeakAnyPtr localWeakMaster = destination;
    auto weakT1 = t1.destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = weakT1.lock()) {
                func(strongMaster.template get<C>(),
                    std::dynamic_pointer_cast<S1>(strongT1));
            }
        }
    });
}

template<typename C, typename S1, typename S2, typename F, typename T1, typename T2>
void DataTransmitter::sendCommand(F&& func, T1 t1, T2 t2)
{
    WeakAnyPtr localWeakMaster = destination;
    auto weakT1 = t1.destination;
    auto weakT2 = t2.destination;
    sendFunction([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = weakT1.lock()) {
                if (auto strongT2 = weakT2.lock()) {
                    func(strongMaster.template get<C>(),
                        std::dynamic_pointer_cast<S1>(strongT1),
                        std::dynamic_pointer_cast<S2>(strongT2));
                }
            }
        }
    });
}

template <typename F>
void DataTransmitter::sendFunction(F&& fn)
{
    masterDataProxy.sendEvent(std::forward<F>(fn));
}
