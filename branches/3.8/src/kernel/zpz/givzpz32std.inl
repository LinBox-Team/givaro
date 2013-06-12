// ==========================================================================
// $Source: /var/lib/cvs/Givaro/src/kernel/zpz/givzpz32std.inl,v $
// Copyright(c)'1994-2009 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.
// Authors: T. Gautier
// $Id: givzpz32std.inl,v 1.20 2011-02-02 17:16:43 bboyer Exp $
// ==========================================================================

#ifndef __GIVARO_zpz32std_INL
#define __GIVARO_zpz32std_INL


// Description:

// ---------
// -- normalized operations
// ---------
// r = a*b
#define __GIVARO_ZPZ32_N_MUL(r,p,a,b) ( r = (Rep) ( (uint32_t)(a*b) % (uint32_t)p ) )
// r *= a
#define __GIVARO_ZPZ32_N_MULIN(r,p,a) (  r = (Rep) ( (uint32_t)(r*a) % (uint32_t)p  ) )

// r = a - b
//#define __GIVARO_ZPZ32_N_SUB(r,p,a,b) ( r = (a>b)? a-b: (p-b)+a )
#define __GIVARO_ZPZ32_N_SUB(r,p,a,b) ( r = (Rep) ( (r=a-b) < 0 ? r+p : r ) )
// r -= a
#define __GIVARO_ZPZ32_N_SUBIN(r,p,a) { r -= a; r= (r < 0 ? r+p : r); }

// r = a+b
#define __GIVARO_ZPZ32_N_ADD(r,p,a,b) { r = (a+b); r= (r < p ? r : r-p); }
// r += a
#define __GIVARO_ZPZ32_N_ADDIN(r,p,a) { r += a;  r= (r < p ? r : r-p); }

// r <- a*b+c % p
#define __GIVARO_ZPZ32_N_MULADD(r,p,a,b,c) ( r = (Rep) ( (uint32_t)(a*b+c) % (uint32_t)p ) )

#define __GIVARO_ZPZ32_N_MULADDIN(r,p,a,b) ( r = (Rep) ( (uint32_t)(a*b+r) % (uint32_t)p ) )

#define __GIVARO_ZPZ32_N_NEG(r,p,a) ( r = (a == 0 ? 0 : p-a) )
#define __GIVARO_ZPZ32_N_NEGIN(r,p) ( r = (r == 0 ? 0 : p-r) )

// a*b-c
#define __GIVARO_ZPZ32_N_MULSUB(r,p,a,b,c) ( r = (Rep) ( (uint32_t)(a*b+p-c) % (uint32_t)p ) )

// r-a*b
#define __GIVARO_ZPZ32_N_SUBMULIN(r,p,a,b) { \
	__GIVARO_ZPZ32_N_MULSUB(r,p,a,b,r); __GIVARO_ZPZ32_N_NEGIN(r,p); }

namespace Givaro {

