project(algorithms)

if(WIN32)
  set(CMAKE_GENERATOR "Visual Studio 10")
else()
  set(CMAKE_GENERATOR "Unix Makefiles")
  set(CMAKE_CXX_FLAGS -std=gnu++0x)
endif()



add_executable(algorithms main.cc heap.cc sort.cc red-black.cc sort.cc binary-tree.cc graph.cc)

