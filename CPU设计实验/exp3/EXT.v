/*
    control : 
        0 : 高16位补0.
        1 : 低16位补0
        2 : 符号拓展.
*/

module EXT(
    input [15:0] input_value,
    input [1:0] control,
    output [31:0] ext_value);

    //reg [31:0] ext_value;
    wire [31:0] ext[3:0];

    assign ext[0][15:0] = input_value;                      //高16位补0
    assign ext[0][31:16] = 0;

    assign ext[1][15:0] = 0;                                //低16位补0
    assign ext[1][31:16] = input_value;
    
    assign ext[2][15:0] = input_value;                      //符号拓展.
    assign ext[2][31:16] = input_value[15] ? 16'hffff : 16'h0000;

    assign ext_value = ext[control];
endmodule
