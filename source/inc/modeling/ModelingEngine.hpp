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

#include <modeling/shape/Generator.hpp>
#include <modeling/shape/ShapeManager.hpp>

#define N_SHAPE_I( n_shape ) const Nigel::modeling::shape::Shape* n_shape::Instance() { return PrivateInstance(); }\
	kbool n_shape::RegisterGenerator(Nigel::modeling::shape::Generator* g) { PrivateInstance()->addBlock(g); return true; }\
	Nigel::modeling::shape::Shape* n_shape::PrivateInstance() { return (__N_Instance != K_NULL) ? __N_Instance : __N_Instance = new n_shape(); }\
	Nigel::modeling::shape::Shape* n_shape::__N_Instance = K_NULL;\
	kbool n_shape::__N_Registered = Nigel::modeling::shape::ShapeManager::RegisterShape(n_shape::Instance());

#define N_GENERATOR_I( n_generator, n_shape ) kbool n_generator::__N_Registered = n_shape::RegisterGenerator( n_generator::StaticMetaBlock()->createBlockT<Nigel::modeling::shape::Generator>() );
