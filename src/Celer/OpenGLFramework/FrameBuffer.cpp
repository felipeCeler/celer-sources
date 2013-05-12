/*
 * FrameBuffer.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: felipe
 */

#include "FrameBuffer.hpp"

namespace Celer
{
	namespace OpenGL
	{

		// TODO Por enquanto é o básico do FrameBuffer.
		// TODO Próxima extensão é fazer mais de um Color Attachment.

		FrameBuffer::FrameBuffer ( std::string name )
		{
			name_ = name;
			// TODO Como garantir que há um contexto OpenGL Criado.
			Celer::OpenGL::OpenGLContext::instance( )->glewInitialize( name_ );

			if ( !glewIsSupported ( "GL_EXT_framebuffer_object" ) )
			{
				std::cerr << "ERROR" + name_ + ": Support for  GL_EXT_framebuffer_object OpenGL extensions missing." << std::endl;
			}

		}

		FrameBuffer::~FrameBuffer ( )
		{
			// TODO
			if ( bound_ )
			{
				unbind ( );
			}

			if ( depthBuffer_id_ != 0 )
			{
				glDeleteRenderbuffersEXT ( 1 , &depthBuffer_id_ );
			}

			if ( frameBuffer_id_ != 0 )
			{
				glDeleteFramebuffersEXT ( 1 , &frameBuffer_id_ );
			}

		}

		bool FrameBuffer::create ( const GLuint width , const GLuint height )
		{
			/// XXX: How creat color Attachments and Depth and Stencil Buffer
			/// XXX: This function needs too much attention !!
			/// FIXME: hasDepht;hasStencil,hasTexture: How many and so one ...

			if ( depthBuffer_id_ != 0 )
			{
				glDeleteRenderbuffersEXT ( 1 , &depthBuffer_id_ );
				depthBuffer_id_ = 0;
			}else
			{
				glGenRenderbuffersEXT ( 1 , &depthBuffer_id_ );

			}
			if ( frameBuffer_id_ != 0 )
			{
				glDeleteFramebuffersEXT ( 1 , &frameBuffer_id_ );
				frameBuffer_id_ = 0;
			}else
			{
				glGenFramebuffersEXT ( 1 , &frameBuffer_id_ );

			}

			this->width_ 	= width;
			this->height_ 	= height;

			// create a depth buffer:
			glBindRenderbuffer ( GL_RENDERBUFFER , depthBuffer_id_ );
			glRenderbufferStorage ( GL_RENDERBUFFER , GL_DEPTH_COMPONENT32 , width_ , height_ );
			glBindRenderbuffer ( GL_RENDERBUFFER , 0 );

			// create fbo and attach render texture and depth texture
			glBindFramebuffer ( GL_FRAMEBUFFER , frameBuffer_id_ );
			//glFramebufferTexture2D ( GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D , texture2D_.id ( ) , 0 );
			glFramebufferRenderbuffer ( GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_RENDERBUFFER , depthBuffer_id_ );
			glBindFramebufferEXT ( GL_FRAMEBUFFER_EXT , 0 );


			return checkFramebufferStatus ( );
		}

		bool FrameBuffer::bind ( )
		{
			if ( frameBuffer_id_ == 0 )
			{
				return false;
			}

			glBindFramebufferEXT ( GL_FRAMEBUFFER_EXT , frameBuffer_id_ );

			return bound_;
		}

		bool FrameBuffer::checkFramebufferStatus ( )
		{
			// check FBO status
			GLenum status = glCheckFramebufferStatusEXT ( GL_FRAMEBUFFER_EXT );
			switch ( status )
			{
				case GL_FRAMEBUFFER_COMPLETE_EXT:
					std::cout << name_ + " : Framebuffer complete." << std::endl;
					return true;

				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
					std::cout << name_ + " : [ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
					return false;

				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
					std::cout << name_ + " : [ERROR] Framebuffer incomplete: No image is attached to FBO." << std::endl;
					return false;

				case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
					std::cout << name_ + " : [ERROR] Framebuffer incomplete: Attached images have different dimensions." << std::endl;
					return false;

				case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
					std::cout << "[ERROR] Framebuffer incomplete: Color attached images have different internal formats." << std::endl;
					return false;

				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
					std::cout << name_ + " : [ERROR] Framebuffer incomplete: Draw buffer." << std::endl;
					return false;

				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
					std::cout << name_ + " : [ERROR] Framebuffer incomplete: Read buffer." << std::endl;
					return false;

				case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
					std::cout << name_ + " : [ERROR] Unsupported by FBO implementation." << std::endl;
					return false;

				default:
					std::cout << name_ + " : [ERROR] Unknow error." << std::endl;
					return false;
			}
		}

		bool FrameBuffer::unbind ( )
		{

			glBindFramebufferEXT ( GL_FRAMEBUFFER_EXT , 0 );

			return true;
		}

		// TODO Explicar const correctness C++ - Essa solução em especial está em @see http://www.parashift.com/c++-faq-lite/const-correctness.html#faq-18.11.
		// Eu precisar apenas da referência da class Texture do Framebuffer. Já que a cópia pode gerar o efeito colateral de deletar a textura do Contexto OpenGL.
//		Texture2D const& FrameBuffer::texture ( ) const
//		{
//			return texture2D_;
//		}

		GLuint FrameBuffer::width ( ) const
		{
			return width_;
		}


		GLuint FrameBuffer::height ( ) const
		{
			return height_;
		}

		std::string FrameBuffer::name ( ) const
		{
			return name_;
		}


	}
}
