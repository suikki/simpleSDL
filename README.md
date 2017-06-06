
# simpleSDL

A simple crossplatform libSDL cmake build environment example/test. This is still somewhat
work in progress and is missing support for iOS builds.

Tested to build and run successfully with:
  - Android: ndk-build and gradle+cmake
  - Windows: mingw-w64
  - Windows: Visual Studio 2015
  - Linux (Ubuntu): GCC
  - Mac: (Just building a simple executable, no bundle)
  - Emscripten



Building on Android
-------------------

> NOTE: I had an issue trying to build SDL using the latest NDK (r14) both
> with ndk-build and gradle (https://github.com/android-ndk/ndk/issues/361).
> Seems that it's a bug in clang that has been fixed in NDK r15 Beta 2 (that
> must be currently downloaded manually from the NDK site
> https://developer.android.com/ndk/downloads/index.html).

You need to have NDK and cmake plugins installed on Android SDK
(https://developer.android.com/studio/projects/add-native-code.html)

1. Copy/clone `SDL` to the `contrib/` directory

1. run `gradlew assemble` in `platforms/android`

   or

   Open the project in Android Studio and build using the IDE. NOTE: Make sure
   to open the `platforms/android/` dir. Android studio can also
   open the root dir but it's not recognized as an android project.

The included android project is pretty much what current Android Studio
generates when you create a new empty app with native cmake support. Just
pointing to the CmakeLists.txt in the project root.



Notes
-----

- All build artifacts are set to go to `.build` dir except for `.externalNativeBuild`
that is created by the android gradle cmake to `platforms/android/app`.
There is no way to change its location currently and it seems that the dir needs
to be deleted sometimes, especially when making changes to the build system (bug
  https://issuetracker.google.com/issues/62264618).


Todo
----

- Android: arm64-v8a abi is not compiling. Needs to be fixed in SDL_spinlock.c or with
some kind of compiler switches.
- Nicer way to include SDL in an android project. [A missing android feature](https://issuetracker.google.com/issues/37134163) is needed to include
prebuilt native library with headers in a .aar package.
- iOS build
- Add instructions how to build on all platforms
