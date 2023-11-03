cmake_minimum_required (VERSION 3.8)

add_executable (StructReflector "StructReflector.cpp" "StructReflector.hpp" "Main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StructReflector PROPERTY CXX_STANDARD 20)
endif()
