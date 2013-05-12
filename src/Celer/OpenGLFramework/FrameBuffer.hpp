/*
 * FrameBuffer.hpp
 *
 *  Created on: Mar 5, 2012
 *      Author: felipe
 */


/// OpenGL Extensions 		- Need a OpenGL context to use this class.
#include "OpenGLContext.hpp"
/// Celer OpenGL Framework	- Color Attachments.
#include "GLTexture.hpp"
/// Base			- This class can't be copied.
#include <Celer/Base/Base.hpp>
/// Standard C++ Library	- std::cout and std::string.
#include <iostream>
#include <string>

#ifndef FRAMEBUFFER_HPP_
#define FRAMEBUFFER_HPP_


// Celer::Framebuffer
// References:
// - Steps3D Russian
// - dpix
// - Doom3 SDK
// - G3D Engine
// - libCinder
//____________________________________________________________________________
// TODO: How I will handle the various COLOR_ATTACHMENT ?



namespace Celer
{
	namespace OpenGL
	{
		class FrameBuffer : public Celer::NonCopyable
		{
			protected:
				GLuint 			frameBuffer_id_;
				GLuint 			depthBuffer_id_;
				GLuint			stencilBuffer_id_;

				GLuint 			width_;
				GLuint 			height_;
				std::string 		name_;		///< Something like that ... Why I'm using this framebuffer ?
				bool			isInitialized_;
				bool    		bound_;

			public:

							FrameBuffer ( );
							FrameBuffer ( std::string name );
						       ~FrameBuffer ( );
				//
			        GLuint			id     			( ) const;
				GLuint 			width  			( ) const;
				GLuint 			height 			( ) const;
				std::string	 	name 			( ) const;

				bool 			bind 			( );
				bool 			unbind 			( );
				bool			isInitialized		( ) const;

				bool 			checkFramebufferStatus 	( );
				/// - Shows the current Framebuffer parameters and Objects.
				void                    whoIm  			( ) const;

				bool 			create ( const GLuint width , const GLuint height );



		};
	}
}

#endif /* FRAMEBUFFER_HPP_ */

