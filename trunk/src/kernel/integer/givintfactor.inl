// =================================================================== //
// Givaro : Prime numbers
//              Factors,
// Needs list structures : stl ones for instance
// Time-stamp: <10 Dec 04 13:27:18 Jean-Guillaume.Dumas@imag.fr> 
// =================================================================== //
#ifndef _GIVARO_FACTORISATION_INL_
#define _GIVARO_FACTORISATION_INL_


#include "givtimer.h"
#include "givinteger.h"
#include "givintprime.h"
#include "givintfactor.h"

#include <iostream>
#include <vector>

template<class RandIter>
std::ostream& IntFactorDom<RandIter>::write(std::ostream& o, const Rep& n) const
{
    std::vector<Rep> Lf;
    return write(o, Lf, n);
}


template<class RandIter>
template<class Array> 
std::ostream& IntFactorDom<RandIter>::write(std::ostream& o, Array& Lf, const Rep& n) const 
{
    
//         // n = * Lf[i] ^ Lo[i]
//         // But Lf[i] might not be prime (cf. factor probability)
    Rep nn,g,r,u;
    nn = n;
    long c;
    bool flag = 0;
    Integer tmp;

    if (islt(nn,zero)) {
        nn = -n;
        o << "-";
    }
    
    if (isleq(nn,1)) { Lf.push_back(nn); return IntegerDom::write(o,nn); }
    

    while( isgt(nn,1) ) {
        primefactor(g,nn);
	if (flag)
		o << " * ";
	else
		flag = 1;
        
	Lf.push_back(g);
        IntegerDom::write(o,g);
        c=0;r=0;

	Rep::divexact(u, nn,g);
        for(;isZero(r); ++c) {
		nn.copy(u); 
		Rep::divmod( u, r, nn,g );
        }
	if (c>1) o << "^" << c;
    }
    return o;
}    


// =================================================================== //
// Set or Container of divisors, factors.
// =================================================================== //
#ifndef __ECC
template<class RandIter>
template< template<class> class Container> bool
IntFactorDom<RandIter>::set(Container<Rep>& Lf, Container<unsigned long>& Lo, const Rep& n, unsigned long loops)  const 
#else
template<class RandIter>
template<class Container1, class Container2> bool
IntFactorDom<RandIter>::set(Container1& Lf, Container2& Lo, const Rep& n, unsigned long loops)  const 
#endif
{
        // n = * Lf[i] ^ Lo[i]
    bool factocomplete = true;
    Rep nn,g,r,u;
    if (n<0) Rep::neg(nn,n); else nn=n;
    unsigned long c;
    while(nn > 1) {        
        primefactor(g,nn,loops);
        if (g == 1) {
            factocomplete = false;
            g = nn;
        }
        Lf.push_back(g);
        c=0;r=zero;
        Rep::divexact(u, nn,g);
        while(r == 0) {
                //	nn = nn / g;
                //	r = nn % g;
            nn.copy(u); 
            Rep::divmod( u, r, nn,g );
            c++;
        }
        Lo.push_back( c );
    }
    return factocomplete;
}


#ifndef __ECC
template<class RandIter>
template< template<class> class Container> 
void IntFactorDom<RandIter>::Erathostene(Container<Rep>& Lf, const Rep& p)  const 
#else
template<class RandIter>
template<class Container> 
void IntFactorDom<RandIter>::Erathostene(Container& Lf, const Rep& p)  const 
#endif
{
        // Deterministic algorithm
        // Valid for p < BOUNDARY_factor
        // Lf is the Container of factors
    long n; access(n,p);
    if (! (n & 0x1)) {
        Lf.push_back(Rep(2));
        do
            n >>= 1;
        while (!(n & 0x1));
    }
    short * IP = new short[n+1];
    int i;
    for(int ii=n+1;ii--;)
	IP[ii] = 0L;
    i=3;
    int j, ii, cofact;
    Rep sq;
    while (i<=sqrt(sq,Rep(n))) {
        ii= i << 1;
        j = i+ii;
        while (j<=n) {
            IP[j] = 1L;
            j+=ii;
        }
        if ((j-ii) == n) {
            Lf.push_back(Rep(i));
            do
                n /= i;
            while (!(n%i));
        }
        j = i+1;
        while (IP[++j]) { j++;}
        i = j;
    }
    if (!(IP[n]) && (n>1)) Lf.push_back(Rep(n));
    delete [] IP;
}
 

