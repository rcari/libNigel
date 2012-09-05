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

#include <math/MathEngine.hpp>
#include <math/Matrix4x4fRoutines.hpp>
using namespace Nigel::math;
using namespace Kore::data;

void Matrix4x4fRoutines::library(Library* lib)
{
	Block::library(lib);
	if(hasParent())
	{
		static_cast<MathEngine*>(Block::library())->registerMatrixRoutines(this);
	}
}

void Matrix4x4fRoutines::doInstallRoutine(Routine routine, kvoid* routinePtr) const
{
	switch(routine)
	{
	case Assign:
		Matrix4x4f::_Assign = reinterpret_cast<Matrix4x4f_Assign>(routinePtr);
		break;
	case BatchMultiply:
		Matrix4x4f::_BatchMultiply = reinterpret_cast<Matrix4x4f_BatchMultiply>(routinePtr);
		break;
	case Clear:
		Matrix4x4f::_Clear = reinterpret_cast<Matrix4x4f_Clear>(routinePtr);
		break;
	case Det:
		Matrix4x4f::_Det = reinterpret_cast<Matrix4x4f_Det>(routinePtr);
		break;
	case Identity:
		Matrix4x4f::_Identity = reinterpret_cast<Matrix4x4f_Identity>(routinePtr);
		break;
	case Invert:
		Matrix4x4f::_Invert = reinterpret_cast<Matrix4x4f_Invert>(routinePtr);
		break;
	case LookAt:
		Matrix4x4f::_LookAt = reinterpret_cast<Matrix4x4f_LookAt>(routinePtr);
		break;
	case MulMatrix:
		Matrix4x4f::_MulMatrix = reinterpret_cast<Matrix4x4f_MulMatrix>(routinePtr);
		break;
	case Rotation:
		Matrix4x4f::_Rotation = reinterpret_cast<Matrix4x4f_Rotation>(routinePtr);
		break;
	case Scale:
		Matrix4x4f::_Scale = reinterpret_cast<Matrix4x4f_Scale>(routinePtr);
		break;
	case Translation:
		Matrix4x4f::_Translation = reinterpret_cast<Matrix4x4f_Translation>(routinePtr);
		break;
	case Transpose:
		Matrix4x4f::_Transpose = reinterpret_cast<Matrix4x4f_Transpose>(routinePtr);
		break;
	default:
		qWarning("Trying to install unknown Matrix4x4f routine: %d", routine);
		break;
	}
	// XXX: Adding new routines must be done here too !
}
