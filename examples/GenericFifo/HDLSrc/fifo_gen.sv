module fifo_gen #(
    parameter DBi = 64, 
              DBo = 64, 
              ABi = 64, 
              ABo = 64,
              CBi =  8, 
              CBo =  8,                                 
                E = 16                              
) (
    input                      clk_i,  
    input                      rst_ni, 
    input                      rd_i,        
    input                      wr_i,        
    input       [DBi-1:00]     data_i,      
    input       [ABi-1:00]     address_i,   
    input       [CBi-1:00]     command_i,   
    output reg  [DBo-1:00]     data_o,      
    output reg  [ABo-1:00]     address_o,   
    output reg  [CBo-1:00]     command_o,   
    output reg                 den,         
    output                     empty,       
    output                     full         
);

    localparam PAYLOAD_WIDTH = DBi + ABi + CBi;
    
    reg [PAYLOAD_WIDTH-1:0] fifo_mem [0:E-1];

    localparam PTR_WIDTH = $clog2(E);
    reg [PTR_WIDTH-1:0] wr_ptr;
    reg [PTR_WIDTH-1:0] rd_ptr;
    reg [$clog2(E+1)-1:0] count; 

    
    assign empty = (count == 0);
    assign full  = (count == E);

    
    always @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni) begin
            wr_ptr    <= 0;
            rd_ptr    <= 0;
            count     <= 0;
            data_o    <= 0;
            address_o <= 0;
            command_o <= 0;
            den       <= 1'b0;
        end else begin
            den <= 1'b0;

            if (wr_i && !full && rd_i && !empty) begin
                fifo_mem[wr_ptr] <= {data_i, address_i, command_i};
                wr_ptr           <= (wr_ptr == E-1) ? 0 : wr_ptr + 1;
                
                {data_o, address_o, command_o} <= fifo_mem[rd_ptr];
                rd_ptr           <= (rd_ptr == E-1) ? 0 : rd_ptr + 1;
                den              <= 1'b1;
            end
            
            else if (wr_i && !full) begin
                fifo_mem[wr_ptr] <= {data_i, address_i, command_i};
                wr_ptr           <= (wr_ptr == E-1) ? 0 : wr_ptr + 1;
                count            <= count + 1;
            end
            
            else if (rd_i && !empty) begin
                {data_o, address_o, command_o} <= fifo_mem[rd_ptr];
                rd_ptr           <= (rd_ptr == E-1) ? 0 : rd_ptr + 1;
                count            <= count - 1;
                den              <= 1'b1;
            end
        end
    end

endmodule
