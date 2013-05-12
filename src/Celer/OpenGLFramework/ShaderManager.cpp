/*
 * ShaderManager.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: fmc
 */

#include "ShaderManager.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>

namespace Celer
{

	namespace OpenGL
	{

		ShaderManager::ShaderManager ( )
		{
			// TODO Auto-generated constructor stub
			id_ 		= 0;
			isLinked_ 	= false;
			name_ 		= std::string ("");

		}

		ShaderManager::~ShaderManager ( )
		{
			// TODO Auto-generated destructor stub
		}

		GLuint ShaderManager::loadShaderFromFile ( GLenum shaderType ,  std::string fileName )
		{
			//Open file
			GLuint shaderID = 0;
			std::string shaderString;
			std::ifstream sourceFile ( fileName.c_str ( ) );

			//Source file loaded
			if ( sourceFile )
			{
				//Get shader source
				shaderString.assign ( ( std::istreambuf_iterator<char> ( sourceFile ) ) , std::istreambuf_iterator<char> ( ) );

				//Create shader ID
				shaderID = glCreateShader ( shaderType );

				//Set shader source
				const GLchar* shaderSource = shaderString.c_str ( );
				glShaderSource ( shaderID , 1 , (const GLchar**) &shaderSource , NULL );

				//Compile shader source
				glCompileShader ( shaderID );

				//Check shader for errors
				GLint shaderCompiled = GL_FALSE;
				glGetShaderiv ( shaderID , GL_COMPILE_STATUS , &shaderCompiled );
				if ( shaderCompiled != GL_TRUE )
				{
					printf ( "Unable to compile shader %d!\n\nSource:\n%s\n" , shaderID , shaderSource );
					shaderLogInformation ( shaderID );
					glDeleteShader ( shaderID );
					shaderID = 0;
				}
			}
			else
			{
				printf ( "Unable to open file %s\n" , fileName.c_str ( ) );
			}

			return shaderID;

		}

		void ShaderManager::shaderLogInformation ( GLuint id )
		{

			//Make sure name is shader
			if( glIsShader( id ) )
			{
				//Shader log length
				int infoLogLength = 0;
				int maxLength = infoLogLength;

				//Get info string length
				glGetShaderiv( id, GL_INFO_LOG_LENGTH, &maxLength );

				//Allocate string
				char* infoLog = new char[ maxLength ];

				//Get info log
				glGetShaderInfoLog( id, maxLength, &infoLogLength, infoLog );
				if( infoLogLength > 0 )
				{
					//Print Log
					printf( "%s\n", infoLog );
				}

				//Deallocate string
				delete[] infoLog;
			}
			else
			{
				printf( "Name %d is not a shader\n", id );
			}

		}
		/// TODO: Not Create. It's like requesting resources!
		void ShaderManager::create ( const std::string& vertexShader , const std::string fragmentShader )
		{

			char *infoLog;

			id_ = glCreateProgram();

			GLuint vertexID   = loadShaderFromFile( GL_VERTEX_SHADER,vertexShader );
			GLuint fragmnetID = loadShaderFromFile( GL_FRAGMENT_SHADER,fragmentShader );

			glAttachShader(id_, vertexID);
			glAttachShader(id_, fragmnetID);

			 // Link the program
			glLinkProgram( id_ );
			// Make sure it linked correctly
			int linked;
			glGetProgramiv ( id_ , GL_LINK_STATUS , &linked );
			isLinked_ = linked;
			// Get info log
			GLsizei logsize, logarraysize;
			glGetProgramiv ( id_ , GL_INFO_LOG_LENGTH , &logarraysize );
			infoLog = new char[logarraysize];
			glGetProgramInfoLog ( id_ , logarraysize , &logsize , infoLog );
			if ( !isLinked_ )
			{
				std::cout <<  "Program::link(): Couldn't link program. Log follows:" << std::endl << infoLog;

			}else
			{
				std::cout <<  "Program::link(): link program. Log follows:" << std::endl << infoLog;
				addUniforms();
			}

			std::cout <<  "Uniform Size " << uniforms_.size() << std::endl;

			for ( std::map<std::string, Uniform>::iterator it = uniforms_.begin(); it != uniforms_.end(); it++)
			{
				std::cout <<  "Name " << it->first << std::endl;
				std::cout <<  "Name " << it->second.type << std::endl;
			}

			delete[] infoLog;


		}

		void ShaderManager::addUniforms ( )
		{

			int count;
			GLsizei actualLen;
			GLint size;
			GLint uniArrayStride;
			GLenum type;
			char *name;

			int maxUniLength;
			glGetProgramiv ( id_ , GL_ACTIVE_UNIFORMS , &count );

			glGetProgramiv ( id_ , GL_ACTIVE_UNIFORM_MAX_LENGTH , &maxUniLength );

			name = (char *) malloc ( sizeof(char) * maxUniLength );

			unsigned int loc;
			for ( int i = 0; i < count; ++i )
			{

				glGetActiveUniform ( id_ , i , maxUniLength , &actualLen , &size , &type , name );
				// -1 indicates that is not an active uniform, although it may be present in a
				// uniform block
				loc = glGetUniformLocation ( id_ , name );
				glGetActiveUniformsiv ( id_ , 1 , &loc , GL_UNIFORM_ARRAY_STRIDE , &uniArrayStride );
				if ( loc != -1 )
					addUniform ( name , type , size );

			}
			free ( name );

		}

		void ShaderManager::addUniform ( std::string name , GLenum type , unsigned int size )
		{

			Uniform u;
			u.type = type;
			u.location = glGetUniformLocation ( id_ , name.c_str ( ) );
			u.size = size;
			uniforms_[name] = u;

		}

		void ShaderManager::active	( )
		{
			glUseProgram(id_);
		}

		void ShaderManager::deactive ( )
		{
			glUseProgram(0);
		}


	}

}
