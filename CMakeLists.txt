########################################################################################################################

    #Project

cmake_minimum_required(VERSION 3.15)
project(BlankProject)
set(CMAKE_CXX_STANDARD 20)

########################################################################################################################

    #Variables

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(SERVER_SRC_DIR "${SRC_DIR}/server")
set(CLIENT_SRC_DIR "${SRC_DIR}/client")
set(COMMON_SRC_DIR "${SRC_DIR}/common")
set(UT_DIR "${CMAKE_SOURCE_DIR}/test/ut")
set(IT_DIR "${CMAKE_SOURCE_DIR}/test/it")

########################################################################################################################

    #Flags

set(DEBUG_COMPILER_FLAGS -g -O0 -pedantic -Wall -Wextra -Wsign-conversion -fsanitize=address,leak,undefined)
set(DEBUG_LINKER_FLAGS -fsanitize=address,leak,undefined)
set(RELEASE_COMPILER_FLAGS -O2)
set(RELEASE_LINKER_FLAGS)

########################################################################################################################

    #Glob find files

function(find_src_files root_dir result_files)
    file(GLOB_RECURSE glob_files "${root_dir}/*.cpp")
    list(FILTER glob_files EXCLUDE REGEX "/main.cpp$")
    set("${result_files}" "${glob_files}" PARENT_SCOPE)
endfunction()

function(find_include_directories root_dir result_dirs)
    file(GLOB_RECURSE glob_dirs LIST_DIRECTORIES true "${root_dir}/*include")
    list(FILTER glob_dirs INCLUDE REGEX "/include$")
    set("${result_dirs}" "${glob_dirs}" PARENT_SCOPE)
endfunction()

file(GLOB_RECURSE SERVER_MAIN_SOURCE_FILES "${SERVER_SRC_DIR}*/main.cpp")
file(GLOB_RECURSE CLIENT_MAIN_SOURCE_FILES "${CLIENT_SRC_DIR}*/main.cpp")

find_src_files("${SERVER_SRC_DIR}" SERVER_SOURCE_FILES)
find_include_directories("${SERVER_SRC_DIR}" SERVER_INCLUDE_DIRS)

find_src_files("${CLIENT_SRC_DIR}" CLIENT_SOURCE_FILES)
find_include_directories("${CLIENT_SRC_DIR}" CLIENT_INCLUDE_DIRS)

find_src_files("${COMMON_SRC_DIR}" COMMON_SOURCE_FILES)
find_include_directories("${COMMON_SRC_DIR}" COMMON_INCLUDE_DIRS)

file(GLOB_RECURSE UT_SOURCES "${UT_DIR}/*.cpp")
find_include_directories("${UT_DIR}" UT_INCLUDE_DIRS)

file(GLOB_RECURSE IT_SOURCES "${IT_DIR}/*.cpp")
find_include_directories("${IT_DIR}" IT_INCLUDE_DIRS)

########################################################################################################################

    #Libraries

function(create_static_library lib_name source_files include_dirs compiler_flags linker_flags)
    add_library("${lib_name}" STATIC "${source_files}")
    target_include_directories("${lib_name}" PUBLIC "${include_dirs}")
    target_compile_options("${lib_name}" PUBLIC "${compiler_flags}")
    target_link_options("${lib_name}" PUBLIC "${linker_flags}")
endfunction()

if(SERVER_SOURCE_FILES)
    create_static_library(
        server_debug_lib
        "${SERVER_SOURCE_FILES}"
        "${SERVER_INCLUDE_DIRS}"
        "${DEBUG_COMPILER_FLAGS}"
        "${DEBUG_LINKER_FLAGS}")

    create_static_library(
        server_release_lib
        "${SERVER_SOURCE_FILES}"
        "${SERVER_INCLUDE_DIRS}"
        "${RELEASE_COMPILER_FLAGS}"
        "${RELEASE_LINKER_FLAGS}")
endif()

if(CLIENT_SOURCE_FILES)
    create_static_library(
        client_debug_lib
        "${CLIENT_SOURCE_FILES}"
        "${CLIENT_INCLUDE_DIRS}"
        "${DEBUG_COMPILER_FLAGS}"
        "${DEBUG_LINKER_FLAGS}")

    create_static_library(
        client_release_lib
        "${CLIENT_SOURCE_FILES}"
        "${CLIENT_INCLUDE_DIRS}"
        "${RELEASE_COMPILER_FLAGS}"
        "${RELEASE_LINKER_FLAGS}")
endif()

if(COMMON_SOURCE_FILES)
    create_static_library(
        common_debug_lib
        "${COMMON_SOURCE_FILES}"
        "${COMMON_INCLUDE_DIRS}"
        "${DEBUG_COMPILER_FLAGS}"
        "${DEBUG_LINKER_FLAGS}")

    create_static_library(
        common_release_lib
        "${COMMON_SOURCE_FILES}"
        "${COMMON_INCLUDE_DIRS}"
        "${RELEASE_COMPILER_FLAGS}"
        "${RELEASE_LINKER_FLAGS}")
endif()

########################################################################################################################

    #Google test

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

########################################################################################################################

    #Executables

function(create_executable exec_name main_source_files lib_source_files lib_name additional_libs)
    if(main_source_files)
        add_executable("${exec_name}" "${main_source_files}")
        set_target_properties("${exec_name}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
        if(lib_source_files)
            target_link_libraries("${exec_name}" PRIVATE "${lib_name}")
        endif()
        target_link_libraries("${exec_name}" PRIVATE ${additional_libs})
    endif()
endfunction()

if(COMMON_SOURCE_FILES)
    set(ADDITIONAL_DEBUG_LIBS common_debug_lib)
    set(ADDITIONAL_RELEASE_LIBS common_release_lib)
endif()

create_executable(server_debug "${SERVER_MAIN_SOURCE_FILES}" "${SERVER_SOURCE_FILES}" server_debug_lib "${ADDITIONAL_DEBUG_LIBS}")
create_executable(server_release "${SERVER_MAIN_SOURCE_FILES}" "${SERVER_SOURCE_FILES}" server_release_lib "${ADDITIONAL_RELEASE_LIBS}")

create_executable(client_debug "${CLIENT_MAIN_SOURCE_FILES}" "${CLIENT_SOURCE_FILES}" client_debug_lib "${ADDITIONAL_DEBUG_LIBS}")
create_executable(client_release "${CLIENT_MAIN_SOURCE_FILES}" "${CLIENT_SOURCE_FILES}" client_release_lib "${ADDITIONAL_RELEASE_LIBS}")

set(TEST_LIBS gtest_main)

if(SERVER_SOURCE_FILES)
    list(APPEND TEST_LIBS server_debug_lib)
endif()

if(CLIENT_SOURCE_FILES)
    list(APPEND TEST_LIBS client_debug_lib)
endif()

create_executable(ut "${UT_SOURCES}" "${COMMON_SOURCE_FILES}" common_debug_lib "${TEST_LIBS}")
create_executable(it "${IT_SOURCES}" "${COMMON_SOURCE_FILES}" common_debug_lib "${TEST_LIBS}")

########################################################################################################################
