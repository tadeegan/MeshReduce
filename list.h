/*
 *  A generic template list class.  
 *  Fairly typical of the list example you would 
 *  find in any c++ book.
 */
#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include <assert.h>
#include <stdio.h>

template <class Type> 
class List {
	public:
				List(int s=0);
				~List();
		void	allocate(int s);
		void	SetSize(int s);
		void	Pack();
		void	Add(Type);
		void	AddUnique(Type);
		int 	Contains(Type);
		void	Remove(Type);
		void	DelIndex(int i);
		Type *	element;
		int		num;
		int		array_size;
		Type	&operator[](int i){assert(i>=0 && i<num); return element[i];}
};

#endif
