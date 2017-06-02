@echo off
:: USAGE:
:: "build_android" -> builds android debug apk
:: "build_android clean" -> Detele previously built object files

setlocal
set PROJECT_DIR=%~dp0
set PLATFORM_DIR=%PROJECT_DIR%\platforms\android

set BUILD_TARGETS=assembleDebug

if /I "%1" == "clean" goto clean

pushd %PLATFORM_DIR%
call gradlew.bat %BUILD_TARGETS% || goto error
popd
goto end

:clean
pushd %PLATFORM_DIR%
call gradlew.bat clean || goto error
popd
goto end

:error
echo Build failed!
exit /b 1

:end
