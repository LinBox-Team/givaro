// ==========================================================================
// Copyright(c)'1994-2014 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.
// Authors: A. Breust (taken from FFLAS-FFPACK)
// ==========================================================================

#ifndef __GIVARO_modular_uint64_INL
#define __GIVARO_modular_uint64_INL

#include "givaro/modular-defines.h"

namespace Givaro
{

	// -------------
	// ----- Modular 

    template<>
	inline Modular<uint64_t, uint64_t>::Residu_t
	Modular<uint64_t, uint64_t>::getMaxModulus() { return 4294967295u; } // 2^32 - 1

    template<>
	inline Modular<uint64_t, int64_t>::Residu_t
	Modular<uint64_t, int64_t>::getMaxModulus() { return 4294967295u; }

	// --------------------
	// ----- Initialisation
	
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::init (Element &x) const
	{
		return x = zero ;
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::init (Element &x, const int32_t &y) const
	{
		x = (Element)(uint32_t(std::abs(y)) % _p);
		if (y < 0) x = _p - x;
		return x;
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::init (Element &x, const int64_t &y) const
	{
		x = (Element)(uint64_t(std::abs(y)) % _p);
		if (y < 0) x = _p - x;
		return x;
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::init(Element &x, const uint32_t &y) const
	{
		return x = (Element)( y >= (uint64_t)_p ? y % _p : y);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::init (Element &x, const uint64_t &y) const
	{
		return x = (Element)( y >= (uint64_t)_p ? y % _p : y);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::init (Element &x, const double &y) const
	{
		double z = fmod(y, (double)_p);
		if (z < 0) z += (double) _p;
		return x = (Element) (z);
	}

	template<typename COMP>
	template <class XXX>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::init(Element &x, const XXX &y) const
	{
		return init(x, double(y));
	}
	
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::assign (Element &x, const Element &y) const
	{
		return x = y;
	}

	// ------------------------
	// ----- Classic arithmetic
	
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::add
		(Element &x, const Element &y, const Element &z) const
	{
		__GIVARO_MODULAR_INTEGER_ADD(x,_p,y,z);
		return x;
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::sub
		(Element &x, const Element &y, const Element &z) const
	{
		return __GIVARO_MODULAR_INTEGER_SUB(x,_p,y,z);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::mul
		(Element &x, const Element &y, const Element &z) const
	{
		return __GIVARO_MODULAR_INTEGER_MUL(x,_p,y,z);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::div
		(Element &x, const Element &y, const Element &z) const
	{
		return mulin(inv(x, z), y);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::neg
		(Element &x, const Element &y) const
	{
		return __GIVARO_MODULAR_INTEGER_NEG(x,_p,y);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::inv
		(Element &x, const Element &y) const
	{
		// The extended Euclidean algorithm
		int64_t x_int, y_int, tx, ty;
		x_int = int64_t(_p);
		y_int = int64_t(y);
		tx = 0;
		ty = 1;

		while (y_int != 0) {
			// always: gcd (modulus,residue) = gcd (x_int,y_int)
			//         sx*modulus + tx*residue = x_int
			//         sy*modulus + ty*residue = y_int
			int64_t q = x_int / y_int; // integer quotient
			int64_t temp = y_int;  y_int  = x_int  - q * y_int;
			x_int  = temp;
			temp = ty; ty = tx - q * ty;
			tx = temp;
		}

		if (tx < 0) tx += _p;

		// now x_int = gcd (modulus,residue)
		return x = Element(tx);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::addin
		(Element &x, const Element &y) const
	{
		__GIVARO_MODULAR_INTEGER_ADDIN(x,_p,y);
		return x;
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::subin
		(Element &x, const Element &y) const
	{
		__GIVARO_MODULAR_INTEGER_SUBIN(x,_p,y);
		return x;
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::mulin
		(Element &x, const Element &y) const
	{
		return __GIVARO_MODULAR_INTEGER_MULIN(x,_p,y);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::divin
		(Element &x, const Element &y) const
	{
		typename Modular<uint64_t, COMP>::Element iy;
		return mulin(x, inv(iy, y));
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::negin
		(Element &x) const
	{
		return __GIVARO_MODULAR_INTEGER_NEGIN(x,_p);
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::invin
		(Element &x) const
	{
		return inv(x, x);
	}

	// -- axpy: r <- a * x + y
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::axpy
		(Element &r, const Element &a, const Element &x, const Element &y) const
	{
		__GIVARO_MODULAR_INTEGER_MULADD(r, _p, a, x, y);
		return r;
	}

	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::axpyin
		(Element &r, const Element &a, const Element &x) const
	{
		__GIVARO_MODULAR_INTEGER_MULADDIN(r, _p, a, x);
		return r;
	}
	
	// -- axmy: r <- a * x - y
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::axmy
		(Element& r, const Element &a, const Element &x, const Element &y) const
	{
		__GIVARO_MODULAR_INTEGER_MULSUB(r, _p, a, x, y);
		return r;
	}
	
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element &Modular<uint64_t, COMP>::axmyin
		(Element& r, const Element &a, const Element &x) const
	{
		maxpyin(r,a,x);
		return negin(r);
	}
	
	// -- maxpy:   r <- y - a * x
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element& Modular<uint64_t, COMP>::maxpy
		(Element& r, const Element& a, const Element& x, const Element& y) const
	{
		r = y;
		__GIVARO_MODULAR_INTEGER_SUBMULIN(r, _p, a, x);
		return r;
	}
		
	template<typename COMP>
    inline typename Modular<uint64_t, COMP>::Element& Modular<uint64_t, COMP>::maxpyin
		(Element& r, const Element& a, const Element& x) const
	{
		__GIVARO_MODULAR_INTEGER_SUBMULIN(r, _p, a, x);
		return r;
	}
	
	// ----------------
	// ----- IO methods

	template<>
    inline std::ostream &Modular<uint64_t, int64_t>::write (std::ostream &os) const
	{
		return os << "Modular<uint64_t, uint64_t> mod " << _p;
	}

	template<>
    inline std::ostream &Modular<uint64_t, uint64_t>::write (std::ostream &os) const
	{
		return os << "Modular<uint64_t, uint64_t> mod " << _p;
	}

	template<typename COMP>
    inline std::istream &Modular<uint64_t, COMP>::read (std::istream &is)
	{
		is >> _p;
		return is;
	}

	template<typename COMP>
    inline std::ostream &Modular<uint64_t, COMP>::write (std::ostream &os, const Element &x) const
	{
		return os << x;
	}

	template<typename COMP>
    inline std::istream &Modular<uint64_t, COMP>::read (std::istream &is, Element &x) const
	{
		int64_t tmp;
		is >> tmp;
		init(x,tmp);
		return is;
	}

} // namespace Givaro

#endif // __GIVARO_modular_uint64_INL

// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
