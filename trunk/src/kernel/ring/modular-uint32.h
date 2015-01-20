// ==========================================================================
// $Source: /var/lib/cvs/Givaro/src/kernel/zpz/givzpz32uns.h,v $
// Copyright(c)'1994-2009 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.
// Authors: T. Gautier
// $Id: givzpz32uns.h,v 1.13 2011-02-02 17:16:43 bboyer Exp $
// ==========================================================================
//
//  Modified by Pascal Giorgi on 2002/02/13  (pascal.giorgi@ens-lyon.fr)

/*! @file givzpz32uns.h
 * @ingroup zpz
 * @brief    Arithmetic on Z/pZ, with p a prime number less than 2^32.
 *   Modulo typedef is a signed long number. In case it was modified
 *   then Bézout algorithm must be changed (coefficient can be negative).
 */
#ifndef __GIVARO_zpz32unsigned_H
#define __GIVARO_zpz32unsigned_H

#include "givaro/givbasictype.h"
#include "givaro/giverror.h"
#include "givaro/givranditer.h"
#include <math.h>

namespace Givaro {

template<class TAG> class Modular;

/*! @brief This class implement the standard arithmetic with Modulo Elements.
 * - The representation of an integer a in Zpz is the value a % p
 * - m max is 65536
 * - p max is 65521
 * .
 */
template<>
class Modular<uint32_t> {
public:
  // ----- Exported Types and constantes
  typedef Modular<uint32_t> Self_t;
  typedef uint32_t Residu_t;         // - type to store residue
  typedef uint32_t Compute_t;         // - type to store residue
  enum { size_rep = sizeof(Residu_t) };      // - size of the storage type
  // ----- Representation of Element of the domain Modular
  typedef uint32_t Rep;
  typedef uint32_t Element;
 typedef Element* Element_ptr ;
	typedef const Element* ConstElement_ptr;



  // ----- Representation of vector of the Element
  typedef Rep* Array;
  typedef const Rep* constArray;

  // ----- Constantes
  const Rep zero;
  const Rep one;
  const Rep mOne;

  // ----- Constructor
  Modular();
  Modular( Residu_t p );
  Modular( const Modular<uint32_t>& F);

  int operator==( const Modular<uint32_t>& BC) const { return _p == BC._p;}
  int operator!=( const Modular<uint32_t>& BC) const { return _p != BC._p;}

  Modular<uint32_t>& operator=( const Modular<uint32_t>& F)
  {
	  F.assign(const_cast<Element&>(one),F.one);
	  F.assign(const_cast<Element&>(zero),F.zero);
	  F.assign(const_cast<Element&>(mOne),F.mOne);


	  this->_p = F._p;
	  this->_dp = F._dp;
	  return *this;
  }

 Rep minElement() const
  {
	  return zero ;
  }

  Rep maxElement() const
  {
	  return mOne ;
  }

  // ----- Access to the modulus
	inline Residu_t residu() const { return _p; }
	inline Residu_t size() const { return _p; }
	inline Residu_t characteristic() const { return _p; }
	inline Integer& characteristic(Integer& p) const { return p = _p; }
	inline Residu_t cardinality() const { return _p; }
	inline Integer& cardinality(Integer& p) const { return p = _p; }


  // ----- Access to the modulus
  Rep& init( Rep& a ) const;
  void init( const size_t, Array a, constArray b ) const;
  Rep& init( Rep& r , const long a) const ;
  Rep& init( Rep& r , const unsigned long a) const ;
  Rep& init( Rep& a, const int i) const ;
  Rep& init( Rep& a, const unsigned int i) const ;
    Rep& init( Rep& a, const Integer& i) const ;


  // Initialisation from double ( added for FFLAS usage) (C Pernet)
  Rep& init( Rep& a, const double i) const;
  Rep& init( Rep& a, const float i) const;
  // Conversion to double ( added for FFLAS usage) (C Pernet)
  float& convert(float& r, const Rep a ) const { return r = (float)a ;}
  double& convert(double& r, const Rep a ) const { return r = (double)a ;}
  long int& convert(long int& r, const Rep a) const { return r = (long int)a;}
  unsigned long int& convert(unsigned long int& r, const Rep a) const { return r = (unsigned long int)a;}
  int32_t& convert(int32_t& r, const Rep a) const { return r = (int32_t)a;}
  uint32_t& convert(uint32_t& r, const Rep a) const { return r = (uint32_t)a;}
    Integer& convert(Integer& i, const Rep a) const {
        unsigned long ur;
        return i = (Integer)convert(ur, a);
    }

	inline Element& reduce (Element& x, const Element& y) const { return x = y % _p; }
	inline Element& reduce (Element& x) const { return x %= _p; }

  // ----- Misc methods
  int isZero( const Rep a ) const;
  int isOne ( const Rep a ) const;
  int isMOne ( const Rep a ) const;
  size_t length ( const Rep a ) const;

  // ----- Equality between two Elements
  int areEqual(const  Rep& a, const Rep& b) const { return a==b;}

