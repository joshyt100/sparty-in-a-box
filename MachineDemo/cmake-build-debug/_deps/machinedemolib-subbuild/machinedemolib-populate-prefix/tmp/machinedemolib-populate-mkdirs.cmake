# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-src"
  "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-build"
  "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-subbuild/machinedemolib-populate-prefix"
  "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-subbuild/machinedemolib-populate-prefix/tmp"
  "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-subbuild/machinedemolib-populate-prefix/src/machinedemolib-populate-stamp"
  "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-subbuild/machinedemolib-populate-prefix/src"
  "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-subbuild/machinedemolib-populate-prefix/src/machinedemolib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-subbuild/machinedemolib-populate-prefix/src/machinedemolib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/joshthomas/spartybox/project2-starter/MachineDemo/cmake-build-debug/_deps/machinedemolib-subbuild/machinedemolib-populate-prefix/src/machinedemolib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
