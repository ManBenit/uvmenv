FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# 1. Install system dependencies
RUN apt update && apt install -y \
    nlohmann-json3-dev libyaml-cpp-dev pybind11-dev git tree jq help2man \
    perl python3 python3-pip python3-venv make autoconf g++ flex bison \
    ccache gperf libgoogle-perftools-dev numactl perl-doc libfl2 libfl-dev \
    zlib1g zlib1g-dev gtkwave x11-apps x11-utils dbus-x11 fonts-liberation \
    bc sudo vim nano dos2unix \
    && rm -rf /var/lib/apt/lists/*

# 2. Install Python global dependencies
RUN pip3 install --no-cache-dir --break-system-packages \
    "cocotb<2" "cocotb-coverage<2" pyuvm pyfiglet colorama pytest

# 3. Compile and install Icarus Verilog
# TIP: Considera usar --branch v12_0 para fijar una versión estable
RUN git clone --depth 1 https://github.com/steveicarus/iverilog.git /tmp/iverilog && \
    cd /tmp/iverilog && \
    chmod 775 autoconf.sh && \
    ./autoconf.sh && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/iverilog

# 4. Compile and install Verilator
RUN git clone --depth 1 https://github.com/verilator/verilator.git /tmp/verilator && \
    cd /tmp/verilator && \
    unset VERILATOR_ROOT && \
    autoconf && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/verilator

# 5. create non-root user ("developer")
RUN useradd -m -s /bin/bash developer && \
    echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

WORKDIR /uvmenv_repo
RUN chown -R developer:developer /uvmenv_repo

USER developer

# 5.5 Create .vimrc for developer
RUN echo 'set tabstop=4       " Tab as 4 spaces' > /home/developer/.vimrc && \
    echo 'set shiftwidth=4    " Indent size when using << or >>' >> /home/developer/.vimrc && \
    echo 'set expandtab       " Transform Tabs into Spaces when writing' >> /home/developer/.vimrc && \
    echo '' >> /home/developer/.vimrc && \
    echo 'set number' >> /home/developer/.vimrc && \
    echo 'set autoindent' >> /home/developer/.vimrc && \
    echo '' >> /home/developer/.vimrc && \
    echo 'augroup ResurrectCursor' >> /home/developer/.vimrc && \
    echo '  autocmd!' >> /home/developer/.vimrc && \
    echo '  autocmd BufReadPost * if line("'\''\"") >= 1 && line("'\''\"") <= line("$") && &filetype !~# '\''commit'\'' | execute "normal! g`\"" | endif' >> /home/developer/.vimrc && \
    echo 'augroup END' >> /home/developer/.vimrc

# 6. Copy repository content
COPY --chown=developer:developer . /uvmenv_repo

RUN mkdir -p /home/developer/uvmenv_install
RUN mkdir -p /home/developer/workspace

# Clean files with dos2unix to convert all files to Linux format safely
RUN find . -type f -print0 | xargs -0 dos2unix -q || true
RUN chmod +x install.sh

# Run UVMEnv installation
RUN chmod +x install.sh 2>/dev/null || true
RUN if [ -f "./install.sh" ]; then echo "y" | ./install.sh --home /home/developer/uvmenv_install; fi

# Configure environment variables
ENV USER=developer
ENV UVMENV_HOME=/home/developer/uvmenv_install
ENV PATH="${UVMENV_HOME}/bin:${PATH}"

RUN cp -r /uvmenv_repo/examples /home/developer


WORKDIR /home/developer/workspace

# Force X11
ENV GDK_BACKEND=x11
ENV NO_AT_BRIDGE=1
ENV LIBGL_ALWAYS_INDIRECT=1

CMD ["/bin/bash"]