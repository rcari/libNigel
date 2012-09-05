/*
 * 	Copyright (c) 2010-2011, Romuald CARI
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *		* Redistributions of source code must retain the above copyright
 *		  notice, this list of conditions and the following disclaimer.
 *		* Redistributions in binary form must reproduce the above copyright
 *		  notice, this list of conditions and the following disclaimer in the
 *		  documentation and/or other materials provided with the distribution.
 *		* Neither the name of the <organization> nor the
 *		  names of its contributors may be used to endorse or promote products
 *		  derived from this software without specific prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	DISCLAIMED. IN NO EVENT SHALL Romuald CARI BE LIABLE FOR ANY
 *	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <math/Matrix4x4fRoutines_SSE.hpp>
using namespace Nigel::math;

kint Matrix4x4fRoutines_SSE::routinePerformanceScore(Routine routine) const
{
	// TODO: Add test for SSE availability.

	switch(routine)
	{
	case Assign:
	case BatchMultiply:
	case Clear:
	case MulMatrix:
	case Transpose:
		return 1;
	default:
		return -1;
	}
}

/* 	------------------------------------------
 *	SSE1 function definitions in inline C/C++.
 *	------------------------------------------	*/

inline void loadMatrix(const mat4x4f& src)
{
	asm volatile
		(
			"movaps		0x00(%0),	%%xmm4					\n\t"
			"movaps		0x10(%0),	%%xmm5					\n\t"
			"movaps		0x20(%0),	%%xmm6					\n\t"
			"movaps		0x30(%0),	%%xmm7					\n\t"
			:
			: "r" (&src)
			: "%xmm4", "%xmm5", "%xmm6", "%xmm7"
		);
}

inline void loadTransposeMatrix(const mat4x4f& src)
{
	/*
	 * MATRIX (OpenGL style for example...) - COLUMN MAJOR
	 *
	 * 0	4	8	12
	 * 1	5	9	13
	 * 2	6	10	14
	 * 3	7	11	15
	 *
	 * Memory layout and SSE registers are not in the same order, we need to transpose.
	 */

	asm volatile
		(
			"movlps 	0x00(%0),	%%xmm4					\n\t" // XMM4:	[	0,		1,		x,		x	]
			"movhps 	0x10(%0),	%%xmm4					\n\t" // XMM4:	[	0,		1,		4,		5	]
			"movlps 	0x20(%0),	%%xmm3					\n\t" // XMM3:	[	8,		9,		x,		x	]
			"movhps 	0x30(%0),	%%xmm3					\n\t" // XMM3:	[	8,		9,		12,		13	]
			"movaps 	%%xmm4, 	%%xmm5					\n\t" // XMM5:	[	0,		1,		4,		5	]
			"shufps 	$0x88,		%%xmm3,		%%xmm4		\n\t" // XMM4:	[	0,		4,		8,		12	] <-- XMM4 is set
			"shufps 	$0xDD,		%%xmm3,		%%xmm5		\n\t" // XMM5:	[	1,		5,		9,		13	] <-- XMM5 is set
			"movlps		0x08(%0),	%%xmm6					\n\t" // XMM6:	[	2,		3,		x,		x	]
			"movhps 	0x18(%0), 	%%xmm6					\n\t" // XMM6:	[	2,		3,		6,		7	]
			"movlps 	0x28(%0), 	%%xmm3					\n\t" // XMM3:	[	10,		11,		x,		x	]
			"movhps 	0x38(%0), 	%%xmm3					\n\t" // XMM3:	[	10,		11,		14,		15	]
			"movaps		%%xmm6, 	%%xmm7					\n\t" // XMM7:	[	2,		3,		6,		7	]
			"shufps 	$0x88, 		%%xmm3, 	%%xmm6		\n\t" // XMM6:	[	2,		6,		10,		14	] <-- XMM6 is set
			"shufps 	$0xDD, 		%%xmm3,		%%xmm7		\n\t" // XMM7:	[	3,		7,		11,		15	] <-- XMM7 is set
			:
			: "r" (&src)
			: "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7"
		);
}

inline void storeMatrix(mat4x4f& dest)
{
	asm volatile
		(
			"movaps		%%xmm4,		0x00(%0)				\n\t"
			"movaps		%%xmm5,		0x10(%0)				\n\t"
			"movaps		%%xmm6,		0x20(%0)				\n\t"
			"movaps		%%xmm7,		0x30(%0)				\n\t"
			:
			: "r" (&dest)
			: "%xmm4", "%xmm5", "%xmm6", "%xmm7", "memory"
		);
}

void Matrix4x4fRoutines_SSE::AssignImpl(mat4x4f& dest, const mat4x4f& src)
{
	loadMatrix(src);
	storeMatrix(dest);
}

