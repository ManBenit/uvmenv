#!/usr/bin/env bash

IMAGE_NAME="uvmenv-framework:latest"
CONTAINER_NAME="uvmenv_container"

# Grant permissions to X11 server if available
if command -v xhost >/dev/null 2>&1; then
    xhost +local:docker >/dev/null 2>&1
fi

X11_SOCKET="/tmp/.X11-unix"
DISPLAY_VAR="${DISPLAY:-:0}"

# 1. Verify if image exists (build it otherwise)
if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo -e "\e[33m[INFO] Image $IMAGE_NAME does not exist locally. Building, please wait...\e[39m"
    echo -e "\e[33m[INFO] This process can take a few minutes.\e[39m"
    
    if ! docker build -t "$IMAGE_NAME" . > docker_build.log 2>&1; then
        echo -e "\e[31m[ERROR] Something went wrong during installation.\e[39m"
        echo -e "\e[31m[ERROR] Open file 'docker_build.log' for more details.\e[39m"
        exit 1
    fi
    echo -e "\e[32m[INFO] Image successfully created\e[39m"
fi

# 2. Verify if container exists
if docker container inspect "$CONTAINER_NAME" >/dev/null 2>&1; then
    echo -e "\e[34m[INFO] Container $CONTAINER_NAME already exists.\e[39m"
    
    # Verify if container is running
    if [ "$(docker inspect -f '{{.State.Running}}' "$CONTAINER_NAME")" = "true" ]; then
        echo -e "\e[32m[INFO] Container is already running. Opening new terminal session...\e[39m"
        docker exec -it "$CONTAINER_NAME" /bin/bash
    else
        echo -e "\e[32m[INFO] Starting existing stopped container...\e[39m"
        docker start -i "$CONTAINER_NAME"
    fi
else
    echo -e "\e[32m[INFO] Launching new container, please wait...\e[39m"

    # Map to work directory inside container
    docker run -it \
        --name "$CONTAINER_NAME" \
        -e DISPLAY="$DISPLAY_VAR" \
        -v "$X11_SOCKET:$X11_SOCKET" \
        -v "$(pwd):/uvmenv_repo" \
        -v uvmenv_data:/home/developer/workspace \
        "$IMAGE_NAME" "$@"
fi
