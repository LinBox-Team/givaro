// ==========================================================================
// $Source: /var/lib/cvs/Givaro/src/kernel/zpz/givzpz16table1.inl,v $
// Copyright(c)'94-97 by Givaro Team
// see the copyright file.
// Authors: J.G. Dumas$
// Modified by Pascal Giorgi 2002/04/24
// $Id: givzpz16table1.inl,v 1.3 2004-07-20 12:03:46 giorgi Exp $
// ==========================================================================
// Description:

// ---------
// -- normalized operations
// ---------

#define __GIVARO_ZPZ16_LOG_MUL(r,p,a,b) \
  {(r)= _tab_mul[(a) + (b)]; }
#define __GIVARO_ZPZ16_LOG_DIV(r,p,a,b) \
  {(r)= _tab_div[(a) - (b)]; }
#define __GIVARO_ZPZ16_LOG_INV(r,p,b)   \
  {(r)= _tab_div[ - (b)]; }
#define __GIVARO_ZPZ16_LOG_SUB(r,p,a,b) \
  {(r)= _tab_mul[(a) + _tab_subone[(b) - (a)] ]; }
#define __GIVARO_ZPZ16_LOG_ADD(r,p,a,b) \
  {(r)=  _tab_mul[(a) + _tab_addone[(b) - (a)] ];}
#define __GIVARO_ZPZ16_LOG_NEG(r,p,a) \
  { r = _tab_neg[(a)];}

/* Pascal Giorgi
   Changing the order of parameters.
*/	
#define __GIVARO_ZPZ16_LOG_MULADD(r,p,a,b,c) \
  { __GIVARO_ZPZ16_LOG_MUL(r, p, a, b); __GIVARO_ZPZ16_LOG_ADD(r, p, r, c); }
#define __GIVARO_ZPZ16_LOG_MULSUB(r,p,a,b,c) \
  { __GIVARO_ZPZ16_LOG_MUL(r, p, a, b); __GIVARO_ZPZ16_LOG_SUB(r, p, r, c); }



inline ZpzDom<Log16>::Residu_t ZpzDom<Log16>::residu( ) const
{ return _p; }

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::mul (Rep& r, const Rep a, const Rep b) const
{ 
  register int32 tmp; 	
  __GIVARO_ZPZ16_LOG_MUL(tmp,(int32)_p,(int32)a,(int32)b);
  return r= (ZpzDom<Log16>::Rep)tmp;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::div (Rep& r, const Rep a, const Rep b) const
{ 
  __GIVARO_ZPZ16_LOG_DIV(r,_p,a,b); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::sub (Rep& r, const Rep a, const Rep b) const
{ 
  __GIVARO_ZPZ16_LOG_SUB(r,_p,a,b); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::add (Rep& r, const Rep a, const Rep b) const
{ 
  __GIVARO_ZPZ16_LOG_ADD(r,_p,a,b); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::neg (Rep& r, const Rep a) const
{ 
  __GIVARO_ZPZ16_LOG_NEG(r,_p,a); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::inv (Rep& r, const Rep a) const
{ 
  __GIVARO_ZPZ16_LOG_INV(r,_p,a);
  // GivError::throw_error( GivMathDivZero("Zpz::inv"));
  return r;
}

 // -- inline array operations between ZpzDom<Log16>::Rep
inline void ZpzDom<Log16>::mul (const size_t sz, Array r, constArray a, constArray b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_MUL(r[i], _p,a[i], b[i]); 
  }
}

inline void ZpzDom<Log16>::mul (const size_t sz, Array r, constArray a, Rep b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_MUL(r[i], _p, a[i], b);
  }
}

inline void ZpzDom<Log16>::div (const size_t sz, Array r, constArray a, constArray b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_DIV( r[i], _p, a[i], b[i]); 
  }
}

inline void ZpzDom<Log16>::div (const size_t sz, Array r, constArray a, Rep b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_DIV( r[i], _p, a[i], b); 
  }
}

inline void ZpzDom<Log16>::add (const size_t sz, Array r, constArray a, constArray b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_ADD(r[i], _p, a[i], b[i]);
  }
}

inline void ZpzDom<Log16>::add (const size_t sz, Array r, constArray a, Rep b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_ADD(r[i], _p, a[i], b);
  }
}

inline void ZpzDom<Log16>::sub (const size_t sz, Array r, constArray a, constArray b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_SUB(r[i], _p, a[i], b[i]);
  }
}

inline void ZpzDom<Log16>::sub (const size_t sz, Array r, constArray a, Rep b) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_SUB(r[i], _p, a[i], b);
  }
}

inline void ZpzDom<Log16>::neg (const size_t sz, Array r, constArray a) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_NEG(r[i], _p, a[i]);
  }
}


inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::mulin (Rep& r, const Rep a) const
{ 
  __GIVARO_ZPZ16_LOG_MUL(r,_p, r,a); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::divin (Rep& r, const Rep a) const
{ 
  ZpzDom<Log16>::Rep ia;
  inv(ia, a);
  mulin(r, ia);
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::addin (Rep& r, const Rep a) const
{ 
  __GIVARO_ZPZ16_LOG_ADD(r, _p, r,a); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::subin (Rep& r, const Rep a) const
{ 
  __GIVARO_ZPZ16_LOG_SUB(r,_p, r,a); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::negin (Rep& r) const
{
  __GIVARO_ZPZ16_LOG_NEG(r,_p,r);
  return r;
}	

inline ZpzDom<Log16>::Rep&  ZpzDom<Log16>::invin (Rep& r) const
{
  __GIVARO_ZPZ16_LOG_INV(r,_p,r);
  return r;
}	

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::axpy 
 (Rep& r, const Rep a, const Rep b, const Rep c) const
{ 
  __GIVARO_ZPZ16_LOG_MULADD(r, _p, a, b, c); 
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::axpyin 
 (Rep& r, const Rep a, const Rep b) const
{ 
  //__GIVARO_ZPZ16_LOG_MULADD(r, _p, a, b, r);
  // Pascal giorgi
  // non consistant because don't perform an axpyin 
  // due to the name of parameter
  // the operation performed is 2*a*b 
 
  return axpy(r,a,b,r);
}


inline void ZpzDom<Log16>::axpy 
  (const size_t sz, Array r, constArray a, constArray x, constArray y) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_MULADD(r[i], _p, a[i], x[i], y[i]);
  }
}

inline void ZpzDom<Log16>::axpyin 
  (const size_t sz, Array r, constArray a, constArray x) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_MULADD(r[i], _p, a[i], x[i], r[i]);
  }
}


inline void ZpzDom<Log16>::axmy 
  (Rep& r, const Rep a, const Rep b, const Rep c) const
{ 
  __GIVARO_ZPZ16_LOG_MULSUB(r,_p,a,b,c); 
}

inline void ZpzDom<Log16>::axmy 
  (const size_t sz, Array r, constArray a, constArray x, constArray y) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_MULSUB(r[i], _p, a[i], x[i], y[i]);
  }
}

inline void ZpzDom<Log16>::axmyin 
  (const size_t sz, Array r, constArray a, constArray x) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    __GIVARO_ZPZ16_LOG_MULSUB(r[i], _p, a[i], x[i], r[i]);
    __GIVARO_ZPZ16_LOG_NEG(r[i], _p, r[i]);
  }
}

 // ------------------------- Miscellaneous functions

inline int ZpzDom<Log16>::iszero(const Rep a) const
{ return a >= _p; }

inline int ZpzDom<Log16>::isone(const Rep a) const
{ return a == ZpzDom<Log16>::one; }

inline size_t ZpzDom<Log16>::length(const Rep a) const
{ return ZpzDom<Log16>::size_rep;}

inline int ZpzDom<Log16>::isZero( const Rep a ) const {return iszero(a);}
inline int ZpzDom<Log16>::isOne ( const Rep a ) const {return isone(a);}


// ---------
// -- misc operations
// ---------
/* 
inline void ZpzDom<Log16>::assign 
  ( const size_t sz, Array r, constArray a ) const
{
  for (register size_t i=sz-1; i!=0; --i) {
    if (a[i] <ZpzDom<Log16>::zero) {
       r[i] = a[i] + _p;
       if (r[i] <ZpzDom<Log16>::zero) r[i] = r[i] % _p;
    }
    else if (a[i] >_p) {
       r[i] = a[i] - _p;
       if (r[i] >_p) r[i] = r[i] % _p;
    }
    else r[i] = a[i];
  }
}
*/

