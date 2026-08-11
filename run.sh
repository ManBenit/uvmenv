#!/usr/bin/env bash

IMAGE_NAME="uvmenv-framework:latest"

echo -e "\e[32m[INFO] Iniciando contenedor UVMEnv con soporte para GTKWave...\e[39m"

# Otorgar permisos al servidor X11 si está disponible
if command -v xhost >/dev/null 2>&1; then
    xhost +local:docker >/dev/null 2>&1
fi

X11_SOCKET="/tmp/.X11-unix"
DISPLAY_VAR="${DISPLAY:-:0}"

if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo -e "\e[33m[INFO] La imagen $IMAGE_NAME no se encontró localmente. Construyendo...\e[39m"
    docker build -t "$IMAGE_NAME" .
fi

# Mapear al directorio de trabajo correcto dentro del contenedor
docker run -it --rm \
    --name uvmenv_container \
    -e DISPLAY="$DISPLAY_VAR" \
    -v "$X11_SOCKET:$X11_SOCKET" \
    -v "$(pwd):/home/developer/uvmenv_repo" \
    "$IMAGE_NAME" "$@"
    