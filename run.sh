#!/usr/bin/env bash

IMAGE_NAME="uvmenv-framework:latest"

echo -e "\e[32m[INFO] Starting container...\e[39m"

# Otorgar permisos al servidor X11 si está disponible
if command -v xhost >/dev/null 2>&1; then
    xhost +local:docker >/dev/null 2>&1
fi

X11_SOCKET="/tmp/.X11-unix"
DISPLAY_VAR="${DISPLAY:-:0}"

if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo -e "\e[33m[INFO] Image $IMAGE_NAME does not exist locally. Building...\e[39m"
    docker build -t "$IMAGE_NAME" .
fi

# Map to work directory inside container
docker run -it --rm \
    --name uvmenv_container \
    -e DISPLAY="$DISPLAY_VAR" \
    -v "$X11_SOCKET:$X11_SOCKET" \
    -v "$(pwd):/uvmenv_repo" \
    "$IMAGE_NAME" "$@"