inline void ZpzDom<Log16>::assign ( const size_t sz, Array r, constArray a ) const
{
  for (register size_t i=sz-1; i!=0; --i) 
    r[i] = a[i];
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::assign ( Rep& r, const Rep a ) const
{ return r = a; }

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::assign ( Rep& r, const long a ) const
{
  int sign; unsigned long ua;
  if (a <0) { sign =-1; ua = -a;}
  else { ua = a; sign =1; }
  r = (ua >_p) ? ua % _p : ua;
  if (sign ==-1) r = _p - r;
  return r;
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::assign ( Rep& r, const int a ) const
{ return ZpzDom<Log16>::assign( r, (long)a); }

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::assign ( Rep& r, const unsigned long a ) const
{ r = (a >_p) ? a % _p : a; return r;}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::assign ( Rep& r, const unsigned int a ) const
{ r = (a >_p) ? a % _p : a; return r;}



inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::init ( Rep& r ) const
{ return r = zero; }


inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::init ( Rep& r , const long a) const
{
    Power_t tmp;
    assign(tmp,a);
    return r= _tab_value2rep[tmp];
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::init ( Rep& r , const unsigned long a) const
{ 
    Power_t tmp;
  assign(tmp,a);
  return r= _tab_value2rep[tmp];
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::init( Rep& a, const unsigned int i) const {
  return init(a,(unsigned long)i); 
}

inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::init( Rep& a, const int i) const {
  return init(a,(long)i); 
}


inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::init( Rep& a, const double i) const {
	  return init(a,(long)i);
}
inline ZpzDom<Log16>::Rep& ZpzDom<Log16>::init( Rep& a, const float i) const {
	  return init(a,(double)i);
}


inline void ZpzDom<Log16>::dotprod 
  ( Rep& r, const int bound, const size_t sz, constArray a, constArray b ) const
{
  unsigned int stride = 1;
  if ((unsigned long)bound < GIVARO_MAXUINT16)
   stride = GIVARO_MAXUINT32/((unsigned long)bound * (unsigned long)bound);
  uint32 dot = zero;
  if ((sz <10) && (sz <stride)) {
    for( register int i= sz-1; i>=0; --i) 
      dot += _tab_rep2value[a[i]] * _tab_rep2value[b[i]]; 
    if (dot > _p) r = _tab_value2rep[(Rep)(dot % _p)];
    else r = _tab_value2rep[dot];
    return;
  }
  unsigned int i_begin=0;
  stride &= ~0x1;
  if (stride ==0) {
    for( register int i= sz-1; i>0; --i) {
      dot += _tab_rep2value[a[i]] * _tab_rep2value[b[i]]; 
      if (dot>_p) dot %= _p;
    }
    r = _tab_value2rep[dot];
    return;
  }
  do {
    size_t min_sz = ((sz-i_begin) < stride ? (sz-i_begin) : stride);
    if (min_sz & 0x1 !=0) { 
      min_sz--; i_begin++; 
      dot += _tab_rep2value[a++[min_sz]] * _tab_rep2value[b++[min_sz]]; 
    }
    if (min_sz > 1) 
      for( register size_t i= min_sz; i>0; --i, --i, ++a, ++a, ++b, ++b ) 
      {
        dot += _tab_rep2value[a[0]] * _tab_rep2value[b[0]]; 
        dot += _tab_rep2value[a[1]] * _tab_rep2value[b[1]]; 
      }
    if (dot>_p) dot %= _p;
    i_begin += min_sz;
  } while (i_begin <sz);
  r = _tab_value2rep[dot];
}

inline void ZpzDom<Log16>::dotprod
  ( Rep& r, const size_t sz, constArray a, constArray b ) const
{
  return ZpzDom<Log16>::dotprod(r, _p, sz, a, b);
}


  //  a -> r: int16 to double
inline void 
  ZpzDom<Log16>::i2d ( const size_t sz, double* r, constArray a ) const
{
  for (size_t i=0; i<sz; ++i) r[i] = _tab_rep2value[a[i]];
}

  //  a -> r: double to int16 
inline void 
  ZpzDom<Log16>::d2i ( const size_t sz, Array r, const double* a ) const
{
  union d_2_l {
    double d;
    int32 r[2];
  };
  static const double offset = 4503599627370496.0; // 2^52
  register size_t i=sz-1;
label1: 
  {
      register d_2_l tmp;
      // - normalization: put fractional part at the end of the representation
      tmp.d = a[i] + offset; 
      r[i--] = _tab_value2rep[(tmp.r[1] >_p ? tmp.r[1] : tmp.r[1] % _p)];
  }
  if (i >0) goto label1;
  //for (size_t i=sz-1; i>=0; --i)
}


 // -- Input: (z, <_p>)
inline std::istream& ZpzDom<Log16>::read (std::istream& s) 
{
  char ch; 
  s >> std::ws >> ch;
//   if (ch != '(')
//     GivError::throw_error( GivBadFormat("ZpzDom<Log16>::read: syntax error: no '('"));
  if (ch != '(')
      std::cerr << "ZpzDom<Log16>::read: syntax error: no '('" << std::endl;

  s >> std::ws >> ch;
//   if (ch != 'z')
//     GivError::throw_error( GivBadFormat("ZpzDom<Log16>::read: bad domain object"));
  if (ch != 'z')
    std::cerr << "ZpzDom<Log16>::read: bad domain object" << std::endl ;

  s >> std::ws >> ch;
//   if (ch != ',')
//     GivError::throw_error( GivBadFormat("ZpzDom<Log16>::read: syntax error: no ','"));
  if (ch != ',')
      std::cerr << "ZpzDom<Log16>::read: syntax error: no ','" << std::endl;


  s >> std::ws >> _p;

  s >> std::ws >> ch;
//   if (ch != ')')
//     GivError::throw_error( GivBadFormat("ZpzDom<Log16>::read: syntax error: no ')'"));
  if (ch != ')')
      std::cerr << "ZpzDom<Log16>::read: syntax error: no ')'" << std::endl;

  return s;
}

inline std::ostream& ZpzDom<Log16>::write (std::ostream& s ) const
{
  return s << "Log16 Givaro Z/pZ modulo " << residu();
}

inline std::istream& ZpzDom<Log16>::read (std::istream& s, Rep& a) const
{
  int tmp; //dpritcha
  s >> tmp;
  tmp %= _p;
  if (tmp < 0) tmp += _p;
  a = _tab_value2rep[tmp];
  return s;
}

inline std::ostream& ZpzDom<Log16>::write (std::ostream& s, const Rep a) const
{
  if (a >= _p) return s << '0';
  return s << _tab_rep2value[a]; //dpritcha
}
