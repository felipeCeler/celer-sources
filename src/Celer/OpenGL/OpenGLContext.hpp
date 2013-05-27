/*
 * OpenGL.h
 *
 *  Created on: Mar 21, 2012
 *      Author: felipe
 */

#ifndef OPENGL_CELER_HPP_
#define OPENGL_CELER_HPP_

#define GLEW_STATIC

// Unix Like OpenGL inlcudes.
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Standart Library
#include <iostream>
#include <sstream>

// Celer Framework
#include <Celer/Base/Exception.hpp>

namespace Celer
{
	namespace OpenGL
	{
		class OpenGLContext
		{
			private:
				                        OpenGLContext();
				static OpenGLContext* 	instance_;
				       bool 		isglewInitialized_;

			public:
				static OpenGLContext* 	instance 	( );
				       void 		glewInitialize 	( const std::string& who ) throw ( Celer::Log::Exception );

		};

	}
}
#endif /* OPENGL_CELER_HPP_ */
