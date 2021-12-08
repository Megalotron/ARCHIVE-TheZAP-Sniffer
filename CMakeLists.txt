cmake_minimum_required(VERSION 3.17)

project(TheZap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

option(BUILD_TESTS "When sets to ON, builds the unit tests" OFF)

if(BUILD_TESTS)
    set(BIN TheZapTests)
    include(deps/FetchGoogleTest.cmake)
else()
    set(BIN TheZap)
endif()

include(deps/FetchLibTins.cmake)

add_compile_options(-Wall -Wextra -Weffc++)

set(COMMON_SOURCES
    common/src/logger.cpp
)

set(COMMON_TEST_SOURCES
    common/tests/test_logger.cpp
)

set(INJECTOR_SOURCES
    injector/src/injector.cpp
)

set(INJECTOR_TEST_SOURCES
    injector/tests/test_injector.cpp
)

set(SNIFFER_SOURCES
    sniffer/src/sniffer.cpp
)

set(SNIFFER_TEST_SOURCES
    sniffer/tests/test_sniffer.cpp
)

if(BUILD_TESTS)
    add_executable(${BIN}
        ${COMMON_SOURCES}
        ${INJECTOR_SOURCES}
        ${SNIFFER_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${INJECTOR_TEST_SOURCES}
        ${SNIFFER_TEST_SOURCES}
    )
    target_include_directories(${BIN} PRIVATE
        injector/include
        sniffer/include
        common/include
    )
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(${BIN})
    target_link_libraries(${BIN} PRIVATE gtest_main)
else()
    add_executable(${BIN}
        ${COMMON_SOURCES}
        ${INJECTOR_SOURCES}
        ${SNIFFER_SOURCES}
        common/src/main.cpp
    )
    target_include_directories(${BIN} PRIVATE
        injector/include
        sniffer/include
        common/include
    )
endif()

# PTHREAD

target_link_libraries(${BIN} PRIVATE pthread)

# PCAP

target_link_libraries(${BIN} PRIVATE pcap)

# libtins

add_dependencies(${BIN} libtins)
ExternalProject_Get_Property(libtins install_dir)
target_link_directories(${BIN} PRIVATE ${install_dir}/src/libtins-build/lib)
target_link_libraries(${BIN} PRIVATE tins)
target_include_directories(${BIN} PRIVATE ${install_dir}/src/libtins/include)