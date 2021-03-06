#pragma once

#include <armadillo>
#include <iostream>

typedef double (*FnCallback)(double x, double y);

/// Abstract class for a functor that takes (x,y) coordinates and return a function value
struct FnFunctor
{
    virtual double operator()(double x, double y) const = 0;
    
    FnFunctor() {};
    //FnFunctor(const FnFunctor &fn) { };
    
    virtual ~FnFunctor() {};
};

/// Functor that wraps a basic callback function
struct FnCallbackFunctor : FnFunctor
{   
    FnCallback cb;
    
    FnCallbackFunctor(FnCallback fn) : cb(fn) { }
    
    double operator()(double x, double y) const
    {
        return cb(x, y);
    }
};

/// Abstract class for a functor that takes (x,y) coordinates and returns a vector
struct VecFunctor
{
    int n_rows = 1;
    int n_cols = 1;
    // allow for time-dependency with this variable t
    double t = 0;
    
    //VecFunctor() { };
    VecFunctor(int a_n_rows, int a_n_cols = 1) : n_rows(a_n_rows), n_cols(a_n_cols) { };
    
    virtual arma::mat operator()(double x, double y) const = 0;
    virtual ~VecFunctor() {};
};

struct VecFnFunctor : VecFunctor
{
    const FnFunctor &fncb;
    VecFnFunctor(const FnFunctor &fn) : VecFunctor(1), fncb(fn) { };
    
    arma::mat operator()(double x, double y) const
    {
        return arma::vec::fixed<1>({fncb(x, y)});
    }
};

/// Functor that wraps a basic callback function
struct VecFnCallbackFunctor : VecFunctor
{   
    FnCallback cb;
    
    VecFnCallbackFunctor(FnCallback fn) : VecFunctor(1), cb(fn) { }
    
    arma::mat operator()(double x, double y) const
    {
        arma::vec::fixed<1> result;
        result(0) = cb(x, y);
        return result;
    }
};
