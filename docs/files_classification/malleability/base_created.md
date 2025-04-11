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

### Base created files
Files whose base is already fully written, meaning they do not contain keywords to be replaced through the user interface and therefore do not require user manipulation.

- `AgentBase.py`
- `SeqItemBase.py`
- `BFMBase.py`
- `RefModelBase.py`
- `TopBase.py`
- `PathsFileBase.py`
- `UtilsFileBase.py`

Here an example, using the top base Python module:

```python
import paths
import cocotb
from pyuvm import uvm_root
from colorama import Fore
import pyfiglet
from utils import load_config

from Test import Test

CONFIG = load_config('config.json')

@cocotb.test()
async def main_test(dut):
    print( Fore.BLUE+pyfiglet.figlet_format('UVMEnv')+Fore.RESET )
    print( Fore.YELLOW+pyfiglet.figlet_format(CONFIG.dut_design.top_module)+Fore.RESET )
    await uvm_root().run_test('Test')

```



