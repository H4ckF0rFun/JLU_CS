module REGS(
    input         rw,                 //0:read,1:write
    input         clock,
    input         reset,

    input [4:0]   read_0_idx,
    input [4:0]   read_1_idx,
    
    output [31:0] output_0,
    output [31:0] output_1,

    input [4:0]   write_idx,
    input [31:0]  write_data);

    //regs.
    reg [31:0] regs [31:0];

    //initialize regs.
    integer i;
    initial
    begin
        for(i = 0 ;i < 32;i = i + 1)
            regs[i] = 32'h0;
    end

    //sync read
    assign output_0 = regs[read_0_idx];
    assign output_1 = regs[read_1_idx];

    //Async Write.
    always @ (posedge clock)
    begin
        //$display("rw:%d ,w_idx: %d ,w_data:%x",rw ,write_idx,write_data);

        if (reset)
        begin
            for(i = 0 ;i < 32;i = i + 1)
                regs[i] <= 32'h0;
        end
        else if (rw && write_idx)           //regs[0] Always 0.
         begin
            //$display("regs[%x] <= %x ",write_idx,write_data);
            regs[write_idx] <= write_data;
        end
    end
endmodule