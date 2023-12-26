

/*
    func:
        00: slt
        01: or
        10: sub
        11: add
*/

module alu(input_0,input_1,func,result);
    input [31:0] input_0;
    input [31:0] input_1;
    input [1:0]  func;
    output[31:0] result;

    wire [31:0] compute_result[3:0]; 

    assign  compute_result[1] = input_0 | input_1;
    assign  compute_result[2] = input_0 - input_1;
    assign  compute_result[3] = input_0 + input_1;
    
    assign  compute_result[0][31:1] = 0;
    assign  compute_result[0][0] = compute_result[2][31]; //sign bit.

    assign result = compute_result[func];    
endmodule


// module alu_test;
//     reg [31:0] num0;
//     reg [31:0] num1;
//     reg [1:0]  func;
//     wire[31:0] result;

//     alu alu_unit(num0,num1,func,result);

//     initial begin
//         num0 = 1;
//         num1 = 1;
//         func = 3;

//         #100

//         $display("output 0 -> %d \n",result);
//         $finish;
//     end
//     /*
//         1. =  同步赋值
//         2. <= 异步赋值
//     */
// endmodule