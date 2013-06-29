/*
 * ShaderManager.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: fmc
 */

#include "ShaderManager.hpp"

// TODO Get filename from the filePath -
//      http://stackoverflow.com/a/5523506/1204876
// TODO Use the new way to query information about the shader program -
//	http://stackoverflow.com/a/12611619/1204876

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

			uniforms_ = std::map<std::string, Uniform> ( );

		}

		ShaderManager::~ShaderManager ( )
		{
			// TODO Auto-generated destructor stub
		}

		GLint ShaderManager::id()
		{
			return id_;
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
					std::cerr << "Unable to compile shader "  << fileName <<  std::endl;
					shaderLogInformation ( shaderID );
					glDeleteShader ( shaderID );
					shaderID = 0;
				}
			}
			else
			{
				std::cerr << "Unable to open file "  << fileName <<  std::endl;
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
		/// FIXME: Not Create. It's like requesting resources!
		void ShaderManager::create ( const std::string name, const std::string& vertexShader , const std::string& fragmentShader )
		{

			name_ = name;
			//TODO - Remove that, and changet to std::vector<char>
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
				std::cout <<  name_+" Couldn't link program. Log follows:" << std::endl << infoLog;

			}else
			{
				std::cout <<  name_+" Link program. Log follows:" << std::endl << infoLog;
				addUniforms();
				addSubRoutines (GL_VERTEX_SHADER);
				addSubRoutines (GL_GEOMETRY_SHADER);
				addSubRoutines (GL_FRAGMENT_SHADER);

			}

			std::cout <<  "Uniform Size " << uniforms_.size() << std::endl;

			for ( std::map<std::string, Uniform>::iterator it = uniforms_.begin(); it != uniforms_.end(); it++)
			{
				std::cout <<  "Name " << it->first << std::endl;
				std::cout <<  "Name " << it->second.location << std::endl;
			}

			delete[] infoLog;


		}

		/// TODO: Not Create. It's like requesting resources!
		void ShaderManager::create (  const std::string name, const std::string& vertexShader , const std::string& geometryShader , const std::string& fragmentShader )
		{
			name_ = name;
			char *infoLog;

			id_ = glCreateProgram();

			GLuint vertexID   = loadShaderFromFile( GL_VERTEX_SHADER,vertexShader );
			GLuint geometryID = loadShaderFromFile( GL_GEOMETRY_SHADER,geometryShader );
			GLuint fragmnetID = loadShaderFromFile( GL_FRAGMENT_SHADER,fragmentShader );


			glAttachShader(id_, vertexID);
			glAttachShader(id_, fragmnetID);
			glAttachShader(id_, geometryID);

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
				std::cout <<  name_+" Couldn't link program. Log follows:" << std::endl << infoLog;

			}else
			{
				std::cout <<  name_+" Link program. Log follows:" << std::endl << infoLog;
				addUniforms();
				addSubRoutines(GL_VERTEX_SHADER);
				addSubRoutines(GL_GEOMETRY_SHADER);
				addSubRoutines(GL_FRAGMENT_SHADER);
				addUniformBlocks();

			}

			std::cout <<  "Uniform Size " << uniforms_.size() << std::endl;

			for ( std::map<std::string, Uniform>::iterator it = uniforms_.begin(); it != uniforms_.end(); it++)
			{
				std::cout <<  "Name " << it->first << std::endl;
				std::cout <<  "Name " << it->second.location << std::endl;
			}

			delete[] infoLog;


		}


		void ShaderManager::addSubRoutines ( GLenum shader_type )
		{

			int number_of_subroutines_uniforms;

			GLuint           	location_uniform;
			std::string 		uniform_name;
			GLint 			actual_length_uniform_name;
			GLint         		max_length_uniform_name;
			GLint        		number_of_active_subroutine;


			std::vector < GLint > 	locations_subroutine;
			std::string 		subroutine_name;
			GLint         		max_length_subroutine_name;
			GLint 			actual_length_subroutine_name;


			/// Get the number of SubRoutines Uniforms - Each subroutine represent a type function to choose.
			/// Ex: shaderModel   - can be Phong or Garound.
			///     distanceModel - can be Euclidian, Manhattan or Chessboard
			glGetProgramStageiv( id_ , shader_type, GL_ACTIVE_SUBROUTINE_UNIFORMS, &number_of_subroutines_uniforms );
			std::cout << "GL_ACTIVE_SUBROUTINES_UNIFORMS : " << number_of_subroutines_uniforms << std::endl;

			/// Get the biggest uniform name length;
			glGetProgramStageiv ( id_ , shader_type, GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &max_length_uniform_name);
			/// Get the biggest subroutine  name length;
			glGetProgramStageiv ( id_ , shader_type, GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &max_length_subroutine_name);
			/// For each subroutine uniform, get the informations for each function.
			for ( int i = 0; i < number_of_subroutines_uniforms; ++i )
			{
				uniform_name.resize(max_length_uniform_name);
				subroutine_name.resize (max_length_subroutine_name);
				/// Get the uniform subroutine name.
				glGetActiveSubroutineUniformName ( id_ , shader_type , i , max_length_uniform_name, &actual_length_uniform_name, &uniform_name[0] );
				location_uniform = i;
				glGetActiveSubroutineUniformiv ( id_ , shader_type, i, GL_NUM_COMPATIBLE_SUBROUTINES, &number_of_active_subroutine);
				locations_subroutine.resize(number_of_active_subroutine);
				glGetActiveSubroutineUniformiv ( id_ , shader_type, i, GL_COMPATIBLE_SUBROUTINES, &locations_subroutine[0]);

				std::cout <<  " Uniform Name " << uniform_name << " has "<< number_of_active_subroutine << " subroutines to choose. " << std::endl;
				std::cout <<  " Subroutines: " << std::endl;

				for ( std::vector<GLint>::iterator index = locations_subroutine.begin ( ); index != locations_subroutine.end ( ); ++index )
				{
					glGetActiveSubroutineName ( id_, shader_type, *index , max_length_subroutine_name, &actual_length_subroutine_name, &subroutine_name[0]);

					addSubRoutine( std::string(subroutine_name.begin(),subroutine_name.begin()+actual_length_subroutine_name),
					               shader_type,
					               *index,
					               location_uniform,
					               std::string(uniform_name.begin(),uniform_name.begin()+actual_length_uniform_name));
					std::cout << *index << " - "<< subroutine_name << std::endl;
				}

			}


		}

		void ShaderManager::addSubRoutine( std::string name, GLenum shader_type , GLint index, GLint uniform_location, std::string uniform_name  )
		{
			SubRoutine s;

			s.name 			= name;
			s.shader_type 		= shader_type;
			s.index  		= index;

			s.uniform_location	= uniform_location;
			s.uniform_name          = uniform_name;

			subroutines_[uniform_name][name] = s;

		}

		void ShaderManager::addUniforms ( )
		{

			// @see - http://www.opengl.org/wiki/Program_Introspection#Naming

			GLint numUniforms = 0;
			GLsizei actualLen;
			glGetProgramInterfaceiv ( id_ , GL_UNIFORM , GL_ACTIVE_RESOURCES , &numUniforms );
			int size_of_properties = 5;
			const GLenum properties[] =
			{ GL_BLOCK_INDEX, GL_NAME_LENGTH, GL_TYPE, GL_ARRAY_STRIDE, GL_LOCATION };

			for ( int unif = 0; unif < numUniforms; ++unif )
			{
				GLint values[size_of_properties];
				glGetProgramResourceiv ( id_ , GL_UNIFORM , unif , size_of_properties , properties , size_of_properties , 0 , values );

				//Skip any uniforms that are in a block.
				if ( values[0] != -1 )
					continue;

				//Get the name. Must use a std::vector rather than a std::string for C++03 standards issues.
				//C++11 would let you use a std::string directly.
				std::string name;


				// @see - "+ 1" to make room for the terminating NUL for the C API
				// 	   http://stackoverflow.com/a/12742517/1204876
				name.resize( values[1] + 1 );

				glGetProgramResourceName ( id_ , GL_UNIFORM , unif , name.size ( ) , &actualLen , &name[0] );

				name.resize( actualLen );

				addUniform ( name , values[2] , values[3] , values[4] );
			}

		}

		void ShaderManager::addUniform ( std::string name , GLenum type , GLint size, GLuint location )
		{

			Uniform u;
			u.type = type;
			u.size = size;
			u.location = location;
			uniforms_[name] = u;

		}

		void ShaderManager::addUniformBlocks ( )
		{

			// @see - http://www.opengl.org/wiki/Program_Introspection#Naming

			GLint number_of_blocks = 0;

			glGetProgramInterfaceiv ( id_ , GL_UNIFORM_BLOCK , GL_ACTIVE_RESOURCES , &number_of_blocks );

			// GL_NUM_ACTIVE_VARIABLES, the number of active variables associated with an active uniform block.
			const GLenum block_properties[2] =
			{ GL_NUM_ACTIVE_VARIABLES , GL_NAME_LENGTH };

			const GLenum activeUnifProp[1] = {GL_ACTIVE_VARIABLES};

			int size_of_properties = 5;
			const GLenum uniform_properties[] =
			{ GL_BLOCK_INDEX, GL_NAME_LENGTH, GL_TYPE, GL_ARRAY_STRIDE, GL_LOCATION };

			GLsizei actualLen;

			for ( int block_index = 0; block_index < number_of_blocks; ++block_index )
			{

				GLint uniform_block_values[2];

				glGetProgramResourceiv(id_, GL_UNIFORM_BLOCK, block_index, 2, block_properties, 2, NULL, uniform_block_values);

				std::string uniform_block_name;
				// @see - "+ 1" to make room for the terminating NUL for the C API
				// 	   http://stackoverflow.com/a/12742517/1204876
				uniform_block_name.resize( uniform_block_values[1] + 1 );

				glGetProgramResourceName ( id_ , GL_UNIFORM_BLOCK , block_index , uniform_block_name.size ( ) , &actualLen , &uniform_block_name[0] );

				uniform_block_name.resize( actualLen );

				if (  uniform_block_values[0] == 0 )
					continue;

				 std::vector<GLint> blockUnifs(uniform_block_values[0]);
				 glGetProgramResourceiv(id_, GL_UNIFORM_BLOCK, block_index, 1, activeUnifProp , uniform_block_values[0], 0, &blockUnifs[0]);

				for ( int unif = 0; unif < blockUnifs.size(); ++unif )
				{
					GLint values[size_of_properties];
					glGetProgramResourceiv ( id_ , GL_UNIFORM , blockUnifs[unif] , size_of_properties , uniform_properties , size_of_properties , 0 , values );

					//Skip any uniforms that are in a block.
					if ( values[0] != -1 )
						continue;

					//Get the name. Must use a std::vector rather than a std::string for C++03 standards issues.
					//C++11 would let you use a std::string directly.
					std::string name;


					// @see - "+ 1" to make room for the terminating NUL for the C API
					// 	   http://stackoverflow.com/a/12742517/1204876
					name.resize( values[1] + 1 );

					glGetProgramResourceName ( id_ , GL_UNIFORM , blockUnifs[unif] , name.size ( ) , &actualLen , &name[0] );

					name.resize( actualLen );

					addUniform ( name , values[2] , values[3] , values[4] );
				}


			}


		}

		void ShaderManager::addUniformBlock ( std::string name, GLint index )
		{
			UniformBlock u;

			u.index = index;

			uniform_blocks_[name] = u;


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
