`include "reg_file.v"

// module regfile_test;
//     reg [31:0] input_data;

//     reg rw;
//     reg clock;
//     reg reset;

//     reg [4:0] r0_idx;
//     reg [4:0] r1_idx;
//     reg [4:0] w_idx;

//     wire [31:0] output_0;
//     wire [31:0] output_1;

//     reg_file regfile(input_data,rw,clock,reset,r0_idx,r1_idx,w_idx,output_0,output_1);
    
//     initial begin
//         //read test
//         rw = 0;
//         r0_idx = 0;
//         r1_idx = 0;
//         #1000

//         //write test
//         clock = 0;
//         #50
//         rw = 1;
//         input_data = 10086;

//         w_idx = 0;
//         r0_idx = 0;
//         r1_idx = 0;
//         #1000
//         clock = 1;

//         #1000
//         rw = 0;
//         r0_idx = 0;
//         r1_idx = 0;
//         #1000

//         $display("output 0 -> %d \n",output_0);
//         $display("output 1 -> %d \n",output_1);

//         $finish;
//     end
//     /*
//         1. =  同步赋值
//         2. <= 异步赋值
//     */
// endmodule

module memory_test;
    
    wire zero;
    reg [31:0] value;
    assign zero = value ? 0 : 1;

    initial begin
        //value = 10086;

        value = 0;
        #100

        $display("output 0 -> %d \n",zero);
        $finish;
    end
    /*
        1. =  同步赋值
        2. <= 异步赋值
    */
endmodule



