module main();
reg clk, rst;
reg[3:0] o;
always begin
	#40 clk = ~clk;
end
initial begin
	clk = 0;
	#10485760 $finish;
end
always @(posedge clk or posedge rst) begin
	if (rst)
		o = 0;
	else if (clk)
		o = o + 1;
	end
endmodule
