#include "utils.hpp"

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

namespace TPL
{
    using CYTL::UTIL::enable_if;
    using CYTL::UTIL::EmptyType;
    using CYTL::UTIL::Select;
    using CYTL::UTIL::IsEQ;


    // ------------------------------------------
    // VarValList
    struct EmptyVarValList;
    template<class Varible, class Val, class Tail> struct VarValList;
    template<class Varible, class Val>
    struct VarValList<Varible, Val, EmptyVarValList>;

    // VarValListExtend
    template<class Varible, class Val, class L>
    struct VarValListExtend
    { typedef VarValList<Varible, Val, L> value; };

    // VarValListLookup
    template<class V, class L> struct VarValListLookup;
    template<class V, class Varible, class Val, class Tail> // Search next Node
    struct VarValListLookup< V, VarValList<Varible, Val, Tail> >
    { typedef typename VarValListLookup<V, Tail>::value value; };
    template<class V, class Val, class Tail> // V found
    struct VarValListLookup< V, VarValList<V, Val, Tail> >
    { typedef Val value; };
    template<class V> // till the end, nothing is found
    struct VarValListLookup<V, EmptyVarValList>
    { typedef EmptyType value; };



    // -------------------------------------------------
    // Env
    struct EmptyEnv;
    template<class Head, class Tail> struct Env;
    template<class T> struct Env<T, EmptyEnv>;

    // EnvExtend
    template<class Head, class E>
    struct EnvExtend
    { typedef Env<Head, E> value; };

    // EnvLookup
    template<class V, class E> struct EnvLookup;
    template<class V, class L, class ETail>
    struct EnvLookup< V, Env<L, ETail> >
    {
        typedef typename VarValListLookup<V, L>::value ResultType;
        typedef typename Select< IsEQ<ResultType, EmptyType>::value,
                                 typename EnvLookup<V, ETail>::value,
                                 ResultType >::value
                value;
    };
    template<class V> // till the end, nothing is found
    struct EnvLookup<V, EmptyEnv>
    { typedef EmptyType value; };



    //------------------------------------------------
    // Eval
    template<class Exp, class Environ> struct EvalUnderEnv;

    template<class Exp> struct Eval
    { typedef typename EvalUnderEnv<Exp, EmptyEnv>::value value; };



    // ------------------------------------------------
    // Basic Data Type
    template<int N> struct Int;
    template<bool B> struct Bool;
    template<int N> struct Var;
    struct Unit;

    template<int N, class Environ>
    struct EvalUnderEnv< Int<N>, Environ >
    { typedef Int<N> value; };
    template<bool B, class Environ>
    struct EvalUnderEnv< Bool<B>, Environ >
    { typedef Bool<B> value; };
    template<int N, class Environ>
    struct EvalUnderEnv< Var<N>, Environ >
    { typedef Var<N> value; };
    template<class Environ>
    struct EvalUnderEnv< Unit, Environ >
    { typedef Unit value; };



    // -----------------------------
    // Add
    template<class T1, class T2> struct Add;

    template<int N1, int N2, class Environ>
    struct EvalUnderEnv< Add< Int<N1>, Int<N2> >, Environ >
    { typedef Int<N1+N2> value; };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< Add<T1, T2>, Environ >
    {
        typedef typename EvalUnderEnv<T1, Environ>::value T1Val;
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef typename EvalUnderEnv<Add<T1Val, T2Val>, Environ>::value value;
    };



    // ----------------------------------
    // Comparing

    // >
    template<class T1, class T2> struct IsGreater;

    template<int N1, int N2, class Environ>
    struct EvalUnderEnv< IsGreater< Int<N1>, Int<N2> >, Environ >
    { typedef Bool<(N1>N2)> value; };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< IsGreater<T1, T2>, Environ >
    {
        typedef typename EvalUnderEnv<T1, Environ>::value T1Val;
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef typename EvalUnderEnv<IsGreater<T1Val, T2Val>, Environ>::value value;
    };

    // <
    template<class T1, class T2> struct IsLess;