#ifndef __ECC
template<class RandIter>
template< template<class> class Container> 
void IntFactorDom<RandIter>::set( Container<Rep>& Lf,  const Rep& n)  const 
#else
template<class RandIter>
template<class Container> 
void IntFactorDom<RandIter>::set( Container& Lf,  const Rep& n)  const 
#endif
{
        // big_factor is executed until
        // a (sometimes probably) prime factor is found.
        // Lf is a Container of divisors
        // Lf is a Container of factors with probability -- TO EXPLICIT
        // something like : 1 - (big_factor to be composite)*(big_isprime)
    Rep nn,g,r,u;
    nn = n;
    while(nn > 1) {
        primefactor(g,nn);
        r=0;
	Rep::divexact(u, nn,g);
        while(r == 0) {
		nn.copy(u); 
		Rep::divmod( u, r, nn,g ); 
        }
	// gcc 3.3.3 (Debian 20040422) : internal compiler error !!!
        Lf.push_back(g);
	//Lf.resize(Lf.size()+1);
	//Lf.back() = g;
    }
}


#ifndef __ECC
template<class RandIter>
template< template<class> class Container, template<class> class Cont2> Container< typename IntFactorDom<RandIter>::Rep >&  IntFactorDom<RandIter>::divisors( Container<Rep>& L, const Cont2<Rep>& Lf, const Cont2<unsigned long>& Le)  const 
{
    typename Cont2<Rep>::const_iterator li = Lf.begin();
    typename Cont2<unsigned long>::const_iterator lj = Le.begin();
    Container<Rep> Res(1,Rep(1));
    Container<Rep> Res2;
    typename Container<Rep>::iterator lr;
#else
template<class RandIter>
template<class Container, class Cont2, class Cont3> Container&  IntFactorDom<RandIter>::divisors( Container& L, const Cont2& Lf, const Cont3& Le)  const 
{
    typename Cont2::const_iterator li = Lf.begin();
    typename Cont3::const_iterator lj = Le.begin();
    Container Res(1,Rep(1));
    Container Res2;
    typename Container::iterator lr;
#endif
    Rep Itmp;
    for(;li!=Lf.end();++li,++lj) {
        for(lr = Res.begin();lr!=Res.end();++lr) {
		Itmp = *lr;
      		for(unsigned long i=*lj;i--;) {
			Itmp = Itmp * *li;
            		Res2.push_back( Itmp );
		}
	}
        Res.splice(Res.end(),Res2);
    }
    return L = Res;
}


#ifndef __ECC
template<class RandIter>
template< template<class> class Container> Container<typename IntFactorDom<RandIter>::Rep>& IntFactorDom<RandIter>::divisors( Container<Rep>& L, const Rep& n)  const 
{
    Container<Rep> Lf;
    Container<unsigned long> Le;
#else
#include <vector>
template<class RandIter>
template<class Container> Container& IntFactorDom<RandIter>::divisors( Container& L, const Rep& n)  const 
{
    Container Lf;
    std::vector<unsigned long> Le;
#endif
    IntFactorDom<RandIter>::set(Lf,Le,n);
    return divisors(L, Lf, Le);
}

template<class RandIter>
typename IntFactorDom<RandIter>::Rep& IntFactorDom<RandIter>::Pollard(RandIter& gen, Rep& g, const Rep& n, const unsigned long threshold) const 
{
  // average number of iterations < 13/8*sqrt( Pi*n/2)
  // Sometimes the factor isn't prime -- TO EXPLICIT
    if (islt(n,3)) return g=n;
    if ( isprime(n, _GIVARO_ISPRIMETESTS_) ) return g=n;
    g=1;
    Rep m(zero), x, y, p(one), t;
    random(gen, y, n);

    if (threshold) {
        unsigned long c = 0;
        while( isOne(g) && (++c < threshold)) {
            if(  areEqual(p, addin(m,one)) ) {
                x=y;
                mulin(p,2);
            }
            Pollard_fctin(y,n);
            gcd(g,sub(t,y,x),n);
        }
        if ((g == n)&&(c<threshold)) // Failure with the initial value
            Pollard(gen, g, n, threshold-c);
    } else {
        while(isOne(g)) {
            if(  areEqual(p, addin(m,one)) ) {
                x=y;
                mulin(p,2);
            }
            Pollard_fctin(y,n);
            gcd(g,sub(t,y,x),n);
        }
        if (g == n) // Failure with the initial value
            Pollard(gen, g, n, 0);
    }
    return g;
}


// =================================================================== //
// Elliptic curves routines
// =================================================================== //

inline void Add_Curve( const Integer& n, const Integer A, const Integer& ax, const Integer& az, Integer& cx, Integer& cz) {
    Integer t1,t2;
//     t1 = ((ax+az)*(ax+az))%n; 
//     t2 = ((ax-az)*(ax-az))%n;
    t1 = ax+az; 
    t1 *= t1;
    t1 %= n;
    t2 = ax-az;
    t2 *= t2;
    t2 %= n;
    cx = t1*t2;
    cx %= n; 
    t1 -= t2;
    cz = A;
    cz *= t1;
    cz += t2;
    cz %= n;
//    cz = ((A*t1+t2) % n);
    cz *= t1;
    cz %= n;
}


inline void one_Mul_Curve( const Integer& n, const Integer A, const Integer& mm, const Integer& nn, const Integer& px, const Integer& pz, Integer& ax, Integer& az) {
    Integer bx, bz, cx, cz, tmpx, tmpz, d, e, t2;
    cx = px;
    cz = pz;
    e = mm;
    d = nn;
    d -= mm;
    if (e<d) {
        Add_Curve(n,A,px,pz,bx,bz);ax = px;az = pz;d -= e;
    } else {
        Add_Curve(n,A,px,pz,ax,az);bx = px;bz = pz;e -= d;
    }
    while (! isZero(e)) {
        if (e<d) {
            tmpx = bx; tmpz = bz; 
            bz = ax;
	    bz -= az;  
            t2 = tmpx;
	    t2 += tmpz;
            bz *= t2;
            bz %= n;
            
            t2 = ax;
	    t2 += az;
            bx -= tmpz;
            t2 *= bx;
            t2 %= n;
            
            bx = bz;
	    bx += t2;
	    bx *= bx;
	    bx %= n;
            bx *= cz;
            bx %= n;
            
	    bz -= t2;
	    bz *= bz;
	    bz %= n;
            bz *= cx;
            bz %= n;

            d -= e;
        } else {
            tmpx = ax; tmpz = az; 
            az = tmpx;
	    az -= tmpz;
            t2 = bx;
	    t2 += bz;
            az *= t2;
            az %= n;
            
            t2 = bx;
	    t2 -= bz;
            ax += tmpz;
            t2 *= ax;
            t2 %= n;

            ax = az;
	    ax += t2;
	    ax *= ax;
	    ax %= n;
            ax *= cz;
            ax %= n;
            
	    az -= t2;
	    az *= az;
	    az %= n;
            az *= cx;
            az %= n;
            
            e -= d;
        }
        cx = tmpx;
        cz = tmpz;
    }
}        
    



inline void one_Mul_Curve2( const Integer& n, const Integer A, const Integer& mm, const Integer& nn, const Integer& px, const Integer& pz, Integer& aax, Integer& aaz) {
    Integer ax, az, bx, bz, cx, cz, tmpx, tmpz, d, e, t1, t2,t3,t4;
    cx = px;
    cz = pz;
    e = mm;
    d = nn - mm;
    if (e<d) {
        Add_Curve(n,A,px,pz,bx,bz);ax = px;az = pz;d = d - e;
    } else {
        Add_Curve(n,A,px,pz,ax,az);bx = px;bz = pz;e = e - d;
    }
    while (! isZero(e)) {
        if (e<d) {
            tmpx = bx; tmpz = bz; 
            t1 = ((ax-az)*(bx+bz))%n; 
            t2 = ((ax+az)*(bx-bz))%n; 
//             bx = (cz*(((t1+t2)*(t1+t2))%n))%n;
//             bz = (cx*(((t1-t2)*(t1-t2))%n))%n;
            t3 = t1+t2;
            t4 = t1-t2;
            bx = (cz*(((t3)*(t3))%n))%n;
            bz = (cx*(((t4)*(t4))%n))%n;
            d = d-e;
        } else {
            tmpx = ax; tmpz = az; 
            t1 = ((ax-az)*(bx+bz))%n; 
            t2 = ((ax+az)*(bx-bz))%n; 
            t3 = t1+t2;
            t4 = t1-t2;
//             ax = (cz*(((t1+t2)*(t1+t2))%n))%n;
//             az = (cx*(((t1-t2)*(t1-t2))%n))%n;
            ax = (cz*(((t3)*(t3))%n))%n;
            az = (cx*(((t4)*(t4))%n))%n;
            e = e-d;
        }
        cx = tmpx;
        cz = tmpz;
    }
    aax = ax;
    aaz = az;
}        
    

inline void Mul_Curve( const Integer& n, Integer& Ai, const Integer& mm, const Integer& nn, const Integer& B1, Integer& Xi, Integer& Zi) {
    Integer pow = nn, tXi, tZi;
    tXi = Xi; // Temporaries mandatory -- JGD 24.09.2004
    tZi = Zi; // Temporaries mandatory -- JGD 24.09.2004
    while (pow <= B1) {
        one_Mul_Curve(n,Ai,mm,nn,Xi,Zi,tXi,tZi);
        pow *= nn;
    	Xi = tXi;
    	Zi = tZi;
    }
}

// ======================================================================== //
// Lenstra algorithm for elliptic curves
// Returns -1 if failure to find factors
// heuristically exp( sqrt( (2+epsilon)(ln p)(ln ln p) ) ) multiplications
// to find a factor p of N.
// TODO : make it generic in regards to DOMAINLIKENESS
// ======================================================================== //
template<class RandIter>
typename IntFactorDom<RandIter>::Rep& IntFactorDom<RandIter>::Lenstra(RandIter& gen, Rep& g, const Rep& n, const Rep& B1, const unsigned long curves) const 
{
    if (n<3) return g=n;
    if ( isprime(n,5) ) return g=n;
    if (isZero(n % 2)) return g=2;
    if (isZero(n % 3)) return g=3;

    Rep * A = new Rep[curves]
        , * X = new Rep[curves]
        , * Z = new Rep[curves];

    Rep r,a,asq,kg,kgg;
    for (unsigned long c=0; c<curves;++c)
        Z[c] = one;
    
    Rep u,v, four, two;
    assign(two,2UL);
    gcd(g,u,v,two,n);
    Rep inv2 = u;
    assign(four,4UL);
    gcd(g,u,v,four,n);
    Rep inv4 = u, sixt;
    assign(sixt,16UL);
    gcd(g,u,v,sixt,n);
    Rep inv16 = u,inva;

// Initialize # curves
    for (unsigned long i=0;i<curves;++i) {
        a = 0, asq = 0;
        while ((( a*(asq-1UL)*(9UL*asq-1UL) ) % n) == 0L ) {
            random(gen,r,n);
//             kg = r*r + 6;
            mul(kg,r,r); addin(kg,6UL);
//             kgg = gcd(kg,n);
            gcd(kgg,kg,n);
            if (isOne(kgg)) {
//                 g = gcd(kg,n,u,v); if (! isOne(g)) { delete [] A, X, Z; return g; }
                gcd(g,u,v,kg,n); if (! isOne(g)) { delete [] A; delete [] X; delete [] Z; return g; }
                a = (6UL*r*u)% n;
                asq = (a * a) % n ;
            } else
                return g=kgg;
        }
//         g = gcd(a,n,u,v); if (! isOne(g)) { delete [] A; delete [] X; delete [] Z; return g; }
        gcd(g,u,v,a,n); if (! isOne(g)) { delete [] A; delete [] X; delete [] Z; return g; }
//         A[i] = ( (8-3*a + (1-6*a*a)*u*u*u )*inv16 ) % n;
        A[i] = ( inv2 + ( (1-3*asq*asq-6*asq) %n )* (u*u*u*inv16 % n) ) % n ;
        X[i] = (3*a*inv4)%n;
    }

        // .5*sqrt(5)-.5, 37 digits
//     Rep s("618033988749894848204586834370");
//     Rep si("1000000000000000000000000000000");
//     Rep s("6180339887498948482045868343656381177");
//     Rep si("10000000000000000000000000000000000000");
    Rep s(618033988UL);
    Rep si(1000000000UL);

// Begins search with curves on primes up to B1
    Rep prime = 2, sp, f;
    while (prime <= B1) {
//std::cerr << "p: " << prime << std::endl;
        sp = (prime*s)/si;
        Mul_Curve(n,A[0],sp,prime,B1,X[0],Z[0]);
        f = Z[0];
        for(unsigned long i=1;i<curves;++i) {
            Mul_Curve(n,A[i],sp,prime,B1,X[i],Z[i]);
            f = (f*Z[i])%n;
        }
//         f = gcd(f,n);
        Rep ftm;
        gcd(ftm,f,n);
        f = ftm;
        if (isOne(f)) {
            nextprime(ftm,prime);
            prime = ftm;
//             prime = nextprime(prime);
        } else {
            delete [] A; delete [] X; delete [] Z; 
            return g=f; 
        }
    }
    
    std::cerr << "*** Elliptic curves with " << curves << " curves, threshold " << B1 << " failed ***" << std::endl;
    delete [] A; delete [] X; delete [] Z; 
    return neg(g,one);
}

#endif
