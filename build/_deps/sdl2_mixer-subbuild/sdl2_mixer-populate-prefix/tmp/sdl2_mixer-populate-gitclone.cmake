# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitclone-lastrun.txt" AND EXISTS "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitinfo.txt" AND
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitclone-lastrun.txt" IS_NEWER_THAN "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --depth 1 --no-single-branch --progress --config "advice.detachedHead=false" "https://github.com/libsdl-org/SDL_mixer.git" "sdl2_mixer-src"
    WORKING_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/libsdl-org/SDL_mixer.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "release-2.8.0" --
  WORKING_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'release-2.8.0'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitinfo.txt" "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/sdl2_mixer-populate-gitclone-lastrun.txt'")
endif()