    template<int N1, int N2, class Environ>
    struct EvalUnderEnv< IsLess< Int<N1>, Int<N2> >, Environ >
    { typedef Bool<(N1<N2)> value; };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< IsLess<T1, T2>, Environ >
    {
        typedef typename EvalUnderEnv<T1, Environ>::value T1Val;
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef typename EvalUnderEnv<IsLess<T1Val, T2Val>, Environ>::value value;
    };

    // ==
    template<class T1, class T2> struct IsEqual;

    template<int N1, int N2, class Environ>
    struct EvalUnderEnv< IsEqual< Int<N1>, Int<N2> >, Environ >
    { typedef Bool<(N1==N2)> value; };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< IsEqual<T1, T2>, Environ >
    {
        typedef typename EvalUnderEnv<T1, Environ>::value T1Val;
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef typename EvalUnderEnv<IsEqual<T1Val, T2Val>, Environ>::value value;
    };

    // IsUnit
    template<class T> struct IsUnit;

    template<class Environ>
    struct EvalUnderEnv< IsUnit<Unit>, Environ >
    { typedef Bool<true> value; };
    template<class T, class Environ>
    struct EvalUnderEnv< IsUnit<T>, Environ >
    {
        typedef typename EvalUnderEnv<T, Environ>::value TVal;
        typedef typename Select< IsEQ<TVal, Unit>::value,
                                 Bool<true>,
                                 Bool<false> >::value
                 value;
    };



    // ------------------------------------
    // Pair type
    template<class T1, class T2> struct Pair;

    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< Pair<T1, T2>, Environ >
    {
        typedef typename EvalUnderEnv<T1, Environ>::value T1Val;
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef Pair<T1Val, T2Val> value;
    };
    
    // Pair.1
    template<class T>struct Fst;

    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< Fst< Pair<T1, T2> >, Environ >
    { typedef T1 value; };
    template<class T, class Environ>
    struct EvalUnderEnv< Fst<T>, Environ >
    {
        typedef typename EvalUnderEnv<T, Environ>::value TVal;
        typedef typename EvalUnderEnv< Fst<TVal>, Environ >::value value;
    };

    // Pair.2
    template<class T>struct Snd;

    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< Snd< Pair<T1, T2> >, Environ >
    { typedef T2 value; };
    template<class T, class Environ>
    struct EvalUnderEnv< Snd<T>, Environ >
    {
        typedef typename EvalUnderEnv<T, Environ>::value TVal;
        typedef typename EvalUnderEnv< Snd<TVal>, Environ >::value value;
    };



    // -----------------------------------
    // List type
    template<class... T_Rest> struct List;

    template<class T, class... T_Rest, class Environ>
    struct EvalUnderEnv< List<T, T_Rest...>, Environ >
    {
        static const int ArgsNum = sizeof...(T_Rest) + 1;
        typedef typename EvalUnderEnv<T, Environ>::value TVal;

        typedef typename Select< ArgsNum == 1,
                                 Unit,
                                 List<T_Rest...> >::value
                TailType;
        typedef Pair< TVal, typename EvalUnderEnv< TailType, Environ >::value > value;
    };


    //IsList
    template<class T> 
    struct IsList
    { static const bool MayBeList = false; };
    template<class T1, class T2> 
    struct IsList< Pair<T1, T2> >
    { static const bool MayBeList = true; };
    template<> 
    struct IsList<Unit>
    { static const bool MayBeList = true; };

    template<class T, class Environ>
    struct EvalUnderEnv< IsList<T>, Environ >
    {
        typedef typename EvalUnderEnv<T, Environ>::value TVal;
        typedef typename Select< IsList<TVal>::MayBeList,
                                 TVal,
                                 EmptyType >::value
                TmpType;
        typedef typename EvalUnderEnv< IsList<TmpType>, Environ >::value value;
    };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< IsList< Pair<T1, T2> >, Environ >
    {
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef typename EvalUnderEnv< IsList<T2Val>, Environ >::value value;
    };
    template<class T, class Environ>
    struct EvalUnderEnv< IsList< Pair<T, Unit> >, Environ >
    { typedef Bool<true> value; };
    template<class Environ>
    struct EvalUnderEnv< IsList<Unit>, Environ >
    { typedef Bool<true> value; };
    template<class Environ>
    struct EvalUnderEnv< IsList< EmptyType >, Environ >
    { typedef Bool<false> value; };
    

