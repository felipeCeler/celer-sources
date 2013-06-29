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
#include <Celer/OpenGL/OpenGLContext.hpp>
/// Base			- This class can't be copied.
#include <Celer/Base/Base.hpp>
/// OpenGL Shaders
#include <Celer/OpenGL/Shader.hpp>
/// Standard C++ Library	- std::cout and std::string.
#include <iostream>
#include <fstream>
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
						GLint location;
						GLint array_size;
						GLint array_stride;
						GLint offset;
				};

				/// http://www.opengl.org/wiki/Interface_Block_(GLSL)
				/// If you are using CelerGL, make sure to set translate the matrix after upload to GPU
				/// The way that uniform block carrier data is complex.
				/// This seems to work with a small blocks definition.
				struct UniformBlock
				{
						std::string 	     name;
						GLuint 		     index;
						Uniform uniform;
				};

				struct SubRoutine
				{
						// LORE SubRoutine belong to a shader stage.
						//      There is only on uniform location for them.
						//      One index for each subroutine.
						//
						GLenum 		shader_type;
						GLuint 		index;
						std::string 	name;

						GLuint 		uniform_location;
						std::string     uniform_name;
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

				std::map<std::string, Uniform> 		uniforms_;
				std::map<std::string, UniformBlock>     uniform_blocks_;
				// FIXME <Uniform name, SubRoutine informations>
				std::map<std::string, std::map <std::string , SubRoutine> > 	subroutines_;

				ShaderManager 	   ( );
				ShaderManager 	   ( std::string name );
				GLint    id	   ( );

				void create 	   ( const std::string name , const std::string& vertexShader , const std::string& fragmentShader );
				void create 	   ( const std::string name , const std::string& vertexShader , const std::string& geometryShader , const std::string& fragmentShader );

				void addUniforms ( );
				void addUniform ( std::string name , GLenum type , GLint location, GLint array_size , GLint array_stride, GLint offset );

				void addSubRoutines ( GLenum shader_type );
				void addSubRoutine  ( std::string name , GLenum shader_type, GLint index, GLint uniform_location, std::string uniform_name );

				void addUniformBlocks ( );
				void addUniformBlock ( std::string name, GLint index, Uniform uniform );


				void active   	   ( );
				void deactive 	   ( );

				virtual ~ShaderManager ( );
		};

	}

}

#endif /* SHADERMANAGER_HPP_ */

