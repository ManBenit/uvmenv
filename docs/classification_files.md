## Files classification

In general, file creation is performed through the user interface and
is based on preassembled code templates. As a result, even if only an empty environment
is generated, it will run correctly.

This implementation approach leverages the repetitive and pattern-based nature of
software for UVM, as it follows a standard.
The operation method involves placing keywords in the templates, following the screaming_snake_case convention,
which will be replaced through the user interface.

### By functionality
This classification refers to the role of files when executing and managing
a verification environment.

#### Base files
- **Commands**
They are part of the user interface, serving as a complement of functionality.
They are named following the camel_case convention.
    - `getSignalsBase.py`: Uses Verilator to compile the DUT and, with the help of the generated C++ code, retrieves the corresponding signals.
    - `writeVcdPart.py`: It is an auxiliary tool for writing, at the end of the top module code, the code fragment required for writing waveforms.

- **Components**
- **Configurations**
- **Representative**

#### Tool files
- `command.sh`
- `run.sh`
- `install.sh`
- `uninstall.sh`

### By malleability

#### Base created

#### Fully created

#### Partially created



