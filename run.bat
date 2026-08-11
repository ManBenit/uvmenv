@echo off
setlocal enabledelayedexpansion

:: Unify image name
set IMAGE_NAME=uvmenv-framework:latest

echo [INFO] Verificando estado de Docker...
docker info >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Docker is not running. Please start Docker Desktop.
    pause
    exit /b 1
)

docker image inspect %IMAGE_NAME% >nul 2>&1
if %errorlevel% neq 0 (
    echo [INFO] Image %IMAGE_NAME% does not exist locally. Building...
    docker build -t %IMAGE_NAME% .
)

echo [INFO] Launching container...

:: Map to work directory inside container
docker run -it --rm ^
    --name uvmenv_container ^
    -e DISPLAY=host.docker.internal:0 ^
    -v "%cd%:/uvmenv_repo" ^
    %IMAGE_NAME% %*

if %errorlevel% neq 0 (
    echo.
    echo [NOTA] If error running GTKWave, Ensure your server X11 is running with "Disable access control" disabled.
)
