#include "GatewayApp.hpp"
#include <iostream>
#include <vector>

using namespace SilKit::Services;

GatewayApp::GatewayApp(const std::string& participantName, const std::string& configFile)
{
    _participant = SilKit::CreateParticipant(
        SilKit::Config::ParticipantConfigurationFromFile(configFile),
        participantName
    );

    _canController = _participant->CreateCanController("CAN1", "CAN1");
    _ethController = _participant->CreateEthernetController("ETH1", "ETH1");

    SetupCanToEthernet();
    SetupEthernetToCan();
}

void GatewayApp::SetupCanToEthernet()
{
    _canController->AddFrameHandler(
        [this](ICanController*, const Can::CanFrameEvent& frameEvent) 
        {
            std::cout << "[Gateway] CAN → Ethernet | ID: 0x" << std::hex << frameEvent.frame.canId
                      << " DLC: " << std::dec << static_cast<int>(frameEvent.frame.dataField.size()) << "\n";

            Ethernet::EthernetFrame ethFrame;
            std::vector<uint8_t> rawData(frameEvent.frame.dataField.begin(), frameEvent.frame.dataField.end());
            ethFrame.raw = rawData;

            _ethController->SendFrame(ethFrame);
        }
    );
}

void GatewayApp::SetupEthernetToCan()
{
    _ethController->AddFrameHandler(
        [this](IEthernetController*, const Ethernet::EthernetFrameEvent& ethEvent) 
        {
            std::cout << "[Gateway] Ethernet → CAN | Size: " << ethEvent.frame.raw.size() << "\n";

            Can::CanFrame canFrame;
            canFrame.canId = 0x123; // ID fixe
            canFrame.flags = {};
            std::vector<uint8_t> canData(ethEvent.frame.raw.begin(), ethEvent.frame.raw.end());
            canFrame.dataField = canData;

            _canController->SendFrame(canFrame);
        }
    );
}

