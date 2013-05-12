/*
 * Base.hpp
 *
 *  Created on: Sep 21, 2012
 *      Author: fmc
 */


#ifndef CELER_NONCOPYABLE_H
#define CELER_NONCOPYABLE_H

namespace Celer
{

	/**
	 * Motivation:
	 *
	 *	Sometimes, you don 't want to encounter a situation where something made a copy
	 *	of the object. In C++, a copy of an object can be made in a number of
	 *	situations. The most obvious is direct assignment.Less obvious, but equally
	 *	valid, is a function call using pass-by-value.
	 *	Copying in C++ is handled in two ways:
	 *
	 *		- The copy assignment operator
	 *		- The copy constructor
	 *
	 *	Unfortunately, if the class definition does not explicitly declare a copy
	 *	constructor or a a copy assignment operator, the compiler provides an implicit
	 *	version which is a public member function.
	 *	Solution:
	 *	Now, if we want to make a class non copyable, we can simply define its copy
	 *	constructor and copy assignment operator as private members. But, it makes more
	 *	sense to have a non copyable base class. If a class derives from the non
	 *	copyable base class, it too will be non copyable, since the copy of an object of
	 *	a derived class must necessarily invoke the copy constructor or copy assignment
	 *	operator of the corresponding base class.
	 *	By making the copy constructor or copy assignment operator private, we ensure
	 *	that the derived class is non coyable as well.
	 *	By just providing the declaration and not implementing them, we ensure that the
	 *	compiler does not provide its own versions and a linking error is generated if
	 *	they are used anywhere in the program.
	 *
	 *	From SpeedRun Journal @http://www.gamedev.net/blog/1369/entry-2253938-noncopyable-objects/
	 */

	class NonCopyable
	{
		protected:
			NonCopyable ( )
			{
			}
			~NonCopyable ( )
			{
			} /// Protected non-virtual destructor
		private:
			NonCopyable ( const NonCopyable & );
			NonCopyable & operator = ( const NonCopyable & );
	};
}

#endif /* CELER_NONCOPYABLE_H */
