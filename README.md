
# simpleSDL

A simple crossplatform libSDL cmake build environment example/test. This is still somewhat
work in progress and is missing support for iOS builds.

Tested to build and run successfully with:
  - Android: gradle + cmake
  - Android: gradle + ndk-build
  - Windows: mingw-w64
  - Windows: Visual Studio 2015
  - Linux (Ubuntu): GCC
  - Mac: (Just building a simple executable, no bundle)
  - Emscripten


Building on Android
-------------------

> NOTE:
>
> There is an issue trying to build SDL using NDK r14 both with ndk-build
> and cmake (https://github.com/android-ndk/ndk/issues/361). Make sure you have
> the latest NDK (at least r15).
>
> Also currently (2018-02-25) the latest SDL version from mercurial is needed.
> It has some fixes for gradle+cmake build for android.

You need to have NDK and cmake plugins installed on Android SDK
(https://developer.android.com/studio/projects/add-native-code.html)

1. Copy/clone `SDL` to the `contrib/` directory

1. run `gradlew assemble` in `platforms/android`

   or

   Open the project in Android Studio and build using the IDE. NOTE: Make sure
   to open the `platforms/android/` dir. Android studio can also
   open the root dir but it's not recognized as an android project.

The project includes two versions of the same app. One is built using the old ndk-build system and the other one is using cmake.

The included android gradle cmake project is pretty much what current Android Studio
generates when you create a new empty app with native cmake support. Just
pointing to the CmakeLists.txt in the project root.

> NOTE:
>
> Currently the SDL2 Android Java code is included in this project. This is not a very good system
> as it easily leads to the SDL Java and native code being out of sync (i.e. code from different versions of SDL).
> You should replace the Java sources from the version of SDL you are using to make sure they are from the same version.


Todo
----

- Nicer way to include SDL in an android project. [A missing android feature](https://issuetracker.google.com/issues/37134163) is needed to include
prebuilt native library with headers in a .aar package.
- iOS build
- Add instructions how to build on all platforms
