#!/bin/bash

spinner() {
    local pid=$1 # PID of process
    local spinner_chars='|/-\'
    local i=0

    # While process is alive...
    while kill -0 $pid 2>/dev/null; do
        # Extract a diferent character each time
        local c="${spinner_chars:i++%${#spinner_chars}:1}"
        printf "\r[%s] Please wait..." "$c"
        sleep 0.1
    done

    # Clean line and finish
    printf "\r[✓] Process finished! \n"
}

spinner "$@"
