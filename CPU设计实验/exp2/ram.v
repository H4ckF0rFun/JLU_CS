
/*
32 * 4 = 128 byte 的memory.

一个单元4byte ,一共32个单元.

addr : 5bit
*/

module ram(
    input [4:0] addr,
    input write,
    input read,
    input clock,
    input reset,
    input  [31:0] input_data,
    output [31:0] output_data
    );

    //addr 直接作为idx.
    //实际和regfile是一样的........

    reg [31:0] mem[31:0];
    
    initial
    begin
        for(i = 0 ;i < 32;i = i + 1)
            mem[i] = 32'h0;
    end

    integer i;

    //sync read memory
    assign output_data = mem[addr];

    //上升沿时后将数据写入内存
    always@(posedge clock)
    begin
        if(write)
        begin
            $display("mem[%x] <= %x ",addr,input_data);
            mem[addr] <= input_data;
        end
        else if (reset)
        begin
            for(i = 0;i < 32;i = i + 1)
            begin
                mem[i] = 32'b0;
            end
        end
    end
endmodule