/*
        R:
            addu，subu，            //ok
            slt，                   //ok
            jr                      //ok
        I:
            ori，lui，          //ok
            addi，addiu         //ok
            lw，sw，            //ok.
            
            lb,lbu
            lh,lhu
            sb,sh               

            slti                //ok.

        J:
            beq，j，jal，       //
*/

/*
    next_pc_src:
         00 : offset
         01 : 28 绝对地址
         10 : 32位绝对地址从寄存器取,实际就是  add pc,reg,0,
              所以opcode 会和 算数指令一样.

    ext_mode:
        00 : 高16位补0
        01 : 低16位补0
        10 : 符号拓展

    alu_mode:
        00: slt   out <= 1 if a < b else 0;
        01: or    
        10: sub
        11: add
*/

module CONTROLLER(
    input clock,
    input reset,
    input [5:0] opcode,
    input [5:0] func,
    //ID
    output reg [1:0] ext_mode,              //拓展方式: 0:高16位补0  1:低16位补0  2:符号拓展

    //EX
    output reg alu_src,                     //ALU 第二操作数 立即数还是寄存器输出的值
    output reg alu_0_src,                   //ALU 第一个操作数是 reg 还是PC
    output reg [1:0] alu_mode,              //运算方式

    //MEM
    output reg mem_read,                  //写内存
    output reg mem_write,                 //读内存
    output reg[1:0] mem_width,            //访存数据宽度:0: 32,1:16, 2:0
    output reg mem_signext,               //输出Word,或者byte是有符号还是无符号拓展.

    //WB
    output reg reg_write,                 //写寄存器信号

    output reg [1:0] wb_idx,              //写到哪个寄存器:  0 : rt  
                                          //                1 : rd,
                                          //                2 : reg[31]

    output reg [1:0] wb_src,              //0 : alu
                                          //1 : mem
                                          //2 : default_next_pc.
    output reg pc_write,                  //写pc信号.


    output reg [1:0] next_pc_src          //下一个PC的值从哪来?
                                          //0 : default_next_pc
                                          //1 : alu result : $zero + index (jr)
                                          //2 : default_next_pc + offset
                                          //3 : index.
    );

    //alu_mode
    parameter ALU_ADD = 3;
    parameter ALU_SUB = 2;
    parameter ALU_OR  = 1;
    parameter ALU_SLT = 0;


    parameter STATE_IF  = 3'b000;
    parameter STATE_ID  = 3'b001;
    parameter STATE_EX  = 3'b010;
    parameter STATE_MEM = 3'b011;
    parameter STATE_WB  = 3'b100;

    //
    parameter OPCODE_ALU   = 6'b000000;

    parameter FUNC_ADDU    = 6'b100001;
    parameter FUNC_SUBU    = 6'b100011;
    parameter FUNC_SLT     = 6'b101010;
    parameter FUNC_JR      = 6'b001000;


    parameter OPCODE_ORI   = 6'b001101;
    parameter OPCODE_LUI   = 6'b001111;
    
    
    parameter OPCODE_ADDI  = 6'b001000;
    parameter OPCODE_ADDIU = 6'b001001;
    parameter OPCODE_SLTI  = 6'b001010;

    parameter OPCODE_LW    = 6'b100011;
    parameter OPCODE_LB    = 6'b100000;
    parameter OPCODE_LBU   = 6'b100100;
    
    parameter OPCODE_LH    = 6'b100001;
    parameter OPCODE_LHU   = 6'b100101;

    parameter OPCODE_SW    = 6'b101011;
    parameter OPCODE_SB    = 6'b101000;
    parameter OPCODE_SH    = 6'b101001;


    //
    parameter OPCODE_BEQ   = 6'b000100;
    parameter OPCODE_J     = 6'b000010;
    parameter OPCODE_JAL   = 6'b000011;

    reg [2:0] state;

    initial begin
        wb_idx    = 0;
        wb_src    = 0;

        alu_src   = 0;
        alu_0_src = 0;

        mem_write = 0;
        mem_read  = 0;

        reg_write    = 0;
        next_pc_src  = 0;
        pc_write     = 0;
        ext_mode     = 0;
        alu_mode     = 0;
        mem_width    = 0;
        mem_signext  = 0;

        state = 0;
    end


    always @(posedge clock)

    begin
        if(reset)
        begin
            wb_idx    <= 0;
            wb_src    <= 0;

            alu_src   <= 0;
            alu_0_src <= 0;

            mem_write <= 0;
            mem_read  <= 0;

            reg_write    <= 0;
            next_pc_src  <= 0;
            pc_write     <= 0;
            ext_mode     <= 0;
            alu_mode     <= 0;
            state <= 0;
        end
        else
        begin
            //$display("State: %d",state);
            case (state)
                STATE_IF:
                    begin
                        //disable all control signal.
                        wb_idx    <= 0;
                        wb_src    <= 0;
                        alu_src   <= 0;
                        alu_0_src <= 0;
                        mem_write <= 0;
                        mem_read  <= 0;
                        reg_write    <= 0;
                        next_pc_src  <= 0;
                        pc_write     <= 0;
                        ext_mode     <= 0;
                        alu_mode     <= 0;
                        mem_width    <= 0;
                        mem_signext  <= 0;

                        //next state.
                        state     <= STATE_ID;
                    end
                STATE_ID:
                    begin
                        //立即数拓展.
                        //ori，lui，addi，addiu
                        //lw，sw，
                        case (opcode)
                            OPCODE_ORI:
                                ext_mode <= 0;
                            
                            OPCODE_LUI:
                                ext_mode <= 1;
                            
                            OPCODE_ADDI:
                                ext_mode <= 2;       //符号拓展
                            
                            OPCODE_SLTI:
                                ext_mode <= 2;

                            OPCODE_ADDIU:
                                ext_mode <= 2;       //符号拓展

                            OPCODE_LW:
                                ext_mode <= 2;

                            OPCODE_LB:
                                ext_mode <= 2;      //sign ext.
                            OPCODE_LBU:
                                ext_mode <= 2;

                            OPCODE_LH:
                                ext_mode <= 2;
                            OPCODE_LHU:
                                ext_mode <= 2;
                            
                            OPCODE_SW:
                                ext_mode <= 2;
                            
                            OPCODE_SB:
                                ext_mode <= 2;

                            OPCODE_SH:
                                ext_mode <=2;

                            OPCODE_BEQ:
                                ext_mode <= 2;
                        endcase
                        state <= STATE_EX;
                    end
                // //计算:
                STATE_EX:
                    begin
                        
                        case (opcode)

                            OPCODE_SW:
                            begin
                                alu_0_src <= 0;      //reg_output
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end

                            OPCODE_SB:
                            begin
                                alu_0_src <= 0;      //reg_output
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end

                            OPCODE_SH:
                            begin
                                alu_0_src <= 0;      //reg_output
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end

                            OPCODE_LW:
                            begin
                                alu_0_src <= 0;
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end

                            OPCODE_LB:
                            begin
                                alu_0_src <= 0;        //寄存器
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end

                            OPCODE_LBU:
                            begin
                                alu_0_src <= 0;        //寄存器
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end

                            OPCODE_LH:
                            begin
                                alu_0_src <= 0;        //寄存器
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end
                            
                            OPCODE_LHU:
                            begin
                                alu_0_src <= 0;        //寄存器
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_ADD;
                            end

                            OPCODE_ORI:
                            begin
                                alu_0_src <= 0;
                                alu_src   <= 1;        //立即数
                                alu_mode  <= ALU_OR;
                            end

                            OPCODE_LUI:
                            begin
                                alu_0_src <= 0;
                                alu_mode   <= ALU_ADD;
                                alu_src <= 1;        //立即数
                            end

                            OPCODE_ADDI:
                            begin
                                alu_0_src <= 0;
                                alu_mode  <= ALU_ADD;
                                alu_src <= 1;        //立即数
                            end

                            OPCODE_SLTI:
                            begin
                                alu_0_src  <= 0;
                                alu_src    <= 1;                //立即数
                                alu_mode   <= ALU_SLT;
                            end

                            OPCODE_ADDIU:
                            begin
                                alu_0_src  <= 0;
                                alu_mode   <= ALU_ADD;
                                alu_src    <= 1;        //立即数
                            end


                            OPCODE_ALU:
                            begin
                                
                                alu_src <= 0;            //第二个操作数来源于寄存器.

                                case (func)
                                //addu，subu，slt，jr
                                    FUNC_ADDU:
                                    begin
                                        alu_0_src <= 0;
                                        alu_mode  <= ALU_ADD;
                                    end
                                    FUNC_SUBU:
                                    begin
                                        alu_0_src <= 0;
                                        alu_mode  <= ALU_SUB;
                                    end
                                    FUNC_SLT:
                                    begin
                                        alu_0_src <= 0;
                                        alu_mode  <= ALU_SLT;
                                    end
                                    
                                    FUNC_JR:
                                    begin
                                        alu_0_src <= 0;         //target = rs + $zero.
                                        alu_mode  <= ALU_ADD;
                                    end

                                endcase 
                            end
                            OPCODE_BEQ:
                            begin
                                alu_0_src <= 0;                   //
                                alu_src   <= 0;                   //来源于立即数
                                alu_mode  <= ALU_SUB;             //
                            end
                            

                        endcase
                        state <= STATE_MEM;
                    end

                STATE_MEM:
                    begin
                        case (opcode)
                            OPCODE_SW:
                                mem_write <= 1;

                            OPCODE_SB:
                            begin
                                mem_write <= 1;
                                mem_width <= 2;     //byte
                            end

                            OPCODE_SH:
                            begin
                                mem_write <= 1;
                                mem_width <= 1;     //byte
                            end

                            //
                            OPCODE_LW:
                                mem_read <= 1;

                            OPCODE_LB:
                            begin
                                mem_read    <= 1;     //
                                mem_width   <= 2;     //byte
                                mem_signext <= 1;
                            end     
                            
                            OPCODE_LBU:
                            begin
                                mem_read    <= 1;     //
                                mem_width   <= 2;     //byte
                                mem_signext <= 0;
                            end   

                            OPCODE_LH:
                            begin
                                mem_read    <= 1;     //
                                mem_width   <= 1;     //word
                                mem_signext <= 1;
                            end   

                            OPCODE_LHU:
                            begin
                                mem_read    <= 1;     //
                                mem_width   <= 1;     //word
                                mem_signext <= 0;
                            end   
                        endcase;

                        state <= STATE_WB;
                    end

                    

                STATE_WB:       //写回寄存器,数据来源是alu 的结果还是 mem 的输出内容?写到哪个寄存器,rt还是rd
                    begin
                        case (opcode)
                                OPCODE_ALU:
                                begin
                                    

                                    if (func == FUNC_JR)                //不会save pc.
                                    begin
                                        //$display("FUNC_JR");
                                        next_pc_src <= 1;                //jr 从寄存器里面拿结果作为PC
                                    end
                                    else
                                    begin
                                        wb_idx <= 1;                     //索引是rd
                                        wb_src <= 0;                     //来源于 ALU result
                                        reg_write <= 1;
                                    end


                                end

                                OPCODE_LUI:
                                begin
                                    wb_idx <= 0;
                                    wb_src <= 0;
                                    reg_write <= 1;
                                end

                                OPCODE_ORI:
                                begin
                                    wb_idx <= 0;
                                    wb_src <= 0;
                                    reg_write <= 1;
                                end

                                OPCODE_ADDI:
                                begin
                                    wb_idx <= 0;
                                    wb_src <= 0;
                                    reg_write <= 1;
                                end

                                OPCODE_SLTI:
                                begin
                                    wb_idx <= 0;            //rt
                                    wb_src <= 0;            //alu结果
                                    reg_write <= 1;
                                end


                                OPCODE_ADDIU:
                                begin
                                    wb_idx <= 0;
                                    wb_src <= 0;
                                    reg_write <= 1;
                                end

                                OPCODE_LW:
                                begin
                                    wb_idx <= 0;             //
                                    wb_src <= 1;             //来源于RAM 
                                    reg_write <= 1; 
                                end

                                OPCODE_LB:
                                begin
                                    wb_idx <= 0;             //rt
                                    wb_src <= 1;             //来源于RAM 
                                    reg_write <= 1;         
                                end

                                OPCODE_LBU:
                                begin
                                    wb_idx <= 0;             //rt
                                    wb_src <= 1;             //来源于RAM 
                                    reg_write <= 1;         
                                end

                                OPCODE_LH:
                                begin
                                    wb_idx <= 0;             //rt
                                    wb_src <= 1;             //来源于RAM 
                                    reg_write <= 1;         
                                end

                                OPCODE_LHU:
                                begin
                                    wb_idx <= 0;             //rt
                                    wb_src <= 1;             //来源于RAM 
                                    reg_write <= 1;         
                                end


                                OPCODE_JAL:
                                
                                begin
                                    //$display("OPCODE_JAL");
                                    wb_idx <= 2;         //写到 reg[31]
                                    wb_src <= 2;         //default_next_pc,且写到reg[31]
                                    reg_write <= 1;
                                    next_pc_src <= 3;    //absolute address.
                                end

                                OPCODE_J:           //不写回.只写pc
                                begin
                                    next_pc_src <= 3;    //absolute address.   
                                end

                                OPCODE_BEQ:         //不写回.只写pc
                                begin
                                    next_pc_src <= 2;    //alu_result and zf.
                                end
                        endcase
                        pc_write <= 1;
                        state   <= STATE_IF;
                    end
            endcase
        end
    end
endmodule