//Permanent link: https://rextester.com/IPOV29329
//REVISION OF: https://rextester.com/GSPA46703: bugs removed in y_atof2()
// to accept expressios like " - 12.24999" or " +   12.24999" -with sign
//two versions of my atof function: fast, precise and (possibly) reliable
//clang 6.0.0
//Code by Twareintor 2021 - Copyright(c) 2009-2021 Claudiu Ciutacu

#include  <stdio.h>
#include <string.h>

/** returns a float out of a string: only the first exprLen characters are evaluated
 * The expression can be something like "-12.23 mm" or "CurrentSpeed = 374.803 km/h"
 * In this case the usage may look like\ char const* sz = strchr(szExpr, '=')+1;
 * y = y_atof(sz, strstr(sz, "km/h")-sz) // useful e.g. for processing use input
 * If you don't understand why is this good for and why not to use alternatives like 
 * 'atof()' (which also requires additional linking, beside not being standard C) or
 * sscanf(), you don't need it and you're free to use alternatives. Good luck!
 * NOTE: if the expression to be evaluated is ill-formed the result is undefined
 * DISCLAIMER: NOT FULLY TESTED OR IMPLEMENTED. USE AT OWN RISK
 */
float y_atof(char const* szExpr, int const exprLen)
{
    float y = 0.f; // output value
    char const* szPt = strchr(szExpr, '.'); // the point
    char const* s; // iterates through szExpr[]
    float m = 1.f; // current magnitude
    float sign = 1.f; // the sign of the expression
    
    if(szPt && szPt<szExpr+exprLen) s = szPt-1;
    else{s = szExpr+exprLen-1; while(' '==*s) s--;}
    while(s>=szExpr && !(*s<'0' || '9'<*s))
    {
        y+=(float)(*s-'0')*m;
        m*=10.f;
        s--;
    }
    s++; // forgotten!!!!
    if(s>szExpr) // read the sign, if there
        while(('-'!=*s || ' '==*s) && s>=szExpr) s--;
    if('-'==*s) sign = -1.f; // till '-', if there
    if(szPt) s = szPt+1;
    else return y*sign;
    m = .1f;
    while(s<=(szExpr+exprLen) && !(*s<'0' || '9'<*s))
    {
        y+=(float)(*s-'0')*m;
        m/=10.f;
        s++;
    }
    y = sign*y;
    return y;
}

/** The same as the above: this doesn't need any function from <string.h>
 *  WARNING!!! if expr contains a space will be ignored! This may or may not
 * be exactly what you want! I don't know if this is the same for the 
 * previous function presented here in Rextester!
 * DISCLAIMER: NOT FULLY TESTED OR IMPLEMENTED. USE AT OWN RISK
 */
float y_atof2(char const* szExpr, int const exprLen)
{
    float y = 0.f; // output value;
    char const* sz0 = szExpr; // keeping the starting point of figure series
    char const* sz = sz0; // iterator
    float ord = .1f; // the order: 12.22 is ord. 10, 2212 is ord 1000
    float sign = 1.f; // the sign (the very first char, if '-' ...)
    
    // ignoring the leading blanks and getting the sign, if provided
    while(' '==*sz) sz++; 
    if('-'==*sz){sign = -1.f; sz++;}else if('+'==*sz){sz++;}
    while(' '==*sz) sz++; // ignoring the leading blanks after sign
    sz0 = sz;
    // this is just to guess the order
    while('.'!=*sz && ' '!=*sz && sz-szExpr<exprLen){sz++; ord*=10.f;}
    sz = sz0; // again from the beginning
    // printf("ord = %g\n", ord); // just for debug:
    while(sz-szExpr<exprLen)
    {
        if(!('0'<=*sz && *sz<='9')) sz++;
        y+=(ord*(*sz-'0'));
        ord/=10.f;
        sz++;
    }
    return sign*y; // sign must be found in the output
}

/** same as the above but without sign and leading/ trailing spaces 
 * If there is any other character than '0' to '9' or '.' the 
 * result is undefined.
 * See comments on the functions y_atof() and y_atof2()
 */ 
float y_atofS(char const* szExpr, int const exprLen)
{
    float y = 0.f;
    char const* sz = szExpr;
    float ord = .1f;
    
    while('.'!=*sz && sz-szExpr<exprLen){sz++; ord*=10.f;}
    sz = szExpr;
    while(sz-szExpr<exprLen)
    {
        sz+=('.'==*sz);
        y+=(ord*(*sz-'0'));
        ord/=10.f;
        sz++;
    }
    return y;
}

int main(void)
{
    float x;
    char szText[] = " v = - 12.24999975 m/s   ";
    
    char* szExpr = strchr(szText, '=') + 1; 
    int exprLen = (int)(strstr(szExpr, "m/s") - szExpr);
    x = y_atof(szExpr, exprLen);          printf("x = %G\n", x);
    x = y_atof2(szExpr, exprLen);         printf("x = %G\n", x);

    x = y_atof(szExpr+3, exprLen-3);      printf("x = %G\n", x);
    x = y_atof2(szExpr+3, exprLen-3);     printf("x = %G\n", x);

    char szText2[] = ".22459382322222";
    x = y_atofS(szText2, 7);              printf("x = %G\n", x);
    
    return 0;
}

