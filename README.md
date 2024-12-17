# UVMEnv
*Universal Verification Metodology Environments*

Open source framework based on Python for RTL verification using Universal Verification Metodology (UVM).

**Instituto Politécnico Nacional (IPN).**

**Centro de Investigación en Computación (CIC).**

*2024*


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



# Projects
When you create a new project (uvmenv --new), you should see the next directory hierarchy:
<p align="center">
  <img src="docs/img/directoryTree.png" alt="Directory tree" width="200"/>
  <img src="docs/img/mainDirectories.png" alt="Main directories" width="600"/>
</p>

They match with the main UVM hierarchy, based and implemented on screaming architecture:
![Main UVMEnv hierarchy](docs/img/mainHierarchy.png)

Inside Environment, UVMEnv uses the next TLM communication:
![Environment TLM communication](docs/img/tlmEnvComm.png)




