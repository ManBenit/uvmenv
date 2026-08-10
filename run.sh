#!/usr/bin/env bash

# Configuración de la imagen
IMAGE_NAME="uvmenv-framework:latest"

echo -e "\e[32m[INFO] Iniciando contenedor UVMEnv con soporte para GTKWave...\e[39m"

# Otorgar permisos al servidor X11 si está disponible
if command -v xhost >/dev/null 2>&1; then
    xhost +local:docker >/dev/null 2>&1
fi

# Configuración de sockets X11 para la interfaz gráfica
X11_SOCKET="/tmp/.X11-unix"
DISPLAY_VAR="${DISPLAY:-:0}"

# Construir la imagen localmente si no existe
if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo -e "\e[33m[INFO] La imagen $IMAGE_NAME no se encontró localmente. Construyendo...\e[39m"
    # docker build --progress=plain -t "$IMAGE_NAME" . 2>&1 | tee build_docker.log
    docker build -t "$IMAGE_NAME" .
fi

# Ejecutar contenedor
docker run -it --rm \
    --name uvmenv_container \
    -e DISPLAY="$DISPLAY_VAR" \
    -v "$X11_SOCKET:$X11_SOCKET" \
    -v "$(pwd):/uvmenv_repo" \
    "$IMAGE_NAME" "$@"
