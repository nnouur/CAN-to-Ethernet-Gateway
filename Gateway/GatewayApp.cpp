#include "GatewayApp.hpp"
#include "../CAN/CanDemoCommon.hpp"
#include "../ETHERNET/EthernetDemoCommon.hpp"

using namespace SilKit::Services;

GatewayApp::~GatewayApp()
{
    if (_canTx) _canTx->Stop();
    if (_ethRx) _ethRx->Stop();
}

void GatewayApp::AddCommandLineArgs()
{
    GetCommandLineParser()->Add<CommandlineParser::Option>(
        "can-network", "C", _canNetwork, "-C, --can-network <name>",
        std::vector<std::string>{"CAN network name. Defaults to '" + _canNetwork + "'."});

    GetCommandLineParser()->Add<CommandlineParser::Option>(
        "eth-network", "E", _ethNetwork, "-E, --eth-network <name>",
        std::vector<std::string>{"Ethernet network name. Defaults to '" + _ethNetwork + "'."});
}

void GatewayApp::EvaluateCommandLineArgs()
{
    _canNetwork = GetCommandLineParser()->Get<CommandlineParser::Option>("can-network").Value();
    _ethNetwork = GetCommandLineParser()->Get<CommandlineParser::Option>("eth-network").Value();
}

void GatewayApp::CreateControllers()
{
    // Create controllers on the networks used by your existing apps
    _can = GetParticipant()->CreateCanController("GatewayCanController", _canNetwork);
    _eth = GetParticipant()->CreateEthernetController("GatewayEthernetController", _ethNetwork);

    // TX acks logging (handlers in *DemoCommon must be inline to avoid ODR)
    _can->AddFrameTransmitHandler([this](Can::ICanController*, const Can::CanFrameTransmitEvent& ack) {
        CanDemoCommon::FrameTransmitHandler(ack, GetLogger());
    });
    _eth->AddFrameTransmitHandler([this](Ethernet::IEthernetController*, const Ethernet::EthernetFrameTransmitEvent& ack) {
        EthernetDemoCommon::FrameTransmitHandler(ack, GetLogger());
    });
}

void GatewayApp::InitControllers()
{
    // Bring controllers up like your other demos
    _eth->Activate();
    _can->Start();

    // Start worker 1: Ethernet receiver -> GlobalBuffer
    _ethRx = std::make_unique<EthReceiver>(_eth);
    _ethRx->Start();
    std::cout << "[Gateway] Ethernet Receiver started\n";


    // Start worker 2: GlobalBuffer -> CAN sender
    _canTx = std::make_unique<CanSender>(_can, 0x123);
    _canTx->Start();
    std::cout << "[Gateway] CAN Sender started\n";
}

// ---------- MAIN inside the same file ----------
int main(int argc, char** argv)
{
    Arguments args;
    args.participantName = "Gateway";
    args.duration = 5ms; // keep it small and responsive

    GatewayApp app{args};
    app.SetupCommandLineArgs(argc, argv, "SIL Kit Demo - Ethernet->CAN Gateway (2-thread)");
    return app.Run();
}
