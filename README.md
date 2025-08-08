# CAN-to-Ethernet-Gateway
This project focuses on the development of a CAN-to-Ethernet Gateway using C++, which enables the translation and routing of messages between a CAN bus and an Ethernet network.


***FOR THE CAN APPLICATION ***

Step1 : Run the SIL Kit Registry
    1.Open a terminal.
    2.Navigate to the SilKit registry directory:
        cd SilKit/bin
    3.Start the SIL Kit Registry:
        ./sil-kit-registry

Step2 :  Start the System Controller
    1.cd CAN/build
    or mkdir build 
        cd build
        cmake ..
        make
    2. ../../SilKit/bin/sil-kit-system-controller --configuration ../configs/SilKitConfig.yaml CanWriter CanReader

    ps: --configuration: path to the simulation config file

  
Step3 : Run the CAN Reader
    1. cd CAN/build
    2. ./CanReaderDemo --config ../configs/SilKitConfig.yaml

Step4 : Run the CAN Writer
    1.cd CAN/build
    2. ./CanWriterDemo --config ../configs/SilKitConfig.yaml


***FOR THE Ethernet APPLICATION ***

Step1 : Run the SIL Kit Registry
    1.Open a terminal.
    2.Navigate to the SilKit registry directory:
        cd SilKit/bin
    3.Start the SIL Kit Registry:
        ./sil-kit-registry

Step2 :  Start the System Controller
    1.cd ETHERNET/build
    or mkdir build 
        cd build
        cmake ..
        make
    2. ../../SilKit/bin/sil-kit-system-controller --configuration ../configs/SilKitConfig.yaml EthernetWriter EthernetReader

    ps: --configuration: path to the simulation config file

Step3 : Run the ETHERNET Reader
    1. cd ETHERNET/build
    2. ./EthernetReaderDemo --network Eth1

Step4 : Run the ETHERNET Writer
    1.cd ETHERNET/build
    2. ./EthernetWriterDemo --network Eth1



./GatewayDemo ../Gateway/GatewayConfig.yaml Gateway


./GatewayDemo ../GatewayConfig.yaml
