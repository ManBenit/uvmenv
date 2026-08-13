# UVMEnv new user interface


This framework has not a GUI (but is prepared to support it). IT has a command based user interface, 
provided to handle an entire project without change the project root path.

After the installation, you will have available the 
`uvmenv` command, which works as described below.

## General format
Mandatory arguments
| cmd    |   0  |  1  |  2   |  3   |
|--------|------|-----|------|------|
| uvmenv |  ctx | opt | comp | name |

Where:
|   Param    |   Meaning      |      Mandatory                         | Description                                                                                             |
|------------|----------------|----------------------------------------|---------------------------------------------------------------------------------------------------------|
| `ctx`      |  Context       |  Yes                                   | Current place where you want to work (current directory, project, or component)                         |
| `opt`      |  Option        |  Yes                                   | Specific action for context different with project root                                                 |
| `comp`     |  Component     |  Yes                                   | The UVM component that you want to handle or specific option for showing when context is "project"      |
| `name`     |  Name          |  Yes, except for "list"                | Name defined to specific component, it is necessary to let UVMEnv know what is the searched file        |




Optional arguments:
|  Option       | Applicable opt                                           | Usage                                                                |
|---------------|----------------------------------------------------------|----------------------------------------------------------------------|
| --wave-level  | run                                                      | Define which wave level will be rendered on GTKWave.                 |
| --test        | all comp                                                 | Specify the test where component lives.                              |
| --env         | all comp                                                 | Specify the env where component lives.                               |
| --type        | agent                                                    | Specify which type of agent will be created.                         |
| --module      | bfm, seqitem, agent (for Coverage), refmod (only outs)   | Specify some specific module into DUT to generate UVM classes.       |

NOTE: Although optional arguments are applicable to specific  options (opt), there is no problem if they are included
in any other option because internally are processed on independent way. This means the optional arguments are set only 
for its specific options.


## Format details
```bash
uvmenv
    new <project_name> <rtltop_name>
    search
    help
    project
        init
        view
        run
        show
               wave
               report
               coverage
    component
        create <comp>    <name>
        list   <comp>          
        delete <comp>    <name>
        edit   <comp>    <name>
```

### General handling
- `new`: Creates a new UVMEnv project.
- `search`: Looks for existing UVMEnv project at current path.
- `help`: Shows help message.

### Project handling
Requires being into a valid UVMEnv project.

- `init`: Initializes the project with a basic structure.
- `view`: Shows full project tree using a default file viewer.
- `run`: Runs the project. Starts UVM environment.
- `show`: Shows some of the results into OSimon directory (see Project showing).

#### Project showing
- `wave`: Shows the generated waveform using GTKWave.
- `report`: Shows the generated UVM report file.
- `coverage`. Shows the result of functional coverage.


### Component handling
Requires being into a valid UVMEnv project.
- `create`: Creates a UVM component.
- `list`: Lists UVM components, RTL modules and RTL signals.
- `delete`: Deletes a UVM component.
- `edit`: Allows to use a default editor to write on UVM component or UVMEnv configuration, paths and utils.


### Values for `comp`
|  General      |  Only for `list` | 
|---------------|------------------| 
|   env         |   rtlsig         | 
|   test        |   rtlmod         | 
|   bfm         |                  | 
|   agent       |                  | 
|   seqce       |                  | 
|   seqitem     |                  | 
|   scoredb     |                  | 
|   refmod      |                  | 
|   misc        |                  | 

<!--  Only for `edit` | -->
<!-- -----------------| -->
<!--    config        | -->
<!--    paths         | -->
<!--    utils         | -->
<!--                  | -->
<!--                  | -->
<!--                  | -->
<!--                  | -->
<!--                  | -->
<!--                  | -->


Note: Currently in not implemented functionality for UVM callbacks. 
It is highly not recommended to do coverage into a drive, please find another mechanism while
UVM callbacks are implemented.

