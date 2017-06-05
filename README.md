
# simpleSDL

A simple crossplatform libSDL cmake build environment example/test.

> WARNING: This is still work in progress and does not work with standard
> SDL without modifications.

Tested to build and run successfully with:
  - Android: ndk-build and gradle+cmake
  - Windows: mingw-w64
  - Windows: Visual Studio 2015
  - Linux (Ubuntu): GCC
  - Mac: (Just building a simple executable, no bundle)
  - Emscripten

But the main point is to fix SDL cmake support for Android builds.



Building within Android Studio or with standalone Gradle
--------------------------------------------------------

> NOTE: I had an issue trying to build SDL using the latest NDK (r14) both
> with ndk-build and gradle (https://github.com/android-ndk/ndk/issues/361).
> Seems that it's a bug in clang that has been fixed in NDK r15 Beta 2 (that
> must be currently downloaded manually from the NDK site
> https://developer.android.com/ndk/downloads/index.html).

You need to have NDK and cmake plugins installed on Android SDK
(https://developer.android.com/studio/projects/add-native-code.html)

1. Copy/clone `SDL` to the `contrib/` directory

1. Apply `android_fixes.patch` provided in the contrib dir to SDL. To do so in SDL dir run:  
  `hg import --no-commit ../android_fixes.patch`

1. run `gradlew assemble` in `platforms/android`

   or

   Open the project in Android Studio and build using the IDE. NOTE: Make sure
   to open the `platforms/android/` dir. Android studio can also
   open the root dir but it's not recognized as an android project.

The included android project is pretty much what current Android Studio
generates when you create a new empty app with native cmake support. Just
pointing to the CmakeLists.txt in the project root.


SDL fix details (all for cmake)
-------------------------------
- Fixed some missing CMakeLists.txt android cases and fixed android library
linking. Fixes https://bugzilla.libsdl.org/show_bug.cgi?id=3509

- SDL_spinlock.c is compiled in ARM mode if the target is an arm processor
(similarly to the old Android.mk).

- SDL_android_main.c is now properly compiled to the SDLmain.lib (SDLmain is
statically linked to the user code and SDL is a separate dynamic library).

- Android cmake build was failing when compiled using GCC on arm target. Fixed
with a patch from Martin Gerhardy https://bugzilla.libsdl.org/show_bug.cgi?id=3267
(+a minor formatting fix)

- As a whole the patch basically fixes https://bugzilla.libsdl.org/show_bug.cgi?id=3195.
The android example project in SDL should probably be updated to use gradle still.

Notes
-----

- All build artifacts are set to go to `.build` dir except for `.externalNativeBuild`
that is created by the android gradle cmake to `platforms/android/app`.
There is no way to change its location and it seems the dir needs to be deleted
sometimes, especially when making changes to the build system (bug
  https://issuetracker.google.com/issues/62264618).

- More discussion about android cmake build in
https://discourse.libsdl.org/t/sdl2-cmake-android-on-windows/21505/27

Todo
----

- Android: arm64-v8a abi is not compiling. Needs to be fixed in SDL_spinlock.c or with
some kind of compiler switches.
- Nicer way to include SDL in an android project. [A missing android feature](https://issuetracker.google.com/issues/37134163) is needed to include
prebuilt native library with headers in a .aar package.
- iOS build
