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
 *	DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 *	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <math/Vector4fRoutines_SSE.hpp>
using namespace Nigel::math;

#include <cstdlib>
#include <cmath>

kint Vector4fRoutines_SSE::routinePerformanceScore(Routine routine) const
{
	switch(routine)
	{
	case Dot:
	case Normalize:
	case Prod:
		return 1;
	case Add:
	case Assign:
	case Length:
	case MulMatrix:
	case MulScalar:
	case Sub:
	default:
		return -1;
	}
}

void Vector4fRoutines_SSE::AddImpl(vec4f& lVec, const vec4f& rVec)
{
}

void Vector4fRoutines_SSE::AssignImpl(vec4f& dest, const vec4f& src)
{
}

void Vector4fRoutines_SSE::ClearImpl(vec4f& vec)
{
}

kfloat Vector4fRoutines_SSE::DotImpl(const vec4f& lVec, const vec4f& rVec)
{
	kfloat result[4] _K_SSE_ALIGNED;

	asm volatile
	(
		"movaps		(%0), 	%%xmm0			\n\t"
		"movaps 	(%1), 	%%xmm1			\n\t"
		"mulps 		%%xmm1,	%%xmm0			\n\t"
		"movups		%%xmm0,	(%2)			\n\t"
		:
		: "r" (&lVec), "r" (&rVec), "r" (result)
		: "%xmm0", "%xmm1", "memory"
	);

	return result[0] + result[1] + result[2]; // + result[3];;
}

kfloat Vector4fRoutines_SSE::LengthImpl(const vec4f& vec)
{
	return 0.0f;
}

void Vector4fRoutines_SSE::MulMatrixImpl(vec4f& vec, const mat4x4f& mat)
{
}

void Vector4fRoutines_SSE::MulScalarImpl(vec4f& vec, kfloat scalar)
{
}

void Vector4fRoutines_SSE::NormalizeImpl(vec4f& vec)
{
	asm volatile
	(
		// Load the vector in xmm0
		"movaps	(%0),	%%xmm0			\n\t"
		// Copy vect in xmm2
		"movaps %%xmm0,	%%xmm2			\n\t"
		// Square xmm0
		"mulps 	%%xmm0,	%%xmm0			\n\t"
		// Copy xmm0 in xmm1
		"movaps %%xmm0, %%xmm1			\n\t"
		"shufps $0x4E,	%%xmm1,	%%xmm0	\n\t"

		"addps 	%%xmm1, %%xmm0			\n\t"
		"movaps %%xmm0,	%%xmm1			\n\t"
		"shufps $0x11,	%%xmm1,	%%xmm1	\n\t"
		"addps	%%xmm1,	%%xmm0			\n\t"
		"rsqrtps	%%xmm0,	%%xmm0		\n\t"
		"mulps	%%xmm0,	%%xmm2			\n\t"
		"movaps %%xmm2,	(%0)			\n\t"
		:
		: "r" (&vec)
		: "%xmm0", "%xmm1", "%xmm2"
	);
}

void Vector4fRoutines_SSE::ProdImpl(vec4f& lVec, const vec4f& rVec)
{
	asm volatile
	(
		"movaps		(%0),	%%xmm0			\n\t"
		"movaps		(%1),	%%xmm1			\n\t"
		"movaps		%%xmm0,	%%xmm2			\n\t"
		"shufps		$0xC9,	%%xmm0,	%%xmm0	\n\t"
		"shufps		$0xD2,	%%xmm1,	%%xmm1	\n\t"
		"mulps		%%xmm1,	%%xmm0			\n\t"
		"shufps		$0xD2,	%%xmm1, %%xmm1	\n\t"
		"shufps		$0xD2,	%%xmm2,	%%xmm2	\n\t"
		"mulps		%%xmm2,	%%xmm1			\n\t"
		"subps		%%xmm1,	%%xmm0			\n\t"
		"movaps		%%xmm0,	(%0)			\n\t"
		:
		: "r" (&lVec), "r" (&rVec)
		: "%xmm0", "%xmm1", "%xmm2"
	);
}

void Vector4fRoutines_SSE::SubImpl(vec4f& lVec, const vec4f& rVec)
{
}
