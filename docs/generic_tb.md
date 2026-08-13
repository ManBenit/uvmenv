## Generic testbench


One you have installed `UVMEnv`, you need creating a new project:
``` bash
uvmenv new
```

(give a project name and specify your top model name, without extension).

At this point, you have the basic general architecture (without funcional components), you can verify this by running `uvmenv project view`.


Then, **put your DUT into `HDLSrc` directory** and use the project initialization:
``` bash
uvmenv project init
```

Now, you have a full default project structure, you can verify this by running `uvmenv project view`.

Once you have initialized your project with default components, you can edit the only necessary 
(but no limited)  files indicated at table bellow, 
to get a full custom verification process.

| Combinatorial | Sequential | Component                                |
|---------------|------------|------------------------------------------|
|   &#10004;    |  &#10004;  | Top (To uncomment default test)          |
|   &#10004;    |  &#10004;  | Reference model                          |
|   &#10004;    |  &#10004;  | Sequence item                            |
|               |  &#10004;  | BFM (To comment control signals)         |
|               |  &#10004;  | config.json (to edit the type of desing) |

This edition is possible with the next commands:
- vi Top[ProjectName]
- uvmenv --test TestDefault --env EnvDefault edit refmod RefDefault
- uvmenv --test TestDefault --env EnvDefault edit seqitem SitDefault
- uvmenv --test TestDefault --env EnvDefault edit bfm BfmDefault
- vi config.json


Now you can start the verification process:
``` bash
uvmenv project run
```


Aditionally, you can see the generated waveform, with `uvmenv project show wave`, and the generated report, with `uvmenv project show report`. 

(wave is generated in any case and report is setted by default with a report invokation into default monitor).

**NOTE:** You can make their initialization manually by creating components following the next order:
1. BFM.
2. Reference model.
3. Sequence item.
4. Sequence.
5. Agent.
6. Scoreboard.

[Command details here](https://github.com/ManBenit/uvmenv/blob/uvmenv-2.0/docs/usr_itface.md)

<p align="center">
  <img src="https://github.com/ManBenit/uvmenv/blob/uvmenv-2.0/docs/img/uvmConsoleV2.png" 
    alt="Execution immediatly after creation"
    width="70%" 
  />
</p>

Combinatorial and sequential


