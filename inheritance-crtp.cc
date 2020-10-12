#include <iostream>

template<typename taMostDerived>
struct Base
{
   typedef taMostDerived TUnderlying;

   TUnderlying& Top()
   {
      return static_cast<TUnderlying&>(*this);
   }

   void Process()
   {
      Top().Action();
   }

 protected:
   void Action() {}
};


template<typename taParent>
struct Layer1 : public taParent
{
  typedef taParent TSuper;

  void Action()
  {
    TSuper::Action();
    std::cout << "Layer1::Action()" << std::endl;
  }
};

template<typename taParent>
struct Layer2 : public taParent
{
  typedef taParent TSuper;	
  void Action()
  {
     TSuper::Action();
     std::cout << "Layer2::Action()" << std::endl;
  }	  
};

template<typename taMostDerived, template<class...T> typename taTopLayer, template<class... T> typename... taOtherLayers>
struct RecursiveLinearInherit : public taTopLayer<RecursiveLinearInherit<taMostDerived, taOtherLayers...>>
{};

template<typename taMostDerived, template<class...T> typename taTopLayer>
struct RecursiveLinearInherit<taMostDerived, taTopLayer> : public taTopLayer<Base<taMostDerived>>
{};

template<template<class...T> typename taTopLayer, template<class... T> typename... taOtherLayers>
struct LinearInherit : public taTopLayer<RecursiveLinearInherit<LinearInherit<taTopLayer, taOtherLayers...>, taOtherLayers...> >
{};

int main(int argc, char** argv)
{
  LinearInherit<Layer2,Layer1> l;
  l.Process();
  return 0;
}

