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
    echo [INFO] Image %IMAGE_NAME% does not exist locally. Building, please wait...
    echo [INFO] This process can take a few minutes.
    docker build -t %IMAGE_NAME% . > docker_build.log 2>&1

    if !errorlevel! neq 0 (
        echo [ERROR] Something went wrong during installation.
        echo [ERROR] Open file "docker_build.log" for more details.
        pause
        exit /b 1
    )
    echo [INFO] ^Image successfully created
)

echo [INFO] Launching container, please wait...

:: Map to work directory inside container
docker run -it ^
    --name uvmenv_container ^
    -e DISPLAY=host.docker.internal:0.0 ^
    -v /tmp/.X11-unix:/tmp/.X11-unix ^
    -v "%cd%:/uvmenv_repo" ^
    -v uvmenv_data:/home/developer/workspace ^
    %IMAGE_NAME% %*

if %errorlevel% neq 0 (
    echo.
    echo [NOTA] If error running GTKWave, Ensure your server X11 is running with "Disable access control" disabled.
)
