## Main hierarchy and architecture
`UVMEnv` implements the hierarchy suggested by the standard, adding a coverage collector
into each agent, with the goal of increase the functional and code coverage, 
making more maintainable the coverage of test.

Also, hierarchy has the benefits of OOP in order to have different versions of 
BFM and reference model into the same project.

The hierarchy is directly related with the framework screaming architecture 
(view **directories** and **files** classification for usage details).


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

## Directories scheme
Each component of hierarchy is interpreted as a directory (except `Misces` and `Osimon`)
and the next diagram can help to identify them. 

<p align="center">
  <img src="https://github.com/ManBenit/uvmenv/blob/main/docs/img/mainDirectories.png" 
    alt="Directory tree"
    width="70%" 
  />
</p>


## TLM communication
<p align="center">
  <img src="https://github.com/ManBenit/uvmenv/blob/main/docs/img/tlmEnvComm.png" 
    alt="Environment TLM communication"
    width="70%" 
  />
</p>

## Main work
<p align="center">
  <img src="img/uml_files/flux_sequence/BloqVerifUVMEnv_Vert.png" 
    alt="Environment TLM communication"
    width="75%" 
  />
</p>

- [Here the main structure diagrams of `UVMEnv`](https://github.com/ManBenit/uvmenv/blob/main/docs/opp_description/XXXX.md).
- [Here the extra working diagrams](https://github.com/ManBenit/uvmenv/blob/main/docs/opp_description/XXXX.md).




