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

K_MATH_ROUTINES_I( Nigel::math::Matrix4x4fRoutines_SSE )

Matrix4x4fRoutines_SSE::Matrix4x4fRoutines_SSE()
{
	blockName("Matrix4x4f SSE routines");
}

void Matrix4x4fRoutines_SSE::installRoutine(Routine routine) const
{
	switch(routine)
	{
	case Assign:
		doInstallRoutine(Assign, reinterpret_cast<kvoid*>(&AssignImpl));
		break;
	case BatchMultiply:
		doInstallRoutine(BatchMultiply, reinterpret_cast<kvoid*>(&BatchMultiplyImpl));
		break;
	case Clear:
		doInstallRoutine(Clear, reinterpret_cast<kvoid*>(&ClearImpl));
		break;
	case Det:
		doInstallRoutine(Det, reinterpret_cast<kvoid*>(&DetImpl));
		break;
	case Identity:
		doInstallRoutine(Identity, reinterpret_cast<kvoid*>(&IdentityImpl));
		break;
	case Invert:
		doInstallRoutine(Invert, reinterpret_cast<kvoid*>(&InvertImpl));
		break;
	case MulMatrix:
		doInstallRoutine(MulMatrix, reinterpret_cast<kvoid*>(&MulMatrixImpl));
		break;
	case Rotation:
		doInstallRoutine(Rotation, reinterpret_cast<kvoid*>(&RotationImpl));
		break;
	case Scale:
		doInstallRoutine(Scale, reinterpret_cast<kvoid*>(&ScaleImpl));
		break;
	case Translation:
		doInstallRoutine(Translation, reinterpret_cast<kvoid*>(&TranslationImpl));
		break;
	case Transpose:
		doInstallRoutine(Transpose, reinterpret_cast<kvoid*>(&TransposeImpl));
		break;
	default:
		break;
	}
}
