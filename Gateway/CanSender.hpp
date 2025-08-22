#pragma once

#include <silkit/SilKit.hpp>
#include <silkit/services/orchestration/all.hpp>
#include "silkit/services/all.hpp"



#include <silkit/services/can/all.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <cstdint>

class CanSender
{
public:
    using ICanController = SilKit::Services::Can::ICanController;
    using CanFrame       = SilKit::Services::Can::CanFrame;

    explicit CanSender(ICanController* ctrl, uint32_t canId = 0x123)
        : _can(ctrl)
        , _canId(canId)
    {}

    void Start();  // start worker that pops from GlobalBuffer and sends to CAN
    void Stop();

private:
    void TxThreadLoop();

private:
    ICanController* _can{nullptr};
    std::atomic<bool> _running{false};
    std::thread _txThread;
    uint32_t _canId{0x123};
};
