cmake_minimum_required(VERSION 3.15)

project(test)

# Custom Policy shared library creation START
set(CUSTOM_POLICY_SOURCES 
    custom_policies/custom_policy.hpp
    custom_policies/custom_policy.cpp    
)

add_library(CustomPolicy SHARED ${CUSTOM_POLICY_SOURCES})

target_include_directories(CustomPolicy PRIVATE $ENV{LOCAL_BINARIES}/include)

target_link_directories(CustomPolicy PRIVATE $ENV{LOCAL_BINARIES}/lib)

target_link_libraries(CustomPolicy PRIVATE iris)
# Custom Policy shared library creation END

# Copy kernels to proper directories START

file(GLOB KERNEL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_kernels/*")

add_custom_command(TARGET CustomPolicy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${KERNEL_FILES}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Test START
add_executable(test main.cpp)

target_include_directories(test PRIVATE $ENV{LOCAL_BINARIES}/include)

target_link_directories(test PRIVATE $ENV{LOCAL_BINARIES}/lib)

target_link_libraries(test PRIVATE iris)

target_link_libraries(test PRIVATE CustomPolicy)
# Test END