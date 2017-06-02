cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(simpleSDL C CXX)

#
# Set some helper variables.
#
set(projectDir "${CMAKE_CURRENT_LIST_DIR}")
set(sourceDir       "${projectDir}/source")
set(binDir          "${projectDir}/bin")


if(ANDROID)
	# NOTE: This name (with the typo?) is what the SDL_AndroidCMake fork current seems to require.
	set(targetName "MySDLMainActivitiy")
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${binDir})
	set(targetName "simpleExample")
endif()


if(NOT ANDROID)
	find_package(OpenGL REQUIRED)
endif()


#
# Using SDL as a subproject for simplicity.
# NOTE: CMAKE_C_FLAGS set anywhere here are also passed to SDL.
#
set(SDL_STATIC OFF CACHE STRING "") # Don't build static SDL lib as this project is using just the dynamic one.

if(ANDROID)
	# NOTE: for now using the SDL_AndroidCMake only for only on android.
	# (there were some other issues when building with mingw)
	set(sdlDir "${projectDir}/contrib/SDL_AndroidCMake")
else()
	set(VIDEO_OPENGLES OFF CACHE STRING "")
	set(sdlDir "${projectDir}/contrib/SDL")
endif()

add_subdirectory(${sdlDir})


#
# Sources (relative to the project root dir).
#
file(GLOB_RECURSE projectSources RELATIVE ${projectDir}
	"${sourceDir}/*.h"
	"${sourceDir}/*.c"
	"${sourceDir}/*.cpp"
)

# Include dirs.
set(projectIncludeDirs ${projectIncludeDirs}
	"${sdlDir}/include"
)

message("Sources: ${projectSources}\n")
message("Include dirs: ${projectIncludeDirs}\n")

#
# Platform dependent stuff.
#
if(MINGW)
	# -Create 32-bit executable
	# -Link standard libs statically to reduce dll clutter.
	# -lmingw32 is needed to make WinMain not disappear when linking.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -static -static-libstdc++ -lmingw32")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -static -static-libgcc -lmingw32")

	# Disable console in release builds and strip unused dependencies.
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-mwindows -s")
	set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-mwindows -s")
endif()

#
# Build the binary.
# -----------------------------------------------------------------------
#
if(ANDROID)
	# On android native code is a shared library not an executable.
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

# Not really using C++11 but yeah.
set_property(TARGET ${targetName} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${targetName} PROPERTY CXX_STANDARD_REQUIRED ON)


