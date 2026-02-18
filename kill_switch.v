module kill_switch(
    input clk,
    input reset,
    input software_panic,
    input [31:0] latency_us,
    input [31:0] max_latency,
    output reg system_halted
);
    always @(posedge clk) begin
        if (reset) begin
            system_halted <= 0;
        end else if (software_panic || (latency_us > max_latency)) begin
            system_halted <= 1; 
        end
    end
endmodule
