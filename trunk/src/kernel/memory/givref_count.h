// ==================================================================== //
// Copyright(c)'1994-2009 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software. 
// see the COPYRIGHT file for more details.
// author: Th. Gautier                                                
// version : 2.7
// date: 1995
// Definition of the Counter class, Counter
// This class definition objects to handle reference
// counter for memory allocation (eg array0). 
// ==================================================================== //
#ifndef _GIVARO_REF_COUNTER_H_
#define _GIVARO_REF_COUNTER_H_
#include <stddef.h>

class RefCounter {
public:
   // Cstor and Dstor
inline RefCounter( long l = 0) : counter(l) {} 
//inline RefCounter( const RefCounter& ) : counter(C.counter) {} 
inline ~RefCounter() {}

  //  Return the value
inline long  getvalue() const { return counter ; } 
inline long  val() const { return counter ; }
  // Return a ref to the counter
inline long& refvalue() { return counter ; }
  // Increments the counter and returns the new value 
inline long  incr() { return ++counter ; }
  // Decrements the value and returns the new value 
inline long  decr() { return --counter ; }

protected:
  long counter ;
} ;

#endif
