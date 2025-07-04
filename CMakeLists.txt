cmake_minimum_required(VERSION 3.16.3)
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/yaml-cpp")
find_package(yaml-cpp REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt5" ${CMAKE_PREFIX_PATH})
find_package(Qt5 REQUIRED COMPONENTS Widgets Charts Multimedia)



if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS ON)

project(CS2D_tp
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/Yakolin/CS2D-grupo-13"
    LANGUAGES CXX
    )

option(CS2D_TESTS "Enable / disable tests." ON)
option(CS2D_CLIENT "Enable / disable client program." ON)
option(CS2D_SERVER "Enable / disable server program." ON)
option(CS2D_EDITOR "Enable / disable editor program." ON)
option(CS2D_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Define target: lib common between client, server and editor programs
# HEY TODO XXX: change the name to something that you like
add_library(CS2D_common STATIC)

# add the source files that make the lib
# HEY!! TODO XXX: add more subfolders here
add_subdirectory(common/)


# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(CS2D_common ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(CS2D_common PUBLIC .)

# HEY!! TODO XXX: you need to install some runtime and dev libraries *before*
# compiling the client/editor code.
#
# In xubuntu 24.04 these are:
#
# sudo apt-get install libopus-dev libopusfile-dev libxmp-dev libfluidsynth-dev fluidsynth libwavpack1 libwavpack-dev libfreetype-dev wavpack
#

# Install libSDL2 and libSDL2pp (for client or editor)
# HEY!! TODO XXX: add more dependendies (either for client, server or editor)
if(CS2D_CLIENT OR CS2D_EDITOR)
    include(FetchContent)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.8
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-2.8.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.22.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        libSDL2pp
        OVERRIDE_FIND_PACKAGE
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf libSDL2pp)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2 REQUIRED)
    find_library(SDL2_GFX_LIBRARY SDL2_gfx REQUIRED)


endif()

# Program section
# ---------------
if(CS2D_CLIENT)

    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(CS2D_client)
    # para que me deje compilar las rutas correctamente
    set_target_properties(CS2D_client PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

    # Make them depend on CS2D_common lib
    add_dependencies(CS2D_client CS2D_common SDL2pp::SDL2pp)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(client)

    set_project_warnings(CS2D_client ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(CS2D_client PRIVATE 
        ${libSDL2pp_SOURCE_DIR}
        ${SDL2_image_SOURCE_DIR}/include
        ${SDL2_mixer_SOURCE_DIR}/include
        )


    # Link the CS2D_common lib target
    # Incluir Qt (Widgets)
    target_link_libraries(CS2D_client
        CS2D_common
        SDL2pp::SDL2pp
        Qt5::Widgets
        SDL2_image
        yaml-cpp
        Qt5::Multimedia
        SDL2_mixer  
        SDL2_ttf
        Qt5::Charts
        ${SDL2_GFX_LIBRARY}
    )

endif()

# Commenting out the server, editor, and tests sections
if(CS2D_SERVER)

    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(CS2D_server)

    # Make them depend on CS2D_common lib
    add_dependencies(CS2D_server CS2D_common)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(server)

    set_project_warnings(CS2D_server ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

    find_package(Threads REQUIRED)

    # Link the CS2D_common lib target
    target_link_libraries(CS2D_server 
        CS2D_common
        Threads::Threads
        yaml-cpp
    )

endif()

if(CS2D_EDITOR)
    #add_executable(CS2D_editor)
    #add_dependencies(CS2D_editor CS2D_common SDL2pp::SDL2pp)
    #add_subdirectory(editor)
    #set_project_warnings(CS2D_editor ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)
    #target_include_directories(CS2D_editor PRIVATE ${libSDL2pp_SOURCE_DIR})
    #target_link_libraries(CS2D_editor CS2D_common SDL2pp::SDL2pp)
endif()
if(CS2D_TESTS)
    # Let's use google test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    # (borrowed from https://google.github.io/googletest/quickstart-cmake.html)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    # target for testing
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(CS2D_tests)

    # HEY!! TODO XXX: I'm assuming that the code under testing is in CS2D_common
    # Change this if you have to.
    add_dependencies(CS2D_tests CS2D_common)

    # Say where to find the xoz headers
    # HEY!! TODO XXX: add more subfolders here
    target_include_directories(CS2D_tests PUBLIC .)

    # Add the source files to the CS2D_tests target
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(tests/)

    # Set the compiler warnings to the tests target (but be a little lesser strict)
    set_project_warnings(CS2D_tests ${CS2D_MAKE_WARNINGS_AS_ERRORS} TRUE)

    # Say where googletest headers can be found
    target_include_directories(CS2D_tests
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
        )

    # HEY!! TODO XXX: I'm assuming that the code under testing is in CS2D_common
    # Change this if you have to.
    target_link_libraries(CS2D_tests
        CS2D_common
        GTest::gmock_main
        yaml-cpp
    )
endif()