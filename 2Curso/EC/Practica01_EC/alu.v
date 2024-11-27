module alu(output wire [3:0] R, output wire zero, carry, sign, input wire [3:0] A, B, input wire c_in, input wire [2:0] Op);

  wire [3:0] OP1, OP2, suma_out, ul_out; 
  preprocess preprocesado(OP1, OP2, A, B, Op);
  sum4_v2 Suma(suma_out, carry, OP1, OP2, c_in);
  ul4 UL(ul_out, A, B, Op[1:0]);
  mux2_4 Resultado(R, suma_out, ul_out, Op[2]);
  cero Cero(zero, R);
  senal Sign(sign, R);

endmodule