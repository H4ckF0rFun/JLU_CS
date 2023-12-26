`include "NPC.v"
`include "ROM.v"
`include "RAM.v"
`include "REGS.v"
`include "EXT.v"
`include "CONTROLLER.v"
`include "ALU.v"

module mips(
);
    reg clock;
    reg reset;

    /**************************************控制信号 **********************************/ 
    //ID
    wire [1:0] ext_mode;

    //EX
    wire       alu_src;           //立即数还是寄存器输出的值
    wire       alu_src_0;         //第一个操作数是 reg, 还是 default_next_pc
    wire [1:0] alu_mode;
    
    //MEM
    wire       mem_read;        
    wire       mem_write;
    wire[1:0]  mem_width;
    wire       mem_signext;

    //WB
    wire reg_write;

    wire [1:0] wb_src;       //0:alu ,1:mem ,2:default_next_pc.
    wire [1:0] wb_idx;       //0:rt,1:rd,2:reg[31]

    wire pc_write;


    /************************************************************************/
    
    wire [31:0] reg_output_0;
    wire [31:0] reg_output_1;


   

    //
    wire [31:0] current_pc;
    wire [31:0] current_instrcution;

    //选择下一个PC的值
    wire [31:0] possible_next_pc[3:0];              
    wire [31:0] default_next_pc = current_pc + 4;

    wire [1:0]  next_pc_src;      
    wire [31:0] next_pc;                //最终拿到的next_pc

    //
    wire [15:0] instruction_imm;
    wire [5:0]  instruction_opcode;
    
    //
    wire [4:0]  instruction_rs;
    wire [4:0]  instruction_rt;
    wire [4:0]  instruction_rd;
    wire [5:0]  instruction_func;


    //
    assign instruction_imm    = current_instrcution[15:0];
    assign instruction_opcode = current_instrcution[31:26];
    assign instruction_func   = current_instrcution[5:0];

    assign instruction_rs     = current_instrcution[25:21];
    assign instruction_rt     = current_instrcution[20:16];
    assign instruction_rd     = current_instrcution[15:11];
    //

    //ext
    wire [31:0] extended_imm;
    
    //alu
    wire [31:0] alu_input_0;
    wire [31:0] alu_input_1;
    wire [31:0] alu_result;
    wire zf;

    //ram
    wire [31:0] mem_output;

    /*
        1. PC + 4
        2. PC + 4 + offset
        3. absolute address.
    */

     //0  default
                                                //1. alu result
                                                //2. beqoffset and zf
                                                //3. absolute address
    assign possible_next_pc[0] = default_next_pc;
    assign possible_next_pc[1] = alu_result;
    
    wire [31:0] offset;
    assign offset[31:2] = default_next_pc[31:2] + extended_imm;
    assign offset[1:0]  = 0;

    assign possible_next_pc[2] = zf ? offset : default_next_pc;
    
    assign possible_next_pc[3][27:2] = current_instrcution[25:0];   //26位绝对地址
    assign possible_next_pc[3][31:28] = current_pc[31:28];
    assign possible_next_pc[3][1:0] = current_pc[1:0];

    //
    assign  next_pc = possible_next_pc[next_pc_src];

    //负责更新当前的pc
    NPC npc(clock,reset,pc_write,next_pc,current_pc);
    
    //
    ROM rom(current_pc[11:2],current_instrcution);                 //存储指令.

    //控制信号
    CONTROLLER controller(
        clock,
        reset,
        instruction_opcode,
        instruction_func,
        ext_mode,
        alu_src,
        alu_src_0,
        alu_mode,
        mem_read,
        mem_write,
        mem_width,
        mem_signext,
        reg_write,
        wb_idx,
        wb_src,
        pc_write,
        next_pc_src
        );

    /******************************ID / reg read******************************/

    //regs
    wire [31:0] _w_data[2:0];
    wire [4:0]  _w_idx[2:0];

    assign _w_data[0] = alu_result;             //ALU 结果.
    assign _w_data[1] = mem_output;             //
    assign _w_data[2] = default_next_pc;        //默认的next_pc.

    assign _w_idx[0] = instruction_rt;
    assign _w_idx[1] = instruction_rd;
    assign _w_idx[2] = 31;
    

    REGS regs(
        reg_write,
        clock,
        reset,
        instruction_rs,
        instruction_rt,

        reg_output_0,
        reg_output_1,
        
        _w_idx[wb_idx],           //src = default_next_pc.
        _w_data[wb_src]
        );
    
    //ext 
    EXT ext(instruction_imm,ext_mode,extended_imm);

    /*******************************ALU*************************************/
    //beq的情况,是普通的reg输出,还是default_next_pc.
    assign alu_input_0  = alu_src_0 ? default_next_pc : reg_output_0;            //
    assign alu_input_1  = alu_src   ? extended_imm    : reg_output_1;

    ALU alu(alu_input_0,alu_input_1,alu_mode,alu_result,zf);

    RAM ram(
        clock,
        reset,
        alu_result[11:0],
        mem_width,
        mem_signext,
        mem_write,
        mem_read,
        reg_output_1,
        mem_output);

    /*********************************************************************/


    integer i;
    integer j;

    //exec.
    initial begin
        reset = 0;
        #200;
        clock = 0;
        #200;
     
        i = 0;
        /*
            init 3 * 5
        

            main : 5 * 20
        */
        while ( i < 13000) begin

            clock = 1;
            #200;
            clock = 0;
            #200;
            i = i + 1;

            // $display("pc: %x ",current_pc);
            // $display("zf : %x", zf);
            // $display("next pc src: %x ",next_pc_src);
            // $display("instruction : %x",current_instrcution);
            // $display("instruction_opcode : %x",instruction_opcode);
            // $display("instruction_func : %x",instruction_func);

            // $display("default next pc : %x ",default_next_pc);
            // $display("extended imm: %x",extended_imm);
            // $display("offset: %x",offset);

            // $display("alu_result: %d",alu_result);
            // $display("reg_write:%d",reg_write);
            // $display("write_idx: %d",_w_idx[wb_idx]);
            // $display("write_data: %d",_w_data[wb_src]);

            // $display("default next pc : %x ",default_next_pc);
            // 

            // $display("reg output_0 : %x ",reg_output_0);

            // $display("rs : %x" ,instruction_rs);
            // $display("rt : %x" ,instruction_rt);
            // $display("rd : %x" ,instruction_rd);

            // $display("alu_src_0 signal : %d",alu_src_0);
            // $display("zf signal : %d",zf);
            // $display("extended imm: %x",extended_imm);
            // $display("alu_input_0 : %d",alu_input_0);
            // $display("alu_input_1 : %d",alu_input_1);
            // //

            // $display("data from mem : %x",ram.data_from_mem);
            // $display("mem addr : %x",alu_result);
            //$display("=================================================");

        end      

        // #200; 
        // clock = 1;
        // #200;
        
        $display("====================REGS==================");
        for (j = 0; j < 32;j = j + 1)
        begin
            $display("regs[%d] : 0x%x",j,regs.regs[j]);
        end

        $display("PC: %x",current_pc);

        $display("====================Stack==================");
        for (j = 0; j < 67 ;j = j + 1)
        begin
            $display("mem[0x%x] : 0x%x",(893 + j) * 4,ram.mem[j +  893]);
        end

        $finish;
    end
endmodule

