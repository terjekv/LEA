////////////////////////////////////////////////////////////////////////////////
// File: factorial.c                                                          //
// Routine(s):                                                                //
//    Factorial                                                               //
//    xFactorial                                                              //
//    Factorial_Max_Arg                                                       //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Description:                                                              //
//     The functions Factorial(n) and xFactorial(n) return n!                 //
//     for 0 <= n <= Factorial_Max_Arg().  If n > Factorial_Max_Arg(),        //
//     then DBL_MAX is returned and if n < 0, then 0 is returned.             //
//     The function Factorial_Max_Arg() returns the maximum argument to the   //
//     functions Factorial() and xFactorial().                                //
////////////////////////////////////////////////////////////////////////////////

#include <float.h>                         // required for DBL_MAX

//                         Internally Defined Routines                        //

double Factorial(int n);
long double xFactorial(int n);
int Factorial_Max_Arg( void );

//                         Internally Defined Constants                       //

static long double const factorials[] = {
       1.000000000000000000000e+0L,          //   0!
       1.000000000000000000000e+0L,          //   1!
       2.000000000000000000000e+0L,          //   2!
       6.000000000000000000000e+0L,          //   3!
       2.400000000000000000000e+1L,          //   4!
       1.200000000000000000000e+2L,          //   5!
       7.200000000000000000000e+2L,          //   6!
       5.040000000000000000000e+3L,          //   7!
       4.032000000000000000000e+4L,          //   8!
       3.628800000000000000000e+5L,          //   9!
       3.628800000000000000000e+6L,          //  10!
       3.991680000000000000000e+7L,          //  11!
       4.790016000000000000000e+8L,          //  12!
       6.227020800000000000000e+9L,          //  13!
       8.717829120000000000000e+10L,         //  14!
       1.307674368000000000000e+12L,         //  15!
       2.092278988800000000000e+13L,         //  16!
       3.556874280960000000000e+14L,         //  17!
       6.402373705728000000000e+15L,         //  18!
       1.216451004088320000000e+17L,         //  19!
       2.432902008176640000000e+18L,         //  20!
       5.109094217170944000000e+19L,         //  21!
       1.124000727777607680000e+21L,         //  22!
       2.585201673888497664000e+22L,         //  23!
       6.204484017332394393600e+23L,         //  24!
       1.551121004333098598400e+25L,         //  25!
       4.032914611266056355840e+26L,         //  26!
       1.088886945041835216077e+28L,         //  27!
       3.048883446117138605015e+29L,         //  28!
       8.841761993739701954544e+30L,         //  29!
       2.652528598121910586363e+32L,         //  30!
       8.222838654177922817726e+33L,         //  31!
       2.631308369336935301672e+35L,         //  32!
       8.683317618811886495518e+36L,         //  33!
       2.952327990396041408476e+38L,         //  34!
       1.033314796638614492967e+40L,         //  35!
       3.719933267899012174680e+41L,         //  36!
       1.376375309122634504632e+43L,         //  37!
       5.230226174666011117600e+44L,         //  38!
       2.039788208119744335864e+46L,         //  39!
       8.159152832478977343456e+47L,         //  40!
       3.345252661316380710817e+49L,         //  41!
       1.405006117752879898543e+51L,         //  42!
       6.041526306337383563736e+52L,         //  43!
       2.658271574788448768044e+54L,         //  44!
       1.196222208654801945620e+56L,         //  45!
       5.502622159812088949850e+57L,         //  46!
       2.586232415111681806430e+59L,         //  47!
       1.241391559253607267086e+61L,         //  48!
       6.082818640342675608723e+62L,         //  49!
       3.041409320171337804361e+64L,         //  50!
       1.551118753287382280224e+66L,         //  51!
       8.065817517094387857166e+67L,         //  52!
       4.274883284060025564298e+69L,         //  53!
       2.308436973392413804721e+71L,         //  54!
       1.269640335365827592597e+73L,         //  55!
       7.109985878048634518540e+74L,         //  56!
       4.052691950487721675568e+76L,         //  57!
       2.350561331282878571829e+78L,         //  58!
       1.386831185456898357379e+80L,         //  59!
       8.320987112741390144276e+81L,         //  60!
       5.075802138772247988009e+83L,         //  61!
       3.146997326038793752565e+85L,         //  62!
       1.982608315404440064116e+87L,         //  63!
       1.268869321858841641034e+89L,         //  64!
       8.247650592082470666723e+90L,         //  65!
       5.443449390774430640037e+92L,         //  66!
       3.647111091818868528825e+94L,         //  67!
       2.480035542436830599601e+96L,         //  68!
       1.711224524281413113725e+98L,         //  69!
       1.197857166996989179607e+100L,        //  70!
       8.504785885678623175212e+101L,        //  71!
       6.123445837688608686152e+103L,        //  72!
       4.470115461512684340891e+105L,        //  73!
       3.307885441519386412260e+107L,        //  74!
       2.480914081139539809195e+109L,        //  75!
       1.885494701666050254988e+111L,        //  76!
       1.451830920282858696341e+113L,        //  77!
       1.132428117820629783146e+115L,        //  78!
       8.946182130782975286851e+116L,        //  79!
       7.156945704626380229481e+118L,        //  80!
       5.797126020747367985880e+120L,        //  81!
       4.753643337012841748421e+122L,        //  82!
       3.945523969720658651190e+124L,        //  83!
       3.314240134565353266999e+126L,        //  84!
       2.817104114380550276949e+128L,        //  85!
       2.422709538367273238177e+130L,        //  86!
       2.107757298379527717214e+132L,        //  87!
       1.854826422573984391148e+134L,        //  88!
       1.650795516090846108122e+136L,        //  89!
       1.485715964481761497310e+138L,        //  90!
       1.352001527678402962552e+140L,        //  91!
       1.243841405464130725548e+142L,        //  92!
       1.156772507081641574759e+144L,        //  93!
       1.087366156656743080274e+146L,        //  94!
       1.032997848823905926260e+148L,        //  95!
       9.916779348709496892096e+149L,        //  96!
       9.619275968248211985333e+151L,        //  97!
       9.426890448883247745626e+153L,        //  98!
       9.332621544394415268170e+155L,        //  99!
       9.332621544394415268170e+157L,        // 100!
       9.425947759838359420852e+159L,        // 101!
       9.614466715035126609269e+161L,        // 102!
       9.902900716486180407547e+163L,        // 103!
       1.029901674514562762385e+166L,        // 104!
       1.081396758240290900504e+168L,        // 105!
       1.146280563734708354534e+170L,        // 106!
       1.226520203196137939352e+172L,        // 107!
       1.324641819451828974500e+174L,        // 108!
       1.443859583202493582205e+176L,        // 109!
       1.588245541522742940425e+178L,        // 110!
       1.762952551090244663872e+180L,        // 111!
       1.974506857221074023537e+182L,        // 112!
       2.231192748659813646597e+184L,        // 113!
       2.543559733472187557120e+186L,        // 114!
       2.925093693493015690688e+188L,        // 115!
       3.393108684451898201198e+190L,        // 116!
       3.969937160808720895402e+192L,        // 117!
       4.684525849754290656574e+194L,        // 118!
       5.574585761207605881323e+196L,        // 119!
       6.689502913449127057588e+198L,        // 120!
       8.094298525273443739682e+200L,        // 121!
       9.875044200833601362412e+202L,        // 122!
       1.214630436702532967577e+205L,        // 123!
       1.506141741511140879795e+207L,        // 124!
       1.882677176888926099744e+209L,        // 125!
       2.372173242880046885677e+211L,        // 126!
       3.012660018457659544810e+213L,        // 127!
       3.856204823625804217357e+215L,        // 128!
       4.974504222477287440390e+217L,        // 129!
       6.466855489220473672507e+219L,        // 130!
       8.471580690878820510985e+221L,        // 131!
       1.118248651196004307450e+224L,        // 132!
       1.487270706090685728908e+226L,        // 133!
       1.992942746161518876737e+228L,        // 134!
       2.690472707318050483595e+230L,        // 135!
       3.659042881952548657690e+232L,        // 136!
       5.012888748274991661035e+234L,        // 137!
       6.917786472619488492228e+236L,        // 138!
       9.615723196941089004197e+238L,        // 139!
       1.346201247571752460588e+241L,        // 140!
       1.898143759076170969429e+243L,        // 141!
       2.695364137888162776589e+245L,        // 142!
       3.854370717180072770522e+247L,        // 143!
       5.550293832739304789551e+249L,        // 144!
       8.047926057471991944849e+251L,        // 145!
       1.174997204390910823948e+254L,        // 146!
       1.727245890454638911203e+256L,        // 147!
       2.556323917872865588581e+258L,        // 148!
       3.808922637630569726986e+260L,        // 149!
       5.713383956445854590479e+262L,        // 150!
       8.627209774233240431623e+264L,        // 151!
       1.311335885683452545607e+267L,        // 152!
       2.006343905095682394778e+269L,        // 153!
       3.089769613847350887959e+271L,        // 154!
       4.789142901463393876336e+273L,        // 155!
       7.471062926282894447084e+275L,        // 156!
       1.172956879426414428192e+278L,        // 157!
       1.853271869493734796544e+280L,        // 158!
       2.946702272495038326504e+282L,        // 159!
       4.714723635992061322407e+284L,        // 160!
       7.590705053947218729075e+286L,        // 161!
       1.229694218739449434110e+289L,        // 162!
       2.004401576545302577600e+291L,        // 163!
       3.287218585534296227263e+293L,        // 164!
       5.423910666131588774984e+295L,        // 165!
       9.003691705778437366474e+297L,        // 166!
       1.503616514864999040201e+300L,        // 167!
       2.526075744973198387538e+302L,        // 168!
       4.269068009004705274939e+304L,        // 169!
       7.257415615307998967397e+306L         // 170!
                                        };

