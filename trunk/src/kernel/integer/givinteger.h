#ifndef _INTEGER_H_
#define _INTEGER_H_
// =============================================================
// Copyright(c)'94-02 by Givaro Team
// see the copyright file.
// Authors: T. Gautier, J.-G. Dumas
// =============================================================
// Description: 
// Integer Domain class definition 
#include "givaro/givbasictype.h"
#include "givaro/givinit.h"
#include "givaro/giverror.h"
#include "givaro-config.h"
#include "gmp++/gmp++_int.h"
#include <string>


//------------------------------------ Class IntegerDom
class IntegerDom : public Integer {
public:
    typedef Integer Rep;
    typedef Rep element;
    typedef Rep Element;


  IntegerDom() : one(1UL), zero(0UL) {}
  IntegerDom(const IntegerDom& D) : one(1UL), zero(0UL) {}

  int operator==( const IntegerDom& BC) const { return 1;}
  int operator!=( const IntegerDom& BC) const { return 0;}

  // -- Constants: 
  const Integer one;
  const Integer zero;

  // -- assignement 
  Rep& init  ( Rep& a ) const {return a;}
  Rep& init  ( Rep& a, const Rep& b) const { return a = b ; }
  Rep& read( Rep& a, const long i) const { return a = Integer(i) ; }
  Rep& read( Rep& a, const unsigned long i) const { return a = Integer(i) ; }
  Rep& read( Rep& a, const int i) const { return a = Integer(i) ; }
  Rep& read( Rep& a, const unsigned int i) const { return a = Integer(i) ; }

  Rep& convert( Rep& a, const Rep& b) const { return a = b ; }
  Rep& assign( Rep& a, const Rep& b) const { return a = b ; }

  // -- access
  const Rep& access(const Rep& a) const { return a; }
  long   Integer2long  ( const Rep& a) const { return ::Integer2long(a); }
  double Integer2double( const Rep& a) const { return ::Integer2double(a); }
  std::string& Integer2string(std::string& s, const Integer& n, int base = 10) const { return ::Integer2string(s,n,base); };

  // -- arithmetic operators
  Rep& mul( Rep& r, const Rep& a, const Rep& b ) const { return Integer::mul(r,a,b); }
  Rep& div( Rep& r, const Rep& a, const Rep& b ) const { return Integer::div(r,a,b); }
  Rep& mod( Rep& r, const Rep& a, const Rep& b ) const { return Integer::mod(r,a,b); }
  Rep& add( Rep& r, const Rep& a, const Rep& b ) const { return Integer::add(r,a,b); }
  Rep& sub( Rep& r, const Rep& a, const Rep& b ) const { return Integer::sub(r,a,b); }
  Rep& divmod( Rep& q, Rep& r, const Rep& a, const Rep& b ) const 
  { return Integer::divmod(q,r,a,b); }
  Rep& divexact( Rep& q, const Rep& a, const Rep& b ) const { return Integer::divexact(q,a,b); }

  Rep& mulin( Rep& r, const Rep& a) const { return r *= a; }
  Rep& divin( Rep& r, const Rep& a) const { return r /= a; }
  Rep& modin( Rep& r, const Rep& a) const { return r %= a; }
  Rep& addin( Rep& r, const Rep& a) const { return r += a; }
  Rep& subin( Rep& r, const Rep& a) const { return r -= a; }

  Rep& axpy( Rep& r, const Rep& a, const Rep& b, const Rep& c ) const 
  { return Integer::axpy(r,a,b,c); }
  Rep& axmy( Rep& r, const Rep& a, const Rep& b, const Rep& c ) const 
  { return Integer::axmy(r,a,b,c); }
  Rep& axpyin( Rep& r, const Rep& a, const Rep& b ) const 
  { return r += a * b; }
  Rep& axmyin( Rep& r, const Rep& a, const Rep& b ) const 
  { return r -= a * b; }

  // -- unary methods
  Rep& neg( Rep& r, const Rep& a ) const { return Integer::neg(r,a); }
  Rep& negin( Rep& r ) const { return Integer::negin(r); }

