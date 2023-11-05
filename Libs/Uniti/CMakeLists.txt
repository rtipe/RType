cmake_minimum_required(VERSION 3.22)

message(STATUS "Fetching Uniti")

FetchContent_Declare(Uniti
        GIT_REPOSITORY https://github.com/rtipe/Uniti.git
        GIT_TAG V0.0.7)
FetchContent_MakeAvailable(Uniti)