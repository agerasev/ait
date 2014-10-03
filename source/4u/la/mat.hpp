#ifndef MAT_HPP
#define MAT_HPP

#include"matnm.hpp"
#include"matn.hpp"

typedef tmatnm<double,2,2> dmat2;
typedef tmatnm<float,2,2>  fmat2;
typedef tmatnm<int,2,2>	   imat2;
typedef tmatnm<double,3,3> dmat3;
typedef tmatnm<float,3,3>  fmat3;
typedef tmatnm<int,3,3>	   imat3;
typedef tmatnm<double,4,4> dmat4;
typedef tmatnm<float,4,4>  fmat4;
typedef tmatnm<int,4,4>	   imat4;
typedef dmat2 mat2;
typedef dmat3 mat3;
typedef dmat4 mat4;

const imat2 nullimat2 = {0,0,0,0};
const dmat2 nulldmat2 = nullimat2;
const fmat2 nullfmat2 = nullimat2;
const imat3 nullimat3 = {0,0,0,0,0,0,0,0,0};
const dmat3 nulldmat3 = nullimat3;
const fmat3 nullfmat3 = nullimat3;
const imat4 nullimat4 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const dmat4 nulldmat4 = nullimat4;
const fmat4 nullfmat4 = nullimat4;
const mat2 nullmat2 = nulldmat2;
const mat3 nullmat3 = nulldmat3;
const mat4 nullmat4 = nulldmat4;

const imat2 uniimat2 = {1,0,0,1};
const dmat2 unidmat2 = uniimat2;
const fmat2 unifmat2 = uniimat2;
const imat3 uniimat3 = {1,0,0,0,1,0,0,0,1};
const dmat3 unidmat3 = uniimat3;
const fmat3 unifmat3 = uniimat3;
const imat4 uniimat4 = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
const dmat4 unidmat4 = uniimat4;
const fmat4 unifmat4 = uniimat4;
const mat2 unimat2 = unidmat2;
const mat3 unimat3 = unidmat3;
const mat4 unimat4 = unidmat4;

#endif // MAT_HPP
