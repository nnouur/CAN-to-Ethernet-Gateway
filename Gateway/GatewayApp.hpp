#pragma once

#include <silkit/services/can/Can.hpp>
#include <silkit/services/ethernet/Ethernet.hpp>
#include <silkit/services/orchestration/ILifecycleService.hpp>
#include <silkit/services/orchestration/ParticipantState.hpp>
#include <silkit/services/orchestration/IParticipantLifecycle.hpp>
#include <silkit/services/orchestration/ILifecycleService.hpp>
#include <silkit/services/orchestration/IApplication.hpp>
#include <silkit/config/IParticipantConfiguration.hpp>
#include <silkit/participant/Participant.hpp>

#include <memory>
#include <string>

class GatewayApp
{
public:
    GatewayApp(const std::string& participantName, const std::string& canNetwork, const std::string& ethernetNetwork);

    void Start();

private:
    void SetupCan();
    void SetupEthernet();

    std::shared_ptr<SilKit::IParticipant> _participant;
    SilKit::Services::Can::ICanController* _canController{nullptr};
    SilKit::Services::Ethernet::IEthernetController* _ethernetController{nullptr};

    std::string _canNetwork;
    std::string _ethernetNetwork;
};
