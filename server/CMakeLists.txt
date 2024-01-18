find_package(Boost COMPONENTS system REQUIRED)
add_executable(usdl_server main.cpp)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
target_include_directories(usdl_server PUBLIC ${Boost_INCLUDE_DIRS})