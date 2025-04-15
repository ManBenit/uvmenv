## Main structure of `UVMEnv`
All the logic and implementation of this framework was developed under the next premises:
- Intuitive translation of diagram to code tree.


- Clear 
  [directories](https://github.com/ManBenit/uvmenv/blob/main/docs/files_classification.md) 
  and 
  [files](https://github.com/ManBenit/uvmenv/blob/main/docs/dirs_classification.md) 
  classification, according to different UVM concepts and implemented characteristics.


- Full use of 
  [TLM communication](https://github.com/ManBenit/uvmenv/blob/main/docs/main_structure/tlm_communication.md) 
  between UVM components inside environment.

- Use of open source HDL processors: Verilator as main 
  signals getter
  and Icarus as main DUT compiler for verification.


- Use all OOP features and software architecture to create the most possible flexibility, reusability and scalability for each project.


- Easy 
  [user interface](https://github.com/ManBenit/uvmenv/blob/main/docs/usr_itface.md)
  for handle all framework characteristics correctly, based on console to be compatible with professional production environments.


Additionally, much characteristics of Cocotb were analized to understand testbenches Python-based and make a correct connection with PyUVM and `UVMEnv` logic. These details 
[here](https://github.com/ManBenit/uvmenv/blob/main/docs/main_structure/extra/index.md).


### Main UVM hierarchy
`UVMEnv` implements the suggested standard hierarchy, adding one coverage collector for each agent (allowed by the standard), with the goal of increase the functional and code coverage, also making more maintainable the test coverage.

Hierarchy is directly related with files and directories tanks to screaming architecture as soon as its full 
[class diagram](https://github.com/ManBenit/uvmenv/blob/main/docs/main_structure/uvmenv_class_diagram.md).

<p align="center">
  <img src="https://github.com/ManBenit/uvmenv/blob/main/docs/img/mainHierarchy.png" 
    alt="Main UVMEnv hierarchy" 
    width="70%" 
  />
  <img src="https://github.com/ManBenit/uvmenv/blob/main/docs/img/directoryTree.png" 
    alt="Main directories" 
    width="20%" 
  />
</p>

### Main directories scheme
Each component of hierarchy is interpreted as a directory (except `Misces` and `Osimon`)
and the next diagram can help to identify them. 

<p align="center">
  <img src="https://github.com/ManBenit/uvmenv/blob/main/docs/img/mainDirectories.png" 
    alt="Directory tree"
    width="70%" 
  />
</p>

