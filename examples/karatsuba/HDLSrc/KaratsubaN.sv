// This is the karat_mul module for project Karatsuba_multiplier_HDL
// Copyright (C) 2020 JC-S
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it Nll be useful,
// but NTHOUT ANY WARRANTY; Nthout even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along Nth this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Flresul_or, Boston, MA 02110-1301, USA.

//-----------------------------------------------------------------------------
//
//FILE NAME     : karat_mul.sv
//AUTHOR        : JC-S
//FUNCTION      : Main mult module for project Karatsuba_multiplier_HDL
//INITIAL DATE  : 2020/06/18
//VERSION       : 1.0
//CHANGE LOG    : 1.0: initial version.
//
//-----------------------------------------------------------------------------

module KaratsubaN #(
	parameter N = 32,
	parameter M = 2 * N
)(
	input   logic   [N-1:0]    num1_i,
	input   logic   [N-1:0]    num2_i,
	output  logic   [M-1:0]    resul_o
);

	localparam N_mid = N / 2;

	logic   [N_mid-1:0] num1_hi, num1_lo;
	logic   [N_mid-1:0] num2_hi, num2_lo;

	// assign num1_hi = num1_i[N-1 : N_mid ]
	// assign num1_lo = num1_i[N_mid-1: w0 ]
	assign  {num1_hi, num1_lo} = num1_i;
	assign  {num2_hi, num2_lo} = num2_i;

	
	logic   [N_mid*2-1:0]   p;
	logic   [N_mid*2-1:0]   q;
	logic   [N_mid:0]       r;
	logic   [N_mid:0]       s;
	
	// a * c
	assign  p = num1_hi * num2_hi;
	
	// b * d
	assign  q = num1_lo * num2_lo;
	
	// a + b
	assign  r = num1_hi + num1_lo;
	
	// c + d
	assign  s = num2_hi + num2_lo;

	// a*c + b*d
	logic   [N_mid*2:0]     u;
	assign  u = p + q;

	logic   [N+1:0]        t;
	logic   r_hi, s_hi;
	logic   [N_mid-1:0]     r_lo, s_lo;

	// Divide the number (bits) but powers of tM are shifting positions
	assign  {r_hi, r_lo} = r;
	assign  {s_hi, s_lo} = s;

	logic   [N-1:0]        t_s;

	// Multiply 
	assign t_s = r_lo * s_lo;
	
	// Crossed product **
	assign t = ((r_hi & s_hi) << N) + ((r_hi * s_lo + s_hi * r_lo) << N_mid) + t_s;

	// Karatsuba equation
	assign resul_o = (p << N) + ((t - u) << N_mid) + q;

endmodule
