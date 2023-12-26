

module NPC(
	input            CLK,		 // 
    input            reset,      // 

	input            w_pc,       // pc 写信号

  	input [31:0]     in_pc,    //
  	output reg[31:0] next_pc);

	initial begin
    	next_pc <= 0;  					// 初始为 0
	end
	
	always@(posedge CLK or posedge reset)
	 begin
		if (reset == 1)  
      		next_pc <= 0;  				// 重置为 0 
		else 
		begin
			if (w_pc)  
			begin
        		//$display("next_pc <= in_pc : %x",in_pc);
				next_pc <= in_pc;	// 更新pc
			end
			else 
        		next_pc <= next_pc;	// 不变
		 end
	 end 
endmodule
