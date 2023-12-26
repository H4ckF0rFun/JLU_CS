module reg_file(
    input [31:0] input_data,
    input rw,                 //0: read, 1:write
    input clock,
    input reset,
    input [4:0] read_0_idx,
    input [4:0] read_1_idx,
    input [4:0] write_idx,
    output [31:0] output_0,
    output [31:0] output_1);
    
    /*
        clock 上升沿输出才会变.
        但是读reg 是同步的.
    */

    //
    reg [31:0] regs [31:0];

    integer i;
    //初始状态都为0
    initial
    begin
        for(i = 0 ;i < 32;i = i + 1)
            regs[i] = 32'h0;
    end

    //上升沿更新寄存器数据.
    always @ (posedge clock)
    begin
        if (reset)
        begin
            for(i = 0 ;i < 32;i = i + 1)
                regs[i] <= 32'h0;
        end
        else if (rw)
        begin
            $display("regs[%x] <= %x ",write_idx,input_data);
            regs[write_idx] <= input_data;
        end
    end
    
    //这个意思是output 和 regs[idx] 绑定在一起.
    assign output_0 = regs[read_0_idx];
    assign output_1 = regs[read_1_idx];

endmodule