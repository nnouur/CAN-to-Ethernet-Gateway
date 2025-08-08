#pragma once

#include <silkit/SilKit.hpp>
#include <silkit/services/can/all.hpp>
#include <silkit/services/ethernet/all.hpp>
#include <silkit/services/orchestration/all.hpp>

#include <memory>
#include <string>

#include "../CAN/CanDemoCommon.hpp"

#include "../Common/ApplicationBase.hpp"
#include "../Common/CommandlineParser.hpp"
#include "../Common/SignalHandler.hpp"

#include "../ETHERNET/EthernetDemoCommon.hpp"

#include "silkit/services/all.hpp"


class GatewayApp
{
public:
    GatewayApp(const std::string& participantName, const std::string& configFile);
    void Run();

private:
    void SetupCanToEthernet();
    void SetupEthernetToCan();

    std::shared_ptr<SilKit::IParticipant> _participant;
    SilKit::Services::Can::ICanController* _canController{nullptr};
    SilKit::Services::Ethernet::IEthernetController* _ethController{nullptr};
};
