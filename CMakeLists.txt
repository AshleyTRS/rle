cmake_minimum_required(VERSION 3.10)
project(RLEApp)

if(MSVC)
    add_compile_options(/utf-8)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

include_directories(src/core src/ui)

add_executable(RLEApp WIN32
    src/main.cpp
    src/core/RLE.cpp
    src/ui/MainFrame.cpp
)

target_link_libraries(RLEApp ${wxWidgets_LIBRARIES})
target_compile_definitions(RLEApp PRIVATE UNICODE _UNICODE)
target_compile_options(RLEApp PRIVATE ${wxWidgets_CXX_FLAGS})