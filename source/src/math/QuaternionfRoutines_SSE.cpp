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

K_MATH_ROUTINES_I( Nigel::math::QuaternionfRoutines_SSE )

QuaternionfRoutines_SSE::QuaternionfRoutines_SSE()
{
	blockName("Quaternionf SSE routines");
}

void QuaternionfRoutines_SSE::installRoutine(Routine routine) const
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
	case AxisAngle:
		routinePtr = reinterpret_cast<kvoid*>(&AxisAngleImpl);
		break;
	case Clear:
		routinePtr = reinterpret_cast<kvoid*>(&ClearImpl);
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
