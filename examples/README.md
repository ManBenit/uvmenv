## Examples section
Here there are 10 example projects done by `UVMEnv`, proved and correctly working, each one ilustrates one acurrent topic of fremework:

<!-- 1. Simple clock generator (`simple_clock`)
   
   Shows a clock generation using the main hirarchy and Cocotb tools, which ensure a correct control signals handling (see `DefaultBfmImpl` and `Test` initialization line).
 -->

1. Combinatorial ALU (`AluComb`)
   
   With a simple combinatorial circuit (in this case, one generic ALU), this project ilustrates how a desing can be compared with a golden model done with Python (see `RefDefault`, method `_do_with_python`) as soon as can be easily edited when it's combinatorial, because base files generate almost all logic by default. 

2. Sequential ALU (`AluSeq`)
   
   With a sequential version of generic ALU, this project ilustrates how a sequential desing can be compared with a golden model which can be reused from combinatorial version since it is done with Python (see `RefDefault` and compare `BfmDefault` and `Test` initialization line) as soon as can be easily edited when it's sequential, but you need also edit more files.


3. Monocycle processor ALU (`AluMonocicloUvm`)
   
   This example takes a version of ALU used in real academic design of monocycle processor, this project shows how `UVMEnv` works more than only generic examples.

<!-- 5. Multiplexer 2 ins, 4 outs (`mux_2_a_4`)
   
   This example takes an example academic HDL class using the watched multiplexer 2 to 4, this project shows how `UVMEnv` works to verify classroom designs.

6. Multiplier Karatsuba (`karatsuba`)
   
   It use a class practice of karatsuba design on verilog, compared with a Python reference model; this project shows the compatibility
   of use simple language operations and RTL components. -->

4. Generic FIFO (`GenericFifo`).
   
   To avoid using the same DUT as golden model when not exist a known reference, `UVMEnv` suggests to use all Python available tools for creating this model, for example data structures (in this case, a Queue) to verify the implemented on HDL. Sice it could exist different ways to implement a FIFO using Python, you can use the polimorphic reference model to use any you want, including communication with external .


5. Finite State Machine (`MyFsm`) 

    Additional to example of FIFO, this project ilustrate the proposal of include the same Verilator as extra tool to have a golden model, but implemented on HDL, maybe when this model is too specific. This proyect has the `RTLRef` directory, which has different implementation (using verilator) and uses `_do_with_verilator` into `RefDefault` to do this switch.
<!--    
- Projects described on 
  [generic testbench](https://github.com/ManBenit/uvmenv/blob/uvmenv-2.0/docs/generic_tb) 
  (and also thesis document):
  1. Example combinatorial ALU (`alu_simple`).
   
     This is the result of following the steps to creating the combinatorial testbench.
     Mainly, it shows how you can create new UVM components, different versions of BFM and reference model and use them by changing invokations into code and configuration file.

  2. Example sequential ALU (`alu_simple_seq`). 

     This project does the same than conbinatorial vertio, but editing more files (as example 3). -->

