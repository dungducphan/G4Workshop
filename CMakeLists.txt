cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# Using C++ 20 standard
set(CMAKE_CXX_STANDARD 17)

# Name of the project
project(g4workshop)

# Locate the dependencies
find_package(Geant4 REQUIRED ui_all vis_all multithreaded)
find_package(ROOT REQUIRED Core)

include(${Geant4_USE_FILE})
include(${ROOT_USE_FILE})

# Globbing the source and header files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)

# Globbing the macro files and copy to build directory
file(GLOB MACROS "*.mac")
file(COPY ${MACROS} DESTINATION ${PROJECT_BINARY_DIR})

# Locate the user-defined header files
include_directories(${PROJECT_SOURCE_DIR}/inc)

# List the source files to compile the target (in this case is our simulation executable)
add_executable(g4sim sim.cc ${sources} ${headers})

# Link to dependency libraries
target_link_libraries(g4sim ${Geant4_LIBRARIES})
target_link_libraries(g4sim ${ROOT_LIBRARIES})
