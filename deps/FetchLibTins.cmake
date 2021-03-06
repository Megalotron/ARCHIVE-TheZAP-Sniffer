cmake_minimum_required(VERSION 3.17)

include(ExternalProject)

ExternalProject_Add(
        libtins
        GIT_REPOSITORY  https://github.com/mfontanini/libtins.git
        GIT_TAG         origin/master
        BUILD_COMMAND   ${CMAKE_COMMAND} -DLIBTINS_ENABLE_CXX11=1 .
        COMMAND         ${CMAKE_COMMAND} --build .
        INSTALL_COMMAND ""
        TEST_COMMAND    ""
)