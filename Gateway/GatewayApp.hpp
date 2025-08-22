#pragma once

#include <silkit/SilKit.hpp>
#include <silkit/services/can/all.hpp>
#include <silkit/services/ethernet/all.hpp>

#include "../Common/ApplicationBase.hpp"

#include "EthReceiver.hpp"
#include "CanSender.hpp"

#include <string>
#include <memory>
#include <chrono>

class GatewayApp : public ApplicationBase
{
public:
    using ApplicationBase::ApplicationBase;
    ~GatewayApp();

private:
    // ApplicationBase hooks
    void AddCommandLineArgs() override;
    void EvaluateCommandLineArgs() override;
    void CreateControllers() override;
    void InitControllers() override;
    void DoWorkSync(std::chrono::nanoseconds) override {}
    void DoWorkAsync() override {}

private:
    // Controllers
    SilKit::Services::Can::ICanController* _can{nullptr};
    SilKit::Services::Ethernet::IEthernetController* _eth{nullptr};

    // Worker threads
    std::unique_ptr<EthReceiver> _ethRx;
    std::unique_ptr<CanSender>   _canTx;

    // Config
    std::string _canNetwork = "CAN1";
    std::string _ethNetwork = "ETH1";
};
