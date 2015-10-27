#ifndef UTILS_H_
#define UTILS_H_

namespace CYTL
{
    namespace UTIL
    {
        template<bool> struct ComileTimeCheck;
        template<> struct ComileTimeCheck<true> {};

        template<class T1, class T2>
        struct StaticCheckEQ;
        template<class T> struct StaticCheckEQ<T, T> {};
    }
}

#endif //UTILS_H_