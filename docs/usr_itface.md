## UVMEnv user interface


This framework has not a GUI but a command based user interface is provided to handle framework and projects.

After the installation, you will have available the 
`uvmenv` command, which always worck with an `OPTION`
(watch this with `uvmenv --help`).

### `OPTION` values

#### Framework management
```bash
-n|--new
    Creates a new UVMEnv project.
-s|--search
    Looks for a valid UVMEnv project into current directory.
-h|--help
    Shows uvmenv command help into system browser (less).
-i|--init
    Create default templates for top module.
    BFM, reference model, sequence item, sequence, agent, scoreboard.
-v|--view
    Shows project tree into system browser (less).
run
    Starts verification process.
wave
    Shows wave form using GTKWave.
report
    Shows the report file content.
```

#### Components handling
```bash
-c|--create
    Create a UVM component.
-l|--list
    List UVM components and RTL modules and signals.
-e|--edit
    Allow to edit each file of current UVMEnv project.
-d|--delete
    Delete a UVM component
```

#### Available selection for components handling 
- `--create` -> `agnt|sitm|seqc|scbd|rmod|bfm|misc`
- `--list` -> `agnt|sitm|seqc|scbd|rmod|bfm|misc|rtlm|rtls`
- `--edit` -> `agnt|sitm|seqc|scbd|rmod|bfm|misc|top|tst|env|conf|util|path`
- `--delete` -> `agnt|sitm|seqc|scbd|rmod|bfm|misc`


##### Handling selection requeriments:
| Selection | Meaning                  | Requires                |            |
|-----------|--------------------------|-------------------------|------------|
|           |                          | -c                      | -l, -e, -d |
| `agnt`    | agent                    | attribute, name, module |    name    |
| `sitm`    | sequence item            | name, module            |    name    |
| `seqc`    | sequence                 | name                    |    name    |
| `scbd`    | scoreboard               | name                    |    name    |
| `rmod`    | reference model impl     | name                    |    name    |
| `bfm`     | BFM impl                 | name                    |    name    |
| `misc`    | miscellaneous            | name                    |    name    |
| `top`     | top representative       |            -            |            |
| `tst`     | test representative      |            -            |            |
| `env`     | environment representative |          -            |            |
| `conf`    | config.json              |            -            |            |
| `util`    | util.py                  |            -            |            |
| `path`    | paths.py                 |            -            |            |
| `rtlm`    | RTL modules              |            -            |            |
| `rtls`    | RTL signals              |            -            |            |


##### Agent `attribute` parameter
The `UVMEnv` agents can be created with a passive, active or standard definition 
(as part of framework future research, will be available a _node agent_, with works between one module output and next module input):
- `s` (standard): With monitor, driver and coverage collector.
- `a` (active): With driver.
- `p` (passive) With monitor and coverage collector.
- `n` (node): On research. 


