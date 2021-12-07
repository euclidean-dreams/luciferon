cmake_minimum_required(VERSION 3.18)
project(luciferon)

set(CMAKE_CXX_STANDARD 14)

include(lib/cmake-utils/dependency-integrator.cmake)
integrate_cmake_dependency(
        NAME pigpio
        GIT_URL git@github.com:joan2937/pigpio.git
        GIT_TAG c33738a320a3e28824af7807edafda440952c05d
)
integrate_cmake_dependency(
        NAME impresario-utils
        GIT_URL git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/dev
)

set(
        SOURCE_FILES
        src/KeyholeConnection.cpp src/KeyholeConnection.h src/Constants.h src/Luciferon.cpp src/Luciferon.h
)
list(APPEND TARGETS luciferon)
add_executable(luciferon src/main.cpp ${SOURCE_FILES})

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_include_directories(${target} PRIVATE ${CMAKE_BINARY_DIR}/pigpio-src)
    target_link_libraries(${target} PRIVATE pigpio)
    target_link_libraries(${target} PRIVATE pthread)
    target_link_libraries(${target} PRIVATE fmt)
    target_link_libraries(${target} PRIVATE impresario-utils)
    target_link_libraries(${target} PRIVATE zmq)
endforeach ()
