//**********************************************************************************************//
//  TITLE:                  ALU - EXECUTION                                                     //
//                                                                                              //
//  PROJECT:                Monociclo                                                           //
//                                                                                              //
//  LANGUAGE:               Verilog                                                             //
//                                                                                              //
//  AUTHOR:                 Lagarto Development Team - lagarto@cic.ipn.mx                       //
//                                                                                              //
//  REVISION:               1.0 - Monociclo CORE2021                                            //
//                                                                                              //
//**********************************************************************************************//
module	ALU #(
	parameter			WORD	= 32,
	parameter			ALUOP	= 4
)(
	input			[WORD-1:0]	ex_datars1_i,
	input			[WORD-1:0]	ex_datars2_i,
	input			[ALUOP-1:0]	ex_aluop_i,
	output reg	[WORD-1:0]	ex_data_o,
	output						ex_zerof_o
);

	//wire 			bne_o;
	assign		ex_zerof_o = (ex_data_o == 32'h0) ? 1'b1 : 1'b0;	//BEQ
					
//	assign		ex_difeq_o = |(ex_data_o);
//	initial
//	begin
//		bne_o = 1'b0;
//	end
	
	wire			[WORD-1:0]	add_result_o;
	wire							add_cout_o;
	
	always @(*)
	begin

		case (ex_aluop_i)
			4'h8:		ex_data_o = add_result_o;
			4'h1:		ex_data_o = ex_datars1_i - ex_datars2_i;
			4'h2:		ex_data_o = ex_datars1_i * ex_datars2_i;
			4'h3:		ex_data_o = ex_datars1_i / ex_datars2_i;
			4'h4:		ex_data_o = ex_datars1_i & ex_datars2_i;
			4'h5:		ex_data_o = ex_datars1_i ^ ex_datars2_i;
			4'h6:		ex_data_o = ex_datars1_i | ex_datars2_i;
			4'h7:		ex_data_o = ex_datars1_i << 2;
			4'hD:		ex_data_o = ex_datars1_i >>> ex_datars2_i; //sra
			4'hE:		ex_data_o = ex_datars1_i >> ex_datars2_i; //sla
			4'h9:		ex_data_o = (ex_datars1_i < ex_datars2_i); //slt
			4'hA:		ex_data_o = (ex_datars1_i < ex_datars2_i); //sltu PENDIENTE
			
	
			default:	ex_data_o = 32'b0;
		
		
		endcase
	
	end
	
	Sumador	Adder_U1 (
		.opea			(ex_datars1_i),	//operador a
		.opeb			(ex_datars2_i),	//operador b
		.cin			(1'b0),				//acarreo de entrada
		.sal			(add_result_o),	//resultado
		.cout			(add_cout_o)		//acarreo de salida
	);
	
endmodule
