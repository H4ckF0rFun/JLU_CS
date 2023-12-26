`include "rom.v"

module IFU(
    input wire jmp,
    
    input wire jr,
    input wire [31:0] jr_addr,

    input wire beq,
    input wire zero,
    input wire clock,
    input wire reset,
    output  wire [31:0]  instruction,
    output wire [31:0] next_pc);

    reg [31:0] pc;
    assign w = 0;
    assign r = 1;

    //pc 是按照字节算的.
    //mem的地址是按4byte 算的
    //idx = pc >> 2;
    rom rom(pc[6:2],instruction);

    initial begin
        pc = 32'b0;          //pc 初始值是0
    end

    //从指令中取出offset 拓展.低16位
    wire [15:0] offset;
    wire [31:0] ext_offset;
    wire [31:0] beq_pc;
    wire [31:0] jmp_offset;
    wire [31:0] jmp_address;


    assign next_pc = pc + 4;
    
    //beq offset.
    assign offset = instruction[15:0];          
    assign ext_offset[31:2] = (instruction[15] ? (32'hFFFF0000 | offset) : (offset));
    assign ext_offset[1:0] = 0;
    assign beq_pc  = next_pc + ext_offset;
    
    //jmp pc
    assign jmp_offset[1:0] = 0;
    assign jmp_offset[27:2] = instruction[25:0];
    assign jmp_offset[31:28] = instruction[25] ? 4'b1111 : 4'b0000;

    //
    assign jmp_address = next_pc + jmp_offset;

    always @(posedge clock) begin
        if(jr)      //jr 
        begin
            pc <= jr_addr;
        end
        else if(jmp)        //j , j
        begin
            pc <= jmp_address;
        end
        else if(beq && zero)
        begin  
            pc <= beq_pc;
        end
        else
        begin
            pc <= next_pc;
        end
    end
    
    always @(reset) begin
        if(reset)
        begin
            pc = 0;
        end
    end
endmodule