static const int N = sizeof(factorials) / sizeof(long double);

////////////////////////////////////////////////////////////////////////////////
// double Factorial( int n )                                                  //
//                                                                            //
//  Description:                                                              //
//     This function computes n! for 0 <= n <= Factorial_Max_Arg().  If       //
//     n > Factorial_Max_Arg(), then DBL_MAX is returned and if n < 0, then   //
//     0 is returned.                                                         //
//                                                                            //
//  Arguments:                                                                //
//     int    n   Argument of the Factorial function.                         //
//                                                                            //
//  Return Values:                                                            //
//     If n is negative, then 0 is returned.  If n > Factorial_Max_Arg(),     //
//     then DBL_MAX is returned.  If 0 <= n <= Factorial_Max_Arg(), then      //
//     n! is returned.                                                        //
//                                                                            //
//  Example:                                                                  //
//     int n;                                                                 //
//     double x;                                                              //
//                                                                            //
//     x = Factorial( n );                                                    //
////////////////////////////////////////////////////////////////////////////////
double Factorial(int n) {

               // For a negative argument (n < 0) return 0.0 //

   if ( n < 0 ) return 0.0;


           // For a large postive argument (n >= N) return DBL_MAX //

   if ( n >= N ) return DBL_MAX;

                          // Otherwise return n!. //

   return (double) factorials[n];
}


