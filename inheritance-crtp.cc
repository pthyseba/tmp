#include <iostream>

template<typename taMostDerived>
struct Base
{
   typedef taMostDerived TUnderlying;

   struct Data
   {};

   TUnderlying& Top()
   {
      return static_cast<TUnderlying&>(*this);
   }

   void Process()
   {
      typedef typename TUnderlying::Data Data;
      Data d;      
      Top().Action(d);
   }

 protected:
   void Action(Data& aData) {}
};


// Functional layer examples
template<typename taParent>
struct Layer1 : public taParent
{
  typedef taParent TSuper;

  struct Data : public TSuper::Data
  {
     int iElement1;
  };

  void Action(Data& aData)
  {
    TSuper::Action(aData);
    aData.iElement1 = 1;
    std::cout << "Layer1::Action()" << std::endl;
  }
};

template<typename taParent>
struct Layer2 : public taParent
{
  typedef taParent TSuper;	
  
  struct Data : public TSuper::Data
  {
    int iElement2;
  };

  void Action(Data& aData)
  {
     TSuper::Action(aData);
     aData.iElement2 = 2;
     std::cout << "Layer2::Action()" << std::endl;
  }	  
};

// Recursive helper class template
template<typename taMostDerived, template<class...T> typename taTopLayer, template<class... T> typename... taOtherLayers>
struct RecursiveLinearInherit : public taTopLayer<RecursiveLinearInherit<taMostDerived, taOtherLayers...>>
{};

// Recursive helper class template: base case
template<typename taMostDerived, template<class...T> typename taTopLayer>
struct RecursiveLinearInherit<taMostDerived, taTopLayer> : public taTopLayer<Base<taMostDerived>>
{};

template<template<class...T> typename taTopLayer, template<class... T> typename... taOtherLayers>
struct LinearInherit : public taTopLayer<RecursiveLinearInherit<LinearInherit<taTopLayer, taOtherLayers...>, taOtherLayers...> >
{};

// Specialization for single layer
template<template<class...T> typename taTopLayer>
struct LinearInherit<taTopLayer> : public taTopLayer<Base<LinearInherit<taTopLayer>>>
{};

int main(int argc, char** argv)
{
  typedef LinearInherit<Layer2, Layer1> TProduct;
  TProduct p;
	
  p.Process();
  
  return 0;
}

