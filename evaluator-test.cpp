#include "evaluator.hpp"
#include "utils.hpp"


using namespace TPL;
using namespace CYTL;
using UTIL::StaticCheckEQ;
using UTIL::ComileTimeCheck;


int main()
{
    // -------------------------------------------------------
    // Add Testing
    StaticCheckEQ< Add< Int<1>, Int<3> >::value, Int<4> >();
    StaticCheckEQ< Add< Int<-9>, Int<45> >::value, Int<36> >();


    // -------------------------------------------------------
    // Comparing Testing
    StaticCheckEQ< IsGreater< Int<5>, Int<8> >::value, Bool<false> >();
    StaticCheckEQ< IsLess< Int<5>, Int<8> >::value, Bool<true> >();
    StaticCheckEQ< IsEqual< Int<8>, Int<8> >::value, Bool<true> >();


    // -------------------------------------------------------
    // Pair Testing
    typedef Pair< Pair< Int<4>, Bool<true> >,
                  Pair< Pair<Int<2>, Unit>, 
                        Bool<false> > > 
            P;
    StaticCheckEQ< Fst< Fst<P>::value >::value, Int<4> >();
    StaticCheckEQ< Snd< Fst< Snd<P>::value >::value >::value, Unit >();
    StaticCheckEQ< Snd< Snd<P>::value >::value, Bool<false> >();


    // -------------------------------------------------------
    // List Testing
    typedef List< List< Int<2>, Bool<false> >::value, 
                  List< Int<4>, Bool<true> >::value, 
                  List< Int<6> >::value >::value
            L1;
    typedef Pair< Pair< Int<2>, Pair<Bool<false>, Unit> >, 
                  Pair< Pair< Int<4>, Pair<Bool<true>, Unit> >,
                        Pair< Pair<Int<6>, Unit>,
                              Unit > > >
            P1;
    StaticCheckEQ<L1, P1>();

    // IsList
    ComileTimeCheck< IsList<L1>::value >();    
    ComileTimeCheck< IsList<P1>::value >();
    ComileTimeCheck< IsList<Unit>::value >();
    ComileTimeCheck< IsList< Snd<Snd<P1>::value>::value >::value >();
    
    // List.N
    typedef List< Int<0>, Int<1>, Int<2>, Int<3>, Int<4> >::value L3;
    StaticCheckEQ< ListRef< L3, Int<2> >::value, Int<2> >();
    StaticCheckEQ< ListRef< ListRef< L1, Int<0> >::value, Int<0> >::value, Int<2> >(); 

    // ListAppend
    typedef List< Int<0>, Int<1>, Int<2>, Int<3>, Int<4>, Int<5> >::value L4;
    StaticCheckEQ< ListAppend< L3, Int<5> >::value, L4 >();
    StaticCheckEQ< ListAppend< ListAppend< L3, Int<5> >::value, List< Int<9> > >, 
                   ListAppend< L4, List< Int<9> > > >();


    // -------------------------------------------------------
    // if-then-else Testing
    StaticCheckEQ< If_Then_Else< IsGreater< Int<5>, Int<8> >::value,
                                 L1,
                                 P>::value,
                    P >();
    StaticCheckEQ< If_Then_Else< IsLess< Int<5>, Int<8> >::value,
                                 L1,
                                 P>::value,
                   L1 >();


    // -----------------------------------------------------
    // VarValList
    typedef VarValList< Var<0>, Int<0>,
                        VarValList< Var<1>, Int<1>, EmptyVarValList > >
            VarValL0;
    typedef VarValList< Var<2>, Int<2>, 
                        VarValList< Var<0>, Int<0>,
                                    VarValList< Var<1>, Int<1>, 
                                                EmptyVarValList > > >
            VarValL1;
    StaticCheckEQ< VarValListExtend< Var<2>, Int<2>, VarValL0 >::value,
                   VarValL1 >;

    // VarValListLookup
    StaticCheckEQ< VarValListLookup<Var<2>, VarValL1>::value, Int<2> >();
    StaticCheckEQ< VarValListLookup<Var<0>, VarValL1>::value, Int<0> >();
    StaticCheckEQ< VarValListLookup<Var<1>, VarValL1>::value, Int<1> >();
    StaticCheckEQ< VarValListLookup<Var<3>, VarValL1>::value, UTIL::EmptyType >();

    return 0;
}