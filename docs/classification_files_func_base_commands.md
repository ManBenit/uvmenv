### Command base files

| Directorio en repositorio        | Directorio de instalación          |
|----------------------------------|------------------------------------|
| `uvmenv_bases/command_files`     | `~/.UVMEnv/bases/command_files`    |



They are part of the user interface, used as a complement of functionality.
They are named following the `camel_case` convention.

- `getSignalsBase.py`: Uses Verilator to compile the DUT and, with the help of the generated C++ code, retrieves the corresponding signals. It has the following options (invoked by user interface and not by user directly):

  - `r`: Refresh option. Created to write the `.allSignals.csv` file if not exist, by reading the inputs and outputs from the generated C++ code.
  
  - `i`: Intern option. Performs the same action as the `r` option but avoids the human-readable format, printing only the type, name, and width of each signal. This is leveraged in the command-line interface to generate different UVM components.
  
  - default: Within the user interface, this option is assigned the value `n`. It corresponds to the main functionality, which consists of reading  DUT signals and their properties, then printing the information on human-readable format.


- `writeVcdPart.py`: It is an auxiliary tool for writing/deleting, at the end of the top module code, the code fragment required for writing waveforms using Icarus.


