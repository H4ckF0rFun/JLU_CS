

/*
    func:
        00: slt
        01: or
        10: sub
        11: add
*/

module ALU(
    input [31:0] input_0,               //operand 1
    input [31:0] input_1,               //operand 2
    input [1:0]  func,                   //how to calc?
    output[31:0] result,                //calc result.
    output zf);                         //flags...

    wire [31:0] compute_result[3:0]; 

    assign  compute_result[1] = input_0 | input_1;
    assign  compute_result[2] = input_0 - input_1;
    assign  compute_result[3] = input_0 + input_1;
    
    //slt ,是用减法的结果去判断.
    assign  compute_result[0][31:1] = 0;
    assign  compute_result[0][0] = compute_result[2][31]; //sign bit.

    assign result = compute_result[func];    
    
    //ZF 标记位 
    assign zf = result ? 0 : 1;
endmodule

