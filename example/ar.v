/*
 *
 * Taken from VCEGAR benchmarks -- http://www.cprover.org/hardware/benchmarks/vcegar-benchmarks.tgz
 * Modified by Ahmed Irfan <irfan@fbk.eu>
 *
 */ 

module main (clk);
input clk;
reg [31:0] a,b;	

initial clk = 0;
always begin
	#10 clk = 1 - clk;
end

initial a = 1;
initial b = 0;


always @ (posedge clk) begin
	if (a<100) 
	   a<=b+a;

	b <=a;
end

endmodule
