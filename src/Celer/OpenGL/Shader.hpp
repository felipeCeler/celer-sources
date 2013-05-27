/*
 * Shader.hpp
 *
 *  Created on: Sep 23, 2012
 *      Author: fmc
 */


#ifndef SHADER_HPP_
#define SHADER_HPP_

/// OpenGL Extensions 		- Need a OpenGL context to use this class.
#include "OpenGLContext.hpp"
/// Base			- This class can't be copied.
#include <Celer/Base/Base.hpp>
/// Standard C++ Library        - Show text and type String
#include <iostream> ///- std::cout
#include <string>   ///- std::string


// Celer::Shader
// References:
// - dpix
// - G3D Engine
// - libCinder
// - Very Simple Library - from http://www.lighthouse3d.com/very-simple-libs
//____________________________________________________________________________
// TODO: Basic
// TODO: C++ Class Inheritance Concepts: Virtual functions, public inheritance, using Namespace::Class

namespace Celer
{

	namespace OpenGL
	{

		class Shader
		{
			private:
				GLenum			shaderType_;    ///< VERTEX, GEOMETRY or FRAGMENT shader.
				std::string 		fileName_;	///< Something.glsl
				std::string 		description_;	///< Something like that ... Why I'm using this shader ?

			public:

			 	Shader&     operator= 			( const Shader & );

					    Shader 			( GLenum      shadertype,
					           			  std::string fileName,
					           			  std::string description );

				std::string showShaderType 		( ) const;
				GLenum 	    shaderType 		( ) const;
				std::string fileName 			( ) const;
				std::string description 		( ) const;
				void        showShaderInformation	( ) const;

				virtual ~Shader ( );
		};

		class VertexShader : public Shader
		{
			public:
				VertexShader (std::string fileName, std::string description );
		};
		class FragmentShader : public Shader
		{
			public:
				FragmentShader ( std::string fileName , std::string description );
		};
		class GeometryShader : public Shader
		{
			public:
				GeometryShader ( std::string fileName , std::string description );
		};

	}

}

#endif /* SHADER_HPP_ */
