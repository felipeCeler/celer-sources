/*
 * Exception.hpp
 *
 *  Created on: Mar 23, 2012
 *      Author: felipe
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

/// Standard C++ library
#include <exception>
#include <string>

// TODO . Mas o que houve de errado ? !!
//        Hoje 23/03/2012 , dia chuvoso, começarei a usar Exceptions e ver onde esse conceito se
//	  encaixa nesse framework.
//

namespace Celer
{
	namespace Log
	{

		class Exception: public std::exception
		{

			private:
				std::string 	     	message_; ///< the message of the exception

			public:
							Exception ( const std::string &message ) throw ();

							Exception ( const std::string &name ,
							            const std::string &message ) throw ();

				virtual 	    	~Exception ( ) throw ();
				virtual const char * 	what 	   ( ) const throw ();

		};

	}
}

#endif /* EXCEPTION_HPP_ */

