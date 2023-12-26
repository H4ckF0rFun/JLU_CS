/*
    该模块用于存储指令.
    32bit * 1024
    10位地址线
*/


module ROM(
    input [9:0]   addr,
    output [31:0] output_data  //wire 
    );
    
    //
    reg [31:0] mem[1023:0];
    assign output_data = mem[addr];

    initial begin
        // mem[0] = 32'h10000002;
        // mem[1] = 32'h0;
        // mem[2] = 32'h0;
        // mem[3] = 32'h0;

        mem[0]  = 32'he821;             //init
        mem[1]  = 32'h27bd0f00;
        mem[2]  = 32'h0C000004;         //jal main
        mem[3]  = 32'h1000ffff;

        mem[4]  = 32'h27bdfef4;         //main
        mem[5]  = 32'hafbe0104;
        mem[6]  = 32'hafbf0108;
        mem[7]  = 32'h1df021;
        mem[8]  = 32'hafa00100;
        mem[9]  = 32'h8fa20100;
        mem[10] = 32'h24030100;
        mem[11] = 32'h10430007;
        mem[12] = 32'h8fa20100;
        mem[13] = 32'h5d1821;
        mem[14] = 32'ha0620000;
        mem[15] = 32'h8fa20100;
        mem[16] = 32'h24420001;
        mem[17] = 32'hafa20100;
        mem[18] = 32'h1000fff6;
        mem[19] = 32'h8fbe0104;
        mem[20] = 32'h8fbf0108;
        mem[21] = 32'h27bd010c;
        mem[22] = 32'h3e00008;
    end
endmodule