void Matrix4x4fRoutines_SSE::BatchMultiplyImpl(vec4f* vecs, kuint vecsNb, const mat4x4f& mat)
{
	//TODO: Add prefetch instructions to increase cache performance + remove vecOffset instructions...
	K_ASSERT( K_IS_ALIGNED( vecs, 16 ) );

	// Load the matrix in xmm4-7
	loadMatrix(mat);

	asm volatile
		(
			"START:											\n\t"
			// Load the vect in xmm0-3
			"movaps		(%%esi),	%%xmm0					\n\t"
			"movaps		%%xmm0,		%%xmm1					\n\t"
			"movaps		%%xmm0,		%%xmm2					\n\t"
			"movaps		%%xmm0,		%%xmm3					\n\t"
			// Broadcast respectively x, y, z and w
			"shufps		$0x00,		%%xmm0,		%%xmm0		\n\t"
			"shufps		$0x55,		%%xmm1,		%%xmm1		\n\t"
			"shufps		$0xAA,		%%xmm2,		%%xmm2		\n\t"
			"shufps		$0xFF,		%%xmm3,		%%xmm3		\n\t"
			// Perform the respective multiplications
			"mulps		%%xmm4,		%%xmm0					\n\t"
			"mulps		%%xmm5,		%%xmm1					\n\t"
			"mulps		%%xmm6,		%%xmm2					\n\t"
			"mulps		%%xmm7,		%%xmm3					\n\t"
			// Perform the additions
			"addps		%%xmm1,		%%xmm0					\n\t"
			"addps		%%xmm3,		%%xmm2					\n\t"
			"addps		%%xmm0,		%%xmm2					\n\t"
			// Save the results in the vector
			"movaps		%%xmm2,		(%%esi)					\n\t"
			// Increment esi by the offset (size of a vector)
			"add		$0x10,		%%esi					\n\t"
			// Loop ?
			"dec		%%ecx								\n\t"
			"jnz		START								\n\t"
			:
			: "S" (vecs), "c" (vecsNb)
			: "%xmm0", "%xmm1", "%xmm2", "%xmm3"
		);
}

void Matrix4x4fRoutines_SSE::ClearImpl(mat4x4f& mat)
{
	K_ASSERT( K_IS_ALIGNED(&mat, 16) )

	asm volatile
		(
			"xorps		%%xmm0,		%%xmm0					\n\t" // XMM0:	[	0,		0,		0,		0	]
			"movaps		%%xmm0,		0x00(%0)				\n\t"
			"movaps		%%xmm0,		0x10(%0)				\n\t"
			"movaps		%%xmm0,		0x20(%0)				\n\t"
			"movaps		%%xmm0,		0x30(%0)				\n\t"
			:
			: "r" (&mat)
			: "%xmm0"
		);
}

kfloat Matrix4x4fRoutines_SSE::DetImpl(const mat4x4f& mat)
{
	return 0;
}

void Matrix4x4fRoutines_SSE::IdentityImpl(mat4x4f& mat)
{

}

void Matrix4x4fRoutines_SSE::InvertImpl(mat4x4f& mat, kbool* inversible)
{

}

void Matrix4x4fRoutines_SSE::LookAtImpl(mat4x4f& mat, const vec4f& pos, const vec4f& at, const vec4f& up)
{

}

