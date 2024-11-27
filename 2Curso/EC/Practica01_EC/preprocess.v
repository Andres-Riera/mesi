module preprocess(output reg [3:0] AMod, output reg [3:0] BMod, input wire [3:0] A, input wire [3:0] B, input wire [2:0] Op);
  reg add1, op1_A, op2_B, cpl;
  wire [3:0] mux1_out, mux2_out, mux3_out, comp_out, aux0, aux1;
  assign aux0 = 4'b0000;
  assign aux1 = 4'b0001;

  always @(A, B, Op)
  begin
    add1 = Op[0];
    op1_A = Op[2] | (Op[1]& ~Op[0]);
    op2_B = Op[2] | (Op[1] & ~Op[0]);
    cpl = ~Op[2] & ~Op[1] & Op[0];
  end

    mux2_4 Mux1(mux1_out, aux0, aux1, add1);
    mux2_4 Mux2(mux2_out, mux1_out, A, op1_A);
    mux2_4 Mux3(mux3_out, A, B, op2_B);
    compl1 Comp1(comp_out, mux3_out, cpl);

  always @(mux2_out, comp_out)
  begin
    AMod = mux2_out;
    BMod = comp_out;
  end

endmodule