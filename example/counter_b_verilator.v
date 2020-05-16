module main(clk, rst, o);
input clk, rst;
output reg[3:0] o;
/* verilator lint_off BLKSEQ */
always @(posedge clk or posedge rst) begin
	if (rst)
		o = 0;
	else if (clk)
		o = o + 1;
	end
endmodule
