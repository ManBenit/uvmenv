//**********************************************************************************************//
//  TITLE:                  Adder 32 bits					                                          //
//                                                                                              //
//  PROJECT:                Monociclo                                                           //
//                                                                                              //
//  LANGUAGE:               Verilog						                                             //
//                                                                                              //
//  AUTHOR:                 Lagarto Development Team - lagarto@cic.ipn.mx						      //
//                                                                                              //
//  REVISION:               1.0 - Monociclo CORE2021                                            //
//                                                                                              //
//**********************************************************************************************//
 
module Sumador #(
	parameter				WORD = 32		//ancho de operadores
  )(
 	input		[WORD-1:0]	opea,		//operador a
	input		[WORD-1:0]	opeb,		//operador b
	input						cin,		//acarreo de entrada
	output	[WORD-1:0]	sal,		//resultado
	output					cout		//acarreo de salida
 
 );
	//señal intermedia para acarreos
	wire		[WORD-1:0]	carry;
	
	//instanciar sumador N bits
	genvar i;
	generate
		for (i = 0; i < WORD; i = i + 1)
		begin	:sumadorNbits
			if (i == 0)
				Sumador_2bits sum	(opea[i], opeb[i], cin, sal[i], carry[i]);
			else
				Sumador_2bits sum	(opea[i], opeb[i], carry[i-1], sal[i], carry[i]);
		end
	endgenerate
	
	assign	cout = carry[WORD-1];
	
 endmodule 

 
 module	Sumador_2bits (
	input				opea,		//operador a
	input				opeb,		//operador b
	input				cin,		//acarreo de entrada
	output			sal,		//resultado
	output			cout		//acarreo de salida
 );
	 //calculo de resultado
	 assign	sal	= opea + opeb + cin;
	 
	 //calculo de acarreo de salida
	 assign	cout	= (opea*opeb) + ((opea+opeb) * cin);
 
 endmodule 
 
 
// module Sumador (
// 	input		[3:0]	opea,		//operador a
//	input		[3:0]	opeb,		//operador b
//	input				cin,		//acarreo de entrada
//	output	[3:0]	sal,		//resultado
//	output			cout		//acarreo de salida
// 
// );
//	//señal intermedia para acarreos
//	wire		[2:0]	carry;
//	
//	//instanciar sumadores 2 bits
//	Sumador_2bits suma (opea[0], opeb[0], cin, sal[0], carry[0]);			//sumador a
//	Sumador_2bits sumb (opea[1], opeb[1], carry[0], sal[1], carry[1]);	//sumador b
//	Sumador_2bits sumc (opea[2], opeb[2], carry[1], sal[2], carry[2]);	//sumador c
//	Sumador_2bits sumd (opea[3], opeb[3], carry[2], sal[3], cout);			//sumador d
//		
// endmodule 


