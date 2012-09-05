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

#include <math/QuaternionfRoutines_CPP.hpp>
using namespace Nigel::math;

#include <cstdlib>
#include <cmath>
#include <float.h>

K_MATH_ROUTINES_I( Nigel::math::QuaternionfRoutines_CPP )

QuaternionfRoutines_CPP::QuaternionfRoutines_CPP()
{
	blockName("Quaternionf C++ routines");
}

kint QuaternionfRoutines_CPP::routinePerformanceScore(Routine routine) const
{
	return 0;
}

void QuaternionfRoutines_CPP::installRoutine(Routine routine) const
{
	// Find it
	kvoid* routinePtr = K_NULL;
	switch(routine)
	{
	case Add:
		routinePtr = reinterpret_cast<kvoid*>(&AddImpl);
		break;
	case Assign:
		routinePtr = reinterpret_cast<kvoid*>(&AssignImpl);
		break;
	case AssignVec:
		routinePtr = reinterpret_cast<kvoid*>(&AssignVecImpl);
		break;
	case AxisAngle:
		routinePtr = reinterpret_cast<kvoid*>(&AxisAngleImpl);
		break;
	case Clear:
		routinePtr = reinterpret_cast<kvoid*>(&ClearImpl);
		break;
	case FromMat:
		routinePtr = reinterpret_cast<kvoid*>(&FromMatImpl);
		break;
	case Identity:
		routinePtr = reinterpret_cast<kvoid*>(&IdentityImpl);
		break;
	case Invert:
		routinePtr = reinterpret_cast<kvoid*>(&InvertImpl);
		break;
	case LookAt:
		routinePtr = reinterpret_cast<kvoid*>(&LookAtImpl);
		break;
	case Magnitude:
		routinePtr = reinterpret_cast<kvoid*>(&MagnitudeImpl);
		break;
	case MulQuat:
		routinePtr = reinterpret_cast<kvoid*>(&MulQuatImpl);
		break;
	case Normalize:
		routinePtr = reinterpret_cast<kvoid*>(&NormalizeImpl);
		break;
	case RotateVec:
		routinePtr = reinterpret_cast<kvoid*>(&RotateVecImpl);
		break;
	case Rotation:
		routinePtr = reinterpret_cast<kvoid*>(&RotationImpl);
		break;
	case RotationMat:
		routinePtr = reinterpret_cast<kvoid*>(&RotationMatImpl);
		break;
	case Sub:
		routinePtr = reinterpret_cast<kvoid*>(&SubImpl);
		break;
	default:
		qFatal("Trying to register an unsupported routine for Quaternion");
		break;
	}
	// Install it !
	doInstallRoutine(routine, routinePtr);
}

void QuaternionfRoutines_CPP::AddImpl(quatf& lQuat, const quatf& rQuat)
{
	lQuat.x += rQuat.x;
	lQuat.y += rQuat.y;
	lQuat.z += rQuat.z;
	lQuat.s += rQuat.s;
}

void QuaternionfRoutines_CPP::AssignImpl(quatf& dest, const quatf& src)
{
	dest = src;
}

void QuaternionfRoutines_CPP::AssignVecImpl(quatf& dest, const vec4f& vec, kfloat s)
{
	dest.x = vec.x;
	dest.y = vec.y;
	dest.z = vec.z;
	dest.s = s;
}

void QuaternionfRoutines_CPP::AxisAngleImpl(kfloat* data, const quatf& src)
{
	quatf q = src;
	NormalizeImpl(q);

	data[0] = 2.0f * acosf(q.s);
	kfloat s = sqrtf(1.0f - q.s*q.s);

	if(qFuzzyCompare(1.0f, 1.0f+s))
	{
		data[1] = 1.0f;
		data[2] = 0.0f;
		data[3] = 0.0f;
	}
	else
	{
		s = 1.0f / s;
		data[1] = q.x * s;
		data[2] = q.y * s;
		data[3] = q.z * s;
	}
}

void QuaternionfRoutines_CPP::ClearImpl(quatf& quat)
{
	memset(&quat, 0x00, sizeof(quatf));
}

void QuaternionfRoutines_CPP::FromMatImpl(quatf& quat, const mat4x4f& mat)
{
	// See: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

	const kfloat* m = mat.values;

	quat.s = sqrtf( qMax( 0.0f, 1.0f + m[0] + m[5] + m[10] ) );
	quat.x = sqrtf( qMax( 0.0f, 1.0f + m[0] - m[5] - m[10] ) );
	quat.y = sqrtf( qMax( 0.0f, 1.0f - m[0] + m[5] - m[10] ) );
	quat.z = sqrtf( qMax( 0.0f, 1.0f - m[0] - m[5] + m[10] ) );

	quat.x = copysign( quat.x, m[9] - m[6] );
	quat.y = copysign( quat.y, m[2] - m[8] );
	quat.z = copysign( quat.z, m[4] - m[1] );
}

