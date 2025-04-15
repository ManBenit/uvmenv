## Generic testbench


One you have installed `UVMEnv`, you need creating a new project:
``` bash
uvmenv --new
```



(give a project name and specify your top model name without extension).

At this point, you have the basic general architecture (without funcional components), you can verify this by running `uvmenv --view`.


Then, **put your DUT (HDL source code) into `HDLSrc` directory** and use the environment initialization:
``` bash
uvmenv --init
```

At this point, you have a full general prohject structure (with default funcional components), you can verify this by running `uvmenv --view`.


Now you can start the verification process:
``` bash
uvmenv run
```


Aditionally, you can see the generated waveform, with `uvmenv wave`, and the generated report, with `uvmenv report`. 

(wave is generated in any case and report is setted by default with a report invokation into default monitor).

**NOTE:** You can make their initialization manually by creating components following the next order:
1. BFM.
2. Reference model.
3. Sequence item.
4. Sequence.
5. Agent.
6. Scoreboard.

[Command details here](https://github.com/ManBenit/uvmenv/blob/main/docs/usr_itface.md)

<p align="center">
  <img src="https://github.com/ManBenit/uvmenv/blob/main/docs/img/uvmConsoleV2.png" 
    alt="Execution immediatly after creation"
    width="70%" 
  />
</p>

Combinatorial and sequential


