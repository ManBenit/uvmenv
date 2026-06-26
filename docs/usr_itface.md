# UVMEnv new user interface


This framework has not a GUI (but is prepared to support it). IT has a command based user interface, 
provided to handle an entire project without change the project root path.

After the installation, you will have available the 
`uvmenv` command, which works as described below.

## General format
| cmd    |   0  |  1  |  2   |  3   |  4    |  5   |  6   |  7   |
|--------|------|-----|------|------|-------|------|------|------|
| uvmenv |  ctx | opt | comp | name | test  | env  | mt   | attr |

Where:
|   Param    |   Meaning      |      Mandatory                         | Description                                                                                             |
|------------|----------------|----------------------------------------|---------------------------------------------------------------------------------------------------------|
| `ctx`      |  Context       |  Yes                                   | Current domain where you are placed (project root, project or component)                                |
| `opt`      |  Option        |  Yes                                   | Specific option for domains different with project root                                                 |
| `comp`     |  Component     |  Yes                                   | The UVM component that you want to handle or specific option for showing when context is "project"      |
| `name`     |  Name          |  Yes, except for "list"                | Name defined to specific component, it is necessary to let UVMEnv know what is the searched file        |
| `test`     | Parent test    |  Yes, when component is into a test    | Test where your component is placed                                                                     |
| `env`      | Parent env     |  Yes, when component is into an env    | Env name where your component is placed                                                                 |
| `mt`       | Module or type |  Yes, when exists "env" or "test"      | Specific RTL module from which signals will be got to create certain components or type when you want to edit a component subpart (for example, Monitor of some agent) |
| `attr`     |  Attribute     |  Yes, when component is agent          | Type of agent that you need (standard, passive or active)                                               |


## Format details
```bash
uvmenv
    new <project_name> <rtltop_name> [init]
    search
    help
    project
        init
        view
        run
        show
               wave  <wave_level>
               report
               coverage
    component
        create <comp>    <name> [test] [env] <module> <attr>
        list   <comp>           [test] [env]
        delete <comp>    <name> [test] [env] 
        edit   <comp>    <name> [test] [env] <type>
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
- `wave`: Shows the generated waveform using GTKWave. **(currently implemented directly on project handling)**
- `report`: Shows the generated UVM report file. **(currently implemented directly on project handling)**
- `coverage`. Shows the result of functional coverage. (soon implemented)


### Component handling
Requires being into a valid UVMEnv project.
- `create`: Creates a UVM component.
- `list`: Lists UVM components, RTL modules and RTL signals.
- `delete`: Deletes a UVM component.
- `edit`: Allows to use a default editor to write on UVM component or UVMEnv configuration, paths and utils.


### Values for `comp`
|  General      |  Only for `list` | Only for `edit` |
|---------------|------------------|-----------------|
|   env         |   rtlsig         |   config        |
|   test        |   rtlmod         |   paths         |
|   bfm         |                  |   utils         |
|   agent       |                  |                 |
|   seqce       |                  |                 |
|   seqitem     |                  |                 |
|   scoredb     |                  |                 |
|   refmod      |                  |                 |
|   misc        |                  |                 |



### Values for `attr`
Agents on UVMEnv can be generated as passive, active or standard type and you can specify which with the next values:
- `s` (standard): With monitor, driver and coverage.
- `a` (active): With driver.
- `p` (passive) With monitor and coverage.

Note: Currently in not implemented functionality for UVM callbacks. 
It is highly not recommended to do coverage into a drive, please find another mechanism while
UVM callbacks are implemented.

