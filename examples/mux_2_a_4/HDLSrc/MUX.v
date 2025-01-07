//************************************************************//
//  Proyecto:     Ejercicio MUX 4 to 1                        //
//  Archivo:      MUX.v                                       //
//  Organización: Instituto Politécnico Nacional              //
//  Autor(es):    Miguel Aleman                               //
//  E-mail:       lagarto@cic.ipn.mx                          //
//  Referencias:  www.verificationacademy.com                 //
//                                                            //
//************************************************************//

module MUX(

 input [3:0] i_a,
 input [3:0] i_b,
 input [3:0] i_c,
 input [3:0] i_d,
 
 input [1:0] i_sel,
 
 output reg [3:0] o_y
 
);
   
always@(*)

    begin
     case(i_sel)
      2'b00 : o_y = i_a;
      2'b01 : o_y = i_b;
      2'b10 : o_y = i_c;
      2'b11 : o_y = i_d;
      default : o_y = 4'b0000;
     endcase
    end
 
endmodule
