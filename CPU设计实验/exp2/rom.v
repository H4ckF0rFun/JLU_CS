module rom(
    input [4:0] addr,
    output [31:0] output_data  //wire 
    );

    reg [31:0] mem[31:0];
    assign output_data = mem[addr];

    initial begin
        mem[0] = 32'h34630010;
        mem[1] = 32'hac030000;
        mem[2] = 32'hac000004;
        mem[3] = 32'hac000008;
        mem[4] = 32'h8c030000;
        mem[5] = 32'h10600012;
        mem[6] = 32'h8c020004;
        mem[7] = 32'h2042000c;
        mem[8] = 32'h8c030000;
        mem[9] = 32'hac430000;
        mem[10] = 32'h1821;
        mem[11] = 32'h34630004;
        mem[12] = 32'h8c020004;
        mem[13] = 32'h621021;
        mem[14] = 32'hac020004;
        mem[15] = 32'h8c020000;
        mem[16] = 32'h1821;
        mem[17] = 32'h34630001;
        mem[18] = 32'h431023;
        mem[19] = 32'hac020000;
        mem[20] = 32'h8c030008;
        mem[21] = 32'h2063029a;
        mem[22] = 32'hac030008;
        mem[23] = 32'hbffffec;      //jmp loop;
        mem[24] = 32'h00000000;     //hlt.
        
        //jr test
        //mem[24] = 32'h3c0200FF;     //$v0 = 100
        //mem[25] = 32'b10000000000000000001000; //jr $v0

        //jal test.
        //mem[24] = 32'b00001100000000000000000000000000;
        //mem[25] = 32'b00001100000000000000000000000000;
        
        //stl test.
        // mem[25] = 32'h3c030064;     //$v1 = 101;
        // mem[26] = 32'h62f82a;       //sti
        // mem[27] = 32'h00000000;
    end
endmodule