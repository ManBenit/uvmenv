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

### Fully created files
They contain keywords in their base version, and when substitution is performed, the result is a fully written file, so user manipulation is not necessary.

Some of them include instructions and filling examples in the comments to facilitate their editing, if required. 

- `AgentDriverBase.py`
- `BFMImplBase.py`
- `SeqItemRequestBase.py`
- `SeqItemResponseBase.py`

Here is a fragment of BFM implementation code:

Firstly when it is on his base version:
```python
class CLASS_NAME(BFM):
    def __init__(self):
        self.dut = cocotb.top

    async def set(self, *, PARAMETERS):
INIT_VALUES

        await Timer(CLOCK_CYCLES...)
    async def get(self):
        ins = {
GET_INS
        }

        outs = {
GET_OUTS
        }
        
        return (ins, outs)
```

And then the version after substitution process:
```python
class BfmNew(BFM):
    def __init__(self):
        self.dut = cocotb.top

    async def set(self, *, a,b):
        self.dut.a.value = a
        self.dut.b.value = b
        await Timer(CLOCK_CYCLES...)

    async def get(self):
        ins = {
            'a': self.dut.a.value,
            'b': self.dut.b.value
        }
        
        outs = {
            'y': self.dut.y.value
        }

        return (ins, outs)
```


