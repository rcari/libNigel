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

#include "MathTypes.hpp"

#include "Matrix4x4f.hpp"
#include "Vector4f.hpp"

namespace Nigel { namespace math {

class MathEngine;
class Matrix4x4f;
class QuaternionfRoutines;

class NigelExport _K_SSE_ALIGNED Quaternionf
{
	friend class MathEngine;
	friend class Matrix4x4f;
	friend class QuaternionfRoutines;

public:
	inline Quaternionf() { (*_Clear)(_values); }
	inline Quaternionf(kfloat s, const Vector4f& v) { (*_AssignVec)(_values, v._values, s); }

	inline Quaternionf(kfloat s, kfloat x, kfloat y, kfloat z)
	{ _values.s = s; _values.x = x; _values.y = y; _values.z = z; }

	inline kfloat magnitude() const { return (*_Magnitude)(_values); }

	inline Quaternionf inverse() const { Quaternionf result(*this); result.invert(); return result; }
	inline Quaternionf operator~() const { Quaternionf result(*this); result.invert(); return result; }
	inline Quaternionf& invert() { (*_Invert)(_values); return *this; }

	inline Quaternionf normalized() const { Quaternionf result(*this); result.normalize(); return result; }
	inline Quaternionf& normalize() { (*_Normalize)(_values); return *this; }

	inline Quaternionf operator+(const Quaternionf& q) const { Quaternionf result(*this); result += q; return result; }
	inline Quaternionf& operator+=(const Quaternionf& q) { (*_Add)(_values, q._values); return *this; }

	inline Quaternionf operator-(const Quaternionf& q) const { Quaternionf result(*this); result -= q; return result; }
	inline Quaternionf& operator-=(const Quaternionf& q) { (*_Sub)(_values, q._values); return *this; }

	inline Quaternionf operator*(const Quaternionf& q) const { Quaternionf result(*this); result *= q; return result; }
	inline Quaternionf& operator*=(const Quaternionf& q) { (*_MulQuat)(_values, q._values); return *this; }

	inline Quaternionf& operator=(const Quaternionf& q) { (*_Assign)(_values, q._values); return *this; }

	inline Vector4f& rotateVector(Vector4f& v) const { (*_RotateVec)(v._values, _values); return v; }
	inline Vector4f rotatedVector(const Vector4f& v) const { Vector4f result(v); rotateVector(result); return result; }

	inline Quaternionf& lookAt(const Vector4f& center, const Vector4f& to, const Vector4f& up)
	{
		(*_LookAt)(_values, center._values, to._values, up._values);
		return *this;
	}

	inline Quaternionf& identity() { (*_Identity)(_values); return *this; }

	inline Quaternionf& rotation(kfloat angle, kfloat x, kfloat y, kfloat z) { (*_Rotation)(_values, x, y, z, angle); return *this; }

	inline void setRotationMatrix(Matrix4x4f& m) const { (*_RotationMat)(m._values, _values); }
	inline void fromRotationMatrix(const Matrix4x4f& m) { (*_FromMat)(_values, m._values);  }

	inline void toAxisAngle(kfloat* data) const { (*_AxisAngle)(data, _values); }

	inline const quatf& data() const { return _values; }
	inline quatf& data() { return _values; }

private:
	quatf _values;

private:
	static Quaternionf_Add			_Add;
	static Quaternionf_Assign		_Assign;
	static Quaternionf_AssignVec	_AssignVec;
	static Quaternionf_Clear		_Clear;
	static Quaternionf_FromMat		_FromMat;
	static Quaternionf_Identity		_Identity;
	static Quaternionf_Invert		_Invert;
	static Quaternionf_LookAt		_LookAt;
	static Quaternionf_Magnitude	_Magnitude;
	static Quaternionf_MulQuat		_MulQuat;
	static Quaternionf_Normalize	_Normalize;
	static Quaternionf_RotateVec	_RotateVec;
	static Quaternionf_Rotation		_Rotation;
	static Quaternionf_RotationMat	_RotationMat;
	static Quaternionf_AxisAngle	_AxisAngle;
	static Quaternionf_Sub			_Sub;

};

}}
