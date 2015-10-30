#include "expression.hpp"
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

    cout<<"4 > 5 : ";
    cout<< Eval< IsGreater< Int<4>, Int<5> > >::value::value;
    cout<<endl;
    cout<<"4 < 5 : ";
    cout<< Eval< IsLess< Int<4>, Int<5> > >::value::value;
    cout<<endl;
    cout<<"4 = 4 : ";
    cout<< Eval< IsEqual< Int<4>, Int<5> > >::value::value;
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
    cout<< Eval< IsList< Pair< Int<4>, Int<5> > > >::value::value;
    cout<<endl;
    cout<<"The num at index 2 of List<0, 1, 2, 3>                  : ";
    cout<< Eval< ListRef< List< Int<0>, Int<1>, Int<2>, Int<3> >, Int<2> > >::value::value;
    cout<<endl;
    cout<<"The num at index 4 of ListAppend< List<0, 1, 2, 3>, 9 > : ";
    cout<< Eval< ListRef< ListAppend< List< Int<0>, Int<1>, Int<2>, Int<3> >, Int<9> >, Int<4> > >::value::value;
    cout<<endl;

    cout<<endl;
    cout<<"If 4<5 then 4+5 else 4-5 = ";
    cout<< Eval< If_Then_Else< IsLess< Int<4>, Int<5> >,
                               Add< Int<4>, Int<5> >,
                               Add< Int<4>, Int<-5> > > >::value::value;
    cout<<endl;

    cout<<endl;
    cout<<"Multi-Parameter Lambda:"<<endl;
    cout<<"(lambda x y z. x+y*z 2 3 4) = ";
    cout<< Eval< Call< Lambda< ParamList< Var<0>, Var<1>, Var<2> >,
                               Add< Var<0>, Mul< Var<1>, Var<2> > > >,
                       Int<2>, Int<3>, Int<4> > >::value::value;
    cout<<endl;

    // ----------------------------------------------------------------------------------------
    // anonymous recursion, Factorial, F = lambda f. lambda n. n==0 ? 1 : n*( (f f) (n-1) )
    // ( (F F) n ) = n!
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
    // Y Combinator, lambda f. (lambda x. (f lambda y. ((x x) y))
    //                          lambda x. (f lambda y. ((x x) y)))
    typedef Lambda< ParamList< Var<0> >,
                    Call< Lambda< ParamList< Var<1> >,
                                  Call< Var<0>,
                                        Lambda< ParamList< Var<2> >,
                                                Call< Call< Var<1>, Var<1> >,
                                                      Var<2> > > > >,
                          Lambda< ParamList< Var<1> >,
                                  Call< Var<0>,
                                        Lambda< ParamList< Var<2> >,
                                                Call< Call< Var<1>, Var<1> >,
                                                      Var<2> > > > > > >
            YCombinater;

    // ---------------------------------------------------
    // Reduce = lambda List. lambda Op. lambda Init. List==Nil ? Init : Fst(list) Op (((Reduce Snd(list)) Op) Init)
    // F = lambda f. lambda List. lambda Op. lambda Init. List==Nil ? Init : (Op Fst(list) (((f Snd(list)) Op) Init))
    // Reduce = (Y F)
    typedef Call<YCombinater, Lambda< ParamList< Var<0> >, // f
                                      Lambda< ParamList< Var<1> >, // List
                                              Lambda< ParamList< Var<2> >, // Op
                                                      Lambda< ParamList< Var<3> >, // Init
                                                              If_Then_Else< IsUnit< Var<1> >,
                                                                            Var<3>,
                                                                            Call< Var<2>,
                                                                                  Fst< Var<1> >,
                                                                                  Call< Call< Call< Var<0>,
                                                                                                    Snd< Var<1> > >,
                                                                                              Var<2> >,
                                                                                        Var<3> > > > > > > > >
            Reduce;

    // -----------------------------------------------------------------------
    // Sum = lambda List. (((Reduce List) lambda x y. Add(x, y)) 0)
    typedef Lambda< ParamList< Var<0> >, // List
                    Call< Call< Call< Reduce, Var<0> >,
                                Lambda< ParamList< Var<2>, Var<1> >,
                                        Add< Var<2>, Var<1> > > >,
                          Int<0> > >
            Sum;

    // ------------------------------------------------------------------
    cout<<endl;
    cout<<"Sum the List that contains 1 to 5 using Reduce:"<<endl;
    cout<<"Sum(1 ... 5) = ";
    cout<< Eval< Call< Sum, List< Int<1>, Int<2>, Int<3>, Int<4>, Int<5> > > >::value::value;
    cout<<endl;

    // ------------------------------------------------------
    // F = lambda f. lambda n. n==0 ? 1 : n*(f n-1)
    // (Fact 5) = ((Y F) 5)
    cout<<endl;
    cout<<"Caculate Factorial(5) with Y-Combinator:"<<endl;
    cout<<"Fact(5) = ";
    cout<< Eval< Call< Call< YCombinater,
                             Lambda< ParamList< Var<0> >, // F
                                     Lambda< ParamList< Var<1> >,
                                             If_Then_Else< IsEqual< Var<1>, Int<0> >,
                                                           Int<1>,
                                                           Mul< Var<1>,
                                                                Call< Var<0>,
                                                                      Add< Var<1>, Int<-1> > > > > > > >,
                       Int<5> > >::value::value; // (Fact 5)
    cout<<endl;

    return 0;
}