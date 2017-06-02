@echo off
setlocal
set PROJECT_DIR=%~dp0

:: Remove comments for verbose mode.
::set VERBOSE_BUILD="VERBOSE=1"

set BUILD_DIR=%PROJECT_DIR%\.build\win32_mingw_make
set CMAKE_EXE=cmake.exe
set MAKE_EXE=%MINGW_HOME%\bin\mingw32-make.exe


:: Builds just the debug version
if not exist "%BUILD_DIR%_debug" mkdir "%BUILD_DIR%_debug" || goto error
pushd "%BUILD_DIR%_debug" || goto error
call %CMAKE_EXE% -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Debug "%PROJECT_DIR%" || goto error
call %MAKE_EXE% %VERBOSE_BUILD% || goto error_pop
popd

goto end

:error
echo Build failed!
exit /b 1

:end
