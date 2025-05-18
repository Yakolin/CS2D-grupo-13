# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-src"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-build"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/tmp"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src"
  "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/mari/OneDrive/Desktop/tp final taller/CS2D-grupo-13/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
