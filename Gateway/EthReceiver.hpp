#pragma once

#include <silkit/SilKit.hpp>
#include <silkit/services/can/all.hpp>
#include <silkit/services/orchestration/all.hpp>
#include "silkit/services/all.hpp"



#include <silkit/services/ethernet/all.hpp>
#include <thread>
#include <atomic>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <vector>

class EthReceiver
{
public:
    using IEthernetController = SilKit::Services::Ethernet::IEthernetController;
    using EthernetFrame       = SilKit::Services::Ethernet::EthernetFrame;
    using EthernetFrameEvent  = SilKit::Services::Ethernet::EthernetFrameEvent;

    explicit EthReceiver(IEthernetController* ctrl)
        : _eth(ctrl)
    {}

    // Register frame handler and start worker thread that copies payloads into the global buffer
    void Start();

    // Stop worker thread
    void Stop();

private:
    void RxThreadLoop();
    // Called in SIL Kit callback thread
    void OnEthernetFrame(const EthernetFrameEvent& ev);

private:
    IEthernetController* _eth{nullptr};

    // Local queue for frames received in callbacks -> processed by Rx thread
    std::deque<EthernetFrame> _rxQueue;
    std::mutex _mx;
    std::condition_variable _cv;

    std::atomic<bool> _running{false};
    std::thread _rxThread;
};
