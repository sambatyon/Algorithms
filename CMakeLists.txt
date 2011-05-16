project(algorithms)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS -std=gnu++0x)
endif()

add_executable(algorithms main.cc heap.cc sort.cc red-black.cc sort.cc binary-tree.cc graph.cc)

