FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# 1. Instalar dependencias del sistema
RUN apt update && apt install -y \
    nlohmann-json3-dev libyaml-cpp-dev pybind11-dev git tree jq help2man \
    perl python3 python3-pip python3-venv make autoconf g++ flex bison \
    ccache gperf libgoogle-perftools-dev numactl perl-doc libfl2 libfl-dev \
    zlib1g zlib1g-dev gtkwave x11-apps x11-utils dbus-x11 fonts-liberation \
    bc sudo vim nano \
    && rm -rf /var/lib/apt/lists/*

# 2. Instalar dependencias globales de Python
RUN pip3 install --no-cache-dir --break-system-packages \
    "cocotb<2" "cocotb-coverage<2" pyuvm pyfiglet colorama pytest

# 3. Compilar e instalar Icarus Verilog
# TIP: Considera usar --branch v12_0 para fijar una versión estable
RUN git clone --depth 1 https://github.com/steveicarus/iverilog.git /tmp/iverilog && \
    cd /tmp/iverilog && \
    chmod 775 autoconf.sh && \
    ./autoconf.sh && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/iverilog

# 4. Compilar e instalar Verilator
RUN git clone --depth 1 https://github.com/verilator/verilator.git /tmp/verilator && \
    cd /tmp/verilator && \
    unset VERILATOR_ROOT && \
    autoconf && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/verilator

# 5. Crear usuario no-root ("developer")
RUN useradd -m -s /bin/bash developer && \
    echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

WORKDIR /home/developer/uvmenv_repo
RUN chown -R developer:developer /home/developer/uvmenv_repo

USER developer

# 6. Optimización de Caché: Copiar SOLO el instalador primero
COPY --chown=developer:developer . /home/developer/uvmenv_repo/

RUN mkdir /home/developer/uvmenv_install

# LIMPIEZA WINDOWS: Eliminar retornos de carro (CRLF -> LF) y dar permisos
RUN sed -i 's/\r$//' install.sh && chmod +x install.sh

# Ejecutar la instalación de UVMEnv
RUN chmod +x install.sh 2>/dev/null || true
RUN if [ -f "./install.sh" ]; then echo "y" | ./install.sh --home /home/developer/uvmenv_install; fi

# Configurar variables de entorno
ENV USER=developer
ENV UVMENV_HOME=/home/developer/uvmenv_install
ENV PATH="${UVMENV_HOME}/bin:${PATH}"


WORKDIR /home/developer

CMD ["/bin/bash"]