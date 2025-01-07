//*************************************************************	
// Proyecto: 				MEM  FIFO WPXRP 
// Archivo: 				fifo_generic.v
// Organización: 			Instituto Politécnico Nacional
// Autor: 					Lagarto team
// E-mail: 					Lagarto@cic.ipn.mx
// Referencias: 			Libro Lagarto I, Capítulo 4
//*************************************************************

module fifo_gen #(parameter 
							  DBi = 64		  , 
							  DBo = 64		  , 
							  ABi = 64		  , 
							  ABo = 64		  ,
							  CBi =  8		  , 
							  CBo =  8		  ,  								
								 E = 16		   						 
)    (
 input              		clk_i         ,  
 input              		rst_ni        , 
 input              		rd_i          , // señal de habilitacion de lectura
 input              		wr_i          , // señal de hablitacion de escritura
 input       [DBi-1:00] data_i        , // bus de datos       de entrada
 input       [ABi-1:00] address_i     , // bus de direcciones de entrada
 input       [CBi-1:00] command_i     , // bus de comandos    de entrada 
 output      [DBo-1:00]	data_o        , // bus de datos       de salida 
 output      [ABo-1:00]	address_o     , // bus de direcciones de salida
 output      [CBo-1:00]	command_o     , // bus de comandos    de salida
 output reg          	den			  , // bus de comandos    de salida
 output      		 		empty         , // señal de fifo vacia
 output      				full            // señal de fifo totalmente llena

);

localparam P = $clog2(E)              ;
reg	            [P-1:0] entries     ; 
wire [(CBi+DBi+ABi)-1:00] data_wr     ;
reg                       rd_reg      ;

// Memoria FIFO de E entradas x RB bits
reg [(CBi+DBi+ABi)-1:00] fifo [E-1:0] ;  // FIFO MEM 
// 
assign data_wr = {{command_i},{address_i},{data_i}};   

reg          [P-1:00] tail     ;        
reg          [P-1:00] head     ;        
reg 			 [P-1:00] index_reg;
 		
 assign full  = (tail == E-1 ) & (entries == E); // llena 
 assign empty = (head == tail) & (entries == 0); // vacia
 
// Escritura por ciclo 
always @(posedge clk_i)   
begin	
   if (wr_i) begin
	    fifo [tail] <= data_wr; // 	 
	end
end

// Lectura por ciclo 
always @(posedge clk_i, negedge rst_ni)   
begin
   if (rst_ni == 0) begin
	    rd_reg    <= 1'b0;
	    index_reg <= {P{1'b0}};
	end
	else if (rd_i) begin
	    rd_reg    <= rd_i;
	    index_reg <= head;	 
	end
	else begin
	rd_reg    <= 1'b0;
	end
end


// Etapa de salida 
assign {{command_o},{address_o},{data_o}} = (rd_reg)? fifo[index_reg]:{(CBi+ABi+DBi){1'b0}}; 
 



always @(posedge clk_i, negedge rst_ni)
begin
  if (rst_ni == 0) begin				   	   // inicializa registros
		 head  <= {P{1'b0}};
		 tail  <= {P{1'b0}}; 
        den  <= 1'b0;	
	 entries  <= {P{1'b0}};;	
  end
  else  begin 
	  case ({rd_i,wr_i}) 							// lecturas y escrituras	 
	        2'b00: begin 
			         tail     <= tail;
						head     <= head;
						den      <= 1'b0;						
			  end			  
	   	  2'b01: begin  // Escritura        // caso: rdwr=01 -se trata de escritura				  
				  if (!full ) begin         		// si no esta totalmente llena!
						 tail    <= (tail + 3'h1);	// escribe 1 entrada
						 entries <=  entries + 1'b1;
						 den     <=  1'b0;
				  end
	   	  end // 2'd1 	     
	   	  2'b10: begin  // Lectura          // caso: fb_rdwr=10 -se trata de lectura	   	  	  
	   	  	  if (!empty) begin              // si no esta vacia
	   	  	       head    <= (head + 3'h1);	// 
						  den    <=  1'b1;
					 entries    <=  entries - 1'b1;
	   	  	  end
	   	  end // 2'd2 
	   	  2'b11: begin                      // caso: fb_rdwr=11 -se trata de lectura-Escritura	   	  	  
	   	  	  if (!empty) begin              // si no esta vacia
				       tail    <= (tail + 3'h1);	// escribe 1 entrada
	   	  	       head    <= (head + 3'h1);	// 
						  den    <=  1'b1;
	   	  	  end
	   	  end // 2'd2 
	   	  default: begin            			// caso:default
			  			head   <= head;
						den    <= 1'b0;	
	   	  end // 2'd2 				   		
	   endcase // fb_rdwr
	end
end

endmodule
