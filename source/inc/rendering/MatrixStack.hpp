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

#include <QtCore/QVector>
#include <math/Matrix4x4f.hpp>
#include <math/Quaternionf.hpp>

namespace Nigel { namespace rendering {

class NigelExport MatrixStack
{
public:
	MatrixStack();

	void reset();

	inline kint currentIndex() const { return _currentIndex; }

	inline Nigel::math::Matrix4x4f& top()
	{
		return *(_matrices.data() + _currentIndex);
	}

	inline const Nigel::math::Matrix4x4f& top() const
	{
		return _matrices.at(_currentIndex);
	}

	inline Nigel::math::Matrix4x4f& inverseTop()
	{
		return *(_inverseMatrices.data() + _currentIndex);
	}

	inline const Nigel::math::Matrix4x4f& inverseTop() const
	{
		return _inverseMatrices.at(_currentIndex);
	}

	inline Nigel::math::Matrix4x4f* history(kint history)
	{
		return (_matrices.data() + _currentIndex - history);
	}

	inline const Nigel::math::Matrix4x4f* history(kint history) const
	{
		return &_matrices.at(_currentIndex - history);
	}

	inline Nigel::math::Matrix4x4f* inverseHistory(kint history)
	{
		return (_inverseMatrices.data() + _currentIndex - history);
	}

	inline const Nigel::math::Matrix4x4f* inverseHistory(kint history) const
	{
		return &_inverseMatrices.at(_currentIndex - history);
	}

	inline Nigel::math::Matrix4x4f& push()
	{
		_currentIndex++;
		if(_currentIndex == _matrices.size())
		{
			// We double the stack capacity every time its needed.
			int newSize = _matrices.size() * 2;
			_matrices.resize( newSize );
			_inverseMatrices.resize( newSize );
		}

		// Copy the inverse matrix at the top
		*(_inverseMatrices.data() + _currentIndex) = *(_inverseMatrices.data() + _currentIndex - 1);

		// Return the top matrix
		return *(_matrices.data() + _currentIndex) = *(_matrices.data() + _currentIndex - 1); // Copy the matrix at the top !
	}

	inline void pop()
	{
		K_ASSERT( _currentIndex > 0 )
		_currentIndex--;
	}

	inline void translate(const Nigel::math::Vector4f& direction)
	{
		Nigel::math::Matrix4x4f matrix;
		// Post-multiply the matrix
		*(_matrices.data() + _currentIndex) *= matrix.translation(
				direction.values().x,
				direction.values().y,
				direction.values().z
			);
		// Pre-multiply the inverse matrix by the inverse transformation
		*(_inverseMatrices.data() + _currentIndex) =
			matrix.translation(
				-direction.values().x,
				-direction.values().y,
				-direction.values().z
			)
			*
			(*(_inverseMatrices.data() + _currentIndex));
	}

	inline void rotate(const Nigel::math::Quaternionf& orientation)
	{
		Nigel::math::Matrix4x4f matrix;
		orientation.setRotationMatrix(matrix);

		// Post-multiplty the matrix
		*(_matrices.data() + _currentIndex) *= matrix;

		// Set the inverse transformation
		orientation.inverse().setRotationMatrix(matrix);

		// Pre-multiply the inverse matrix
		*(_inverseMatrices.data() + _currentIndex) =
			matrix
			*
			*(_inverseMatrices.data() + _currentIndex);
	}

	inline void scale(const Nigel::math::Vector4f& weights)
	{
		Nigel::math::Matrix4x4f matrix;
		// Post-multiply the matrix
		*(_matrices.data() + _currentIndex) *= matrix.scale(
				weights.values().x,
				weights.values().y,
				weights.values().z
			);
		// Pre-multiply the inverse matrix by the inverse transformation
		*(_inverseMatrices.data() + _currentIndex) =
			matrix.scale(
				1.0f / weights.values().x,
				1.0f / weights.values().y,
				1.0f / weights.values().z
			)
			*
			(*(_inverseMatrices.data() + _currentIndex));
	}

	/*!
	 * This is potentially very slow (due to the matrix inversion). There might however be cases where you absolutely need
	 * to pass a transformation matrix rather than using one of the translate, rotate and scale functions.
	 */
	inline void applyTransformationMatrix(const Nigel::math::Matrix4x4f& matrix)
	{
		// Post-multiply the top matrix by the transformation matrix
		*(_matrices.data() + _currentIndex) *= matrix;

		// Pre-multiply the top inverse matrix by the inverse transformation matrix
		*(_inverseMatrices.data() + _currentIndex) = matrix.inverse() *	(*(_inverseMatrices.data() + _currentIndex));
	}

private:
	kint _currentIndex;
	QVector<Nigel::math::Matrix4x4f> _matrices;
	QVector<Nigel::math::Matrix4x4f> _inverseMatrices;
};

}}
