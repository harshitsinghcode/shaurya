module rate_limiter(
    input clk,
    input trade_request,
    output reg trade_approved
);
    reg [15:0] tokens = 100;
    reg [15:0] clock_ticks = 0;

    always @(posedge clk) begin
        clock_ticks <= clock_ticks + 1;
        if (clock_ticks == 1000) begin
            if (tokens < 100) tokens <= tokens + 1;
            clock_ticks <= 0;
        end

        if (trade_request && tokens > 0) begin
            trade_approved <= 1;
            tokens <= tokens - 1;
        end else begin
            trade_approved <= 0;
        end
    end
endmodule
