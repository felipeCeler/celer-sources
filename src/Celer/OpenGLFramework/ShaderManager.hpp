/**
    Celer OpenGL Framework

    ShaderManager.hpp
    Purpose    : Manage GPU shader resources.
    Created on : Sep 26, 2012

    @author    : Felipe de Carvalho
    @version   : 0.1.0 Initial Release

    @TODO: For while only one shader program is managed.
           You need more than one class to several program.
           Next step is build a real shader manager for the hole OpenGL context.
*/


#ifndef SHADERMANAGER_HPP_
#define SHADERMANAGER_HPP_

/// OpenGL Extensions 		- Need an OpenGL context to use this class.
#include "OpenGLContext.hpp"
/// Base			- This class can't be copied.
#include <Celer/Base/Base.hpp>
/// OpenGL Shaders
#include <Celer/OpenGLFramework/Shader.hpp>
/// Standard C++ Library	- std::cout and std::string.
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Celer::ShaderManager
// References:
// - dpix
// - G3D Engine
// - libCinder
// - Very Simple Library - from http://www.lighthouse3d.com/very-simple-libs
// - Open
//____________________________________________________________________________
// TODO: Basic

namespace Celer
{

	namespace OpenGL
	{

		class ShaderManager
		{
			private:

				struct Uniform
				{
						GLenum type;
						GLuint location;
						GLuint size;
						GLuint stride;
				};

				GLuint 			id_; ///< Identification
				std::string 		name_; ///< Some name that remember the purpose of the shader.
				bool			isLinked_;
				///TODO: Will be a list to take advantage of subroutine.

				std::vector<Celer::OpenGL::VertexShader> vertexShaders_;
				std::vector<Celer::OpenGL::FragmentShader> fragmentShaders_;


				bool 	compile 		( );
				GLuint 	loadShaderFromFile 	( GLenum shaderType , std::string fileName );
				void 	shaderLogInformation 	( GLuint id );
				void 	programLogInformation	( );

			public:

				std::map<std::string, Uniform> uniforms_;

				ShaderManager 	   ( );
				ShaderManager 	   ( std::string name );

				void create 	   ( const std::string& vertexShader , const std::string fragmentShader );

				void addUniforms ( );
				void addUniform  ( std::string name , GLenum type , unsigned int size );

				void active   	   ( );
				void deactive 	   ( );

				virtual ~ShaderManager ( );
		};

	}

}

#endif /* SHADERMANAGER_HPP_ */

