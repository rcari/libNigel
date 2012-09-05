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
	const mat4x4f *m = &src;
	__asm {
			mov			edx, m
			movaps		xmm4, [edx+0x00]
			movaps		xmm5, [edx+0x10]
			movaps		xmm6, [edx+0x20]
			movaps		xmm7, [edx+0x30]
		}
}

inline void loadTransposeMatrix(const mat4x4f& src)
{
	const mat4x4f *m = &src;
	__asm {
			mov			edx, m
			movlps		xmm4, [edx+0x00]
			movhps		xmm4, [edx+0x10]
			movlps		xmm3, [edx+0x20]
			movhps		xmm3, [edx+0x30]
			movaps		xmm5, xmm4
			shufps		xmm4, xmm3, 0x88
			shufps		xmm5, xmm3, 0xDD
			movlps		xmm6, [edx+0x08]
			movhps		xmm6, [edx+0x18]
			movlps		xmm3, [edx+0x28]
			movhps		xmm3, [edx+0x38]
			movaps		xmm7, xmm6
			shufps		xmm6, xmm3, 0x88
			shufps		xmm7, xmm3, 0xDD
		}
}

inline void storeMatrix(mat4x4f& dest)
{
	mat4x4f *m = &dest;
	__asm {
			mov			edx, m
			movaps		[edx+0x00], xmm4
			movaps		[edx+0x10], xmm5
			movaps		[edx+0x20], xmm6
			movaps		[edx+0x30], xmm7
		}
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

	
}

void Matrix4x4fRoutines_SSE::ClearImpl(mat4x4f& mat)
{
	
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

void Matrix4x4fRoutines_SSE::MulMatrixImpl(mat4x4f& lMat, const mat4x4f& rMat)
{
	loadMatrix(rMat);
	
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
