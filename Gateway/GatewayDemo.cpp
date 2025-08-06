#include "GatewayApp.hpp"
#include <string>

int main(int argc, char** argv)
{
    std::string canNetwork = "CAN1";
    std::string ethernetNetwork = "ETH1";

    GatewayApp app("GatewayParticipant", canNetwork, ethernetNetwork);
    app.Start();

    return 0;
}
