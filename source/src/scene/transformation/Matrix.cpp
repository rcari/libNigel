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

#include <scene/transformation/Matrix.hpp>
using namespace Nigel::scene::transformation;

using namespace Nigel::math;

#define K_BLOCK_TYPE		Nigel::scene::transformation::Matrix
#define K_BLOCK_SUPER_TYPE	Nigel::scene::transformation::Transformation
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
K_BLOCK_ICON("nigel/images/icons/transformation.matrix.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_METHOD( Matrix::MatrixProperties )
K_BLOCK_END

#include <QtCore/QtEndian>

Matrix::Matrix()
:	_matrix(new Matrix4x4f)
{
	blockName(tr("Matrix"));
	_matrix->identity();
}

Matrix::~Matrix()
{
	delete _matrix;
}

Matrix4x4f& Matrix::matrix()
{
	return *_matrix;
}

const Matrix4x4f& Matrix::matrix() const
{
	return *_matrix;
}

QByteArray Matrix::matrixData() const
{
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
	return QByteArray::fromRawData(reinterpret_cast<const char*>(_matrix->values()), sizeof(mat4x4f));
#else
	QByteArray data(reinterpret_cast<const char*>(_matrix.values()), sizeof(mat4x4f));
	kuint* values = reinterpret_cast<kuint*>(data.data());
	for(kint i = 0; i < 16; i++)
	{
		values[i] = qToLittleEndian(values[i]);
	}
	return data;
#endif
}

void Matrix::matrixData(const QByteArray& data)
{
	memcpy(_matrix->values(), data.data(), sizeof(mat4x4f));
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	kuint* values = reinterpret_cast<kuint*>(_matrix.values());
	for(kint i = 0; i < 16; i++)
	{
		values[i] = qToBigEndian(values[i]);
	}
#endif
}

QString Matrix::matrixDataString() const
{
	return QString(
			"%1 %2 %3 %4\n"
			"%5 %6 %7 %8\n"
			"%9 %10 %11 %12\n"
			"%13 %14 %15 %16"
		)
		.arg(_matrix->values()[ 0], -10)
		.arg(_matrix->values()[ 1], -10)
		.arg(_matrix->values()[ 2], -10)
		.arg(_matrix->values()[ 3], -10)
		.arg(_matrix->values()[ 4], -10)
		.arg(_matrix->values()[ 5], -10)
		.arg(_matrix->values()[ 6], -10)
		.arg(_matrix->values()[ 7], -10)
		.arg(_matrix->values()[ 8], -10)
		.arg(_matrix->values()[ 9], -10)
		.arg(_matrix->values()[10], -10)
		.arg(_matrix->values()[11], -10)
		.arg(_matrix->values()[12], -10)
		.arg(_matrix->values()[13], -10)
		.arg(_matrix->values()[14], -10)
		.arg(_matrix->values()[15], -10);
}

QVariant Matrix::MatrixProperties(int property)
{
	switch(property)
	{
	case Block::BlockTypeName:
 		return tr("Matrix");
 	case Block::BlockPropertiesName:
 		{
 			QHash<QString,QVariant> result;
 			result.insert("matrixDataString", tr("Values:"));
 			return result;
 		}
 	default:
 		return QVariant();
	}
}