  // ----- Operations with reduction: r <- a op b mod p, r <- op a mod p
  Rep& mul (Rep& r, const Rep a, const Rep b) const;
  Rep& div (Rep& r, const Rep a, const Rep b) const;
  Rep& add (Rep& r, const Rep a, const Rep b) const;
  Rep& sub (Rep& r, const Rep a, const Rep b) const;
  Rep& neg (Rep& r, const Rep a) const;
  Rep& inv (Rep& r, const Rep a) const;

  Rep& mulin (Rep& r, const Rep a) const;
  Rep& divin (Rep& r, const Rep a) const;
  Rep& addin (Rep& r, const Rep a) const;
  Rep& subin (Rep& r, const Rep a) const;
  Rep& negin (Rep& r) const;
  Rep& invin (Rep& r) const;

  // ----- Operations with reduction: r <- a op b mod p, r <- op a mod p
  void mul (const size_t sz, Array r, constArray a, constArray b) const;
  void mul (const size_t sz, Array r, constArray a, Rep b) const;

  void div (const size_t sz, Array r, constArray a, constArray b) const;
  void div (const size_t sz, Array r, constArray a, Rep b) const;

  void add (const size_t sz, Array r, constArray a, constArray b) const;
  void add (const size_t sz, Array r, constArray a, Rep b) const;

  void sub (const size_t sz, Array r, constArray a, constArray b) const;
  void sub (const size_t sz, Array r, constArray a, Rep b) const;

  void neg (const size_t sz, Array r, constArray a) const;
  void inv (const size_t sz, Array r, constArray a) const;

  // -- axpy: r <- a * x + y mod p
  Rep& axpy  (Rep& r, const Rep a, const Rep b, const Rep c) const;
  void axpy (const size_t sz, Array r, constArray a, constArray x, constArray c) const;
  // -- axpyin: r <- r + a * x mod p
  Rep& axpyin(Rep& r, const Rep a, const Rep b) const;
  void axpyin (const size_t sz, Array r, constArray a, constArray x) const;

  // -- axmy: r <- a * x - y mod p
  Rep& axmy  (Rep& r, const Rep a, const Rep b, const Rep c) const;
  void axmy (const size_t sz, Array r, constArray a, constArray x, constArray c) const;
  // -- axmyin: r <- a * x -r mod p
  Rep& axmyin(Rep& r, const Rep a, const Rep b) const;
  // void axmyin (const size_t sz, Array r, constArray a, constArray x) const;

  // -- maxpy: r <- c - a * b mod p
  Rep& maxpy  (Rep& r, const Rep a, const Rep b, const Rep c) const;
  // -- maxpyin: r <- r - a * b mod p
  Rep& maxpyin(Rep& r, const Rep a, const Rep b) const;
  void maxpyin (const size_t sz, Array r, constArray a, constArray x) const;

  // -- Misc: r <- a mod p
  void assign ( const size_t sz, Array r, constArray a ) const;
  Rep& assign ( Rep& r, const Rep a) const;
  Rep& assign ( Rep& r, const long a ) const;
  Rep& assign ( Rep& r, const unsigned long a ) const;
  Rep& assign ( Rep& r, const short a ) const;
  Rep& assign ( Rep& r, const unsigned short a ) const;

	// ----- Random generators
	typedef ModularRandIter<Self_t> RandIter;
	typedef GeneralRingNonZeroRandIter<Self_t> NonZeroRandIter;
    template< class Random > Element& random(const Random& g, Element& r) const { return init(r, g()); }
    template< class Random > Element& nonzerorandom(const Random& g, Element& a) const
    	{ while (isZero(init(a, g())));
    	  return a; }

  // <- \sum_i a[i], return 1 if a.size() ==0,
  Rep& reduceadd ( Rep& r, const size_t sz, constArray a ) const;

  // <- \prod_i a[i], return 1 if a.size() ==0,
  Rep& reducemul ( Rep& r, const size_t sz, constArray a ) const;

  // <- \sum_i a[i] * b[i]
  Rep& dotprod ( Rep& r, const size_t sz, constArray a, constArray b ) const;
  Rep& dotprod ( Rep& r, const int bound, const size_t sz, constArray a, constArray b ) const;

  // ----- a -> r: uint32_t to double
  void i2d ( const size_t sz, double* r, constArray a ) const;

  // ----- a -> r % p: double to uint32_t % p
  void d2i ( const size_t sz, Array r, const double* a ) const;

  // --- IO methods
  std::istream& read ( std::istream& s );
  std::ostream& write( std::ostream& s ) const;
  std::istream& read ( std::istream& s, Rep& a ) const;
  std::ostream& write( std::ostream& s, const Rep a ) const;

protected:
  // -- based for modular inverse, d = a*u + b*v
//   static const int32_t gcdext ( int32_t& u, int32_t& v, const int32_t a, const int32_t b );
  int32_t& gcdext (int32_t& d, int32_t& u, int32_t& v, const int32_t a, const int32_t b ) const;
  uint32_t& invext (uint32_t& u, const uint32_t a, const uint32_t b ) const;

protected:
  // -- data representation of the domain:
    Residu_t _p;
    double _dp;

public: static inline Residu_t getMaxModulus() { return 65536; }
	static inline Residu_t getMinModulus() { return 2; }

};

} // namespace Givaro


#include "givaro/modular-uint32.inl"

#endif // __GIVARO_zpz32unsigned_H
// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
