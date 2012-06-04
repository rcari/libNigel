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

#pragma once

#include <NigelExport.hpp>

#include <data/Block.hpp>

#include <geometry/GeometricElement.hpp>

#include <QtCore/QVariant>

namespace Nigel { namespace modeling { namespace shape {

class GeneratorParameter;
class Shape;

/*!
 * @brief Primitive Generator.
 *
 * The role of a Generator is to create Primitive instances based on a Shape.
 */
class NigelExport Generator : public Kore::data::Block
{
	Q_OBJECT

public:
	Generator();

	/*!
	 * @brief Generate a primitive.
	 *
	 * Returns an instance of the Primitive described by the primitiveFactory given the specified
	 * shape and parameters or K_NULL in case of an error (@sa lastErrorMessage).
	 *
	 * @param shape	The shape.
	 * @param parameters The shape and generator parameters.
	 * @return an instance of the Primitive.
	 */
	virtual Nigel::geometry::GeometricElement* generatePrimitive(const QVariantMap& parameters) const = K_NULL;

	/*!
	 * @brief Geometry meta block.
	 * @return The meta block of the Geometry supported by this generator.
	 */
	virtual const Kore::data::MetaBlock* geometryMetaBlock() const = K_NULL;

	/*!
	 * @brief Primitive parameters.
	 * @return The parameters required to generate the Primitive.
	 */
	const QList<const GeneratorParameter*> parameters() const;

	/*!
	 * @brief The shape of this Generator.
	 * @return The shape instance.
	 */
	const Shape* shape() const;

public:
	static QVariantMap CreateDefaultParametersList(const Generator* generator);

protected:
	QList<const GeneratorParameter*> _parameters;
};

}}}

#define N_GENERATOR( geometry ) private: static kbool __N_Registered;\
	public:\
		virtual const Kore::data::MetaBlock* geometryMetaBlock() const { return geometry::StaticMetaBlock(); }
