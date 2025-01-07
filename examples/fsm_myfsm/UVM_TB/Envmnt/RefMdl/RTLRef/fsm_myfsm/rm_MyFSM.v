///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Example Finite State Machine
// Copyright @ 2023
// This is the Module for My Finite State Machine
//
///////////////////////////////////////////////////////////////////////////////////////////////////

module rm_MyFSM(

        input i_clk,
		input i_rst_n,

        input i_x,

        output  reg o_y,
		
		output [1:0] o_state);

    reg [1:0] state;


    always @ (posedge i_clk or negedge i_rst_n)
	
	if (!i_rst_n) begin
	    state <= 2'b00;
		o_y <= 1'b0;
    end
    else
      begin
        case (state)

            2'b00: state <= i_x?2'b01:2'b00;

            2'b01: state <= i_x?2'b10:2'b00;

            2'b10: state <= i_x?2'b11:2'b00;

            2'b11: state <= 2'b00;
        endcase
        o_y <= state[1] & state[0] & i_x;
      end 

	assign o_state = state;
endmodule

