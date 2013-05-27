/*
 * Celer GL Texture.hpp
 *
 *  Created on: Jan 26, 2012
 *      Author: felipe
 */

#ifndef _CELER_TEXTURE_HPP_
#define _CELER_TEXTURE_HPP_

/// OpenGL Extensions 		- Need a OpenGL context to use this class.
#include "OpenGLContext.hpp"
/// Base			- This class can't be copied.
#include <Celer/Base/Base.hpp>
/// Standard C++ Library	- std::cout and std::string.

#include <string>

// Celer::Texture
// References:
// - Steps3D Russian
// - dpix
// - Doom3 SDK
// - G3D Engine
// - libCinder
//____________________________________________________________________________
// TODO: Better namespace.
// TODO: Better name
// TODO: A Template parameter to choose into float or int Texute,
//	 isn't it a good feature?.

namespace Celer
{
	namespace OpenGL
	{

		class Texture2D
		{
			protected:

				GLuint 			id_;      	///< Identification
				GLuint 			height_;   	///< Image Height
				GLuint 			width_;  	///< Image width

				GLuint			internalFormat_;
				GLenum			format_;
				GLenum			type_;
				GLenum			target_;	///< Can be 2D or Rectangle

				std::string 		name_;		///< Something like that ... Why I'm using this texture ?
				bool			isInitialized_;
				bool    		bound_;    	///< If it's bind

				std::string determineFormat	(GLint  internalFormat) const;
				std::string determineType	(GLenum type	      ) const;
				std::string determineTarget	(GLenum target        ) const;

			public:

				Texture2D       ( );
				Texture2D   	( std::string name );
			       ~Texture2D       ( );

				GLuint 			id    		( ) const;
				GLuint  		width  		( ) const;
				GLuint  		height 		( ) const;

				bool			bind		( ) ;
				bool    		unbind		( ) ;
				bool			isInitialized	( ) const;

				/// - Shows the current Texture with its default parameters.
				void                    whoIm  		( ) const;

				int    			create	( const GLuint width , const GLuint height );
				int    			create	( const GLuint width , const GLuint height,
				       			      	  	  	       GLuint internalFormat,
				       			      	  	  	       GLenum format,
				       			      	  	  	       GLenum type,
				       			      	  	  	       GLenum target	    );

				void 			loadFromRawData ( const GLubyte* pixels );
		};
	}
}

#endif /* _CELER_TEXTURE_HPP_ */


