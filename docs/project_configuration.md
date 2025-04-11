## Project (environment) configuration


### `load_config` usage
Inside `utils.py` is the `load_config` function, used to retrieve information 
from the configuration file (`.json`).

In the case of the environment, it has a specific use for loading a particular implementation 
of the BFM (in the **driver** and the **monitor**) or the reference model (in the **environment**).



```python
def _import_bfm(self):
    # Get an specific value from .json
    config = load_config('config.json')
    implementation_class = config.uvm_components.itface.bfm_impl
    ...
```

```python
def _import_refmdl(self):
    # Get an specific value from .json
    config = load_config('config.json')
    implementation_class = config.uvm_components.refmdl.refmdl_impl
    ...
```

**This way to invoke different configuration is used into all `UVMEnv`**. 

In particular case of driver, monitor and environment there is an extra block whose work is load a certain implementation of BFM/Reference model:

```python
    # Convert value into Python implementation that you want to use
    try:
        module = importlib.import_module(implementation_class)
        clazz = getattr(module, implementation_class)
        self.bfm = clazz()
    except Exception as e:
        self.logger.critical(f'Failed to load BFM implementation: {e}')
        return
```


### Configuration file
It does not have a base file; instead, it is generated at the moment the verification environment 
is created using the `-n|--new` option from the 
[user interface](https://github.com/ManBenit/uvmenv/blob/main/docs/usr_itface.md).

The generated file is `config.json`, located in the `UvmenvProject` directory.

Here is an example of 
[MUX example project](https://github.com/ManBenit/uvmenv/tree/main/examples/mux_2_a_4)
```json
{
    "id": "dXZtOk11eFRlc3Q6ZW52Cg==",
    "name": "MuxTest",
    "simtool": "icarus",
    "dut_design": {
        "type": "combinatorial",
        "top_module": "MUX",
        "sync_clock_cycles": "1"
    },
    "uvm_components": {
        "itface":{
            "bfm_impl":""
        },
        "refmdl":{
            "refmdl_impl":""
        }
    }
}
```

where:

- `id`: Unique identifier that ensures the current directory is a `UVMEnv` project, allowing the use of the user interface.

- `name`: The project name assigned by the user at the time of its creation.

- `simtool`: The main simulation tool for the environment. By default, its value is `"icarus"`, although it can be set according to the tool used. Supported simulators are mentioned in 
[Cocotb doc](https://docs.cocotb.org/en/stable/simulator_support.html).

- `dut_design`: Configuration of the DUT.
  - `type`: Takes one of the values: `"combinatorial"` or `"sequential"` to define the type of DUT in the project.
  - `top_module`: Indicates the name of the top-level DUT file/module.
  - `sync_clock_cycles`: Value used to synchronize the read and write cycles between the monitor and the BFM when the circuit is combinatorial.

- `uvm_components`: An object that contains the specific implementation of polymorphic components. Currently, it only includes the BFM (interface) and reference model.
  - `itface`: An object that holds the names of the BFM implementations.
  - `refmdl`: An object that holds the names of the reference model implementations.






