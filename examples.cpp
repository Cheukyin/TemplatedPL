#include "expression.hpp"
#include <iostream>

using namespace TPL;
using std::cout;
using std::endl;

int main()
{
    // Y Combinator, lambda f. (lambda x. (f lambda y. ((x x) y))
    //                          lambda x. (f lambda y. ((x x) y)))
    // F = lambda f. lambda n. n==0 ? 1 : n*(f n-1)
    // (Fact 5) = ((Y F) 5)
    cout<<endl;
    cout<<"Caculate Factorial(5) with Y-Combinator:"<<endl;
    cout<<"Fact(5) = ";
    cout<< Eval< Call< // Fact = (Y F)
                     Call<Lambda< ParamList< Var<0> >, // Y Combinator
                                  Call< Lambda< ParamList< Var<1> >,
                                                Call< Var<0>,
                                                      Lambda< ParamList< Var<2> >,
                                                              Call< Call< Var<1>, Var<1> >,
                                                                    Var<2> > > > >,
                                        Lambda< ParamList< Var<1> >,
                                                Call< Var<0>,
                                                      Lambda< ParamList< Var<2> >,
                                                              Call< Call< Var<1>, Var<1> >,
                                                                    Var<2> > > > > > >,
                          Lambda< ParamList< Var<0> >, // F
                                  Lambda< ParamList< Var<1> >,
                                          If_Then_Else< IsEqual< Var<1>, Int<0> >,
                                                        Int<1>,
                                                        Mul< Var<1>,
                                                             Call< Var<0>,
                                                                   Add< Var<1>, Int<-1> > > > > > > >,
                     Int<5> > >::value::value; // (Fact 5)
    cout<<endl;


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


    cout<<endl;
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

    return 0;
}