void Matrix4x4fRoutines_SSE::MulMatrixImpl(mat4x4f& lMat, const mat4x4f& rMat)
{
	loadMatrix(rMat);
	asm volatile
		(
			// Broadcast m1[0] -> m1[3]
			"movaps 	0x00(%0),	%%xmm0					\n\t"
			"movaps 	%%xmm0,		%%xmm1					\n\t"
			"movaps 	%%xmm0,		%%xmm2					\n\t"
			"movaps 	%%xmm0,		%%xmm3					\n\t"
			"shufps		$0x00,		%%xmm0,		%%xmm0		\n\t"
			"shufps		$0x55,		%%xmm1,		%%xmm1		\n\t"
			"shufps		$0xAA,		%%xmm2,		%%xmm2		\n\t"
			"shufps		$0xFF,		%%xmm3,		%%xmm3		\n\t"
			// Multiply and add
			"mulps		%%xmm4,		%%xmm0					\n\t"
			"mulps		%%xmm5,		%%xmm1					\n\t"
			"mulps		%%xmm6,		%%xmm2					\n\t"
			"mulps		%%xmm7,		%%xmm3					\n\t"
			"addps		%%xmm1,		%%xmm0					\n\t"
			"addps		%%xmm3,		%%xmm2					\n\t"
			"addps		%%xmm2,		%%xmm0					\n\t"
			// Save the result in m1[0] -> m1[3]
			"movaps		%%xmm0,		0x00(%0)				\n\t"

			// Broadcast m1[4] -> m1[7]
			"movaps		0x10(%0),	%%xmm0					\n\t"
			"movaps		%%xmm0,		%%xmm1					\n\t"
			"movaps		%%xmm0,		%%xmm2					\n\t"
			"movaps		%%xmm0,		%%xmm3					\n\t"
			"shufps		$0x00,		%%xmm0,		%%xmm0		\n\t"
			"shufps		$0x55,		%%xmm1,		%%xmm1		\n\t"
			"shufps		$0xAA,		%%xmm2,		%%xmm2		\n\t"
			"shufps		$0xFF,		%%xmm3,		%%xmm3		\n\t"

			// Multiply and add
			"mulps		%%xmm4,		%%xmm0					\n\t"
			"mulps		%%xmm5,		%%xmm1					\n\t"
			"mulps		%%xmm6,		%%xmm2					\n\t"
			"mulps		%%xmm7,		%%xmm3					\n\t"
			"addps		%%xmm1,		%%xmm0					\n\t"
			"addps		%%xmm3,		%%xmm2					\n\t"
			"addps		%%xmm2,		%%xmm0					\n\t"
			// Save the result in m1[4] -> m1[7]
			"movaps		%%xmm0,		0x10(%0)				\n\t"

			// Broadcast m1[8] -> m1[11]
			"movaps		0x20(%0),	%%xmm0					\n\t"
			"movaps		%%xmm0,		%%xmm1					\n\t"
			"movaps		%%xmm0,		%%xmm2					\n\t"
			"movaps		%%xmm0,		%%xmm3					\n\t"
			"shufps		$0x00,		%%xmm0,		%%xmm0		\n\t"
			"shufps		$0x55,		%%xmm1,		%%xmm1		\n\t"
			"shufps		$0xAA,		%%xmm2,		%%xmm2		\n\t"
			"shufps		$0xFF,		%%xmm3,		%%xmm3		\n\t"

			// Multiply and add
			"mulps		%%xmm4,		%%xmm0					\n\t"
			"mulps		%%xmm5,		%%xmm1					\n\t"
			"mulps		%%xmm6,		%%xmm2					\n\t"
			"mulps		%%xmm7,		%%xmm3					\n\t"
			"addps		%%xmm1,		%%xmm0					\n\t"
			"addps		%%xmm3,		%%xmm2					\n\t"
			"addps		%%xmm2,		%%xmm0					\n\t"
			// Save the result in m1[8] -> m1[11]
			"movaps		%%xmm0,		0x20(%0)				\n\t"

			// Broadcast m1[12] -> m1[15]
			"movaps		0x30(%0),	%%xmm0					\n\t"
			"movaps		%%xmm0,		%%xmm1					\n\t"
			"movaps		%%xmm0,		%%xmm2					\n\t"
			"movaps		%%xmm0,		%%xmm3					\n\t"
			"shufps		$0x00,		%%xmm0,		%%xmm0		\n\t"
			"shufps		$0x55,		%%xmm1,		%%xmm1		\n\t"
			"shufps		$0xAA,		%%xmm2,		%%xmm2		\n\t"
			"shufps		$0xFF,		%%xmm3,		%%xmm3		\n\t"

			// Multiply and add
			"mulps		%%xmm4,		%%xmm0					\n\t"
			"mulps		%%xmm5,		%%xmm1					\n\t"
			"mulps		%%xmm6,		%%xmm2					\n\t"
			"mulps		%%xmm7,		%%xmm3					\n\t"
			"addps		%%xmm1,		%%xmm0					\n\t"
			"addps		%%xmm3,		%%xmm2					\n\t"
			"addps		%%xmm2,		%%xmm0					\n\t"
			// Save the result in m1[12] -> m1[15]
			"movaps		%%xmm0,		0x30(%0)				\n\t"
			:
			: "r" (&lMat)
			: "%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7"
		);
}

void Matrix4x4fRoutines_SSE::RotationImpl(mat4x4f& mat, kfloat x, kfloat y, kfloat z, kfloat angle)
{

}

void Matrix4x4fRoutines_SSE::ScaleImpl(mat4x4f& mat, kfloat kx, kfloat ky, kfloat kz)
{

}

void Matrix4x4fRoutines_SSE::TranslationImpl(mat4x4f& mat, kfloat x, kfloat y, kfloat z)
{

}

void Matrix4x4fRoutines_SSE::TransposeImpl(mat4x4f& mat)
{
	loadTransposeMatrix(mat);
	storeMatrix(mat);
}
