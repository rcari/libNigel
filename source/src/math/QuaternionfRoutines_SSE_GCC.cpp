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

#include <math/QuaternionfRoutines_SSE.hpp>
using namespace Nigel::math;

#include <cstdlib>
#include <cmath>

kint QuaternionfRoutines_SSE::routinePerformanceScore(Routine routine) const
{
	/*switch(routine)
	{
	case Normalize:
	case Rotation:
		return 1;
	default:
		return -1;
	}*/
	return -1;
}

void QuaternionfRoutines_SSE::AddImpl(quatf& lQuat, const quatf& rQuat)
{
}

void QuaternionfRoutines_SSE::AssignImpl(quatf& dest, const quatf& src)
{
}

void QuaternionfRoutines_SSE::AxisAngleImpl(kfloat* data, const quatf& src)
{
}

void QuaternionfRoutines_SSE::ClearImpl(quatf& quat)
{
}

void QuaternionfRoutines_SSE::IdentityImpl(quatf& quat)
{
}

void QuaternionfRoutines_SSE::InvertImpl(quatf& quat)
{
}

void QuaternionfRoutines_SSE::LookAtImpl(quatf& quat, const vec4f& center, const vec4f& to, const vec4f& up)
{
	// TODO: Add an implementation for that ?
}

kfloat QuaternionfRoutines_SSE::MagnitudeImpl(const quatf& quat)
{
	return 0.0f;
}

void QuaternionfRoutines_SSE::MulQuatImpl(quatf& lQuat, const quatf& rQuat)
{
}

void QuaternionfRoutines_SSE::NormalizeImpl(quatf& quat)
{
	asm volatile
	(
		// Load the quaternion in xmm0
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
		: "r" (&quat)
		: "%xmm0", "%xmm1", "%xmm2"
	);
}

void QuaternionfRoutines_SSE::RotateVecImpl(vec4f& vec, const quatf& quat)
{
}

void QuaternionfRoutines_SSE::RotationImpl(quatf& quat, kfloat x, kfloat y, kfloat z, kfloat angle)
{
	angle /= 2.0f;
	kfloat sina = sinf(angle);

	vec4f vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;

	asm volatile
	(
		"movaps	(%0),			%%xmm0		\n\t" // Loading axis in xmm0
		"movss	(%1),			%%xmm1		\n\t" // Loading sin in xmm1-0
		"shufps	$0x00,	%%xmm1,	%%xmm1		\n\t" // Shuffling sin in xmm1
		"mulps	%%xmm1,			%%xmm0		\n\t" // Multiplying
		"movaps %%xmm0,			(%2)		\n\t" // Save in quat
		:
		: "r" (&vec), "r" (&sina), "r" (&quat)
		: "%xmm0", "%xmm1"
	);

	// Change the S of the quaternion.
	quat.s = cosf(angle);
}

void QuaternionfRoutines_SSE::RotationMatImpl(mat4x4f& mat, const quatf& quat)
{
}

void QuaternionfRoutines_SSE::SubImpl(quatf& lQuat, const quatf& rQuat)
{
}
