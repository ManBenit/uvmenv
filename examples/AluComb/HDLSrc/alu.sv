module alu (
    input  wire [31:0] a, 
    input  wire [31:0] b, 
    input  wire [3:0]  alu_op,
    output reg  [31:0] result, 
    output             zero 
);

    // Definición de operaciones
    localparam [3:0] 
        ALU_ADD = 4'b0000, // Suma
        ALU_SUB = 4'b0001, // Resta
        ALU_AND = 4'b0010, // AND lógico
        ALU_OR  = 4'b0011, // OR lógico
        ALU_XOR = 4'b0100, // XOR lógico
        ALU_SLL = 4'b0101, // Shift left logical
        ALU_SRL = 4'b0110, // Shift right logical
        ALU_SRA = 4'b0111, // Shift right arithmetic
        ALU_SLT = 4'b1000; // Menor que (signed)

    // Indicador de si el resultado es cero
    assign zero = (result == 32'b0) ? 1'b1 : 1'b0;

    always @(*) begin
        case (alu_op)
            ALU_ADD: result = a + b;
            ALU_SUB: result = a - b;
            ALU_AND: result = a & b;
            ALU_OR:  result = a | b;
            ALU_XOR: result = a ^ b;
            // Usar los 5 bits menos significativos de B
            ALU_SLL: result = a << b[4:0]; 
            ALU_SRL: result = a >> b[4:0];
            ALU_SRA: result = $signed(a) >>> b[4:0];
            ALU_SLT: result = ($signed(a) < $signed(b)) ? 32'b1 : 32'b0;
            default: result = 32'b0;
        endcase
    end
endmodule
