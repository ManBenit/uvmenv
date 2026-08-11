@echo off
setlocal enabledelayedexpansion

:: Unificamos el nombre de la imagen con el script de Linux
set IMAGE_NAME=uvmenv-framework:latest

echo [INFO] Verificando estado de Docker...
docker info >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Docker no esta en ejecucion. Por favor inicia Docker Desktop.
    pause
    exit /b 1
)

docker image inspect %IMAGE_NAME% >nul 2>&1
if %errorlevel% neq 0 (
    echo [INFO] La imagen %IMAGE_NAME% no existe localmente. Construyendo imagen...
    docker build -t %IMAGE_NAME% .
)

echo [INFO] Lanzando contenedor con soporte para GTKWave...

:: Mapear al directorio de trabajo correcto dentro del contenedor
docker run -it --rm ^
    --name uvmenv_container ^
    -e DISPLAY=host.docker.internal:0 ^
    -v "%cd%:/home/developer/uvmenv_repo" ^
    %IMAGE_NAME% %*

if %errorlevel% neq 0 (
    echo.
    echo [NOTA] Si no abre GTKWave, asegurate de que tu servidor X11 -como VcXsrv- este corriendo con "Disable access control" activado.
)
