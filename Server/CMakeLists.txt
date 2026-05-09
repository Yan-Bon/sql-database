file(GLOB_RECURSE SERVER_SOURCES
    *.cpp
    *.h
)

add_executable(ServerApp ${SERVER_SOURCES})

# Подключение nlohmann/json (через system install или CMake FetchContent)
find_package(nlohmann_json REQUIRED)

target_link_libraries(ServerApp PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(ServerApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

