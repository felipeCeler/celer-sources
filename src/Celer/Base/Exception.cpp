/*
 * Exception.cpp
 *
 *  Created on: Mar 23, 2012
 *      Author: felipe
 */

#include "Exception.hpp"

namespace Celer
{
	namespace Log
	{

		Exception::Exception ( const std::string& message ) throw ( )
		{
			// TODO Auto-generated constructor stub
			message_ = message;
		}

		Exception::Exception ( const std::string& name , const std::string& message ) throw ( )
		{
			message_ = name + ": " + message;
		}

		Exception::~Exception ( ) throw ( )
		{
			// TODO Auto-generated destructor stub
		}

		const char* Exception::what ( ) const throw ( )
		{
			return message_.c_str ( );
		}

	}
}
