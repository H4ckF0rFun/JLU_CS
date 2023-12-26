/*
    control : 
        0 : 高16位补0.
        1 : 低16位补0
        2 : 符号拓展.
*/

module ext(input_value,control,ext_value);
    input [15:0] input_value;
    input [1:0] control;
    output [31:0] ext_value;

    //reg [31:0] ext_value;
    wire [31:0] ext[3:0];

    assign ext[0][15:0] = input_value;
    assign ext[0][31:16] = 0;

    assign ext[1][15:0] = 0;
    assign ext[1][31:16] = input_value;
    
    assign ext[2][15:0] = input_value;
    assign ext[2][31:16] = input_value[15] ? 16'hffff : 16'h0000;

    assign ext_value = ext[control];
endmodule


// module ext_test;

//     reg [15:0] test_value;
//     reg ext_mode;
    
//     wire [31:0] out_value;
//     ext ext_uint(test_value,ext_mode,out_value);

//     initial begin
//         ext_mode = 1;
//         test_value = 16'h1122;
//         #100
//         $display("output value -> %x \n",out_value);
//         $finish;
//     end 
// endmodule