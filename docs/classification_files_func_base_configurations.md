### Configurations base files

| Directorio en repositorio        | Directorio de instalación          |
|----------------------------------|------------------------------------|
| `uvmenv_bases/config_files`     | `~/.UVMEnv/bases/config_files`|


They are `auxiliary scripts` at working of `framework`, providing extra (non-miscellaneous) settings and functionality defined by the user.


- `PathsFileBase.py`: Will become `paths.py`, which loads the paths defined  
  by the directories main structure into Python environment, so they  
  can be recognized by default when running the verification.  
  It will be stored in the root directory of the project (`UvmenvProject`).

    ```
    import sys
    import os

    PROJECT_PATH=os.getcwd()

    # Directory structure paths ##########################################
    sys.path.append(f'{PROJECT_PATH}')
    sys.path.append(f'{PROJECT_PATH}/Itface')

    ...

    sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt/RefMdl')
    sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt/RefMdl/_impl')
    ######################################################################
    ```


- `UtilsFileBase.py`: Will become `utils.py`, which contains functionality **external** to the environment and its standard, used to facilitate specific operations within a verification environment. This file helps to avoid repetitive code in the environment and aims to create a customizable and reusable library. It will be stored in the root directory of the project (`UvmenvProject`).

    ```
    import json
    from types import SimpleNamespace

    def load_config(filename):...

    def extract_bits_from_integer(number, high, low):...

    def dict_to_namespace(d):...
    ```





