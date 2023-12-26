
module controller(
    input [5:0] opcode,
    input [5:0] func,
    output reg reg_dst,
    output reg alusrc,
    output reg mem2reg,
    output reg regwrite,
    output reg memwrite,
    output reg beq,
    output reg jmp,
    output reg save_pc,
    output reg jr,
    output reg [1:0] extop,             //0 , 高位16位补0,1 低16位补0,10 符号拓展.
    output reg [1:0] aluop
    );

    always @ (*)
    begin

        case(opcode)
            //add,sub
            6'b000000:
                begin

                    if(func == 6'b001000)
                    begin
                        regwrite = 0;
                        memwrite = 0;
                        beq = 0;
                        jmp = 0;
                        jr = 1;
                        save_pc = 0;
                        $display("controller : jr");
                    end

                    else
                    begin
                        reg_dst = 1;
                        alusrc = 0;
                        mem2reg = 0;
                        regwrite = 1;
                        memwrite = 0;
                        beq = 0;
                        jmp = 0;
                        save_pc = 0;
                        jr = 0;
                        //slt $d, $s, $t $d = ($s < $t)
                        case(func)
                            6'b100001 : aluop = 2'b11;  //add
                            6'b100011 : aluop = 2'b10;  //sub
                            6'b101010 : aluop = 2'b00;  //slt. 
                        endcase
                    end
                    
                end
            
            //ori
            6'b001101:
                begin
                    reg_dst = 0;
                    alusrc = 1;
                    mem2reg = 0;
                    regwrite = 1;
                    memwrite = 0;
                    beq = 0;
                    jmp = 0;
                    extop = 0;
                    aluop = 2'b01;
                    jr = 0;
                    save_pc = 0;
                end

            //beq
            6'b000100:
                begin
                    alusrc = 0;
                    mem2reg = 0;
                    regwrite = 0;
                    memwrite = 0;
                    beq = 1;
                    jmp = 0;
                    save_pc = 0;
                    jr = 0;
                    aluop = 2'b10;
                end

            //sw 
            6'b101011:
                begin
                    alusrc = 1;
                    regwrite = 0;
                    memwrite = 1;
                    beq = 0;
                    jmp = 0;
                    save_pc = 0;
                    jr = 0;
                    aluop = 2'b11;
                    extop = 0;
                end

            //LW
            6'b100011:
                begin
                    reg_dst = 0;
                    regwrite = 1;
                    alusrc = 1;
                    mem2reg = 1;
                    memwrite = 0;
                    extop = 0;
                    beq = 0;
                    jr = 0;
                    save_pc = 0;
                    aluop = 2'b11;      //2
                    jmp = 0;
                end

            //lui reg,imm
            //reg = zero + imm.
            6'b001111:
                begin
                    alusrc = 1;
                    reg_dst = 0;
                    regwrite = 1;
                    mem2reg = 0;
                    memwrite = 0;
                    extop = 1;  //extmode =
                    aluop = 3;
                    beq = 0;
                    jmp = 0;
                    save_pc = 0;
                    jr = 0;
                end

            //addi reg,reg,imm
            //reg = reg + imm
            6'b001000:
                begin
                    alusrc = 1;
                    reg_dst = 0;
                    regwrite = 1;
                    mem2reg = 0;
                    memwrite = 0;
                    extop = 2;  //符号拓展.
                    aluop = 3;
                    beq = 0;
                    jmp = 0;
                    save_pc = 0;
                    jr = 0;
                end

            //addiu.
            6'b001001:
                begin
                    alusrc = 1;
                    reg_dst = 0;
                    regwrite = 1;
                    mem2reg = 0;
                    memwrite = 0;
                    extop = 0;  //高16位补0.
                    aluop = 3;
                    beq = 0;
                    jmp = 0;
                    save_pc = 0;
                    jr = 0;
                end
           
            //j : 000010 + 26 offset.
            6'b000010:
                begin
                    reg_dst = 0;
                    regwrite = 0;
                    mem2reg = 0;
                    memwrite = 0;
                    beq = 0;
                    jmp = 1;
                    save_pc = 0;
                    jr = 0;
                end

            //jal , pc + 4 + offset. pc+4 => reg[31];
            6'b000011:
                begin
                    reg_dst = 0;
                    regwrite = 1;
                    mem2reg = 0;
                    memwrite = 0;
                    beq = 0;
                    jmp = 1;
                    save_pc = 1;
                    jr = 0;
                end
        endcase
    end
endmodule