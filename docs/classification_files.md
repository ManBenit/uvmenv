## Files classification

In general, file creation is performed through the user interface and
is based on preassembled code templates. As a result, even if only an empty environment
is generated, it will run correctly (See the [generic testbench](https://github.com/ManBenit/uvmenv/blob/main/docs/generic_tb.md)).

This implementation approach leverages the repetitive and pattern-based nature of
software for UVM because it follows a standard.
The operation method involves placing keywords in the templates, following the `screaming_snake_case` convention,
which will be replaced through the user interface.

Each file into `UVMEnv` can be classifien in different ways, according different characteristics:

### By functionality
This classification refers to the role of files when executing and managing
a verification environment from their handling through the user interface
to their use as execution aids or UVM components abstracted as
[main structure](https://github.com/ManBenit/uvmenv/blob/main/docs/main_structure.md) ilustrates.

#### Base files
It's the fundamental characteristic of `UVMEnv` to create verification environments (creating and managing projects and UVM components). 

This code can be rewritten with DUT signals got from Verilator when it contains `KEY_WORDS` or have coding instructions (on comments) for creating each environment component. 

- [Commands](https://github.com/ManBenit/uvmenv/blob/main/docs/classification_files_func_base_commands.md).
- [Components](https://github.com/ManBenit/uvmenv/blob/main/docs/classification_files_func_base_components.md).
- [Configurations](https://github.com/ManBenit/uvmenv/blob/main/docs/classification_files_func_base_configurations.md).
- [Representatives](https://github.com/ManBenit/uvmenv/blob/main/docs/classification_files_func_base_representatives.md).



#### Tool files
- `command.sh`
- `run.sh`
- `install.sh`
- `uninstall.sh`

### By malleability

#### Base created

#### Fully created

#### Partially created



