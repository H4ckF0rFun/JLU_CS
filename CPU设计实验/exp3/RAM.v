/*
    size :  0 : word
            1 : half word
            2 : byte
*/

module RAM(
    input  clock,
    input  reset,
    input [11:0] addr,              //地址按字节编号.
    input [1:0] width,              //操作的数据宽度: 0 :32, 1:16,  2:8
    input sign_ext,                 //如果读取一个或两个字节的话,如何拓展数据
    input  write,                   //写信好
    input  read,                    //读信号

    input  [31:0] input_data,   //输入的数据
    output [31:0] output_data   //输出的数据
    );

    //
    reg [31:0] mem[1023:0];
    
    initial
    begin
        for(i = 0 ;i < 1024 ;i = i + 1)
            mem[i] = 32'h0;
    end

    integer i;

    //sync read memory
    wire [31:0] data_from_mem;
    wire [15:0] words[1:0];
    wire [7:0]  bytes[3:0];

    wire [31:0] possible_output_data[2:0];          //0. word,1. half,2. byte

    assign data_from_mem = mem[addr[11:2]];          //先取出一个字.
    
    assign words[0] = data_from_mem[15:0];
    assign words[1] = data_from_mem[31:16];

    assign bytes[0] = data_from_mem[7:0];
    assign bytes[1] = data_from_mem[15:8];
    assign bytes[2] = data_from_mem[23:16];
    assign bytes[3] = data_from_mem[31:24];

    //word.
    assign possible_output_data[0] = data_from_mem;
    
    //half word
    assign possible_output_data[1][15:0] = words[addr[1]];            //word 的话,只需要看第1位.
    assign possible_output_data[1][31:16] = sign_ext ? (possible_output_data[1][15] ? 16'hffff : 16'h0000) : 16'h0000;

    //byte
    assign possible_output_data[2][7:0] = bytes[addr[1:0]];
    assign possible_output_data[2][31:8] = sign_ext ? (possible_output_data[2][7] ? 24'hffffff : 24'h000000) : 24'h000000;

    //根据read 宽度来选择数据.
    assign output_data = possible_output_data[width];

    reg [31:0] temp;

    //上升沿时后将数据写入内存
    always@(posedge clock)
    begin
        if(write)
        begin
            $display("mem[%x] <= %x ",addr[11:0],input_data);

            if(width == 0)                      //write word.
            begin
                temp = input_data;
            end
            else if(width == 1)                //write half word.
            begin
                temp = (data_from_mem & (~(32'hffff << (addr[1] * 16)))) | ((input_data & 32'hffff) << (addr[1] * 16));
            end
            else if(width == 2)
            begin
                temp = (data_from_mem & (~(32'hff << (addr[1:0] * 8)))) | ((input_data & 32'hff) << (addr[1:0] * 8));
            end

            mem[addr[11:2]] <= temp;
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