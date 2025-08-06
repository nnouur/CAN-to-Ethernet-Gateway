#include "GatewayApp.hpp"
#include <silkit/config/ParticipantConfiguration.hpp>
#include <silkit/services/orchestration/ILifecycleService.hpp>
#include <iostream>
#include <vector>

using namespace SilKit;
using namespace SilKit::Services::Can;
using namespace SilKit::Services::Ethernet;

GatewayApp::GatewayApp(const std::string& participantName, const std::string& canNetwork, const std::string& ethernetNetwork)
    : _canNetwork{canNetwork}, _ethernetNetwork{ethernetNetwork}
{
    auto config = SilKit::Config::ParticipantConfigurationFromString(R"(
        ParticipantConfiguration:
            logging:
                sinks:
                  - type: Stdout
                    level: Info
    )");

    _participant = SilKit::CreateParticipant(config, participantName);

    SetupCan();
    SetupEthernet();
}

void GatewayApp::SetupCan()
{
    _canController = _participant->CreateCanController("CAN_Controller", _canNetwork);

    _canController->AddFrameHandler(
        [this](ICanController*, const CanFrameEvent& event) {
            std::cout << "[Gateway] Received CAN frame, forwarding to Ethernet" << std::endl;

            // Extract CAN data into a vector
            std::vector<uint8_t> payload(event.frame.data.begin(), event.frame.data.begin() + event.frame.dlc);

            // Create Ethernet frame with the payload
            EthernetFrame ethFrame;
            ethFrame.raw = payload;

            _ethernetController->SendFrame(ethFrame);
        });
}

void GatewayApp::SetupEthernet()
{
    _ethernetController = _participant->CreateEthernetController("ETH_Controller", _ethernetNetwork);

    _ethernetController->AddFrameHandler(
        [this](IEthernetController*, const EthernetFrameEvent& event) {
            std::cout << "[Gateway] Received Ethernet frame, forwarding to CAN" << std::endl;

            // Extract Ethernet payload into vector
            std::vector<uint8_t> payload = event.frame.raw;

            // Construct CAN frame
            CanFrame canFrame;
            canFrame.canId = 0x123;
            canFrame.flags = CanFrameFlag::None;
            canFrame.dlc = static_cast<uint8_t>(payload.size());

            // Copy up to 8 bytes (max for CAN)
            std::copy_n(payload.begin(), std::min<size_t>(8, payload.size()), canFrame.data.begin());

            _canController->Send(canFrame);
        });
}

void GatewayApp::Start()
{
    auto* lifecycleService = _participant->GetLifecycleService();

    lifecycleService->SetCommunicationReadyHandler([] {
        std::cout << "[Gateway] Communication ready." << std::endl;
    });

    lifecycleService->StartLifecycle();
    lifecycleService->Run(); // blocking call
}
