module counter(clk, rst, o);
input clk, rst;
output reg o;
always @(posedge clk) begin
	if (rst)
		o <= 0;
	else if (clk)
		o <= o + 1;
end
endmodule
