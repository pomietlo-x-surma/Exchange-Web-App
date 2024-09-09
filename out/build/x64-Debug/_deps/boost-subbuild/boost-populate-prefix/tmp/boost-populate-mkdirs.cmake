# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-src"
  "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-build"
  "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-subbuild/boost-populate-prefix"
  "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-subbuild/boost-populate-prefix/tmp"
  "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp"
  "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-subbuild/boost-populate-prefix/src"
  "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/User/source/repos/Exchange-Web-App/out/build/x64-Debug/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
