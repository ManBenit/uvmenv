## Signals getting

<p align="center">
  <img src="../img/uml_files/flux_sequence/FluxGetSignals.png"
    alt="Flux getting signals of DUT modules" 
    width="45%" 
  />
</p>

As is visible, you can get signals of each module:
- [By compilation](#get-signals-by-compilation) or
- [By .csv](#get-signals-by-csv).


<div id="get-signals-by-compilation">
If it is the first time signal data is being retrieved, DUT is compiled with **Verilator** through the user interface . Then, using **signals.py**, the generated **.cpp** files are scanned to find a file like **VMyDesign.cpp**, and the signal information for each module is saved to the file **.allSignals.csv**, which is also showed in the console.

<p align="center">
  <img src="../img/uml_files/flux_sequence/FluxGetSignalsComp.png"
    alt="Flux getting signals of DUT modules by compilation" 
    width="45%" 
  />
</p>
</div>


<div id="get-signals-by-csv">
On the other hand, if the **.csv** file was already generated, it is used directly instead of recompiling the design. This enables fast access to the signal information, which can then be showed to the user.

<p align="center">
  <img src="../img/uml_files/flux_sequence/FluxGetSignalsCsv.png"
    alt="Flux getting signals of DUT modules by csv" 
    width="45%" 
  />
</p>
</div>


