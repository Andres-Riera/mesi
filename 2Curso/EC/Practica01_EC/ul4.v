module ul4(output wire[3:0] Out, input wire[3:0] A, input wire[3:0] B, input wire [1:0] S);

    cl C0(Out[0], A[0], B[0], S);
    cl C1(Out[1], A[1], B[1], S);
    cl C2(Out[2], A[2], B[2], S);
    cl C3(Out[3], A[3], B[3], S);

endmodule 