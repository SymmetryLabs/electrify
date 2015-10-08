#pragma once

#include <functional>
#include <memory>

#include "data_proxy.h"
#include "observes.h"
#include "observable.h"
#include "observable_vector.h"
#include "token_source.h"
#include "weak_any_ptr.h"
#include "enable_type_erasure.h"

class DataTransmitter : public std::enable_shared_from_this<DataTransmitter>, public Observes {

public:
    DataTransmitter() = default;
    template <typename T>
    explicit DataTransmitter(const std::shared_ptr<T>& destination);

    template <typename T>
    void setDestination(const std::shared_ptr<T>& destination);
    void setDataProxies(const DataProxy& masterDataProxy, const DataProxy& slaveDataProxy);
    
protected:
    template<typename T>
    void bind(Observable<T>& masterSignal, TokenSource<T>& slaveSignal);
    template<typename MasterType, typename SlaveType>
    void bind(ObservableVector<MasterType>& masterVector, ObservableVector<SlaveType>& slaveVector);

    template<typename C, typename F>
    void sendCommand(F&& func);
    template<typename C, typename R, typename F, typename FResp>
    void sendCommand(F&& func, FResp&& response);

    template<typename C, typename S1, typename F, typename T1>
    void sendCommand(F&& func, std::weak_ptr<T1> t1);
    template<typename C, typename S1, typename S2, typename F, typename T1, typename T2>
    void sendCommand(F&& func, std::weak_ptr<T1> t1, std::weak_ptr<T2> t2);

    template<typename C, typename S1, typename F, typename T1>
    void sendCommand(F&& func, T1 t1);
    template<typename C, typename S1, typename S2, typename F, typename T1, typename T2>
    void sendCommand(F&& func, T1 t1, T2 t2);

private:
    WeakAnyPtr destination;

    DataProxy masterDataProxy;
    DataProxy slaveDataProxy;

    template <typename F>
    void sendFunction(F&& fn);

    ENABLE_TYPE_ERASURE_BASE();

};

#include "data_transmitter.hpp"
