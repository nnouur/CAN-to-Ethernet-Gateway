#include "CanSender.hpp"
#include "GlobalBuffer.hpp"
#include <iostream>   // for std::cout
#include <sstream>    // for std::stringstream

using namespace SilKit::Services::Can;

void CanSender::Start()
{
    if (!_can) return;
    _running = true;
    _txThread = std::thread(&CanSender::TxThreadLoop, this);
}

void CanSender::Stop()
{
    _running = false;
    // Wake any waiting PopBlocking by telling buffer to stop (non-destructive)
    GetGlobalBuffer().Stop();
    if (_txThread.joinable()) _txThread.join();
}

void CanSender::TxThreadLoop()
{
    while (_running)
    {
        std::vector<uint8_t> payload;
        if (!GetGlobalBuffer().PopBlocking(payload))
        {
            // Stop requested and queue empty
            break;
        }

        CanFrame frame{};
        frame.canId = _canId;
        frame.dataField = std::move(payload); // most SIL Kit versions support vector here

        // 💡 Log to console before sending
        std::stringstream stream;
        stream << "[Gateway] Sending CAN frame from Gateway (canId=" << frame.canId
               << ", size=" << frame.dataField.size() << " bytes)";
        std::cout << stream.str() << std::endl;

        _can->SendFrame(frame);
    }
}