  // -- extended gcd  q = gcd(a,b) = u*a+v*b;
  Rep& gcd( Rep& g, Rep& u, Rep& v, const Rep& a, const Rep& b ) const 
  { return ::gcd(g, a, b, u, v); }
  Rep& gcd( Rep& g, const Rep& a, const Rep& b ) const 
  { return ::gcd(g, a, b); }
  Rep& lcm( Rep& l, const Rep& a, const Rep& b ) const 
  { return ::lcm(l, a, b); }
  Rep& lcmin( Rep& l, const Rep& a) const 
  { Rep tmp(l); return lcm(l, tmp, a); }

  // - return n^l 
  Rep& pow(Rep& r, const Rep& n, const long l) const { return r = ::pow(n, l); }
  Rep& pow(Rep& r, const Rep& n, const unsigned long l) const { return r = ::pow(n, l); }
  Rep& pow(Rep& r, const Rep& n, const int l) const { return r = ::pow(n, l); }
  Rep& pow(Rep& r, const Rep& n, const unsigned int l) const { return r = ::pow(n, l); }

  // - return square root of n  
  Rep& sqrt(Rep& s, const Rep& n) const { return s = ::sqrt(n); }
  Rep& sqrt(Rep& s, Rep& r, const Rep& n) const { return s = ::sqrt(n, r); }
  // - base p logarithm of a
  long logp(const Rep& a, const Rep& p) const { return ::logp(a,p); }

  // - return n^e % m
  Rep& powmod(Rep& r, const Rep& n, const long e, const Rep& m) const
  { return r = ::powmod(n, e, m);}
  Rep& powmod(Rep& r, const Rep& n, const Rep& e, const Rep& m) const
  { return r = ::powmod(n, e, m);}

  // - Misc
  unsigned long length (const Rep& a) const { return ::length(a); }
  int sign   (const Rep& a) const { return ::sign(a); }
  bool iszero (const Rep& a) const { return ::iszero(a); }
  bool isZero (const Rep& a) const { return ::iszero(a); }
  bool isone  (const Rep& a) const { return ::isone(a); }
  bool areEqual (const Rep& a, const Rep& b) const { return compare(a,b) ==0;}
  bool areNEqual(const Rep& a, const Rep& b) const { return compare(a,b) !=0;}
    bool isgeq(const Rep& a, const Rep& b) const { return compare(a,b) >= 0;}
    bool isleq(const Rep& a, const Rep& b) const { return compare(a,b) <= 0;}
    bool isgeq(const long b,const Rep& a ) const { return isgeq(Rep(b),a);}
    bool isleq(const long b,const Rep& a ) const { return isleq(Rep(b),a);}
    bool isgeq(const Rep& a, const long b) const { return isgeq(a,Rep(b));}
    bool isleq(const Rep& a, const long b) const { return isleq(a,Rep(b));}
    bool isgt(const Rep& a, const Rep& b) const { return compare(a,b) > 0;}
    bool islt(const Rep& a, const Rep& b) const { return compare(a,b) < 0;}
    bool isgt(const long b,const Rep& a ) const { return isgt(Rep(b),a);}
    bool islt(const long b,const Rep& a ) const { return islt(Rep(b),a);}
    bool isgt(const Rep& a, const long b) const { return isgt(a,Rep(b));}
    bool islt(const Rep& a, const long b) const { return islt(a,Rep(b));}


#ifdef __GMP_PLUSPLUS__
    void seeding(unsigned long s = 0) const { Integer::seeding(s) ; }
#endif
    template< class RandIter > Rep& random(RandIter& g, Rep& r, long s = 1) const { return Integer::random(r,s); }
    template< class RandIter > Rep& random(RandIter& g, Rep& r, const Rep& b) const { return Integer::random(r,b); }
    template< class RandIter > Rep& nonzerorandom(RandIter& g, Rep& r, long s = 1) const { return Integer::nonzerorandom(r,s); }
    template< class RandIter > Rep& nonzerorandom (RandIter& g,Rep& r, const Rep& b) const { return Integer::nonzerorandom(r,b); }

  // -- IO
  std::istream& read ( std::istream& i ) 
  { char ch;
    i >> std::ws >> ch; 
// JGD 22.03.03
//    if (ch != 'I') 
//      GivError::throw_error(GivBadFormat("IntegerDom::read: bad signature domain"));
    return i;
  }
  std::ostream& write( std::ostream& o ) const { return o << 'I'; }
  std::istream& read ( std::istream& i, Rep& n) const { return i >> n; }
  std::ostream& write( std::ostream& o, const Rep& n) const { return o << n; }
};



#endif //__INT_H_

