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

#pragma once

#include <NigelExport.hpp>

#include <data/Library.hpp>

#include <QtCore/QVector>

namespace Nigel { namespace math {

class Matrix4x4fRoutines;
class QuaternionfRoutines;
class Vector4fRoutines;

class NigelExport MathEngine : public Kore::data::Library
{
	friend class Matrix4x4fRoutines;
	friend class QuaternionfRoutines;
	friend class Vector4fRoutines;

private:
	MathEngine();

	void registerMatrixRoutines(Matrix4x4fRoutines*);
	void registerQuaternionRoutines(QuaternionfRoutines*);
	void registerVectorRoutines(Vector4fRoutines*);

private:
	QVector<kint> _matrixRoutinesScores;
	QVector<kint> _quaterionRoutinesScores;
	QVector<kint> _vectorRoutinesScores;

public:
	static MathEngine* Instance();
private:
	static MathEngine* _Instance;
};

}}

#define K_MATH_ROUTINES private: static kbool __K_Registered; static kbool RegisterRoutines();
#define K_MATH_ROUTINES_I( routines ) kbool routines::__K_Registered = routines::RegisterRoutines();\
	kbool routines::RegisterRoutines() { Nigel::math::MathEngine::Instance()->addBlock( new routines ); return true; }
