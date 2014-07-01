//
//  Mach7: Pattern Matching Library for C++
//
//  Copyright 2011-2013, Texas A&M University.
//  Copyright 2014 Yuriy Solodkyy.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//
//      * Neither the names of Mach7 project nor the names of its contributors
//        may be used to endorse or promote products derived from this software
//        without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

///
/// \file
///
/// This file is a part of Mach7 library test suite.
///
/// \author Yuriy Solodkyy <yuriy.solodkyy@gmail.com>
///
/// \see https://parasol.tamu.edu/mach7/
/// \see https://github.com/solodon4/Mach7
/// \see https://github.com/solodon4/SELL
///

#include <iostream>
#include <utility>
#include "../type_switchN-decl.hpp"

//------------------------------------------------------------------------------

typedef std::pair<double,double> loc;

//------------------------------------------------------------------------------

// An Algebraic Data Type implemented through inheritance
struct Shape
{
    virtual ~Shape() {}
};

//------------------------------------------------------------------------------

struct Circle : Shape
{
    Circle(const loc& c, const double& r) : center(c), radius(r) {}

    const loc& get_center() const { return center; }

    loc    center;
    double radius;
};

//------------------------------------------------------------------------------

struct Square : Shape
{
    Square(const loc& c, const double& s) : upper_left(c), side(s) {}

    loc    upper_left;
    double side;
};

//------------------------------------------------------------------------------

struct Triangle : Shape
{
    Triangle(const loc& a, const loc& b, const loc& c) : first(a), second(b), third(c) {}

    loc first;
    loc second;
    loc third;
};

//------------------------------------------------------------------------------

void do_match(const Shape* s0)
{
    const char* text = "unknown";

    Match(s0)
    {
    Case(const Circle&   a) text = "C"; break;
    Case(const Square&   a) text = "S"; break;
    Case(const Triangle& a) text = "T"; break;
    Otherwise()             text = "other"; break;
    }
    EndMatch

    std::cout << text << std::endl;
}

//------------------------------------------------------------------------------

void do_match(const Shape* s0, const Shape* s1)
{
    const char* text = "unknown";

    Match(s0,s1)
    {
  //Case(const Circle&   a, const Circle&   b) text = "C,C"; break;
    Case(const Circle&   a, const Square&   b) text = "C,S"; break;
    Case(const Square&   a, const Circle&   b) text = "S,C"; break;
  //Case(const Square&   a, const Square&   b) text = "S,S"; break;
    Case(const Square&   a, const Triangle& b) text = "S,T"; break;
    Case(const Triangle& a, const Square&   b) text = "T,S"; break;
    Case(const Triangle& a, const Triangle& b) text = "T,T"; break;
    Case(const Triangle& a, const Circle&   b) text = "T,C"; break;
    Case(const Circle&   a, const Triangle& b) text = "C,T"; break;
    Otherwise()                                text = "other"; break;
    }
    EndMatch

    std::cout << text << std::endl;
}

//------------------------------------------------------------------------------

