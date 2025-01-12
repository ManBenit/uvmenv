# UVMEnv

*Universal Verification Metodology Environments*

Open source framework based on Python and Universal Verification Metodology (UVM),
to generate RTL digital designs verification environments. 

[**Instituto Politécnico Nacional (IPN).**](https://www.ipn.mx/)

[**Centro de Investigación en Computación (CIC).**](https://www.cic.ipn.mx/)

<p align="center">
  <img src="uvmenv_logo.png" alt="uvmenv_logo" width="30%">
  <br/>
  2024 - 2025
</p>

`UVMEnv` is intended for easy UVM environments creation, using a screaming architecture and  working by projects with a general 
hierarchy based on [UVM standard 1.2](https://accellera.org/images/downloads/standards/uvm/uvm_users_guide_1.2.pdf), 
making directly understandable the `UVMEnv` project structure (files and directories) with the hierarchy, supported
by the command [user interface](https://github.com/ManBenit/uvmenv/blob/main/docs/usr_itface.md).

In other words: seeing the `UVMEnv` main hierarchy, get exactly which part of project structure is necessary to edit and
which is its hierarchy level.


## Requeriments

- Linux Debian based distribution.

- Python 3.10.X.
  
  ```Note:``` **If you have a later Python version**, you will need to create a **virtual environment** before running the installer.


## `UVMEnv` structure

### Main hierarchy and architecture
`UVMEnv` implements the hierarchy suggested by the standard, adding a coverage collector
into each agent, with the goal of increase the functional and code coverage, 
making more maintainable the coverage of test.

Also, hierarchy has the benefits of OOP in order to have different versions of 
BFM and reference model into the same project.

The hierarchy is directly related with the framework screaming architecture 
(view **directories** and **files** classification for usage details).

[View more](#) 

<p align="center">
  <img src="docs/img/mainHierarchy.png" 
    alt="Main UVMEnv hierarchy" 
    width="70%" 
  />
  <img src="docs/img/directoryTree.png" 
    alt="Main directories" 
    width="20%" 
  />
</p>

### Directories scheme
Each component of hierarchy is interpreted as a directory (except `Misces` and `Osimon`)
and the next diagram can help to identify them.

[View more](#) 

<p align="center">
  <img src="docs/img/mainDirectories.png" 
    alt="Directory tree"
    width="70%" 
  />
</p>


Inside Environment, `UVMEnv` uses the next TLM communication:
<p align="center">
  <img src="docs/img/tlmEnvComm.png" 
    alt="Environment TLM communication"
    width="70%" 
  />
</p>

## OOP structure
The framework is developed with a OOP design, the main class structure is also directly related and visible 
comparing with main hierarchy.

[View more](#) 

<p align="center">
  <img src="docs/img/classDiagram.png" 
    alt="Class diagram"
    width="70%" 
  />
</p>



## Install
Run: ```./install.sh [update]```

The installation path is ```/home/your_user/.UVMEnv```. Inside of this directory you must view 
the next subdirectories:
- ```bases```: Templates for code generation.
- ```repos```: Where util repositories (currently Verilator and Icarus) are located.
- ```tools```: Scripts for run verification and user interface source.

The optional parameter ```update``` will run a system update, and replacement of 
installation files, also will update base simulators (Verilator and Icarus) and update
Cocotb and PyUVM versions.

After your installation you should have available the ```uvmenv``` command,
test typing ```uvmenv --help```.


## Uninstall
Run ```./uninstall.sh [all]```.

By default, this script will uninstall only the ```UVMEnv``` components but it will keep the rest
of elements (dependencies, simulators, etc.)

If you use the ```all``` option, then every dependencies, tools and simulators.

## User interface
- Framework management.
- Components handling.
- [View more](https://github.com/ManBenit/uvmenv/blob/main/docs/usr_itface.md)

## Generic testbench
- Create project.
- Save DUT.
- Init project.
- Run verification.
- [View more](https://github.com/ManBenit/uvmenv/blob/main/docs/generic_tb.md)

## Files and directories classification
- Implementation directory
- Multiple files directory.
- [View more](https://github.com/ManBenit/uvmenv/blob/main/docs/classification_dirs.md)
- Base created files.
- Full created files.
- Partially created files.
- [View more](https://github.com/ManBenit/uvmenv/blob/main/docs/classification_files.md)

## Naming conventions
- For directory components.
- For implemented components.
- For component files.
- [View more](https://github.com/ManBenit/uvmenv/blob/main/docs/name_conventions.md)






