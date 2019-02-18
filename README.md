
# simpleSDL

A simple crossplatform libSDL cmake build environment example/test. This is still somewhat
work in progress and is missing support for iOS builds.

Tested to build and run successfully with:
  - Android: gradle + cmake
  - Windows: mingw-w64
  - Windows: Visual Studio 2015
  - Linux (Ubuntu): GCC
  - Mac: (Just building a simple executable, no bundle)
  - Emscripten


Building on Android
-------------------

You need to have NDK and cmake plugins installed on Android SDK
(https://developer.android.com/studio/projects/add-native-code.html)

1. Copy/clone `SDL` to the `contrib/` directory

1. run `gradlew assemble` in `platforms/android`

   or

   Open the project in Android Studio and build using the IDE. NOTE: Make sure
   to open the `platforms/android/` dir. Android studio can also
   open the root dir but it's not recognized as an android project.

The included android gradle cmake project is pretty much what Android Studio
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
