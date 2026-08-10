FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# 1. Instalar dependencias del sistema y sudo
RUN apt update && apt install -y \
    nlohmann-json3-dev \
    libyaml-cpp-dev \
    pybind11-dev \
    git \
    tree \
    jq \
    help2man \
    perl \
    python3 \
    python3-pip \
    python3-venv \
    make \
    autoconf \
    g++ \
    flex \
    bison \
    ccache \
    gperf \
    libgoogle-perftools-dev \
    numactl \
    perl-doc \
    libfl2 \
    libfl-dev \
    zlib1g \
    zlib1g-dev \
    gtkwave \
    x11-apps \
    x11-utils \
    dbus-x11 \
    fonts-liberation \
    bc \
    sudo \
    vim \
    nano \
    && rm -rf /var/lib/apt/lists/*

# 2. Instalar dependencias globales de Python
RUN pip3 install --no-cache-dir --break-system-packages \
    "cocotb<2" \
    "cocotb-coverage<2" \
    pyuvm \
    pyfiglet \
    colorama \
    pytest

# 3. Compilar e instalar Icarus Verilog
RUN git clone https://github.com/steveicarus/iverilog.git /tmp/iverilog && \
    cd /tmp/iverilog && \
    chmod 775 autoconf.sh && \
    ./autoconf.sh && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/iverilog

# 4. Compilar e instalar Verilator
RUN git clone https://github.com/verilator/verilator.git /tmp/verilator && \
    cd /tmp/verilator && \
    unset VERILATOR_ROOT && \
    autoconf && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/verilator

# 5. Crear usuario no-root ("developer") y darle permisos sudo
RUN useradd -m -s /bin/bash developer && \
    echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

WORKDIR /home/developer/uvmenv_repo
RUN chown -R developer:developer /home/developer/uvmenv_repo

USER developer

# Copiar el proyecto
COPY --chown=developer:developer . /home/developer/uvmenv_repo

RUN mkdir /home/developer/uvmenv_install

# Ejecutar la instalación de UVMEnv como usuario no-root
RUN chmod +x install.sh 2>/dev/null || true
RUN if [ -f "./install.sh" ]; then echo "y" | ./install.sh --home /home/developer/uvmenv_install; fi

# Configurar explícitamente UVMENV_HOME pointing al directorio bin/ y añadirlo al PATH
ENV USER=developer
ENV UVMENV_HOME=/home/developer/uvmenv_install
ENV PATH="${UVMENV_HOME}/bin:${PATH}"


# Escribir la variable en el .bashrc para sesiones interactivas
# RUN echo 'export UVMENV_HOME=/home/developer/uvmenv_install' >> /home/developer/.bashrc && \
#     echo 'export PATH="$UVMENV_HOME/bin:$PATH"' >> /home/developer/.bashrc

# RUN echo 'force_color_prompt=yes' >> /home/developer/.bashrc && \
#     echo 'parse_git_branch() {' >> /home/developer/.bashrc && \
#     echo '    git branch 2> /dev/null | sed -e '\''/^[^*]/d'\'' -e '\''s/* \(.*\)/(\1)/'\''' >> /home/developer/.bashrc && \
#     echo '}' >> /home/developer/.bashrc && \
#     echo 'PS1='\''${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[01;31m\]$(parse_git_branch)\[\033[00m\]\$ '\'' >> /home/developer/.bashrc


WORKDIR /home/developer

CMD ["/bin/bash"]
