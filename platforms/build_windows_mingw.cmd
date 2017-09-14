@echo off
setlocal
title=mingw [building]
set PROJECT_DIR=%~dp0\..
set BUILD_DIR=%PROJECT_DIR%\.build\win32_mingw_make

:: Setup the build environment
if exist "%MINGW_HOME%\bin\mingw32-make.exe" goto mingw_ok
echo MinGW not found or location not defined (MINGW_HOME="%MINGW_HOME%")
goto error
:mingw_ok
::set VERBOSE_BUILD="VERBOSE=1"
set CMAKE_EXE=cmake.exe
set MAKE_EXE=%MINGW_HOME%\bin\mingw32-make.exe



:: Build debug version
if not exist "%BUILD_DIR%_debug" mkdir "%BUILD_DIR%_debug" || goto error
pushd "%BUILD_DIR%_debug" || goto error
call %CMAKE_EXE% -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Debug "%PROJECT_DIR%" || goto error
call %MAKE_EXE% %VERBOSE_BUILD% || goto error
popd

:: Build release version
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" || goto error
pushd "%BUILD_DIR%" || goto error
call %CMAKE_EXE% -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=MinSizeRel "%PROJECT_DIR%" || goto error
call %MAKE_EXE% %VERBOSE_BUILD% || goto error
popd


goto end

:error
echo Build failed!
title=mingw [fail]
exit /b 1

:end
title=mingw [done]
