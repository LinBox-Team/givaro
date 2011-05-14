// ==========================================================================
// $Source: /var/lib/cvs/Givaro/src/library/poly1/givpoly1cstor.inl,v $
// Copyright(c)'1994-2009 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.
// Authors: T. Gautier
// $Id: givpoly1cstor.inl,v 1.15 2011-02-02 16:23:56 bboyer Exp $
// ==========================================================================
#ifndef __GIVARO_poly1_cstor_INL
#define __GIVARO_poly1_cstor_INL

namespace Givaro {
	template<class Domain>
	inline Poly1Dom<Domain,Dense>::Poly1Dom(const Domain& d, const Indeter& X )
	: _domain(d), _x(X) ,zero(1,d.zero), one(1,d.one)
	{}

	template<class Domain>
	inline Poly1Dom<Domain,Dense>::Poly1Dom(const Self_t& P)
	: _domain(P._domain), _x(P._x) ,zero(P.zero), one(P.one)
	{}

	template<class Domain>
	inline Poly1Dom<Domain,Dense>::~Poly1Dom()
	{
	}


	template<class Domain>
	inline typename Poly1Dom<Domain,Dense>::Rep& Poly1Dom<Domain,Dense>::init( Rep& P) const
	{ P.reallocate(0); return P; }

	/*
	   template<class Domain>
	   inline typename Poly1Dom<Domain,Dense>::Rep& Poly1Dom<Domain,Dense>::init( Rep& P, const Rep& Q ) const
	   {
	   Degree degQ;
	   degree(degQ,Q);
	   if (degQ <0) {
	   P.reallocate(0);
	   return P;
	   }
	   P.reallocate(++degQ);
	   for (int i=0; degQ>i; ++i)
	   _domain.init(P[i], Q[i]);
	   return P;
	   }
	   */

	template<class Domain>
	inline typename Poly1Dom<Domain,Dense>::Rep& Poly1Dom<Domain,Dense>::assign( Rep& P, const Rep& Q ) const
	{
		Degree degQ;
		degree(degQ,Q);
		if (degQ <0) {
			P.reallocate(0);
			return P;
		}
		P.reallocate(++degQ);
		for (int i=0; degQ>i; ++i)
			_domain.assign(P[i], Q[i]);
		return P;
	}


	template<class Domain> template<class XXX>
	inline typename Poly1Dom<Domain,Dense>::Rep& Poly1Dom<Domain,Dense>::init( Rep& P, const XXX& val ) const
	{
		P.reallocate(1);
		_domain.init(P[0], val);
		return P;
	}


	template<class Domain>
	inline typename Poly1Dom<Domain,Dense>::Type_t& Poly1Dom<Domain,Dense>::convert(typename Poly1Dom<Domain,Dense>::Type_t & val, const typename Poly1Dom<Domain,Dense>::Rep& P ) const
	{
		if (P.size())
			return _domain.assign(val, P[0]);
		else
			return _domain.init(val, 0UL);
	}

	template<class Domain> template<class XXX>
	inline XXX& Poly1Dom<Domain,Dense>::convert( XXX& val, const typename Poly1Dom<Domain,Dense>::Rep& P ) const
	{
		if (P.size())
			return _domain.convert(val, P[0]);
		else
			return _domain.convert(val, 0UL);
	}

	template<class Domain> template<class UU, template<class XX> class Vect>
	inline Vect<UU>& Poly1Dom<Domain,Dense>::convert( Vect<UU>& val, const typename Poly1Dom<Domain,Dense>::Rep& P ) const
	{
		val.resize( P.size() );
		typename Vect<UU>::iterator vit = val.begin();
		typename Rep::const_iterator        pit = P.begin();
		for ( ; pit != P.end(); ++pit, ++vit)
			_domain.convert(*vit, *pit);
		return val;
	}



	template<class Domain>
	inline typename Poly1Dom<Domain,Dense>::Rep& Poly1Dom<Domain,Dense>::init( Rep& P, const Degree deg ) const
	{
		P.reallocate(value(deg+1));

		size_t sz = P.size();
		for (unsigned int i=0; i<sz-1; ++i)
			_domain.assign(P[i], _domain.zero);
		_domain.assign(P[sz-1], _domain.one);
		return P;
	}

	template<class Domain> template<class XXX>
	inline typename Poly1Dom<Domain,Dense>::Rep& Poly1Dom<Domain,Dense>::init
	( Rep& P, const Degree d, const XXX& val ) const
	{
		long deg = value(d);
		P.reallocate(deg+1);
		for (int i=0; i<deg; ++i)
			_domain.assign(P[i], _domain.zero);
		_domain.init(P[deg], val);

		if (_domain.isZero(P[deg])) {
			P.reallocate(0);
		}
		return P;
	}


	template<class Domain>
	inline typename Poly1Dom<Domain,Dense>::Rep& Poly1Dom<Domain,Dense>::assign
	( Rep& P, const Degree d, const Type_t& lcoeff ) const
	{
		long deg = value(d);
		if (_domain.isZero(lcoeff)) {
			P.reallocate(0);
		} else {
			P.reallocate(deg+1);
			for (int i=0; i<deg; ++i)
				_domain.assign(P[i], _domain.zero);
			_domain.assign(P[deg], lcoeff);
		}
		return P;
	}

} // Givaro
#endif // __GIVARO_poly1_cstor_INL
/* -*- mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
