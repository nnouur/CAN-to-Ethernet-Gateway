#include "GatewayApp.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <ParticipantName> <ConfigFile>\n";
        return 1;
    }

    try
    {
        GatewayApp app(argv[1], argv[2]);
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error starting Gateway: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
