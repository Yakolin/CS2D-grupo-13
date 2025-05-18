# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-src"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-build"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/tmp"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
