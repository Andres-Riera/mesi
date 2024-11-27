// Testbench para el módulo cuenta1
`timescale 1 ns / 10 ps //Directiva que fija la unidad de tiempo de simulación y la precisión

module cuenta1_tb;  // Testbench
    // Declaración de señales
    reg [2:0] Valor; 
    reg start;
    reg clk;
    wire [3:0] Cuenta; 
    wire Fin;          
    
    // Instanciar el módulo cuenta1
    cuenta1 cuenta(Valor, start, clk, Cuenta, Fin);
    
    
    always begin
        #5 clk = ~clk;
    end
    
    initial begin
        $monitor("Time = %0d Valor = %b Cuenta = %b Fin = %b", $time, Valor, Cuenta, Fin);
        $dumpfile("cuenta1.vcd");
        $dumpvars;  
        // Inicializar señales
        clk = 0;
        start = 0;
        Valor = 3'b000;
        repeat(7) begin
            #10 start = 1;
            #100  
            Valor = Valor + 1; 
            #100 start = 0;     
            #100;         
        end
        
        // Fin de simulación
        #100
        $finish;
    end

endmodule
