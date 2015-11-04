#ifndef TPL_LIB_H
#define TPL_LIB_H

#include "expression.hpp"

namespace TPL
{
    namespace Lib
    {
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
        // _Reduce = lambda List. lambda Op. lambda Init. List==Nil ? Init : Fst(list) Op (((_Reduce Snd(list)) Op) Init)
        // F = lambda f. lambda List. lambda Op. lambda Init. List==Nil ? Init : (Op Fst(list) (((f Snd(list)) Op) Init))
        // _Reduce = (Y F)
        typedef Call< YCombinater, Lambda< ParamList< Var<0> >, // f
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
                _Reduce;
        // Reduce = lambda List Op Init. (((_Reduce, List) Op) Init)
        typedef Lambda< ParamList< Var<0>, Var<1>, Var<2> >,
                        Call< Call< Call< _Reduce, Var<0> >,
                                    Var<1> >,
                              Var<2> > >
                Reduce;

        // ----------------------------------------------------
        // _Map = lambda List. lambda Op. List==Nil ? Nil : (Pair (Op Fst(List)) ((_Map Snd(List)) Op)
        // _Map = lambda List. lambda Op. (Reduce List lambda x y. Pair((Op x) y)) Nil)
        typedef Lambda< ParamList< Var<0> >, // List
                        Lambda< ParamList< Var<1> >, //Op
                                Call< Reduce,
                                      Var<0>,
                                      Lambda< ParamList< Var<2>, Var<3> >,
                                              Pair< Call< Var<1>, Var<2> >,
                                                    Var<3> > >,
                                      Unit > > >
                _Map;
        // Map = lambda List Op. ((_Map List) Op)
        typedef Lambda< ParamList< Var<0>, Var<1> >,
                        Call< Call< _Map, Var<0> >,
                              Var<1> > >
                Map;

        // ----------------------------------------------------
        // _Filter = lambda List. lambda Cond. List==Nil ? Nil :
        //                                                 (Cond Fst(List))==true ? Pair(Fst(List),
        //                                                                               ((_Filter Snd(List)) Cond)) :
        //                                                                          ((_Filter Snd(List)) Cond)
        //F = lambda f. lambda List. lambda Cond. List==Nil ? Nil :
        //                                                   (Cond Fst(List))==true ? Pair(Fst(List),
        //                                                                                 ((f Snd(List)) Cond)) :
        //                                                                          ((f Snd(List)) Cond)
        // _Filter = (Y F)
        typedef Call< YCombinater,
                      Lambda< ParamList< Var<0> >, // f
                              Lambda< ParamList< Var<1> >, // List
                                      Lambda< ParamList< Var<2> >, // Cond
                                              If_Then_Else< IsUnit< Var<1> >,
                                                            Unit,
                                                            If_Then_Else< Call< Var<2>, Fst< Var<1> > >,
                                                                          Pair< Fst< Var<1> >,
                                                                                Call< Call< Var<0>, Snd< Var<1> > >,
                                                                                      Var<2> > >,
                                                                          Call< Call< Var<0>, Snd< Var<1> > >,
                                                                                Var<2> > > > > > > >
                _Filter;
        // Filter = lambda List Cond. ((_Filter List) Cond)
        typedef Lambda< ParamList< Var<0>, Var<1> >,
                        Call< Call< _Filter, Var<0> >,
                              Var<1> > >
                Filter;

        //-----------------------------------------------------
        // _Range = lambda x. lambda y. x<y ? Nil : Pair(x ((_Range x-1) y))
        // F = lambda f. lambda x. lambda y. x>y ? Nil : Pair(x ((f x+1) y))
        // _Range = (Y F)
        typedef Call< YCombinater, Lambda< ParamList< Var<0> >, // f
                                           Lambda< ParamList< Var<1> >, // x
                                                   Lambda< ParamList< Var<2> >, // y
                                                           If_Then_Else< IsGreater< Var<1>, Var<2> >,
                                                                         Unit,
                                                                         Pair< Var<1>,
                                                                               Call< Call< Var<0>,
                                                                                           Add< Var<1>, Int<1> > >,
                                                                                     Var<2> > > > > > > >
                _Range;
        // Range = lambda x y. ((_Range x) y)
        typedef Lambda< ParamList< Var<0>, Var<1> >,
                        Call< Call< _Range, Var<0> >,
                              Var<1> > >
                Range;

        // -----------------------------------------------------------------------
        // Sum = lambda List. (((Reduce List) lambda x y. Add(x, y)) 0)
        typedef Lambda< ParamList< Var<0> >, // List
                        Call< Reduce,
                              Var<0>,
                              Lambda< ParamList< Var<2>, Var<1> >,
                                      Add< Var<2>, Var<1> > >,
                              Int<0> > >
                Sum;

        // -----------------------------------------------------------------------
        // IsList = lambda L. IsPair(L) ? IsList(Snd(L)) : IsUnit(L)
        // F = lambda f. lambda L. IsPair(L) ? f(Snd(L)) : IsUnit(L)
        // IsList = (Y F)
        typedef Call< YCombinater, Lambda< ParamList< Var<0> >, // f
                                           Lambda< ParamList< Var<1> >, // L
                                                   If_Then_Else< IsPair< Var<1> >,
                                                                 Call< Var<0>, Snd< Var<1> > >,
                                                                 IsUnit< Var<1> > > > > >
                IsList;

        // -----------------------------------------------------------------------
        // _ListRef = lambda L. lambda N. N==0 ? Fst(L) : ((_ListRef Snd(L)) N-1)
        // F = lambda f. lambda L. lambda N. N==0 ? Fst(L) : ((f Snd(L)) N-1)
        // _ListRef = (Y F)
        typedef Call< YCombinater, Lambda< ParamList< Var<0> >, // f
                                           Lambda< ParamList< Var<1> >, // L
                                                   Lambda< ParamList< Var<2> >, // N
                                                           If_Then_Else< IsEqual< Var<2>, Int<0> >,
                                                                         Fst< Var<1> >,
                                                                         Call< Call< Var<0>,
                                                                                     Snd< Var<1> > >,
                                                                               Add< Var<2>, Int<-1> > > > > > > >
                _ListRef;
        // ListRef = lambda L N. ((_ListRef L) N)
        typedef Lambda< ParamList< Var<0>, Var<1> >,
                        Call< Call< _ListRef, Var<0> >,
                              Var<1> > >
                ListRef;

        // ------------------------------------------------------------------------
        // _ListAppend = lambda L. lambda E. IsUnit(L) ? Pair<E, Unit> : Pair< Fst(L), ((_ListAppend Snd(L)) E) >
        // F = lambda f. lambda L. lambda E. IsUnit(L) ? Pair<E, Unit> : Pair< Fst(L), ((f Snd(L)) E) >
        // _ListAppend = (Y F)
        typedef Call< YCombinater, Lambda< ParamList< Var<0> >, // f
                                           Lambda< ParamList< Var<1> >, // L
                                                   Lambda< ParamList< Var<2> >, // E
                                                           If_Then_Else< IsUnit< Var<1> >,
                                                                         Pair< Var<2>, Unit >,
                                                                         Pair< Fst< Var<1> >,
                                                                               Call< Call< Var<0>,
                                                                                           Snd< Var<1> > >,
                                                                                     Var<2> > > > > > > >
                _ListAppend;
        // ListAppend = lambda L E. ((_ListAppend L) E)
        typedef Lambda< ParamList< Var<0>, Var<1> >,
                        Call< Call< _ListAppend, Var<0> >,
                              Var<1> > >
                ListAppend;

    } // namespace Lib

} // namespace TPL

#endif // TPL_LIB_H