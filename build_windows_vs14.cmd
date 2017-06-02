@echo off
setlocal
set PROJECT_DIR=%~dp0

set BUILD_DIR=%PROJECT_DIR%\platforms\windows_vs14_win64
set CMAKE_EXE=cmake.exe

:: Builds just the debug version
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" || goto error
pushd "%BUILD_DIR%" || goto error
::call %CMAKE_EXE% -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE:STRING=Debug "%PROJECT_DIR%" || goto error
call %CMAKE_EXE% -G "Visual Studio 14 2015 Win64" "%PROJECT_DIR%" || goto error
popd

goto end

:error
echo Build failed!
exit /b 1

:end