    // List.N
    template<class T, class N> 
    struct ListRef
    { static const bool MayBeList = false; };
    template<class T1, class T2, int N> 
    struct ListRef< Pair<T1, T2>, Int<N> >
    { static const bool MayBeList = true; };

    template<class T, class N, class Environ>
    struct EvalUnderEnv< ListRef<T, N>, Environ >
    {
        typedef typename EvalUnderEnv<T, Environ>::value TVal;
        typedef typename EvalUnderEnv<N, Environ>::value Num;

        typedef typename Select< ListRef<TVal, Num>::MayBeList,
                                 TVal,
                                 EmptyType >::value
                TmpType;
        typedef typename EvalUnderEnv< ListRef<TmpType, Num>, Environ >::value value;
    };
    template<class T1, class T2, int N, class Environ>
    struct EvalUnderEnv< ListRef< Pair<T1, T2>, Int<N> >, Environ >
    {
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef typename EvalUnderEnv< ListRef< T2Val, Int<N - 1> >, Environ>::value value;
    };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< ListRef< Pair<T1, T2>, Int<0> >, Environ >
    {
        typedef typename EvalUnderEnv< IsList<T2>, Environ>::value IsT2List;
        typedef typename enable_if< IsEQ< IsT2List,
                                          Bool<true> >::value,
                                    IsT2List >::type
                         ISLIST;

        typedef typename EvalUnderEnv<T1, Environ>::value value;
    };
    template<class N, class Environ>
    struct EvalUnderEnv< ListRef< EmptyType, N >, Environ >
    { typedef Bool<false> value; };
    

    // ListAppend
    template<class L, class NewT> struct ListAppend;

    template<class T, class NewT, class Environ>
    struct EvalUnderEnv< ListAppend<T, NewT>, Environ >
    {
        typedef typename EvalUnderEnv<T, Environ>::value TVal;
        typedef typename EvalUnderEnv<NewT, Environ>::value NewTVal;
        typedef typename EvalUnderEnv< ListAppend<TVal, NewTVal>, Environ >::value value;
    };
    template<class H, class T, class NewT, class Environ>
    struct EvalUnderEnv< ListAppend<Pair<H, T>, NewT>, Environ >
    { 
        typedef typename EvalUnderEnv<H, Environ>::value HVal;
        typedef typename EvalUnderEnv<T, Environ>::value TVal;
        typedef typename EvalUnderEnv<NewT, Environ>::value NewTVal;
        typedef Pair< HVal, 
                      typename EvalUnderEnv< ListAppend<TVal, NewTVal>, Environ >::value > 
                value;
    };
    template<class NewT, class Environ>
    struct EvalUnderEnv< ListAppend<Unit, NewT>, Environ >
    {
        typedef typename EvalUnderEnv<NewT, Environ>::value NewTVal;
        typedef Pair<NewTVal, Unit> value;
    };
    
    

    // ------------------------------------
    // if-then-else
    template<class Cond, class T1, class T2> struct If_Then_Else;

    template<class Cond, class T1, class T2, class Environ>
    struct EvalUnderEnv< If_Then_Else<Cond, T1, T2>, Environ >
    {
        typedef typename EvalUnderEnv<Cond, Environ>::value CondVal;
        typedef typename EvalUnderEnv< If_Then_Else<CondVal, T1, T2>, Environ >::value value;
    };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< If_Then_Else<Bool<true>, T1, T2>, Environ >
    { 
        typedef typename EvalUnderEnv<T1, Environ>::value T1Val;
        typedef T1Val value;
    };
    template<class T1, class T2, class Environ>
    struct EvalUnderEnv< If_Then_Else<Bool<false>, T1, T2>, Environ >
    {
        typedef typename EvalUnderEnv<T2, Environ>::value T2Val;
        typedef T2Val value;
    };
}

#endif //EVALUATOR_H_