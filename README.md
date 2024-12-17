# UVMEnv
Open source framework based on Python for RTL verification using Universal Verification Metodology (UVM).

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

## Options




# Projects
When you create a new project (uvmenv --new), you should see the next directory hierarchy:

UVMEnvProject/
├── config.json
├── HDLSrc/
├── Itface/
│   ├── BFM.py
│   └── _impl/
├── OSimon/
├── paths.py
├── Top_adder.py
├── utils.py
└── UVM_TB/
    ├── Envmnt/
    │   ├── Agents/
    │   ├── Environment.py
    │   ├── RefMdl/
    │   │   ├── _impl/
    │   │   └── RefModel.py
    │   └── Scorbd/
    ├── Misces/
    │   └── UVMEnvReport.py
    ├── SeqItm/
    ├── Seqnce/
    └── Test.py

They match with the main UVM hierarchy, based and implemented on screaming architecture:

![Main UVMEnv hierarchy](docs/mainHierarchy.png)


Inside Environment, UVMEnv uses the next TLM communication:

![Environment TLM communication](docs/tlmEnvComm.png)



13 directories, 9 files
