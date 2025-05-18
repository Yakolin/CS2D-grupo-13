# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-src"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-build"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/tmp"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
