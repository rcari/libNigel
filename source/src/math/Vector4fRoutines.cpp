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
#include <math/Vector4fRoutines.hpp>
using namespace Nigel::math;

using namespace Kore::data;

void Vector4fRoutines::library(Library* lib)
{
	Block::library(lib);
	if(hasParent())
	{
		static_cast<MathEngine*>(Block::library())->registerVectorRoutines(this);
	}
}

void Vector4fRoutines::doInstallRoutine(Routine routine, kvoid* routinePtr) const
{
	switch(routine)
	{
	case Add:
		Vector4f::_Add = reinterpret_cast<Vector4f_Add>(routinePtr);
		break;
	case Assign:
		Vector4f::_Assign = reinterpret_cast<Vector4f_Assign>(routinePtr);
		break;
	case Dot:
		Vector4f::_Dot = reinterpret_cast<Vector4f_Dot>(routinePtr);
		break;
	case Length:
		Vector4f::_Length = reinterpret_cast<Vector4f_Length>(routinePtr);
		break;
	case MulMatrix:
		Vector4f::_MulMatrix = reinterpret_cast<Vector4f_MulMatrix>(routinePtr);
		break;
	case MulScalar:
		Vector4f::_MulScalar = reinterpret_cast<Vector4f_MulScalar>(routinePtr);
		break;
	case Normalize:
		Vector4f::_Normalize = reinterpret_cast<Vector4f_Normalize>(routinePtr);
		break;
	case Prod:
		Vector4f::_Prod = reinterpret_cast<Vector4f_Prod>(routinePtr);
		break;
	case Sub:
		Vector4f::_Sub = reinterpret_cast<Vector4f_Sub>(routinePtr);
		break;
	default:
		qWarning("Trying to install unknown Vector4f routine: %d", routine);
		break;
	}
	// XXX: Adding new routines must be done here too !
}
