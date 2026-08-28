@echo off
setlocal enabledelayedexpansion

:: Unify image and container names
set IMAGE_NAME=uvmenv-framework:latest
set CONTAINER_NAME=uvmenv_container

docker info >nul 2>&1
if !errorlevel! neq 0 (
    echo [ERROR] Docker is not running. Please start Docker Desktop.
    pause
    exit /b 1
)

:: 1. Verify if image exists (build it otherwise)
docker image inspect %IMAGE_NAME% >nul 2>&1
if !errorlevel! neq 0 (
    echo [INFO] Image %IMAGE_NAME% does not exist locally. Building, please wait...
    echo [INFO] This process can take a few minutes.
    docker build -t %IMAGE_NAME% . > docker_build.log 2>&1

    if !errorlevel! neq 0 (
        echo [ERROR] Something went wrong during installation.
        echo [ERROR] Open file "docker_build.log" for more details.
        pause
        exit /b 1
    )
    echo [INFO] Image successfully created
)

:: 2. Verify if container exists
docker container inspect %CONTAINER_NAME% >nul 2>&1
if !errorlevel! equ 0 (
    echo [INFO] Container %CONTAINER_NAME% already exists.
    
    :: Verify if container is running
    for /f "tokens=*" %%i in ('docker inspect -f "{{.State.Running}}" %CONTAINER_NAME%') do set IS_RUNNING=%%i
    
    if "!IS_RUNNING!"=="true" (
        echo [INFO] Container is already running. Opening new terminal session...
        docker exec -it %CONTAINER_NAME% /bin/bash
    ) else (
        echo [INFO] Starting existing stopped container...
        docker start -i %CONTAINER_NAME%
    )
) else (
    echo [INFO] Launching new container, please wait...

    :: Map to work directory inside container
    docker run -it ^
        --name %CONTAINER_NAME% ^
        -e DISPLAY=host.docker.internal:0.0 ^
        -v /tmp/.X11-unix:/tmp/.X11-unix ^
        -v "%cd%:/uvmenv_repo" ^
        -v uvmenv_data:/home/developer/workspace ^
        %IMAGE_NAME% %*
)

if !errorlevel! neq 0 (
    echo.
    echo [NOTA] If error running GTKWave, Ensure your server X11 is running with "Disable access control" disabled.
)
