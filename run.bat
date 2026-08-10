@echo off
setlocal enabledelayedexpansion

set IMAGE_NAME=uvmenv-tools:latest

echo [INFO] Verificando estado de Docker...
docker info >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Docker no esta en ejecucion. Por favor inicia Docker Desktop.
    pause
    exit /b 1
)

:: Verificar si la imagen existe localmente, si no, construirla
docker image inspect %IMAGE_NAME% >nul 2>&1
if %errorlevel% neq 0 (
    echo [INFO] La imagen %IMAGE_NAME% no existe localmente. Construyendo imagen...
    docker build -t %IMAGE_NAME% .
)

echo [INFO] Lanzando contenedor con soporte para GTKWave...

:: Lanzar contenedor mapeando la pantalla X11 y el directorio actual
docker run -it --rm ^
    --name uvmenv_container ^
    -e DISPLAY=host.docker.internal:0 ^
    -v "%cd%:/uvmenv_repo" ^
    %IMAGE_NAME% %*

if %errorlevel% neq 0 (
    echo.
    echo [NOTA] Si no abre GTKWave, asegúrate de que tu servidor X11 (ej. VcXsrv) o WSLg esté habilitado.
)
