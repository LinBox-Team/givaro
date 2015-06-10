// ==========================================================================
// Copyright(c)'1994-2015 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.
// Authors: BB <brice.boyer@lip6.fr>
//          A. Breust (adapted)
// ==========================================================================

/*! @file field/modular-uint64.h
 * @ingroup field
 * @brief  representation of <code>Z/mZ</code> over \c uint64_t .
 */

#ifndef __GIVARO_modular_uint16_H
#define __GIVARO_modular_uint16_H

#include "givaro/givcaster.h"
#include "givaro/givranditer.h"
#include "givaro/ring-interface.h"
#include "givaro/modular-general.h"

namespace Givaro {

    /** \brief Specialization of Modular to uint64_t element type with efficient dot product.
     *
     * Efficient element operations for dot product, mul, axpy, by using floating point
     * inverse of modulus (borrowed from NTL) and some use of non-normalized intermediate values.
     *
     * For some uses this is the most efficient field for primes in the range from half word
     * to 2^30.
     *
     * Requires: Modulus < 2^30.
     * Intended use: 2^15 < prime modulus < 2^30.
     * \ingroup field
     */

    template <typename COMP>
    class Modular<uint16_t, COMP> : public RingInterface<uint16_t>
    {
    public:
        // ----- Exported Types and constantes
        using Self_t = Modular<uint16_t, COMP>;
        using Compute_t = typename std::make_unsigned<COMP>::type;
        using Residu_t = uint16_t;
        enum { size_rep = sizeof(Residu_t) };

        // ----- Constantes
        const Element zero;
        const Element one;
        const Element mOne;

        // ----- Constructors
        Modular()
            : zero(Element(0)), one(Element(1)), mOne(Element(0)), _p(Element(0)) {}

        Modular(Residu_t p)
            : zero(Element(0)), one(Element(1)), mOne(Element(p-1)), _p(p)
        {
            assert(_p >= getMinModulus());
            assert(_p <= getMaxModulus());
        }

        Modular(const Self_t& F)
            : zero(F.zero), one(F.one), mOne(F.mOne), _p(F._p) {}

        // ----- Accessors
        inline Element minElement() const override { return zero; }
        inline Element maxElement() const override { return mOne; }

        // ----- Access to the modulus
        inline Residu_t residu() const { return _p; }
        inline Residu_t size() const { return _p; }
        inline Residu_t characteristic() const { return _p; }
        inline Residu_t cardinality() const { return _p; }
        template<class T> inline T& characteristic(T& p) const { return p = _p; }
        template<class T> inline T& cardinality(T& p) const { return p = _p; }
        static inline Residu_t getMaxModulus();
        static inline Residu_t getMinModulus() { return 2; }

        // ----- Checkers
        inline bool isZero(const Element& a) const override { return a == zero; }
        inline bool isOne (const Element& a) const override { return a == one; }
        inline bool isMOne(const Element& a) const override { return a == mOne; }
        inline bool areEqual(const Element& a, const Element& b) const override { return a == b; }
        inline size_t length(const Element a) const { return size_rep; }

        // ----- Ring-wise operators
        bool operator==(const Self_t& F) const { return _p == F._p; }
        bool operator!=(const Self_t& F) const { return _p != F._p; }
        Self_t& operator=(const Self_t& F)
        {
            F.assign(const_cast<Element&>(one),  F.one);
            F.assign(const_cast<Element&>(zero), F.zero);
            F.assign(const_cast<Element&>(mOne), F.mOne);
            _p = F._p;
            return *this;
        }

        // ----- Initialisation
        Element& init (Element& x) const
        { return x = 0; }
        Element& init (Element& x, const float a) const;
        Element& init (Element& x, const double a) const;
        Element& init (Element& x, const int32_t a) const;
        Element& init (Element& x, const uint32_t a) const;
        Element& init (Element& x, const int64_t a) const;
        Element& init (Element& x, const uint64_t a) const;
        Element& init (Element& x, const Integer& a) const;
        template<typename T> Element& init(Element& r, const T& a) const
        {
            reduce(r, Caster<Element>((a < 0)? -a : a));
	    if (a < 0) negin(r);
            return r;
        }

        Element& assign (Element& x, const Element& y) const
        { return x = y; }
    
        // ----- Convert and reduce
        template<typename T> T& convert(T& r, const Element& a) const
        { return r = Caster<T>(a); }

        Element& reduce (Element& x, const Element& y) const
        { x = y % _p; return x; }
        Element& reduce (Element& x) const
        { x %= _p; return x; }

        // ----- Classic arithmetic
        Element& mul(Element& r, const Element& a, const Element& b) const override;
        Element& div(Element& r, const Element& a, const Element& b) const override;
        Element& add(Element& r, const Element& a, const Element& b) const override;
        Element& sub(Element& r, const Element& a, const Element& b) const override;
        Element& neg(Element& r, const Element& a) const override;
        Element& inv(Element& r, const Element& a) const override;

        Element& mulin(Element& r, const Element& a) const override;
        Element& divin(Element& r, const Element& a) const override;
        Element& addin(Element& r, const Element& a) const override;
        Element& subin(Element& r, const Element& a) const override;
        Element& negin(Element& r) const override;
        Element& invin(Element& r) const override;

        // -- axpy:   r <- a * x + y
        // -- axpyin: r <- a * x + r
        Element& axpy  (Element& r, const Element& a, const Element& x, const Element& y) const override;
        Element& axpyin(Element& r, const Element& a, const Element& x) const override;

        // -- axmy:   r <- a * x - y
        // -- axmyin: r <- a * x - r
        Element& axmy  (Element& r, const Element& a, const Element& x, const Element& y) const override;
        Element& axmyin(Element& r, const Element& a, const Element& x) const override;

        // -- maxpy:   r <- y - a * x
        // -- maxpyin: r <- r - a * x
        Element& maxpy  (Element& r, const Element& a, const Element& x, const Element& y) const override;
        Element& maxpyin(Element& r, const Element& a, const Element& x) const override;

        // ----- Random generators
        typedef ModularRandIter<Self_t> RandIter;
        typedef GeneralRingNonZeroRandIter<Self_t> NonZeroRandIter;
        template< class Random > Element& random(const Random& g, Element& r) const
        { return init(r, g()); }
        template< class Random > Element& nonzerorandom(const Random& g, Element& a) const
        { while (isZero(init(a, g())));
            return a; }

        // --- IO methods
        std::ostream& write(std::ostream& s) const;
        std::istream& read (std::istream& s, Element& a) const;
        std::ostream& write(std::ostream& s, const Element& a) const;

    protected:
        // -- data representation of the domain:
        Residu_t _p;
    };

}

#include "givaro/modular-uint16.inl"

#endif //__GIVARO_modular_uint16_H

