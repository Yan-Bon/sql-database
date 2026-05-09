add_executable(ClientApp Source.cpp)

# Найти Boost
find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(ClientApp PRIVATE Boost::system)
target_include_directories(ClientApp PRIVATE ${Boost_INCLUDE_DIRS})

