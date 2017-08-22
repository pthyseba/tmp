#ifndef TYPELIST_H
#define TYPELIST_H

#include "equaltypes.h"
#include <type_traits>

namespace utils {

template<typename... Types>
struct TypeList {};

template<typename SearchType, typename... Types>
struct ContainsType;

template<typename SearchType, typename Head, typename... Tail>
struct ContainsType<SearchType, TypeList<Head, Tail...> >
{
  const static bool TResult = EqualTypes<SearchType, Head>::TResult ? true : ContainsType<SearchType, TypeList<Tail...> >::TResult;  
};

template<typename SearchType, typename Head>
struct ContainsType<SearchType, TypeList<Head> >
{
  const static bool TResult = EqualTypes<SearchType, Head>::TResult ? true : false;  
};

template<int n, typename... Types>
struct TypeAtIndex;

template<int n>
struct TypeAtIndex<n, TypeList<> >
{
  typedef void TResult;
};

template<int n, typename Head, typename... Tail>
struct TypeAtIndex<n, TypeList<Head, Tail...> >
{
  typedef typename TypeAtIndex<n-1, TypeList<Tail...> >::TResult TResult;
};

template<typename Head, typename... Tail>
struct TypeAtIndex<0, TypeList<Head, Tail...> >
{
  typedef Head TResult;
};

template<typename... Types>
struct push_front;

template<typename TNewHead, typename... Types>
struct push_front<TNewHead, TypeList<Types...> >
{
  typedef TypeList<TNewHead, Types...> TResult;
};

template<typename... Types>
struct push_back;

template<typename TNewTail, typename... Types>
struct push_back<TNewTail, TypeList<Types...> >
{
  typedef TypeList<Types..., TNewTail> TResult;
};

// Get index of first element of specified type in TypeList
template<typename TWanted, typename... Types>
struct IndexOf;

template<typename TWanted, typename THead, typename... TTail>
struct IndexOf<TWanted, TypeList<THead, TTail...> >
{
  const static int TResult = !ContainsType<TWanted, TypeList<THead, TTail...> >::TResult ? -1 : (EqualTypes<TWanted, THead>::TResult ? 0 : 1 + IndexOf<TWanted, TypeList<TTail...> >::TResult);
};

template<typename TWanted, typename THead>
struct IndexOf<TWanted, TypeList<THead> >
{
  const static int TResult = EqualTypes<TWanted, THead>::TResult ? 0 : -1;
};

} // namespace utils

#endif // TYPELIST_H 
