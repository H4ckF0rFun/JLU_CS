`include "alu.v"
`include "controller.v"
`include "ext.v"
`include "IFU.v"
`include "ram.v"
//`include "memory.v" memory.v has been included in IFU.v
`include "reg_file.v"

module mips();

    wire [31:0] next_pc;
    //公共信号.
    reg clock;
    reg reset;

    //IFU 输入信号.
    wire ifbeg;
    wire zero;
    wire jmp;
    
    wire jr;
    wire [31:0] jr_addr;

    //IFU 输出
    wire [31:0] instruction;
    wire [5:0] opcode;
    wire [5:0] func;    
    IFU IFU_unit(jmp,jr,jr_addr,ifbeg,zero,clock,reset,instruction,next_pc);

    /* 
        ins:
        rs ,rt (imm | rd)
    */
    wire [4:0] rs;
    wire [4:0] rt;
    wire [4:0] rd;          
    wire [15:0] imm;

    // output. of controller
    wire regdst;
    wire alusrc;
    wire mem2reg;
    wire regwrite;
    wire memwrite;
    wire beq;
    wire save_pc;
    
    wire [1:0] extop;
    wire [1:0] aluop;

    //input of controller.
    assign opcode = instruction[31:26];
    assign func = instruction[5:0];

    //
    controller Controller_Unit(
        opcode,
        func,
        regdst,
        alusrc,
        mem2reg,
        regwrite,
        memwrite,
        beq,
        jmp,
        save_pc,
        jr,
        extop,
        aluop);

    //beq - > ifbeq
    assign ifbeg = beq;

    //input of regs.
    assign rs = instruction[25:21];
    assign rt = instruction[20:16];
    assign rd = instruction[15:11];
    assign imm = instruction[15:0];

    wire [31:0] regs_input_data;

    //output of regs.
    wire [31:0] regs_out_value0;
    wire [31:0] regs_out_value1;

    // wire [31:0] return_pc = 
    wire [31:0] regs_input_data2;
    wire [4:0 ] write_idx;
    wire [4:0 ] write_idx2;

    assign regs_input_data2 = save_pc ? next_pc : regs_input_data;
    assign write_idx = regdst ? rd : rt;
    assign write_idx2 = save_pc ? 5'b11111 : write_idx;

    reg_file regs_Unit(
        regs_input_data2,
        regwrite,
        clock,
        reset,
        rs,
        rt,
        write_idx2,
        regs_out_value0,
        regs_out_value1);

    //
    assign jr_addr = regs_out_value0;

    //imm : input of ext.
    //extended_value : output of ext.
    wire [31:0] extended_value;
    ext ext_Unit(imm,extop,extended_value);

    /******************************** ALU Unit *********************************/
    //input .
    wire [31:0] alu_input_value0;
    wire [31:0] alu_input_value1;

    //out .
    wire [31:0] alu_result;

    assign alu_input_value0 = regs_out_value0;
    assign alu_input_value1 = alusrc ? extended_value : regs_out_value1;
    assign zero = alu_result ? 0 : 1;               //IFU zero.
    alu aluUnit(alu_input_value0,alu_input_value1,aluop,alu_result);
    
    /******************************** RAM Unit *********************************/
    //in
    wire [4:0] address;
    assign address = alu_result[6:2];
    
    //out
    wire [31:0] ram_out_data;

    ram RAM_Unit(address,memwrite,mem2reg,clock,reset,regs_out_value1,ram_out_data);

    //
    assign regs_input_data = mem2reg ? ram_out_data : alu_result;

    always @(posedge clock)
    begin
        $display("regwrite : %d ",regwrite);
    end

    integer i;
    integer j;

    //exec.
    initial begin
        reset = 0;
        #200;
        clock = 0;
        #200;
     
        i = 0;
        while ( i > -1) begin
            clock = 1;
            #200;
            clock = 0;
            #200;
            
            i = i + 1;
            //$display("==============================");
            $display("[%d] pc : %x , alu result: %x ,ins : %x ,jmp : %d,save_pc: %d",
                i - 1,
                IFU_unit.pc,
                alu_result,
                instruction,
                jmp,
                save_pc);

            if (instruction == 32'h0)
            begin
                i = -1;
            end

        end       
        #200; 
        clock = 1;
        #200;
        
        $display("====================REGS==================");
        for (j = 0; j < 32;j = j + 1)
        begin
            $display("regs[%d] : 0x%x",j,regs_Unit.regs[j]);
        end

        $display("====================RAM==================");
        for (j = 0; j < 32;j = j + 1)
        begin
            $display("mem[0x%x] : 0x%x",j * 4,RAM_Unit.mem[j]);
        end

        $finish;
    end
endmodule

