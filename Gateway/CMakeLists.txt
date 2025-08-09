cmake_minimum_required(VERSION 3.14)
project(Gateway LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SilKit paths (ajuste si besoin)
set(SILKIT_INCLUDE_DIR "../SilKit/include")
set(SILKIT_LIB_DIR "../SilKit/lib")

add_executable(GatewayDemo GatewayApp.cpp GatewayApp.hpp)

target_include_directories(GatewayDemo PRIVATE ${SILKIT_INCLUDE_DIR})
target_link_directories(GatewayDemo PRIVATE ${SILKIT_LIB_DIR})
target_link_libraries(GatewayDemo PRIVATE SilKit pthread)
