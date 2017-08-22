#ifndef ARGLIST_H
#define ARGLIST_H

#include "typelist.h"

namespace utils {

template<typename... Types>
class ArgList;

template<typename THead>
class ArgList<THead>
{
public:
  ArgList(const THead& aHead) :  iHead(aHead) {}
  const THead& Head() const { return iHead; }
private:
  const THead iHead;
};

template<typename THead, typename... TTail>
class ArgList<THead, TTail...> : public ArgList<TTail...>
{
public:
  typedef ArgList<TTail...> TSuper;
  ArgList(const THead& aHead, const TTail&... aTail) : TSuper(aTail...), iHead(aHead) {}
  const THead& Head() const { return iHead; }
private:
  const THead iHead;
};

template<typename... Types>
ArgList<Types...> CreateArgList(const Types&... aTypes)
{
  return ArgList<Types...>(aTypes...);
}

// Get object at position n in ArgList.
template<int n, typename THead, typename... TTail>
typename std::enable_if<n != 0, typename TypeAtIndex<n, TypeList<THead, TTail...> >::TResult>::type ExtractAtIndex(const ArgList<THead, TTail...>& aList)
{
  static_assert(!EqualTypes<void, typename TypeAtIndex<n, TypeList<THead, TTail...> >::TResult>::TResult, "Index out of bounds!");
  return ExtractAtIndex<n-1, TTail...>(static_cast<typename ArgList<THead, TTail...>::TSuper>(aList));
}

template<int n, typename THead, typename... TTail>
typename std::enable_if<n == 0, THead>::type ExtractAtIndex(const ArgList<THead, TTail...>& aList)
{
  return aList.Head();
}

// Get first element of specified type from ArgList, or retrun default-constructed object of specified type.
template<typename TWanted, typename THead, typename... TTail>
typename std::enable_if<EqualTypes<TWanted, THead>::TResult, TWanted>::type Extract(const ArgList<THead, TTail...>& aList)
{
  return aList.Head();
}

template<typename TWanted, typename THead, typename... TTail>
typename std::enable_if<!ContainsType<TWanted, TypeList<THead, TTail...> >::TResult, TWanted>::type Extract(const ArgList<THead, TTail...>& aList)
{
  return TWanted();
}

template<typename TWanted, typename THead, typename... TTail>
typename std::enable_if<!EqualTypes<TWanted, THead>::TResult && ContainsType<TWanted, TypeList<TTail...> >::TResult, TWanted>::type Extract(const ArgList<THead, TTail...>& aList)
{
  return Extract<TWanted, TTail...>(static_cast<typename ArgList<THead, TTail...>::TSuper>(aList));
}

} // namespace utils

#endif // ARGLIST_H
