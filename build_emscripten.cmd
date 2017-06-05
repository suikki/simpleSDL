@echo off
setlocal
title=emscripten [building]
set PROJECT_DIR=%~dp0
set BUILD_DIR=%PROJECT_DIR%\.build\emscripten

:: Setup the build environment
if exist "%EMSCRIPTEN_HOME%\emsdk.bat" goto emscripten_ok
echo Emscripten not found or location not defined (EMSCRIPTEN_HOME="%EMSCRIPTEN_HOME%")
goto error
:emscripten_ok
::set VERBOSE_BUILD="VERBOSE=1"
call "%EMSCRIPTEN_HOME%\emsdk.bat" activate latest
set CMAKE_EXE=emcmake cmake
set MAKE_EXE=emmake make


:: Build debug version
if not exist "%BUILD_DIR%_debug" mkdir "%BUILD_DIR%_debug" || goto error
pushd "%BUILD_DIR%_debug" || goto error
call %CMAKE_EXE% -D CMAKE_BUILD_TYPE:STRING=Debug "%PROJECT_DIR%" || goto error
call %MAKE_EXE% %VERBOSE_BUILD% || goto error
popd

:: Build release version
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" || goto error
pushd "%BUILD_DIR%" || goto error
call %CMAKE_EXE% -D CMAKE_BUILD_TYPE:STRING=Release "%PROJECT_DIR%" || goto error
call %MAKE_EXE% %VERBOSE_BUILD% || goto error
popd


goto end

:error
echo Build failed!
title=emscripten [fail]
exit /b 1

:end
title=emscripten [done]
