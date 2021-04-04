# my_atof-
more than two versions of my atof function: fast, precise and (possibly) reliable

//Permanent link: https://rextester.com/IPOV29329
//REVISION OF: https://rextester.com/GSPA46703: bugs removed in y_atof2()
// to accept expressios like " - 12.24999" or " +   12.24999" -with sign
//two versions of my atof function: fast, precise and (possibly) reliable
//clang 6.0.0
//Code by Twareintor 2021 - Copyright(c) 2009-2021 Claudiu Ciutacu

/** returns a float out of a string: only the first exprLen characters are evaluated
 * The expression can be something like "-12.23 mm" or "CurrentSpeed = 374.803 km/h"
 * In this case the usage may look like\ char const* sz = strchr(szExpr, '=')+1;
 * y = y_atof(sz, strstr(sz, "km/h")-sz) // useful e.g. for processing use input
 * If you don't understand why is this good for and why not to use alternatives like 
 * 'atof()' (which also requires additional linking, beside not being standard C) or
 * sscanf(), you don't need it and you're free to use alternatives. Good luck!
 * DISCLAIMER: NOT FULLY TESTED OR IMPLEMENTED. USE AT OWN RISK
 */
float y_atof(char const* szExpr, int const exprLen);

/** The same as the above: this doesn't need any function from <string.h>
 *  WARNING!!! if expr contains a space will be ignored! This may or may not
 * be exactly what you want! I don't know if this is the same for the 
 * previous function presented here in Rextester!
 * DISCLAIMER: NOT FULLY TESTED OR IMPLEMENTED. USE AT OWN RISK
 */
float y_atof2(char const* szExpr, int const exprLen)

/** same as the above but without sign and leading/ trailing spaces 
 * If there is any other character than '0' to '9' or '.' the 
 * result is undefined.
 * See comments on the functions y_atof() and y_atof2()
 */ 
float y_atofS(char const* szExpr, int const exprLen)
