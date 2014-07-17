#ifndef OP_H
#define OP_H

/*
 * These are some redefinitions of standard C/C++ operations
 * which aren't correct for negative values.
 */

inline int _mod(int num, int den)
{
    return (num<0)?(((num+1)%den)+den-1):(num%den);
}
inline int _div(int num, int den)
{
    if(den<0){num=-num;den=-den;}
    return (num<0)?(((num+1)/den)-1):(num/den);
}
inline int _divmod(int &num, int den)
{
    int ret = _div(num,den);
    num = _mod(num,den);
    return ret;
}
inline int _min(int a, int b)
{
    return (a<b)?a:b;
}
inline double _min(double a, double b)
{
    return (a<b)?a:b;
}
inline int _max(int a, int b)
{
    return (a>b)?a:b;
}
inline double _max(double a, double b)
{
    return (a>b)?a:b;
}
inline long _floor(double a)
{
    return (a < 0.0)?(static_cast<int>(a) - 1):(static_cast<int>(a));
}
inline long _ceil(double a)
{
    return (a < 0.0)?(static_cast<int>(a)):(static_cast<int>(a + 1));
}


#endif // OP_H