void do_match(Shape* s0, const Shape* s1, const Shape* s2)
{
    const char* text = "unknown";

    Match(s0,s1,s2)
    {
    Case(Circle&   a, const Circle&   b, const Circle&   c) text = "C,C,C"; break;
    Case(Circle&   a, const Circle&   b, const Square&   c) text = "C,C,S"; break;
    Case(Circle&   a, const Square&   b, const Circle&   c) text = "C,S,C"; break;
    Case(Circle&   a, const Square&   b, const Square&   c) text = "C,S,S"; break;
    Case(Circle&   a, const Square&   b, const Triangle& c) text = "C,S,T"; break;
    Case(Circle&   a, const Triangle& b, const Square&   c) text = "C,T,S"; break;
    Case(Circle&   a, const Triangle& b, const Triangle& c) text = "C,T,T"; break;
    Case(Circle&   a, const Triangle& b, const Circle&   c) text = "C,T,C"; break;
    Case(Circle&   a, const Circle&   b, const Triangle& c) text = "C,C,T"; break;
                   
  //Case(Square&   a, const Circle&   b, const Circle&   c) text = "S,C,C"; break;
  //Case(Square&   a, const Circle&   b, const Square&   c) text = "S,C,S"; break;
    Case(Square&   a, const Square&   b, const Circle&   c) text = "S,S,C"; break;
    Case(Square&   a, const Square&   b, const Square&   c) text = "S,S,S"; break;
    Case(Square&   a, const Square&   b, const Triangle& c) text = "S,S,T"; break;
    Case(Square&   a, const Triangle& b, const Square&   c) text = "S,T,S"; break;
    Case(Square&   a, const Triangle& b, const Triangle& c) text = "S,T,T"; break;
    Case(Square&   a, const Triangle& b, const Circle&   c) text = "S,T,C"; break;
  //Case(Square&   a, const Circle&   b, const Triangle& c) text = "S,C,T"; break;

    Case(Triangle& a, const Circle&   b, const Circle&   c) text = "T,C,C"; break;
    Case(Triangle& a, const Circle&   b, const Square&   c) text = "T,C,S"; break;
    Case(Triangle& a, const Square&   b, const Circle&   c) text = "T,S,C"; break;
    Case(Triangle& a, const Square&   b, const Square&   c) text = "T,S,S"; break;
    Case(Triangle& a, const Square&   b, const Triangle& c) text = "T,S,T"; break;
    Case(Triangle& a, const Triangle& b, const Square&   c) text = "T,T,S"; break;
    Case(Triangle& a, const Triangle& b, const Triangle& c) text = "T,T,T"; break;
    Case(Triangle& a, const Triangle& b, const Circle&   c) text = "T,T,C"; break;
    Case(Triangle& a, const Circle&   b, const Triangle& c) text = "T,C,T"; break;

    Otherwise()                        text = "other"; break;
    }
    EndMatch

    std::cout << text << std::endl;
}

//------------------------------------------------------------------------------

