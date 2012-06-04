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

#include <math/MathEngine.hpp>
#include <math/Quaternionf.hpp>
#include <math/QuaternionfRoutines.hpp>
using namespace Nigel::math;
using namespace Kore::data;

void QuaternionfRoutines::library(Library* lib)
{
	Block::library(lib);
	if(hasParent())
	{
		static_cast<MathEngine*>(Block::library())->registerQuaternionRoutines(this);
	}
}

void QuaternionfRoutines::doInstallRoutine(Routine routine, kvoid* routinePtr) const
{
	switch(routine)
	{
	case Add:
		Quaternionf::_Add = reinterpret_cast<Quaternionf_Add>(routinePtr);
		break;
	case Assign:
		Quaternionf::_Assign = reinterpret_cast<Quaternionf_Assign>(routinePtr);
		break;
	case AssignVec:
		Quaternionf::_AssignVec = reinterpret_cast<Quaternionf_AssignVec>(routinePtr);
		break;
	case AxisAngle:
		Quaternionf::_AxisAngle = reinterpret_cast<Quaternionf_AxisAngle>(routinePtr);
		break;
	case Clear:
		Quaternionf::_Clear = reinterpret_cast<Quaternionf_Clear>(routinePtr);
		break;
	case FromMat:
		Quaternionf::_FromMat = reinterpret_cast<Quaternionf_FromMat>(routinePtr);
		break;
	case Identity:
		Quaternionf::_Identity = reinterpret_cast<Quaternionf_Identity>(routinePtr);
		break;
	case Invert:
		Quaternionf::_Invert = reinterpret_cast<Quaternionf_Invert>(routinePtr);
		break;
	case LookAt:
		Quaternionf::_LookAt = reinterpret_cast<Quaternionf_LookAt>(routinePtr);
		break;
	case Magnitude:
		Quaternionf::_Magnitude = reinterpret_cast<Quaternionf_Magnitude>(routinePtr);
		break;
	case MulQuat:
		Quaternionf::_MulQuat = reinterpret_cast<Quaternionf_MulQuat>(routinePtr);
		break;
	case Normalize:
		Quaternionf::_Normalize = reinterpret_cast<Quaternionf_Normalize>(routinePtr);
		break;
	case RotateVec:
		Quaternionf::_RotateVec = reinterpret_cast<Quaternionf_RotateVec>(routinePtr);
		break;
	case Rotation:
		Quaternionf::_Rotation = reinterpret_cast<Quaternionf_Rotation>(routinePtr);
		break;
	case RotationMat:
		Quaternionf::_RotationMat = reinterpret_cast<Quaternionf_RotationMat>(routinePtr);
		break;
	case Sub:
		Quaternionf::_Sub = reinterpret_cast<Quaternionf_Sub>(routinePtr);
		break;
	default:
		break;
	}
}
