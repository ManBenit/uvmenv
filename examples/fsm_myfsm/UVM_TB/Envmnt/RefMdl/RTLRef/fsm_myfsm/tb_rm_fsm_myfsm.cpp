#include "Vrm_MyFSM.h"
#include "verilated.h"

// Pointer to DUT (Device Under Test)
Vrm_MyFSM* dut = nullptr;

// Variable to track the clock state
bool i_clk = false;

extern "C" {
    /*############ DUT MAIN HANDLERS ############*/
    // Toggle clock
    void toggle_clock() {
        i_clk = !i_clk;
        dut -> i_clk = i_clk;
        dut -> eval();
    }

    // Evaluate (simulate a clock cycle if DUT is sequential)
    void sim_eval() {
        toggle_clock(); // Rising edge
        toggle_clock(); // Falling edge
    }

    // Apply reset
    void reset() {
        dut -> i_rst_n = 0; // 1 for pos active, 0 for neg active
        sim_eval();
        dut -> i_rst_n = 1;  // 0 for pos active, 1 for neg active
    }

    // Initialize DUT
    void init() {
        dut = new Vrm_MyFSM();
        reset();
    }

    // Finalize simulation
    void finalize() {
        delete dut;
    }



    /*############ SETTERS (for inputs) ############*/
    void set_i_clk(long i_clk){
        dut -> i_clk = i_clk;
        sim_eval();
    }

    void set_i_rst_n(long i_rst_n){
        dut -> i_rst_n = i_rst_n;
        sim_eval();
    }

    void set_i_x(long i_x) {
        dut -> i_x = i_x;
        sim_eval();
    }


    /*############ SETTERS (for outputs) ############*/
    long get_o_y() {
        return dut -> o_y;
    }

    long get_o_state() {
        return dut -> o_state;
    } 
}


