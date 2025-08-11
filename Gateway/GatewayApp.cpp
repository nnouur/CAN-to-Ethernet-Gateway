#include "GatewayApp.hpp"
#include <iostream>
#include <vector>


GatewayApp::GatewayApp(const std::string& participantName,
                      const std::string& configFilePath)
{
   auto participantConfig =
       SilKit::Config::ParticipantConfigurationFromFile(configFilePath);


   _participant = SilKit::CreateParticipant(participantConfig, participantName);


   // Connexion aux contrôleurs existants
   _canController = _participant->CreateCanController("CAN1", "CAN1");
   _ethController = _participant->CreateEthernetController("ETH1", "ETH1");


   // Abonnement CAN → Ethernet
   _canController->AddFrameHandler(
       [this](SilKit::Services::Can::ICanController* /*ctrl*/,
              const SilKit::Services::Can::CanFrameEvent& frameEvent) {
           OnCanFrameReceived(frameEvent.frame);
       });


   // Abonnement Ethernet → CAN
   _ethController->AddFrameHandler(
       [this](SilKit::Services::Ethernet::IEthernetController* /*ctrl*/,
              const SilKit::Services::Ethernet::EthernetFrameEvent& frameEvent) {
           OnEthernetFrameReceived(frameEvent.frame);
       });
}


void GatewayApp::OnCanFrameReceived(const SilKit::Services::Can::CanFrame& canFrame)
{
   SilKit::Services::Ethernet::EthernetFrame ethFrame;


   // Copier le contenu car Span n'a pas assign
   std::vector<uint8_t> data(canFrame.dataField.begin(), canFrame.dataField.end());
   ethFrame.raw = data;


   _ethController->SendFrame(ethFrame);
   std::cout << "[Gateway] CAN → ETH frame sent, size=" << canFrame.dataField.size() << "\n";
}


void GatewayApp::OnEthernetFrameReceived(const SilKit::Services::Ethernet::EthernetFrame& ethFrame)
{
   SilKit::Services::Can::CanFrame canFrame{};
   canFrame.canId = 0x123; // Nom de champ correct dans SilKit
   canFrame.flags = {};
  
   std::vector<uint8_t> data(ethFrame.raw.begin(), ethFrame.raw.end());
   canFrame.dataField = data;


   _canController->SendFrame(canFrame);
   std::cout << "[Gateway] ETH → CAN frame sent, size=" << ethFrame.raw.size() << "\n";
}


void GatewayApp::Run()
{
   std::cout << "[Gateway] Running..." << std::endl;


   // SilKit n’a pas de Run() → juste attendre
   while (true)
   {
       std::this_thread::sleep_for(std::chrono::seconds(1));
   }
}


// -------- main (single-file approach) --------


int main(int argc, char** argv)
{
   if (argc < 3)
   {
       std::cerr << "Usage: " << argv[0] << " <ParticipantName> <ConfigFilePath>\n";
       return 1;
   }


   try
   {
       std::string participantName = argv[1];
       std::string configPath = argv[2];


       GatewayApp app(participantName, configPath);
       app.Run();
   }
   catch (const std::exception& e)
   {
       std::cerr << "[Gateway] Exception: " << e.what() << "\n";
       return 1;
   }


   return 0;
}

