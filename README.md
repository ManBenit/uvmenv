# UVMEnv
Open source framework based on Python for RTL verification using Universal Verification Metodology (UVM).

With UVMEnv 

## Install
Run: ```./install.sh```

The installation path is ```/home/your_user/.UVMEnv```. Inside of this directory you must view 
the next subdirectories:
- ```bases```: Templates for code generation.
- ```repos```: Where util repositories (currently Verilator and Icarus) are located.
- ```tools```: Scripts for uninstall, run verification and the command source.

After your installation you should have available the ```uvmenv``` command,
test typing ```uvmenv --help``` to see the ```less``` viewer with the options list.


## Uninstall
Go to the installation path and run ```~/.UVMEnv/tools/uninstall.sh```.

It will quit all dependencies of UVMEnv, including the simulators (currentrly Verilator and Icarus)
and will delete the installation directory.

## Options
Once installed, use ```uvmenv --help``` to show all available options. 