void do_match(Shape* s0, Shape* s1, Shape* s2, Shape* s3)
{
    const char* text = "unknown";

    Match(s0,s1,s2,s3)
    {
    Case(Circle&   a, const Circle&   b, const Circle&   c, const Circle&   t) text = "C,C,C,C"; break;
    Case(Circle&   a, const Circle&   b, const Circle&   c, const Square&   t) text = "C,C,C,S"; break;
    Case(Circle&   a, const Circle&   b, const Square&   c, const Circle&   t) text = "C,C,S,C"; break;
    Case(Circle&   a, const Circle&   b, const Square&   c, const Square&   t) text = "C,C,S,S"; break;
    Case(Circle&   a, const Circle&   b, const Square&   c, const Triangle& t) text = "C,C,S,T"; break;
    Case(Circle&   a, const Circle&   b, const Triangle& c, const Square&   t) text = "C,C,T,S"; break;
    Case(Circle&   a, const Circle&   b, const Triangle& c, const Triangle& t) text = "C,C,T,T"; break;
    Case(Circle&   a, const Circle&   b, const Triangle& c, const Circle&   t) text = "C,C,T,C"; break;
    Case(Circle&   a, const Circle&   b, const Circle&   c, const Triangle& t) text = "C,C,C,T"; break;
                                                                   
    Case(Circle&   a, const Square&   b, const Circle&   c, const Circle&   t) text = "C,S,C,C"; break;
    Case(Circle&   a, const Square&   b, const Circle&   c, const Square&   t) text = "C,S,C,S"; break;
    Case(Circle&   a, const Square&   b, const Square&   c, const Circle&   t) text = "C,S,S,C"; break;
    Case(Circle&   a, const Square&   b, const Square&   c, const Square&   t) text = "C,S,S,S"; break;
    Case(Circle&   a, const Square&   b, const Square&   c, const Triangle& t) text = "C,S,S,T"; break;
    Case(Circle&   a, const Square&   b, const Triangle& c, const Square&   t) text = "C,S,T,S"; break;
    Case(Circle&   a, const Square&   b, const Triangle& c, const Triangle& t) text = "C,S,T,T"; break;
    Case(Circle&   a, const Square&   b, const Triangle& c, const Circle&   t) text = "C,S,T,C"; break;
    Case(Circle&   a, const Square&   b, const Circle&   c, const Triangle& t) text = "C,S,C,T"; break;
                                                                   
    Case(Circle&   a, const Triangle& b, const Circle&   c, const Circle&   t) text = "C,T,C,C"; break;
    Case(Circle&   a, const Triangle& b, const Circle&   c, const Square&   t) text = "C,T,C,S"; break;
    Case(Circle&   a, const Triangle& b, const Square&   c, const Circle&   t) text = "C,T,S,C"; break;
    Case(Circle&   a, const Triangle& b, const Square&   c, const Square&   t) text = "C,T,S,S"; break;
    Case(Circle&   a, const Triangle& b, const Square&   c, const Triangle& t) text = "C,T,S,T"; break;
    Case(Circle&   a, const Triangle& b, const Triangle& c, const Square&   t) text = "C,T,T,S"; break;
    Case(Circle&   a, const Triangle& b, const Triangle& c, const Triangle& t) text = "C,T,T,T"; break;
    Case(Circle&   a, const Triangle& b, const Triangle& c, const Circle&   t) text = "C,T,T,C"; break;
    Case(Circle&   a, const Triangle& b, const Circle&   c, const Triangle& t) text = "C,T,C,T"; break;
                                                             
                                                             
    Case(Square&   a, const Circle&   b, const Circle&   c, const Circle&   t) text = "S,C,C,C"; break;
    Case(Square&   a, const Circle&   b, const Circle&   c, const Square&   t) text = "S,C,C,S"; break;
    Case(Square&   a, const Circle&   b, const Square&   c, const Circle&   t) text = "S,C,S,C"; break;
    Case(Square&   a, const Circle&   b, const Square&   c, const Square&   t) text = "S,C,S,S"; break;
    Case(Square&   a, const Circle&   b, const Square&   c, const Triangle& t) text = "S,C,S,T"; break;
    Case(Square&   a, const Circle&   b, const Triangle& c, const Square&   t) text = "S,C,T,S"; break;
    Case(Square&   a, const Circle&   b, const Triangle& c, const Triangle& t) text = "S,C,T,T"; break;
    Case(Square&   a, const Circle&   b, const Triangle& c, const Circle&   t) text = "S,C,T,C"; break;
    Case(Square&   a, const Circle&   b, const Circle&   c, const Triangle& t) text = "S,C,C,T"; break;
                                                                   
    Case(Square&   a, const Square&   b, const Circle&   c, const Circle&   t) text = "S,S,C,C"; break;
    Case(Square&   a, const Square&   b, const Circle&   c, const Square&   t) text = "S,S,C,S"; break;
    Case(Square&   a, const Square&   b, const Square&   c, const Circle&   t) text = "S,S,S,C"; break;
    Case(Square&   a, const Square&   b, const Square&   c, const Square&   t) text = "S,S,S,S"; break;
    Case(Square&   a, const Square&   b, const Square&   c, const Triangle& t) text = "S,S,S,T"; break;
    Case(Square&   a, const Square&   b, const Triangle& c, const Square&   t) text = "S,S,T,S"; break;
    Case(Square&   a, const Square&   b, const Triangle& c, const Triangle& t) text = "S,S,T,T"; break;
    Case(Square&   a, const Square&   b, const Triangle& c, const Circle&   t) text = "S,S,T,C"; break;
    Case(Square&   a, const Square&   b, const Circle&   c, const Triangle& t) text = "S,S,C,T"; break;
                                                                   
    Case(Square&   a, const Triangle& b, const Circle&   c, const Circle&   t) text = "S,T,C,C"; break;
    Case(Square&   a, const Triangle& b, const Circle&   c, const Square&   t) text = "S,T,C,S"; break;
    Case(Square&   a, const Triangle& b, const Square&   c, const Circle&   t) text = "S,T,S,C"; break;
    Case(Square&   a, const Triangle& b, const Square&   c, const Square&   t) text = "S,T,S,S"; break;
    Case(Square&   a, const Triangle& b, const Square&   c, const Triangle& t) text = "S,T,S,T"; break;
    Case(Square&   a, const Triangle& b, const Triangle& c, const Square&   t) text = "S,T,T,S"; break;
    Case(Square&   a, const Triangle& b, const Triangle& c, const Triangle& t) text = "S,T,T,T"; break;
    Case(Square&   a, const Triangle& b, const Triangle& c, const Circle&   t) text = "S,T,T,C"; break;
    Case(Square&   a, const Triangle& b, const Circle&   c, const Triangle& t) text = "S,T,C,T"; break;
                                                             
                                                             
    Case(Triangle& a, const Circle&   b, const Circle&   c, const Circle&   t) text = "T,C,C,C"; break;
    Case(Triangle& a, const Circle&   b, const Circle&   c, const Square&   t) text = "T,C,C,S"; break;
    Case(Triangle& a, const Circle&   b, const Square&   c, const Circle&   t) text = "T,C,S,C"; break;
    Case(Triangle& a, const Circle&   b, const Square&   c, const Square&   t) text = "T,C,S,S"; break;
    Case(Triangle& a, const Circle&   b, const Square&   c, const Triangle& t) text = "T,C,S,T"; break;
    Case(Triangle& a, const Circle&   b, const Triangle& c, const Square&   t) text = "T,C,T,S"; break;
    Case(Triangle& a, const Circle&   b, const Triangle& c, const Triangle& t) text = "T,C,T,T"; break;
    Case(Triangle& a, const Circle&   b, const Triangle& c, const Circle&   t) text = "T,C,T,C"; break;
    Case(Triangle& a, const Circle&   b, const Circle&   c, const Triangle& t) text = "T,C,C,T"; break;
                                                                   
    Case(Triangle& a, const Square&   b, const Circle&   c, const Circle&   t) text = "T,S,C,C"; break;
    Case(Triangle& a, const Square&   b, const Circle&   c, const Square&   t) text = "T,S,C,S"; break;
    Case(Triangle& a, const Square&   b, const Square&   c, const Circle&   t) text = "T,S,S,C"; break;
    Case(Triangle& a, const Square&   b, const Square&   c, const Square&   t) text = "T,S,S,S"; break;
    Case(Triangle& a, const Square&   b, const Square&   c, const Triangle& t) text = "T,S,S,T"; break;
    Case(Triangle& a, const Square&   b, const Triangle& c, const Square&   t) text = "T,S,T,S"; break;
    Case(Triangle& a, const Square&   b, const Triangle& c, const Triangle& t) text = "T,S,T,T"; break;
    Case(Triangle& a, const Square&   b, const Triangle& c, const Circle&   t) text = "T,S,T,C"; break;
    Case(Triangle& a, const Square&   b, const Circle&   c, const Triangle& t) text = "T,S,C,T"; break;
                                                                   
    Case(Triangle& a, const Triangle& b, const Circle&   c, const Circle&   t) text = "T,T,C,C"; break;
    Case(Triangle& a, const Triangle& b, const Circle&   c, const Square&   t) text = "T,T,C,S"; break;
    Case(Triangle& a, const Triangle& b, const Square&   c, const Circle&   t) text = "T,T,S,C"; break;
    Case(Triangle& a, const Triangle& b, const Square&   c, const Square&   t) text = "T,T,S,S"; break;
    Case(Triangle& a, const Triangle& b, const Square&   c, const Triangle& t) text = "T,T,S,T"; break;
    Case(Triangle& a, const Triangle& b, const Triangle& c, const Square&   t) text = "T,T,T,S"; break;
    Case(Triangle& a, const Triangle& b, const Triangle& c, const Triangle& t) text = "T,T,T,T"; break;
    Case(Triangle& a, const Triangle& b, const Triangle& c, const Circle&   t) text = "T,T,T,C"; break;
    Case(Triangle& a, const Triangle& b, const Circle&   c, const Triangle& t) text = "T,T,C,T"; break;
    
    Otherwise()                                                                      text = "other";   break;
    }
    EndMatch

    std::cout << text << std::endl;
}

//------------------------------------------------------------------------------

int main()
{
    Shape* c = new Circle(loc(1,1),7);
    Shape* s = new Square(loc(1,1),2);
    Shape* t = new Triangle(loc(1,1),loc(1,0),loc(0,0));

    Shape* shapes[] = {c,s,t};

    for (size_t n = 0; n < 3; n++)
    {
        // 1 argument
        for (size_t i = 0; i < 3; ++i)
            do_match(shapes[i]);
        
        // 2 arguments
        for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            do_match(shapes[i], shapes[j]);
        
        // 3 arguments
        for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
        for (size_t k = 0; k < 3; ++k)
            do_match(shapes[i], shapes[j], shapes[k]);
        
        // 4 arguments
        for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
        for (size_t k = 0; k < 3; ++k)
        for (size_t l = 0; l < 3; ++l)
            do_match(shapes[i], shapes[j], shapes[k], shapes[l]);
    }
}

//------------------------------------------------------------------------------
