`timescale 1 ns / 10 ps
module microc_tb;

// declaración de variables
//...
  // entrada
  reg clk, reset, s_inc, s_inm, we3, wez;
  reg [2:0] Op;
  // salida
  wire [5:0] Opcode;
  wire z; 
  
// instanciación del camino de datos
//...
  microc Camino_Datos(Opcode, z, clk, reset, s_inc, s_inm, we3, wez, Op);
  
// generación de reloj clk
  always begin
    #10
    clk = ~clk;
  end 
//...

// Reseteo y configuración de salidas del testbench
initial
begin
  $dumpfile("microc_tb.vcd");
  $dumpvars;
  clk = 1;
  // ... señal de reset
  reset = 1;
  #5
  reset = 0;
  #5 // 10
  s_inc = 0;
  s_inm = 0;
  we3 = 0;
  wez = 0;
  Op = 3'b000;
end

// Bloque simulación señales control por ciclo
initial
begin
  // retardos y señales para ejecutar primera instrucción (ciclo 1) 
  #30 // 30
  s_inc = 1;
  s_inm = 1;
  we3 = 1;
  
  // retardos y señales para ejecutar segunda instrucción (ciclo 2) 
  #20 // 50

  // Ciclo 3
  #20 // 70

  // Ciclo 4
  #20 // 90

  // Ciclo 5
  #20 // 110
  s_inm = 0;
  wez = 1;
  Op = 3'b010;

  // Ciclo 6
  #20 // 130
  Op = 3'b011;

  // Ciclo 7
  #20 // 150
  s_inc = 0;
  we3 = 0;
  wez = 0;
  Op = 3'b000;

  // Ciclo 8
  #20 // 170
  s_inc = 1;
  we3 = 1;
  wez = 1;
  Op = 3'b010;

  // Ciclo 9
  #20 // 190
  Op = 3'b011;

  // Ciclo 10
  #20 // 210
  we3 = 0;
  wez = 0;
  Op = 3'b000;

  // Ciclo 11
  #20 // 230
  s_inc = 0;

  // Ciclo 12
  #20 // 250

  // Ciclo 13
  #20 // 270

  $finish;
end

endmodule
