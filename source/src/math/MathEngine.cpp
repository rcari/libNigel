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

//#include <math/MathEngine.hpp>
#include "../../inc/math/MathEngine.hpp"
#include <math/Matrix4x4fRoutines.hpp>
#include <math/QuaternionfRoutines.hpp>
#include <math/Vector4fRoutines.hpp>
using namespace Nigel::math;

MathEngine::MathEngine()
{
	blockName("Nigel Math Engine");

	// Pre-fill the routines scores arrays.
	_matrixRoutinesScores.fill(-1, Matrix4x4fRoutines::MAX_ROUTINE);
	_quaterionRoutinesScores.fill(-1, QuaternionfRoutines::MAX_ROUTINE);
	_vectorRoutinesScores.fill(-1, Vector4fRoutines::MAX_ROUTINE);
}

void MathEngine::registerMatrixRoutines(Matrix4x4fRoutines* routines)
{
	for(kint i = 0; i < Matrix4x4fRoutines::MAX_ROUTINE; i++)
	{
		Matrix4x4fRoutines::Routine routine = (Matrix4x4fRoutines::Routine)i;
		kint probeScore = routines->routinePerformanceScore( routine );
		if(probeScore > _matrixRoutinesScores.at(i))
		{
			_matrixRoutinesScores[i] = probeScore;
			routines->installRoutine(routine);
		}
	}
}

void MathEngine::registerQuaternionRoutines(QuaternionfRoutines* routines)
{
	for(kint i = 0; i < QuaternionfRoutines::MAX_ROUTINE; i++)
	{
		QuaternionfRoutines::Routine routine = (QuaternionfRoutines::Routine)i;
		kint probeScore = routines->routinePerformanceScore( routine );
		if(probeScore > _quaterionRoutinesScores.at(i))
		{
			_quaterionRoutinesScores[i] = probeScore;
			routines->installRoutine(routine);
		}
	}
}

void MathEngine::registerVectorRoutines(Vector4fRoutines* routines)
{
	for(kint i = 0; i < Vector4fRoutines::MAX_ROUTINE; i++)
	{
		Vector4fRoutines::Routine routine = (Vector4fRoutines::Routine)i;
		kint probeScore = routines->routinePerformanceScore( routine );
		if(probeScore > _vectorRoutinesScores.at(i))
		{
			_vectorRoutinesScores[i] = probeScore;
			routines->installRoutine(routine);
		}
	}
}

MathEngine* MathEngine::Instance()
{
	return _Instance ? _Instance : _Instance = new MathEngine();
}

MathEngine* MathEngine::_Instance = K_NULL;
