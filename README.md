# CAN-to-Ethernet Gateway

This project focuses on the development of a **CAN-to-Ethernet Gateway** using C++, enabling the translation and routing of messages between a CAN bus and an Ethernet network.

---

## 🚗 **For the CAN Application**

### **Step 1 — Run the SIL Kit Registry**
1. Open a terminal.  
2. Navigate to the SIL Kit registry directory:  
   ```bash
   cd SilKit/bin
3. Start the SIL Kit Registry:
    ```bash
    ./sil-kit-registry

### **Step 2 -  Start the System Controller**
1.  ```bash
    cd CAN/build
    or mkdir build 
        cd build
        cmake ..
        make
2.  ```bash
    ../../SilKit/bin/sil-kit-system-controller --configuration ../configs/SilKitConfig.yaml CanWriter CanReader

    ps: --configuration: path to the simulation config file

  
### **Step 3 - Run the CAN Reader**
1.  ```bash
    cd CAN/build
2.  ```bash
    ./CanReaderDemo --config ../configs/SilKitConfig.yaml

### **Step 3 - Run the CAN Writer**
1. ```bash
    cd CAN/build
2. ```bash
    ./CanWriterDemo --config ../configs/SilKitConfig.yaml


## **🌐 For the Ethernet Application**

### **Step 1 - Run the SIL Kit Registry**
1. Open a terminal.
2. Navigate to the SilKit registry directory:
    ```bash
    cd SilKit/bin
3. Start the SIL Kit Registry:
    ```bash
    ./sil-kit-registry

### **Step 2 -  Start the System Controller**
1.  ```bash
    cd ETHERNET/build
    or mkdir build 
        cd build
        cmake ..
        make
2.  ```bash
    ../../SilKit/bin/sil-kit-system-controller --configuration ../configs/SilKitConfig.yaml EthernetWriter EthernetReader

    ps: --configuration: path to the simulation config file

### **Step 3 -  Run the ETHERNET Reader**
1.  ```bash
    cd ETHERNET/build
2.  ```bash
    ./EthernetReaderDemo --network Eth1

### **Step 4 - Run the ETHERNET Writer**
1.  ```bash
    cd ETHERNET/build
2.  ```bash
    ./EthernetWriterDemo --network Eth1



```bash
./GatewayDemo ../Gateway/GatewayConfig.yaml Gateway


./GatewayDemo ../GatewayConfig.yaml
./GatewayDemo GatewayParticipant ConfigFile.yaml

./GatewayDemo Gateway ../configs/SilKitConfig.yaml