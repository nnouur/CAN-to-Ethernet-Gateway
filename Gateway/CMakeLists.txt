cmake_minimum_required(VERSION 3.14)

project(Gateway LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SilKit paths (adjust based on actual location)
set(SILKIT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../SilKit")
set(SILKIT_INCLUDE_DIR "${SILKIT_ROOT_DIR}/include")
set(SILKIT_LIB_DIR "${SILKIT_ROOT_DIR}/lib")

# Debug output
message(STATUS "SilKit include: ${SILKIT_INCLUDE_DIR}")
message(STATUS "SilKit lib: ${SILKIT_LIB_DIR}")

# Headers and sources
set(COMMON_HEADERS GatewayApp.hpp)

add_executable(GatewayDemo GatewayDemo.cpp GatewayApp.cpp ${COMMON_HEADERS})

# Fix the include path
target_include_directories(GatewayDemo PRIVATE ${SILKIT_INCLUDE_DIR})

# Link libraries
target_link_directories(GatewayDemo PRIVATE ${SILKIT_LIB_DIR})
target_link_libraries(GatewayDemo PRIVATE pthread SilKit)
