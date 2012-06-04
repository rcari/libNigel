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

K_MATH_ROUTINES_I( Nigel::math::Vector4fRoutines_SSE )

Vector4fRoutines_SSE::Vector4fRoutines_SSE()
{
	blockName("Vector4f SSE routines");
}

void Vector4fRoutines_SSE::installRoutine(Routine routine) const
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
