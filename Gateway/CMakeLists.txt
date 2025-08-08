cmake_minimum_required(VERSION 3.10)
project(GatewayApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Chemin vers SilKit
include_directories(
    ../SilKit/include
)

# Lien vers la lib SilKit
link_directories(
    ../SilKit/lib
)

add_executable(GatewayDemo
    GatewayDemo.cpp
    GatewayApp.cpp
)

target_link_libraries(GatewayDemo
    SilKit
)
