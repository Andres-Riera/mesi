module cl(output wire out, input wire a, b, input wire [1:0] S);

    wire a_out, o_out, x_out, n_out;

    and A(a_out, a, b);
    or O(o_out, a, b);
    xor X(x_out, a, b);
    not N(n_out, a);
    mux4_1 Mux(out, a_out, o_out, x_out, n_out, S);

endmodule