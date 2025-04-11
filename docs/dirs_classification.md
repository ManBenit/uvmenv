## Directories classification
<p align="center">
  <img src="img/mainDirectories.png" 
    alt="Main UVMEnv hierarchy" 
    width="70%" 
  />
  <img src="img/directoryTree.png" 
    alt="Main directories and files" 
    width="20%" 
  />
</p>

The directory and file hierarchy is a direct representation of the proposed structure shown in image, hierarchically corresponding to some visible element in it (except for `Misces` and `OSimon`).
[Here the directories details](https://github.com/ManBenit/uvmenv/blob/HEAD/docs/dirs_classification/dirs_details.md).

### Abstract

| **Directory Type**        |  **Directories**                                                                                      |
|---------------------------|-------------------------------------------------------------------------------------------------------|
| **Implementation**        | `Itface`, `RefMdl`                                                                                    |
| **Modularization**        | `Agents`, `SeqItm`                                                                                    |
| **Multiple files**        | `Scordb`, `Seqnce`                                                                                    |
| **Representation**        | `UvmenvProject`, `HDLSrc`, `Envmnt`, `UVM_TB`                                                         |
| **Utility**               | `Misces`, `OSimon`                                                                                    |
| **Component**             | Those created using the user interface for components                                                 |


### Details
#### Implementation
They host a unique copy of the component (an OOP interface) and contain a `_impl` subdirectory that stores
the different forms the component can take (its various implementations).
In other words, **the UVM component is polymorphic**.

When coding the environment, it is necessary to create only the instance of the unique component.
The choice of its implementation is then made in the configuration file.

These directories help manage different forms of a single component, providing greater flexibility
and scalability for incorporating new tools, even if they are external to `UVMEnv`.
- `Itface`
- `RefmMdl`


#### Modularization
They host components composed of more than one source file. Each component is represented
by a subdirectory, named following the `snake_case` convention,
where a `__init__.py` file is located to define the component as a \gls{python} module.
In other words, **the UVM component is a directory**.

When coding the environment, it is necessary to use selective import of the component (through its assigned name) and associate it with an alias
to avoid redundancies when running the project. This is because the subdirectory has a distinct name,
but its parts are named the same in each case. Then, create instances using the associated alias.

These directories allow for greater abstraction in encapsulating UVM components
composed of multiple parts with different objectives. At the same time, several of them can be created,
making them easier to manage.
- `Agents`
- `SeqItm`


#### Multiple files
They host different copies of components that can
simultaneously exist within the environment but are not composed of multiple source files.
In other words, **the UVM component is a file**.

When coding the environment, it is necessary to use selective import for the component and then
create instances using its class name.

These directories provide storage for only one type of component in the hierarchy, allowing them
to be managed more systematically by separating them according to the objectives defined
in the verification plan.
- `Seqnce`
- `Scorbd`



#### Representation
They directly represent the hierarchical levels and the DUT of the UVM environment.
- `UvmenvProject`
- `HDLSrc`
- `Envmnt`
- `UVM_TB`
  

#### Environment utils
They host **extra** utilities for the environment defined by the user or other **independent features**,
unrelated to both `UVMEnv` and UVM itself, but they function as an adaptation of it,
providing the environment with auxiliary features or functionalities for more convenient development.
- `Misces`
- `Osimon`

#### Component
These are those that represent a component of the UVM hierarchy but
consist of different files; in other words, they encapsulate the parts of a single component.



