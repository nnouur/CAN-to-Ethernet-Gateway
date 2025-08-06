cmake_minimum_required(VERSION 3.14)

project(EthernetDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SilKit paths (update if needed)
set(SILKIT_INCLUDE_DIR "../SilKit/include")
set(SILKIT_LIB_DIR "../SilKit/lib")

# Common headers
set(COMMON_HEADERS EthernetDemoCommon.hpp)

# EthernetWriterDemo
add_executable(EthernetWriterDemo EthernetWriterDemo.cpp ${COMMON_HEADERS})
target_include_directories(EthernetWriterDemo PRIVATE ${SILKIT_INCLUDE_DIR} ../SilKit)
target_link_directories(EthernetWriterDemo PRIVATE ${SILKIT_LIB_DIR})
target_link_libraries(EthernetWriterDemo PRIVATE pthread SilKit)

# EthernetReaderDemo
add_executable(EthernetReaderDemo EthernetReaderDemo.cpp ${COMMON_HEADERS})
target_include_directories(EthernetReaderDemo PRIVATE ${SILKIT_INCLUDE_DIR} ../SilKit)
target_link_directories(EthernetReaderDemo PRIVATE ${SILKIT_LIB_DIR})
target_link_libraries(EthernetReaderDemo PRIVATE pthread SilKit)
