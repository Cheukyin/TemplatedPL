#include "expression.hpp"
#include "lib.hpp"
#include <iostream>

using namespace TPL;
using std::cout;
using std::endl;

int main()
{
    cout<<endl;
    cout<<"4 + 5 = ";
    cout<< Eval< Add< Int<4>, Int<5> > >::value::value;
    cout<<endl;
    cout<<"4 * 5 = ";
    cout<< Eval< Mul< Int<4>, Int<5> > >::value::value;
    cout<<endl;
    cout<<"4 % 5 = ";
    cout<< Eval< Mod< Int<4>, Int<5> > >::value::value;
    cout<<endl;

    cout<<endl;
    cout<<"4 > 5 : ";
    cout<< Eval< IsGreater< Int<4>, Int<5> > >::value::value;
    cout<<endl;
    cout<<"4 < 5 : ";
    cout<< Eval< IsLess< Int<4>, Int<5> > >::value::value;
    cout<<endl;
    cout<<"4 = 4 : ";
    cout<< Eval< IsEqual< Int<4>, Int<4> > >::value::value;
    cout<<endl;

    cout<<endl;
    cout<<"First  of Pair<4, 5> : ";
    cout<< Eval< Fst< Pair< Int<4>, Int<5> > > >::value::value;
    cout<<endl;
    cout<<"Second of Pair<4, 5> : ";
    cout<< Eval< Snd< Pair< Int<4>, Int<5> > > >::value::value;
    cout<<endl;

    cout<<endl;
    cout<<"Is Pair<4, 5> a List?                                   : ";
    cout<< Eval< Call< Lib::IsList, Pair< Int<4>, Int<5> > > >::value::value;
    cout<<endl;
    cout<<"Is Pair< 4, Pair<5, Unit> > a List?                     : ";
    cout<< Eval< Call< Lib::IsList, List< Int<4>, Int<5> > > >::value::value;
    cout<<endl;
    cout<<"The num at index 2 of List<0, 1, 2, 3>                  : ";
    cout<< Eval< Call< Lib::ListRef, List< Int<0>, Int<1>, Int<2>, Int<3> >, Int<2> > >::value::value;
    cout<<endl;
    cout<<"The num at index 4 of ListAppend< List<0, 1, 2, 3>, 9 > : ";
    cout<< Eval< Call< Lib::ListRef,
                       Call< Lib::ListAppend,
                             List< Int<0>, Int<1>, Int<2>, Int<3> >, Int<9> >,
                       Int<4> > >::value::value;
    cout<<endl;

    cout<<endl;
    cout<<"If 4<5 then 4+5 else 4-5 = ";
    cout<< Eval< If_Then_Else< IsLess< Int<4>, Int<5> >,
                               Add< Int<4>, Int<5> >,
                               Add< Int<4>, Int<-5> > > >::value::value;
    cout<<endl;

    cout<<endl;
    cout<<"Multi-Parameter Lambda:"<<endl;
    cout<<"(lambda x y z. x+y*z 2 3 4) = "; // 14
    cout<< Eval< Call< Lambda< ParamList< Var<0>, Var<1>, Var<2> >,
                               Add< Var<0>, Mul< Var<1>, Var<2> > > >,
                       Int<2>, Int<3>, Int<4> > >::value::value;
    cout<<endl;

    // ------------------------------------------------------------------
    // Sum is implemented with Reduce
    cout<<endl;
    cout<<"Sum(1 ... 10) = "; // 55
    cout<< Eval< Call< Lib::Sum, Call< Lib::Range, Int<1>, Int<10> > > >::value::value;
    cout<<endl;

    // ------------------------------------------------------------
    // Multiply Range(1, 10) by 2, then Sum the List(Using Map) = 110
    cout<<endl;
    cout<<"Sum(Map(Range(1, 10), lambda x. x*2)) = ";
    cout<< Eval< Call< Lib::Sum, Call< Lib::Map,
                                       Call< Lib::Range, Int<1>, Int<10> >,
                                       Lambda< ParamList< Var<0> >,
                                               Mul< Var<0>, Int<2> > > > > >::value::value;
    cout<<endl;

    // --------------------------------------------------------
    // Add all even num in Range(1, 10)(Using Filter) = 30
    cout<<endl;
    cout<<"Sum(Filter(Range(1, 10), lambda x. x%2 == 0)) = ";
    cout<< Eval< Call< Lib::Sum, Call< Lib::Filter,
                                       Call< Lib::Range, Int<1>, Int<10> >,
                                       Lambda< ParamList< Var<0> >,
                                               IsEqual< Mod< Var<0>, Int<2> >,
                                                        Int<0> > > > > >::value::value;
    cout<<endl;

    // ------------------------------------------------------
    // F = lambda f. lambda n. n==0 ? 1 : n*(f n-1)
    //(Fact 5) = ((Y F) 5) = 120
    cout<<endl;
    cout<<"Caculate Factorial(5) with Y-Combinator:"<<endl;
    cout<<"Fact(5) = ";
    cout<< Eval< Call< Call< Lib::YCombinater,
                             Lambda< ParamList< Var<0> >, // F
                                     Lambda< ParamList< Var<1> >,
                                             If_Then_Else< IsEqual< Var<1>, Int<0> >,
                                                           Int<1>,
                                                           Mul< Var<1>,
                                                                Call< Var<0>,
                                                                      Add< Var<1>, Int<-1> > > > > > > >,
                       Int<5> > >::value::value; // (Fact 5)
    cout<<endl;

    // ----------------------------------------------------------------------------------------
    // anonymous recursion, Factorial, F = lambda f. lambda n. n==0 ? 1 : n*( (f f) (n-1) )
    //( (F F) 6 ) = 720
    cout<<endl;
    cout<<"Caculate Factorial(6) with Anonymous Recursion:"<<endl;
    cout<<"Fact(6) = ";
    cout<< Eval< Call< Call< Lambda< ParamList< Var<1> >, // F
                                     Lambda< ParamList< Var<0> >,
                                             If_Then_Else< IsEqual< Var<0>, Int<0> >,
                                                           Int<1>,
                                                           Mul< Var<0>,
                                                                Call< Call< Var<1>, Var<1> >,
                                                                      Add< Var<0>, Int<-1> > > > > > >,
                             Lambda< ParamList< Var<1> >, // F
                                     Lambda< ParamList< Var<0> >,
                                             If_Then_Else< IsEqual< Var<0>, Int<0> >,
                                                           Int<1>,
                                                           Mul< Var<0>,
                                                                Call< Call< Var<1>, Var<1> >,
                                                                      Add< Var<0>, Int<-1> > > > > > > >,
                       Int<6> > >::value::value;
    cout<<endl;

    // ----------------------------------------------------------------------------------------
    // call/cc
    cout<<endl;
    cout<<"(((call/cc (lambda (k) k)) (lambda (k) k)) 3)              = "; // 3
    cout<< Eval< Call< Call< CallCC< Lambda< ParamList< Var<0> >,
                                             Var<0> > >,
                             Lambda< ParamList< Var<0> >,
                                     Var<0> > >,
                       Int<3> > >::value::value;
    cout<<endl;

    // call/cc
    cout<<"((lambda (k) (k (lambda (k) 2))) (call/cc (lambda (k) k))) = "; // 2
    cout<< Eval< Call< Lambda< ParamList< Var<0> >,
                               Call< Var<0>,
                                     Lambda< ParamList< Var<0> >,
                                             Int<2> > > >,
                       CallCC< Lambda< ParamList< Var<0> >,
                                       Var<0> > > > >::value::value;
    cout<<endl;

    return 0;
}