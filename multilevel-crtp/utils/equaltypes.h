#ifndef EQUALTYPES_H
#define EQUALTYPES_H

namespace utils {

template<typename T1, typename T2>
struct EqualTypes
{
  const static bool TResult = false;
};

template<typename T1>
struct EqualTypes<T1, T1>
{
  const static bool TResult = true;
};

} // namespace utils

#endif // EQUALTYPES_H
