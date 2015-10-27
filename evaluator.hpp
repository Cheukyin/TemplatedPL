#include "utils.hpp"

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

namespace TPL
{
    using namespace CYTL::UTIL;

    // ----------------------------
    // Data Type
    template<int N> struct Int;
    template<bool B> struct Bool;


    // -----------------------------
    // Add
    template<class T1, class T2> struct Add;
    template<int N1, int N2>
    struct Add< Int<N1>, Int<N2> >
    { typedef Int<N1+N2> value; };


    // ----------------------------------
    // Comparing
    template<class T1, class T2> struct IsGreater;
    template<int N1, int N2>
    struct IsGreater< Int<N1>, Int<N2> >
    { typedef Bool<(N1>N2)> value; };

    template<class T1, class T2> struct IsLess;
    template<int N1, int N2>
    struct IsLess< Int<N1>, Int<N2> >
    { typedef Bool<(N1<N2)> value; };

    template<class T1, class T2> struct IsEqual;
    template<int N1, int N2>
    struct IsEqual< Int<N1>, Int<N2> >
    { typedef Bool<(N1==N2)> value; };


    // ------------------------------------
}

#endif //EVALUATOR_H_