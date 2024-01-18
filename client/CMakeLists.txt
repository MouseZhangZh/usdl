find_package(Boost COMPONENTS system REQUIRED)
add_executable(usdl_client main.cpp)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
target_include_directories(usdl_client PUBLIC ${Boost_INCLUDE_DIRS})