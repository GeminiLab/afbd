module counter(clk, rst, o);
input clk, rst;
output reg o;
always begin
	#4 clk = 1 - clk;
end
always begin
	#50 rst = 1;
	#3 rst = 0;
end
initial begin
	clk = 0;
end
always @(posedge clk or posedge rst) begin
	if (rst)
		o <= #1 0;
	else if (clk)
		o <= #1 o + 1;
	end
endmodule
