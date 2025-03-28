cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
get_filename_component(PROJECT_NAME ${PROJECT_ROOT} NAME)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

file(GLOB children RELATIVE "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/*")

set(EXTENSIONS h c hpp cpp hxx cxx)

foreach(child ${children})
    if(IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${child}")
		foreach(ext ${EXTENSIONS})
            file(GLOB_RECURSE tmp "${CMAKE_CURRENT_LIST_DIR}/${child}/*.${ext}")
            list(APPEND sources ${tmp})
        endforeach()

        add_executable(${child} ${sources})
        target_include_directories(${child} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/${child}")

        message(STATUS "Added executable: ${child}")
    endif()
endforeach()