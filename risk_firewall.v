// C:\Users\Admin\shaurya\risk_firewall.v
module risk_firewall(
    input clk,
    input [31:0] price,
    output reg safe_to_trade
);

    // This simulates a physical hardware limit check
    always @(posedge clk) begin
        // If price spikes above an insane level (e.g., Flash Crash / Fat Finger)
        // Hardcoded to 1000 for this test.
        if (price > 15000000000) begin
            safe_to_trade <= 0; // PHYSICAL LOCK (Fat Finger)
        end else begin
            safe_to_trade <= 1; // APPROVED
        end
    end

endmodule
