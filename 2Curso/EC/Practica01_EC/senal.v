module senal(output wire sign, input wire [3:0] R);
  assign sign = R[3];
endmodule