void QuaternionfRoutines_CPP::IdentityImpl(quatf& quat)
{
	ClearImpl(quat);
	quat.s = 1.0f;
}

void QuaternionfRoutines_CPP::InvertImpl(quatf& quat)
{
	const kfloat q2 = -1.0f /
		(
			quat.x*quat.x +
			quat.y*quat.y +
			quat.z*quat.z +
			quat.s*quat.s
		);

	// Store...
	quat.x *= q2;
	quat.y *= q2;
	quat.z *= q2;
	quat.s *= -q2;
}

void QuaternionfRoutines_CPP::LookAtImpl(quatf& quat, const vec4f& center, const vec4f& to, const vec4f& up)
{
	// TODO: Add an implementation for that ?
}

kfloat QuaternionfRoutines_CPP::MagnitudeImpl(const quatf& quat)
{
	return sqrtf
		(
			quat.x*quat.x +
			quat.y*quat.y +
			quat.z*quat.z +
			quat.s*quat.s
		);
}

void QuaternionfRoutines_CPP::MulQuatImpl(quatf& lQuat, const quatf& rQuat)
{
	quatf tmp = lQuat;

	lQuat.x = ( tmp.x*rQuat.x - tmp.y*rQuat.y - tmp.z*rQuat.z - tmp.s*rQuat.s );
	lQuat.y = ( tmp.x*rQuat.y + tmp.y*rQuat.x + tmp.z*rQuat.s - tmp.s*rQuat.z );
	lQuat.z = ( tmp.x*rQuat.z - tmp.y*rQuat.s + tmp.z*rQuat.x + tmp.s*rQuat.y );
	lQuat.s = ( tmp.x*rQuat.s + tmp.y*rQuat.z - tmp.z*rQuat.y + tmp.s*rQuat.x );
}

void QuaternionfRoutines_CPP::NormalizeImpl(quatf& quat)
{
	kfloat mag = MagnitudeImpl(quat);

	if(!qFuzzyCompare(1.0f, 1.0f+mag))
	{
		mag = 1.0f / mag;
		quat.x = quat.x * mag;
		quat.y = quat.y * mag;
		quat.z = quat.z * mag;
		quat.s = quat.s * mag;
	}
}

void QuaternionfRoutines_CPP::RotateVecImpl(vec4f& vec, const quatf& quat)
{
	quatf q;
	q.x = vec.x;
	q.y = vec.y;
	q.z = vec.z;
	q.s = 0.0f;

	quatf result = quat;

	// q * v * q^-1

	MulQuatImpl(result, q);

	q = quat;
	InvertImpl(q);

	MulQuatImpl(result, q);

	vec.x = result.x;
	vec.y = result.y;
	vec.z = result.z;
	vec.w = 0.0f;
}

void QuaternionfRoutines_CPP::RotationImpl(quatf& quat, kfloat x, kfloat y, kfloat z, kfloat angle)
{
	kfloat sin_a = sin(angle * 0.5f);
	quat.x = x * sin_a;
	quat.y = y * sin_a;
	quat.z = z * sin_a;
	quat.s = cosf(angle * 0.5f);
}

void QuaternionfRoutines_CPP::RotationMatImpl(mat4x4f& mat, const quatf& quat)
{
	kfloat xx = 2.0f * quat.x * quat.x;
	kfloat yy = 2.0f * quat.y * quat.y;
	kfloat zz = 2.0f * quat.z * quat.z;

	kfloat xy = 2.0f * quat.x * quat.y;
	kfloat xz = 2.0f * quat.x * quat.z;
	kfloat yz = 2.0f * quat.y * quat.z;

	kfloat sx = 2.0f * quat.s * quat.x;
	kfloat sy = 2.0f * quat.s * quat.y;
	kfloat sz = 2.0f * quat.s * quat.z;

	mat.values[ 0] = 1.0f - yy - zz;
	mat.values[ 1] = xy - sz;
	mat.values[ 2] = xz + sy;
	mat.values[ 3] = 0.0f;

	mat.values[ 4] = xy + sz;
	mat.values[ 5] = 1.0f - xx - zz;
	mat.values[ 6] = yz - sx;
	mat.values[ 7] = 0.0f;

	mat.values[ 8] = xy - sy;
	mat.values[ 9] = yz + sx;
	mat.values[10] = 1.0f - xx - yy;
	mat.values[11] = 0.0f;

	mat.values[12] = 0.0f;
	mat.values[13] = 0.0f;
	mat.values[14] = 0.0f;
	mat.values[15] = 1.0f;
}

void QuaternionfRoutines_CPP::SubImpl(quatf& lQuat, const quatf& rQuat)
{
	lQuat.x -= rQuat.x;
	lQuat.y -= rQuat.y;
	lQuat.z -= rQuat.z;
	lQuat.s -= rQuat.s;
}
