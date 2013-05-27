/*
 * OpenGL.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: felipe
 */

#include "OpenGLContext.hpp"
// TODO Totally Crazy this Class , why not constructor !!!!
// TODO Getting better Watching Tublib from Labri Boudeaux.

Celer::OpenGL::OpenGLContext* Celer::OpenGL::OpenGLContext::instance_ = 0;

namespace Celer
{
	namespace OpenGL
	{
		OpenGLContext::OpenGLContext ( ) : isglewInitialized_(false)
		{

		}
		/**
		 * Return the current instance. If instance doesn't exist, create it.
		 */
		OpenGLContext* OpenGLContext::instance ( )
		{
			if ( instance_ == 0 )
			{
				instance_ = new OpenGLContext ( );
			}

			return instance_;
		}

		void OpenGLContext::glewInitialize ( const std::string& who) throw ( Celer::Log::Exception )
		{
			if ( isglewInitialized_ )
			{
				return;
			}

			// Ensure OpenGL Context.
			GLenum error = glewInit ( );
			if ( error != GLEW_OK )
			{
				isglewInitialized_ = false;

				std::ostringstream stream;
				stream << "Glew error : " << glewGetErrorString ( error ) << " from: " << who <<  " => OpenGL can't be used.";
				throw Celer::Log::Exception ( stream.str ( ) );
			}
			else
			{
				std::cout << "GL VERSION : " + who + " " << glGetString ( GL_VERSION ) << std::endl;

				isglewInitialized_ = true;
			}

		}
	}
}

//#include <GlewInit.h>
//#include <GL/glew.h>
//#include <sstream>
//#include <iostream>
//
//using namespace std;
//
//
//namespace glopp
//{
//	void GlewInit::init() throw(GException)
//	{
//		GLenum erreur = glewInit();
//		if (erreur != GLEW_OK)
//		{
//			ostringstream stream;
//			stream<<"Glew error : "<<glewGetErrorString(erreur)<<" => glop can't be used.";
//			throw GException(stream.str());
//		}
//		if(!glewIsSupported("GL_VERSION_1_5"))
//		{
//			ostringstream stream;
//			stream<<"Your GL_VERSION is < 1.5 ("<<glGetString(GL_VERSION)<<"), glop can't be used.";
//			throw GException(stream.str());
//		}
//
//		#ifdef DEBUG
//			cout<<"GL VERSION : "<<glGetString(GL_VERSION)<<endl;
//		#endif
//	}
//
//	GlewInit::GlewInit()
//	{}
//
//}