////////////////////////////////////////////////////////////////////////////////
// long double xFactorial( int n )                                            //
//                                                                            //
//  Description:                                                              //
//     This function computes n! for 0 <= n <= Factorial_Max_Arg().  If       //
//     n > Factorial_Max_Arg(), then DBL_MAX is returned and if n < 0, then   //
//     0 is returned.                                                         //
//                                                                            //
//  Arguments:                                                                //
//     int    n   Argument of the Factorial function.                         //
//                                                                            //
//  Return Values:                                                            //
//     If n is negative, then 0 is returned.  If n > Factorial_Max_Arg(),     //
//     then DBL_MAX is returned.  If 0 <= n <= Factorial_Max_Arg(), then      //
//     n! is returned.                                                        //
//                                                                            //
//  Example:                                                                  //
//     int n;                                                                 //
//     long double x;                                                         //
//                                                                            //
//     x = xFactorial( n );                                                   //
////////////////////////////////////////////////////////////////////////////////
long double xFactorial(int n) {

               // For a negative argument (n < 0) return 0.0 //

   if ( n < 0 ) return 0.0L;


           // For a large postive argument (n >= N) return DBL_MAX //

   if ( n >= N ) return  (long double) DBL_MAX;

                          // Otherwise return n!. //

   return factorials[n];
}


////////////////////////////////////////////////////////////////////////////////
// int Factorial_Max_Arg( void )                                              //
//                                                                            //
//  Description:                                                              //
//     This function returns the maximum argument of the Factorial function   //
//     for which a number < DBL_MAX is returned.                              //
//                                                                            //
//  Arguments:                                                                //
//     none                                                                   //
//                                                                            //
//  Return Values:                                                            //
//     N-1                                                                    //
//                                                                            //
//  Example:                                                                  //
//     int x;                                                                 //
//                                                                            //
//     x = Factorial_Max_Arg();                                               //
////////////////////////////////////////////////////////////////////////////////

int Factorial_Max_Arg( void ) { return N - 1; }
