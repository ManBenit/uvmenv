module clock (
    input logic clk,
    input logic reset, 
    output logic [7:0] count
);

    // Procesar el contador en flanco de reloj
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            count <= 8'b0;
        end else begin
            count <= count + 1;
        end
    end

endmodule
