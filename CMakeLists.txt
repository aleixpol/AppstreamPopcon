project(AppStreamPopcon)

cmake_minimum_required(VERSION 3.0)

find_package(Qt5 REQUIRED COMPONENTS Core Network)
find_package(AppstreamQt REQUIRED)
find_package(KF5Archive REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(appstreampopcon AppStreamPopcon.cpp main.cpp)
target_link_libraries(appstreampopcon Qt5::Core Qt5::Network KF5::Archive AppstreamQt)

install(TARGETS appstreampopcon RUNTIME DESTINATION bin)
