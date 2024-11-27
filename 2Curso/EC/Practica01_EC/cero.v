module cero(output wire resultado, input wire [3:0] R);
  assign resultado = (R == 4'b0000) ? 1 : 0;
endmodule