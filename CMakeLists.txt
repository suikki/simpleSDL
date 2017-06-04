cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(simpleSDL C CXX)

#
# Set some helper variables.
#
string(TOLOWER "${CMAKE_SYSTEM_NAME}" targetSystem)
set(projectDir  "${CMAKE_CURRENT_LIST_DIR}")
set(sourceDir   "${projectDir}/source")
set(targetName  "SimpleExample")
set(binDir      "${projectDir}/bin")

# Define executable output dir.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${binDir}/${targetSystem}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${binDir}/${targetSystem}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${binDir}/${targetSystem}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${binDir}/${targetSystem}_debug")


#
# Dependencies:
#   Using SDL as a subproject for simplicity.
#   NOTE: This means that CMAKE_C_FLAGS set anywhere here are also passed to SDL.
#
if(MINGW)
  set(VIDEO_OPENGLES OFF CACHE STRING "")
endif()

set(sdlDir "${projectDir}/contrib/SDL")
add_subdirectory(${sdlDir} EXCLUDE_FROM_ALL)


#
# Sources (relative to the project root dir).
#
file(GLOB_RECURSE projectSources RELATIVE ${projectDir}
  "${sourceDir}/*.h"
  "${sourceDir}/*.c"
)

# Include dirs.
set(projectIncludeDirs ${projectIncludeDirs}
  "${sdlDir}/include"
)

message("     Sources: ${projectSources}\n")
message("Include dirs: ${projectIncludeDirs}\n")


#
# Platform dependent stuff.
#

if(NOT ANDROID)
  find_package(OpenGL REQUIRED)
endif()

if(MINGW)
  # -Link standard libs statically to reduce dll clutter.
  # -lmingw32 is needed to make WinMain not disappear when linking.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -static-libgcc -lmingw32")

  # Only show the console in debug builds and also strip unused dependencies on MinSizeRel.
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-mconsole")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-mwindows")
  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-mwindows -s")
endif()

#
# Build the binary.
# -----------------------------------------------------------------------
#
if(ANDROID)
  # On android the final binary is a shared library not an executable.
  add_library(${targetName} SHARED ${projectSources})
else()
  add_executable(${targetName} ${projectSources})
endif()

target_link_libraries(${targetName}
  SDL2main
  SDL2
  ${OPENGL_LIBRARY}
)

target_include_directories(${targetName}
  PUBLIC ${projectIncludeDirs}
)


