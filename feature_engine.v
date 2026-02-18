module feature_engine(
    input clk,
    input [31:0] new_price,
    output reg [31:0] price_delta
);
    reg [31:0] last_price = 0;

    always @(posedge clk) begin
        if (last_price == 0) begin
            price_delta <= 0;
        end else begin
            price_delta <= new_price - last_price;
        end
        last_price <= new_price;
    end
endmodule
