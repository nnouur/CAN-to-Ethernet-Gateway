#include "EthReceiver.hpp"
#include "GlobalBuffer.hpp"

#include <iostream>
#include <sstream>

using namespace SilKit::Services::Ethernet;

void EthReceiver::Start()
{
    if (!_eth) return;

    // Subscribe to incoming Ethernet frames
    _eth->AddFrameHandler([this](IEthernetController*, const EthernetFrameEvent& frameEvent) {
        std::stringstream stream;
        stream << "[Gateway] Received Ethernet frame ("
               << frameEvent.frame.raw.size() << " bytes)";
        std::cout << stream.str() << std::endl;
        // Forward the frame into the Rx queue
        OnEthernetFrame(frameEvent);
    });

    _running = true;
    _rxThread = std::thread(&EthReceiver::RxThreadLoop, this);
}

void EthReceiver::Stop()
{
    _running = false;
    _cv.notify_all();
    if (_rxThread.joinable()) _rxThread.join();
}

void EthReceiver::OnEthernetFrame(const EthernetFrameEvent& ev)
{
    {
        std::lock_guard<std::mutex> lock(_mx);
        _rxQueue.emplace_back(ev.frame);
    }
    _cv.notify_one();
}

void EthReceiver::RxThreadLoop()
{
    while (_running)
    {
        EthernetFrame frame;
        {
            std::unique_lock<std::mutex> lock(_mx);
            _cv.wait(lock, [this]{ return !_rxQueue.empty() || !_running; });
            if (!_running && _rxQueue.empty()) break;
            frame = std::move(_rxQueue.front());
            _rxQueue.pop_front();
        }

        // Strip Ethernet header (14 bytes) to keep only payload
        std::vector<uint8_t> payload;
        if (frame.raw.size() > 14)
        {
            payload.assign(frame.raw.begin() + 14, frame.raw.end());
        }
        else
        {
            // Short frame: just forward raw
            payload.assign(frame.raw.begin(), frame.raw.end());
        }

        // Push into the global buffer for the CAN sender thread
        GetGlobalBuffer().Push(std::move(payload));

        // 💡 Log after pushing to buffer
        std::stringstream stream;
        stream << "[Gateway] Forwarded Ethernet payload to CAN sender ("
               << payload.size() << " bytes)";
        std::cout << stream.str() << std::endl;
    }
}
