
# simpleSDL

A simple crossplatform libSDL cmake build environment example/test.

> WARNING: This is still work in progress and does not work with standard
> SDL without modifications.

Tested quickly to be running successfully with:
  - Windows: mingw-w64 (32bit)
  - Windows: Visual Studio 2015 (64bit)
  - Android: (x86) (tested with emulator only)
  - Linux (Ubuntu): GCC (64bit)

But the main point is to fix SDL cmake support for Android builds.



Building within Android Studio / with Gradle
--------------------------------------------

1. Copy/clone/symlink SDL to the `contrib/` directory. The Android build
currently requires `SDL_AndroidCMake`  - a SDL2 fork with some android cmake
related fixes by Eric Wing:	https://bitbucket.org/ewing/sdl_androidcmake (And
the dir should be called SDL_AndroidCMake too).

1. run `gradlew assembleDebug` in or `platforms/android` dir (or on windows you
   can use the`build_android.cmd` in the project root)

   or

   Open the project in Android Studio and build using the IDE.

   NOTE: Make sure to open the `platforms/android/` dir. Android studio can also
   open the root folder but it's not recognized as an android project

The included android project is pretty much what current Android Studio
generates when you create a new empty app with native cmake support. Just
pointing to the CmakeLists.txt in the project root.



Notes
-----

- Currently set to only build x86 because of SDL compilation issues with setting
	 ARM/THUMB mode. So	basically only works on emulator if not fixed.

- All build artifacts are set to go to .build dir except for .externalNativeBuild
that is created by the android gradle cmake integration. There is no way to
change the location and it seems the folder needs to be deleted sometimes when
making changes to the build system.

- Not tested on mac.

- More discussion in https://discourse.libsdl.org/t/sdl2-cmake-android-on-windows/21505/27
