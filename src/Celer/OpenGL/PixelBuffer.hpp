/*
 * PixelBuffer.hpp
 *
 *  Created on: Mar 5, 2012
 *      Author: felipe
 */

#ifndef PIXELBUFFER_HPP_
#define PIXELBUFFER_HPP_

/// System
#include <assert.h>
#include <iostream>
#include <cstdio>
#include <string>

#include "OpenGLContext.hpp"

/// Base			- This class can't be copied.
#include <Celer/Base/Base.hpp>

namespace Celer
{
	namespace OpenGL
	{
		class PixelBuffer : public Celer::NonCopyable
		{
				// TODO better boolean variable names.
				// TODO Does Glew is necessary for every Class ?
			private:

				GLuint 			id_;
				GLenum 			target_;
				bool 			ok_;
				bool 			bound_;
				std::string		name_;

			public:
							PixelBuffer ( std::string name );
							~PixelBuffer ( );

				GLuint 			id ( ) const;
				bool 			bind ( GLenum target );
				bool 			unbind ( );
				void 			setData ( unsigned size , const void * ptr , GLenum usage );
				void 			setSubData ( unsigned offs , unsigned size , const void * ptr );
				void 			getSubData ( unsigned offs , unsigned size , void * ptr );
				void* 			map ( GLenum access );
				bool 			unmap ( );
				void 			clear ( );

				static bool 		isSupported ( );
				std::string 		name ( );
		};
	}
}
#endif /* PIXELBUFFER_HPP_ */
