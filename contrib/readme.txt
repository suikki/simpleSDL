
Copy/clone/symlink dependencies to this dir
-------------------------------------------
	 SDL - Tested against SDL version 2.0.9 (stable)
	       Download from: https://www.libsdl.org/release/SDL2-2.0.9.zip
	       Or clone latest source with: hg clone http://hg.libsdl.org/SDL


	Note: If you are not using the same version you need to copy all .java files from:
		simpleSDL/contrib/SDL/android-project/app/src/main/java/org/libsdl/app/
	to:
		simpleSDL/platforms/android/android-app-cmake/src/main/java/org/libsdl/app/

	*** I Had to remove all the joystick/HID stuff because apparently when building
	    with cmake SDL is not building any of that :|
