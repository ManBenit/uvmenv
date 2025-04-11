### Components base files
<p align="center">
  <img src="img/mainHierarchy.png" 
    alt="Main UVMEnv hierarchy" 
    width="70%" 
  />
  <img src="img/directoryTree.png" 
    alt="Main directories" 
    width="20%" 
  />
</p>


| Repository directory             | Installation directory             |
|----------------------------------|------------------------------------|
| `uvmenv_bases/component_files`     | `~/.UVMEnv/bases/component_files`|


Here are found all file templates which define each UVM component.

#### Agents
All agents components are stored on `Agents` directory, into a directory named with **Snake case** by user when this component will be created.

- `AgentBase.py`: Will become the `__init__.py` of the generated agent; in other words, it is the file that defines the agent as a Python module. It contains the instances of the coverage collector, driver, monitor, and sequencer.

- `AgentCoverageCollectorBase.py`: Will become `CoverageCollector.py`.
- `AgentDriverBase.py`: Will become `Driver.py`.
- `AgentMonitorBase.py`: Will become `Monitor.py`.

<p align="center">
  <img src="img/uml_files/clases_agent.png" 
    alt="Class diagram of agent"
    width="50%" 
  />
</p>




#### Bus Functional Model (BFM)
- `BFMBase.py`: Will become `BFM.py`; it is the unique copy of the BFM that will be invoked in the environment.
It will be stored in the `Itface` directory.

- `BFMImplBase.py`: Will become a user-defined implementation of the BFM, for example `MyBfmImpl.py`, that is, one of the forms that BFM can take. 

    It is important to note that BFM is automatically generated, based on top-level module of the design.  It will be stored in the `Itface/_impl`} directory.  

<p align="center">
  <img src="img/uml_files/clases_bfm.png" 
    alt="Class diagram of bfm"
    width="50%" 
  />
</p>



#### Reference model
- `RefmodelBase.py`: Will become `RefModel.py`; it is the unique copy of the reference model that will be invoked into the environment. It will be stored in the `RefMdl` directory.

- `RefmodelImplBase.py`: Will become a user-defined implementation of the reference model, for example `MyRefmdlImpl.py`,  
  that is, one of the forms the reference model can take.  
  It will be stored in the `RefMdl/_impl` directory.

<p align="center">
  <img src="img/uml_files/clases_refmodel.png" 
    alt="Class diagram of reference model"
    width="50%" 
  />
</p>


#### Sequence item
All sequence items are stored on `SeqItm` directory, into a directory named with **Snake case** by user when this component will be created.

- `SeqItemBase.py`: Will become the `__init__.py` of the generated sequence item; in other words, it is the file that defines the sequence item. It contains the calls to request and response of `DUT`, respectively.

- `SeqItemRequestBase.py`: Will become `Request.py`, which only contains the `DUT` inputs as attributes and a method to randomize those signals if needed.

- `SeqItemResponseBase.py`: Will become `Response.py`, whose attributes include both inputs and outputs of the `DUT`, along with the `copy` method, which is required for TLM communication between monitor with scoreboard and coverage collector (when using the `write` method).

<p align="center">
  <img src="img/uml_files/clases_seqitem.png" 
    alt="Class diagram of sequence item"
    width="50%" 
  />
</p>



#### Sequence
- `SequenceBase.py`: Will become a user-defined version of the sequence, for example `MySequence.py`. It will be stored in the `Seqnce` directory.

<p align="center">
  <img src="img/uml_files/clases_sequence.png" 
    alt="Class diagram of a sequence"
    width="20%" 
  />
</p>

This component has two implementation options, the main and first option is the already described and code templates allow to use a second options with virtual sequence usage.

<p align="center">
  <img src="img/uml_files/clases_vseqr.png" 
    alt="Class diagram of a sequence"
    width="50%" 
  />
</p>



#### Scoreboard
- `ScoreboardBase.py`: Will become a user-defined version of the scoreboard, for example `MyScb.py`. It will be stored in the `Scorbd` directory.

<p align="center">
  <img src="img/uml_files/clases_scb.png" 
    alt="Class diagram of a scoreboard"
    width="20%" 
  />
</p>

