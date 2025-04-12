## General steps
1. Clone this repository; you only need `main` branch.
2. Go to generated `uvmenv` directory. (NOTE: **Every installing/uninstalling process must run from this path**).
3. Follow the **installing** or **uninstalling** instructions.


## Installing
Run: **`./install.sh [update]`**

The installation file has the `update` option, which will run an application update, this option
will update `UVMEnv` repository ans its main dependencies (
    [Verilator](https://github.com/verilator/verilator.git) , 
    [Icarus](https://github.com/steveicarus/iverilog.git),
    [PyUVM](https://github.com/pyuvm/pyuvm.git) and
    [Cocotb](https://github.com/cocotb/cocotb)
), this is:
- Run `./install.sh` if you want to fully **install** `UVMEnv`.
- Run `./install.sh update` if you want to **update** `UVMEnv`.

The local installation path is `/home/<your_user>/.UVMEnv`, also written as `~/.UVMEnv`. Inside of this directory you must see the next subdirectories:

### `bases`
Templates for code generation.
- [`command_files`](https://github.com/ManBenit/uvmenv/blob/main/docs/files_classification/functionality/base_commands.md) directory.
- [`component_files`](https://github.com/ManBenit/uvmenv/blob/main/docs/files_classification/functionality/base_components.md) directory.
- [`config_files`](https://github.com/ManBenit/uvmenv/blob/main/docs/files_classification/functionality/base_configurations.md) directory.
- [`representative_iles`](https://github.com/ManBenit/uvmenv/blob/main/docs/files_classification/functionality/base_representatives.md) directory.


### `repos`
Where util repositories are located. The current version of `UVMEnv` has the official repositories of 
[Verilator](https://github.com/verilator/verilator.git) 
and 
[Icarus](https://github.com/steveicarus/iverilog.git).

### `tools`
Scripts for run verification (`run.sh`) and user interface source (`command.sh`).

After your installation you should have available the `uvmenv` command, this is your 
[user interface](https://github.com/ManBenit/uvmenv/blob/main/docs/usr_itface.md).
Test it typing `uvmenv --help`.


## Uninstalling
Run: **`./uninstall.sh [all]`**.

The uninstallation file has the `all` option, which will delete , this option
will remove `UVMEnv` main dependencies from your system, this is:
- Run `./uninstall.sh` if you want to remove **only `UVMEnv`**.
- Run `./uninstall.sh all` if you want to remove **`UVMEnv` and its dependencies** .




