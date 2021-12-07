cmake_minimum_required(VERSION 3.17)

include(ExternalProject)

ExternalProject_Add(
        libtins
        GIT_REPOSITORY  https://github.com/mfontanini/libtins.git
        GIT_TAG         origin/master
        BUILD_COMMAND   ${CMAKE_COMMAND} . -B build/ -DCMAKE_BUILD_TYPE=Debug
        COMMAND         ${CMAKE_COMMAND} --build build/
)