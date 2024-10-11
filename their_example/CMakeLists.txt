cmake_minimum_required(VERSION 3.25)

project(example)

set(IRIS_ENHANCED_INSTALL_DIR /cta/users/fozdemir/dev/local_pckgs/iris-enhanced/usr/local)

add_library(OpenMPKernel SHARED kernel.cl.openmp.h kernel.cl.openmp.c)
target_include_directories(OpenMPKernel PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/include)
target_link_directories(OpenMPKernel PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/lib)
target_link_libraries(OpenMPKernel PRIVATE iris)
set_target_properties(OpenMPKernel PROPERTIES PREFIX "")
set_target_properties(OpenMPKernel PROPERTIES OUTPUT_NAME "kernel.openmp.so")
set_target_properties(OpenMPKernel PROPERTIES SUFFIX "")

add_library(PolicyGWS SHARED policy_gws.cpp)
target_include_directories(PolicyGWS PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/include)
target_link_directories(PolicyGWS PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/lib)
target_link_libraries(PolicyGWS PRIVATE iris)

add_library(PolicyGWSHook SHARED policy_gws_hook.cpp)
target_include_directories(PolicyGWSHook PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/include)
target_link_directories(PolicyGWSHook PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/lib)
target_link_libraries(PolicyGWSHook PRIVATE iris)

add_executable(test main.cpp)

target_include_directories(test PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/include)
target_link_directories(test PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/lib)
target_link_libraries(test PRIVATE iris)
target_link_libraries(test PRIVATE PolicyGWS)
target_link_libraries(test PRIVATE PolicyGWSHook)





