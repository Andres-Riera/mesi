module microc(output wire [5:0] Opcode, output wire z, input wire clk, reset, s_inc, s_inm, we3, wez, input wire [2:0] Op);
//Microcontrolador sin memoria de datos de un solo ciclo
  wire cero;
  wire [9:0] dir, aux, new_dir;
  wire [15:0] instruccion;
  wire [7:0] reg1, reg2, wd3, S;

  registro #(10) PC(dir, clk, reset, new_dir); 
  memprog Inst(instruccion, clk, dir);  

  sum PC_inc(aux, dir, 10'b0000000001);
  mux2 #(10) nuevo_PC(new_dir, instruccion[9:0], aux, s_inc);

  
  mux2 #(8) Reg_Esc(wd3, S, instruccion[11:4], s_inm);
  regfile registros(reg1, reg2, clk, we3, instruccion[11:8], instruccion[7:4], instruccion[3:0], wd3); 
  alu operacion(S, cero, reg1, reg2, Op);
  
  ffd z_flag(clk, reset, cero, wez, z);

  assign Opcode = instruccion[15:10]; 

endmodule
