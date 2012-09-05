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

#include <math/Vector4fRoutines_CPP.hpp>
using namespace Nigel::math;

K_MATH_ROUTINES_I( Nigel::math::Vector4fRoutines_CPP )

#include <cstdlib>
#include <cmath>

Vector4fRoutines_CPP::Vector4fRoutines_CPP()
{
	blockName("Vector4f C++ routines");
}

kint Vector4fRoutines_CPP::routinePerformanceScore(Routine routine) const
{
	switch(routine)
	{
	case Add:
	case Assign:
	case Dot:
	case Length:
	case MulMatrix:
	case MulScalar:
	case Normalize:
	case Prod:
	case Sub:
		return 0;
	default:
		return -1;
	}
}

void Vector4fRoutines_CPP::installRoutine(Routine routine) const
{
	switch(routine)
	{
	case Add:
		doInstallRoutine(Add, reinterpret_cast<kvoid*>(&AddImpl));
		break;
	case Assign:
		doInstallRoutine(Assign, reinterpret_cast<kvoid*>(&AssignImpl));
		break;
	case Dot:
		doInstallRoutine(Dot, reinterpret_cast<kvoid*>(&DotImpl));
		break;
	case Length:
		doInstallRoutine(Length, reinterpret_cast<kvoid*>(&LengthImpl));
		break;
	case MulMatrix:
		doInstallRoutine(MulMatrix, reinterpret_cast<kvoid*>(&MulMatrixImpl));
		break;
	case MulScalar:
		doInstallRoutine(MulScalar, reinterpret_cast<kvoid*>(&MulScalarImpl));
		break;
	case Normalize:
		doInstallRoutine(Normalize, reinterpret_cast<kvoid*>(&NormalizeImpl));
		break;
	case Prod:
		doInstallRoutine(Prod, reinterpret_cast<kvoid*>(&ProdImpl));
		break;
	case Sub:
		doInstallRoutine(Sub, reinterpret_cast<kvoid*>(&SubImpl));
		break;
	default:
		break;
	}
}

void Vector4fRoutines_CPP::AddImpl(vec4f& lVec, const vec4f& rVec)
{
	lVec.x += rVec.x;
	lVec.y += rVec.y;
	lVec.z += rVec.z;
}

void Vector4fRoutines_CPP::AssignImpl(vec4f& dest, const vec4f& src)
{
	dest = src;
}

void Vector4fRoutines_CPP::ClearImpl(vec4f& vec)
{
	memset(&vec, 0x0, sizeof(vec4f));
}

kfloat Vector4fRoutines_CPP::DotImpl(const vec4f& lVec, const vec4f& rVec)
{
	return lVec.x*rVec.x + lVec.y*rVec.y + lVec.z*rVec.z;
}

kfloat Vector4fRoutines_CPP::LengthImpl(const vec4f& vec)
{
	return sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

void Vector4fRoutines_CPP::MulMatrixImpl(vec4f& vec, const mat4x4f& mat)
{
	const vec4f v = vec;
	vec.x = mat.values[ 0]*v.x + mat.values[ 1]*v.y + mat.values[ 2]*v.z + mat.values[ 3]*v.w;
	vec.y = mat.values[ 4]*v.x + mat.values[ 5]*v.y + mat.values[ 6]*v.z + mat.values[ 7]*v.w;
	vec.z = mat.values[ 8]*v.x + mat.values[ 9]*v.y + mat.values[10]*v.z + mat.values[11]*v.w;
	vec.w = mat.values[12]*v.x + mat.values[13]*v.y + mat.values[14]*v.z + mat.values[15]*v.w;
}

void Vector4fRoutines_CPP::MulScalarImpl(vec4f& vec, kfloat scalar)
{
	vec.x *= scalar;
	vec.y *= scalar;
	vec.z *= scalar;
}

void Vector4fRoutines_CPP::NormalizeImpl(vec4f& vec)
{
	const kfloat norm = 1.0f / LengthImpl(vec);
	vec.x *= norm;
	vec.y *= norm;
	vec.z *= norm;
}

void Vector4fRoutines_CPP::ProdImpl(vec4f& lVec, const vec4f& rVec)
{
	const vec4f v = lVec;
	lVec.x = v.y*rVec.z - v.z*rVec.y;
	lVec.y = v.z*rVec.x - v.x*rVec.z;
	lVec.z = v.x*rVec.y - v.y*rVec.x;
}

void Vector4fRoutines_CPP::SubImpl(vec4f& lVec, const vec4f& rVec)
{
	lVec.x -= rVec.x;
	lVec.y -= rVec.y;
	lVec.z -= rVec.z;
}