	inline ZpzDom<Std32>::Residu_t ZpzDom<Std32>::residu( ) const
	{
		return _p;
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::mul (Rep& r, const Rep a, const Rep b) const
	{
		return  __GIVARO_ZPZ32_N_MUL(r,(int32_t)_p,(int32_t)a,(int32_t)b);
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::sub (Rep& r, const Rep a, const Rep b) const
	{
		return __GIVARO_ZPZ32_N_SUB(r,(int32_t)_p,(int32_t)a,(int32_t)b);
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::add (Rep& r, const Rep a, const Rep b) const
	{
		__GIVARO_ZPZ32_N_ADD(r,(int32_t)_p,(int32_t)a,(int32_t)b);
		return r;
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::neg (Rep& r, const Rep a) const
	{
		return __GIVARO_ZPZ32_N_NEG(r,(int32_t)_p,(int32_t)a);
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::inv (Rep& r, const Rep a) const
	{
		int32_t u;
		ZpzDom<Std32>::invext(u, a, (int32_t)_p);
		//   if ((d != 1) && (d != -1)) std::cerr << "GivMathDivZero(Zpz::inv)" << std::endl;
		return r = (u<0)?(ZpzDom<Std32>::Rep)u + (int32_t)_p:(ZpzDom<Std32>::Rep)u;
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::div (Rep& r, const Rep a, const Rep b) const
	{
		return mulin( inv(r,b), a );
	}

	// -- inline array operations between ZpzDom<Std32>::Rep
	inline void ZpzDom<Std32>::mul (const size_t sz, Array r, constArray a, constArray b) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_MUL(tmp, (int32_t)_p,(int32_t)a[i], (int32_t)b[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	inline void ZpzDom<Std32>::mul (const size_t sz, Array r, constArray a, Rep b) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_MUL(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)b);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	inline void ZpzDom<Std32>::div (const size_t sz, Array r, constArray a, constArray b) const
	{
		for ( size_t i=sz ; --i ; ) {
			div( r[i], a[i], b[i]);
		}
	}

	inline void ZpzDom<Std32>::div (const size_t sz, Array r, constArray a, Rep b) const
	{
		ZpzDom<Std32>::Rep ib;
		inv(ib, b);
		mul(sz, r, a, ib);
	}

	inline void ZpzDom<Std32>::add (const size_t sz, Array r, constArray a, constArray b) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_ADD(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)b[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	inline void ZpzDom<Std32>::add (const size_t sz, Array r, constArray a, Rep b) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_ADD(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)b);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	inline void ZpzDom<Std32>::sub (const size_t sz, Array r, constArray a, constArray b) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_SUB(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)b[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	inline void ZpzDom<Std32>::sub (const size_t sz, Array r, constArray a, Rep b) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_SUB(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)b);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	inline void ZpzDom<Std32>::neg (const size_t sz, Array r, constArray a) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_NEG(tmp, (int32_t)_p, (int32_t)a[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}


	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::mulin (Rep& r, const Rep a) const
	{
		return __GIVARO_ZPZ32_N_MULIN(r,(int32_t)_p, (int32_t)a);
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::divin (Rep& r, const Rep a) const
	{
		ZpzDom<Std32>::Rep ia;
		inv(ia, a);
		return mulin(r, ia);
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::addin (Rep& r, const Rep a) const
	{
		int32_t tmp = (int32_t)r;
		__GIVARO_ZPZ32_N_ADDIN(tmp,(int32_t)_p, (int32_t)a);
		return r = (ZpzDom<Std32>::Rep)tmp;
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::subin (Rep& r, const Rep a) const
	{
		int32_t tmp = (int32_t)r;
		__GIVARO_ZPZ32_N_SUBIN(tmp,(int32_t)_p, (int32_t)a);
		return r = (ZpzDom<Std32>::Rep)tmp;
	}


	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::negin (Rep& r) const
	{
		return __GIVARO_ZPZ32_N_NEGIN(r,(int32_t)_p);
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::invin (Rep& r) const
	{
		int32_t u;
		ZpzDom<Std32>::invext(u, r, (int32_t)_p);
		//   if ((d != 1) && (d != -1)) std::cerr << "GivMathDivZero(Zpz::invin)" << std::endl;
		return r = (u<0)?(ZpzDom<Std32>::Rep)u + (int32_t)_p:(ZpzDom<Std32>::Rep)u;
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::axpy (Rep& r,
							const Rep a, const Rep b, const Rep c) const
	{
		return __GIVARO_ZPZ32_N_MULADD(r, (int32_t)_p, (int32_t)a, (int32_t)b, (int32_t)c);
	}

	inline ZpzDom<Std32>::Rep&  ZpzDom<Std32>::axpyin (Rep& r,
							   const Rep a, const Rep b) const
	{
		return __GIVARO_ZPZ32_N_MULADDIN(r, (int32_t)_p, (int32_t)a, (int32_t)b);
	}


	inline void ZpzDom<Std32>::axpy (const size_t sz,
					 Array r, constArray a, constArray x, constArray y) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_MULADD(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)x[i], (int32_t)y[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	inline void ZpzDom<Std32>::axpyin (const size_t sz,
					   Array r, constArray a, constArray x) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp = (int32_t)r[i];
			__GIVARO_ZPZ32_N_MULADDIN(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)x[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	// -- maxpy: r <- c - a * b mod p
	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::maxpy (Rep& r,
							 const Rep a, const Rep b, const Rep c) const
	{
		int32_t tmp;
		__GIVARO_ZPZ32_N_MUL(tmp, (int32_t)_p, (int32_t)a, (int32_t)b);
		__GIVARO_ZPZ32_N_SUB(r, (int32_t)_p, (int32_t)c, tmp);
		return r;
	}

	inline ZpzDom<Std32>::Rep&  ZpzDom<Std32>::axmy (Rep& r,
							 const Rep a, const Rep b, const Rep c) const
	{
		int32_t tmp;
		__GIVARO_ZPZ32_N_MULSUB(tmp, (int32_t)_p, (int32_t)a, (int32_t)b, (int32_t)c);
		return r = (ZpzDom<Std32>::Rep)tmp;
	}

	// r -= a*b
	inline ZpzDom<Std32>::Rep&  ZpzDom<Std32>::maxpyin (Rep& r,
							    const Rep a, const Rep b) const
	{
		__GIVARO_ZPZ32_N_SUBMULIN(r, (int32_t)_p, (int32_t)a, (int32_t)b );
		return r;
		//    int32_t tmp = (int32_t)r;
		//   __GIVARO_ZPZ32_N_SUBMULIN(tmp, (int32_t)_p, (int32_t)a, (int32_t)b );
		//   return r = (ZpzDom<Std32>::Rep)tmp;
	}

	// r = a*b - r
	inline ZpzDom<Std32>::Rep&  ZpzDom<Std32>::axmyin (Rep& r,
							   const Rep a, const Rep b) const
	{
		return __GIVARO_ZPZ32_N_MULSUB(r, (int32_t)_p, (int32_t)a, (int32_t)b, r );
	}

	inline void ZpzDom<Std32>::axmy (const size_t sz,
					 Array r, constArray a, constArray x, constArray y) const
	{
		for ( size_t i=sz; i--; ) {
			int32_t tmp;
			__GIVARO_ZPZ32_N_MULSUB(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)x[i], (int32_t)y[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	// r = r - a*b
	inline void ZpzDom<Std32>::maxpyin (const size_t sz,
					    Array r, constArray a, constArray x) const
	{
		for ( size_t i=sz ; --i ; ) {
			int32_t tmp = (int32_t)r[i];
			__GIVARO_ZPZ32_N_SUBMULIN(tmp, (int32_t)_p, (int32_t)a[i], (int32_t)x[i]);
			r[i] = (ZpzDom<Std32>::Rep)tmp;
		}
	}

	// ------------------------- Miscellaneous functions

	inline int ZpzDom<Std32>::isZero(const Rep a) const
	{
		return a == ZpzDom<Std32>::zero;
	}

	inline int ZpzDom<Std32>::isOne(const Rep a) const
	{
		return a == ZpzDom<Std32>::one;
	}



	inline size_t ZpzDom<Std32>::length(const Rep ) const
	{
		return ZpzDom<Std32>::size_rep;
	}

	// ---------
	// -- misc operations
	// ---------


	inline  ZpzDom<Std32>::Rep&  ZpzDom<Std32>::init ( Rep& r, const double a ) const
	{
		int sign; double ua;
		if (a < 0.0) { sign =-1; ua = -a;}
		else { ua = a; sign =1; }
		if ( ua > Signed_Trait<uint32_t>::max()){
			//     ua -= (double)floor(ua * _invdp)*_dp;
			ua = fmod(ua,_dp);
			r = (Rep) ua;
		} else
			r = (Rep)((ua >=_p) ? (uint32_t) ua % (uint32_t)_p : (uint32_t) ua);
		if (r && (sign ==-1)) r = (int32_t)_p - r;
		return r;
	}

	inline  ZpzDom<Std32>::Rep&  ZpzDom<Std32>::init ( Rep& r, const float a ) const
	{
		return init(r, (double)a);
	}



	inline  ZpzDom<Std32>::Rep&  ZpzDom<Std32>::init ( Rep& r, const unsigned long a ) const
	{
	       	return r = (Rep)( a >= (unsigned long)_p ? a % (unsigned long)_p : a);
	}

	inline  ZpzDom<Std32>::Rep&  ZpzDom<Std32>::init ( Rep& r, const long a ) const
	{
		int sign;
		unsigned long ua;
		if (a <0) {
			sign =-1;
			ua = (unsigned long)-a;
		}
		else {
			ua = (unsigned long) a;
		       	sign =1;
		}
		r = Rep((ua >=_p) ? ua % (uint32_t)_p : ua);
		if (r && (sign ==-1))
			r = (int32_t)_p - r;
		return r;
	}

	inline ZpzDom<Std32>::Rep&  ZpzDom<Std32>::init ( Rep& r, const Integer& Residu ) const
	{
		long tr;
		if (Residu <0) {
			// -a = b [p]
			// a = p-b [p]
			if ( Residu <= (Integer)(-_p) )
			       	tr = long( (-Residu) % _p) ;
			else
				tr = long(-Residu);
			if (tr)
				return r = Rep(_p - (unsigned long)tr);
			else
				return r = zero;
		}
		else {
			if (Residu >= (Integer)_p ) tr =   long(Residu % _p) ;
			else tr = long(Residu);
			return r = Rep(tr);
		}
	}





	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::init( Rep& a, const int i) const
	{
		return init(a,(long)i);
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::init( Rep& a, const unsigned int i) const
	{
		return init(a,(unsigned long)i);
	}


	inline void ZpzDom<Std32>::assign
	( const size_t sz, Array r, constArray a ) const
	{
		for ( size_t i=sz ; --i ; )
			r[i] = a[i];
	}

	inline  ZpzDom<Std32>::Rep&  ZpzDom<Std32>::assign ( Rep& r, const Rep a ) const
	{
		return r=a;
	}

	inline void ZpzDom<Std32>::init
	( const size_t sz, Array r, constArray a ) const
	{
		for ( size_t i=sz ; --i ; )
			r[i] = a[i];
	}

	inline ZpzDom<Std32>::Rep& ZpzDom<Std32>::init ( Rep& r ) const
	{
		return r = zero;
	}

	inline ZpzDom<Std32>::Rep&  ZpzDom<Std32>::dotprod
	( Rep& r, const int bound, const size_t sz, constArray a, constArray b ) const
	{
		unsigned int stride = 1;
		if ((unsigned long)bound < GIVARO_MAXUINT32)
			//    stride = GIVARO_MAXULONG/((unsigned long)bound * (unsigned long)bound);
			//    hopefully stride is not unsigned long !?!
			stride = (unsigned int) (GIVARO_MAXULONG/((unsigned long)bound) / ((unsigned long)bound));
		unsigned long dot = (unsigned long)zero;
		if ((sz <10) && (sz <stride)) {
			for(  size_t i= sz; i--; )
				dot += (unsigned long)a[i] * (unsigned long)b[i];
			if (dot > _p)  return r = (Rep)(dot % (unsigned long)_p);
			else  return r = (Rep)dot;
		}
		size_t i_begin=0;
		stride &= (unsigned int)~0x1;
		if (stride ==0) {
			for(  size_t i= sz; --i; ) {
				dot += (unsigned long) a[i] * (unsigned long)b[i];
				if (dot>_p) dot %= _p;
			}
			return r = (Rep)dot;
		}
		do {
			size_t min_sz = ((sz-i_begin) < stride ? (sz-i_begin) : stride);
			if ((min_sz & 0x1) !=0) {
				min_sz--; i_begin++;
				dot += (unsigned int) a++[min_sz] * (unsigned int)b++[min_sz];
			}
			if (min_sz > 1)
				for(  size_t i= min_sz; i>0; --i, --i, ++a, ++a, ++b, ++b )
				{
					dot += (unsigned int)a[0] * (unsigned int)b[0];
					dot += (unsigned int)a[1] * (unsigned int)b[1];
				}
			if (dot>_p) dot %= _p;
			i_begin += min_sz;
		} while (i_begin <sz);
		return r = (Rep)dot;
	}

	template< class RandIter >
	inline  ZpzDom<Std32>::Rep& ZpzDom<Std32>::random(RandIter& g, Rep& a) const
	{
		return init(a, g());
	}

	template< class RandIter >
	inline  ZpzDom<Std32>::Rep& ZpzDom<Std32>::random(RandIter& g, Rep& a, const Rep& b) const
	{
		return init(a, g());
	}
	template< class RandIter >
	inline  ZpzDom<Std32>::Rep& ZpzDom<Std32>::random(RandIter& g, Rep& a, long b) const
	{
		return init(a, g() %(uint32_t) b);

	}

	template< class RandIter >
	inline  ZpzDom<Std32>::Rep& ZpzDom<Std32>::nonzerorandom(RandIter& g, Rep& a) const
	{
		while (isZero(init(a, g()))) {};
		return a;
	}

	template< class RandIter >
	inline  ZpzDom<Std32>::Rep& ZpzDom<Std32>::nonzerorandom(RandIter& g, Rep& a, const Rep& b) const
	{
		while (isZero(init(a, g()))) {};
		return a;
	}

	template< class RandIter >
	inline  ZpzDom<Std32>::Rep& ZpzDom<Std32>::nonzerorandom(RandIter& g, Rep& a, long b) const
	{
		while (isZero(init(a, g() %(uint32_t) b))) {};
		return a;
	}

	inline ZpzDom<Std32>::Rep&  ZpzDom<Std32>::dotprod
	( Rep& r, const size_t sz, constArray a, constArray b ) const
	{
		return ZpzDom<Std32>::dotprod(r, (int32_t)_p, sz, a, b);
	}


	//  a -> r: int32_t to double
	inline void
	ZpzDom<Std32>::i2d ( const size_t sz, double* r, constArray a ) const
	{
		for (size_t i=0; i<sz; ++i) r[i] = a[i];
	}

	//  a -> r: double to int32_t
	inline void
	ZpzDom<Std32>::d2i ( const size_t sz, Array r, const double* a ) const
	{
		union d_2_l {
			double d;
			int32_t r[2];
		};
		//  static const double offset = 4503599627370496.0; // 2^52
		double offset = 4503599627370496.0; // 2^52
		for (size_t i=0; i<sz; ++i)
		{
			d_2_l tmp;
			// - normalization: put fractional part at the end of the representation
			tmp.d = a[i] + offset;
			r[i] = tmp.r[1];
			if (r[i] <(int32_t)_p) r[i] %= _p;
		}
		//    r[i] = (tmp.r[1] <_p ? tmp.r[1] : tmp.r[1]-_p);
		//    r[i] = (r[i] <_p ? r[i] : r[i]%_p);
		//    r[i] = (tmp.r[1] <_p ? tmp.r[1] : tmp.r[1]%_p);
	}



	// -- Input: (z, <_p>)
	inline std::istream& ZpzDom<Std32>::read (std::istream& s)
	{
		char ch;
		s >> std::ws >> ch;
		if (ch != '(')
			//    GivError::throw_error( GivBadFormat("ZpzDom<Std32>::read: syntax error: no '('"));
			std::cerr << "GivBadFormat(ZpzDom<Std32>::read: syntax error: no '('))" << std::endl;

		s >> std::ws >> ch;
		if (ch != 'z')
			//    GivError::throw_error( GivBadFormat("ZpzDom<Std32>::read: bad domain object"));
			std::cerr << "GivBadFormat(ZpzDom<Std32>::read: bad domain object))" << std::endl;

		s >> std::ws >> ch;
		if (ch != ',')
			//    GivError::throw_error( GivBadFormat("ZpzDom<Std32>::read: syntax error: no ','"));
			std::cerr << "GivBadFormat(ZpzDom<Std32>::read: syntax error: no ',')) " << std::endl;

		s >> std::ws >> _p;

		s >> std::ws >> ch;
		if (ch != ')')
			//    GivError::throw_error( GivBadFormat("ZpzDom<Std32>::read: syntax error: no ')'"));
			std::cerr << "GivBadFormat(ZpzDom<Std32>::read: syntax error: no ')')) " << std::endl;

		return s;
	}

	inline std::ostream& ZpzDom<Std32>::write (std::ostream& s ) const
	{
		return s << "Std32 Givaro Z/pZ modulo " << residu();
	}

	inline std::istream& ZpzDom<Std32>::read (std::istream& s, Rep& a) const
	{
		Integer tmp;
		s >> tmp;
		init(a, tmp);
		return s;
	}

	inline std::ostream& ZpzDom<Std32>::write (std::ostream& s, const Rep a) const
	{
		return s << a;
	}

} // namespace Givaro

#endif // __GIVARO_zpz32std_INL
// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
