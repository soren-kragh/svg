//
//  MIT No Attribution License
//
//  Copyright 2024, Soren Kragh
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the
//  “Software”), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so.
//

#pragma once

#include <sstream>
#include <iostream>
#include <iomanip>

#define SVG_FATAL( MSG_ ) \
  do \
  { \
    std::cerr << "*** SVG_FATAL: " << MSG_ << std::endl; \
    exit( 1 ); \
  } while ( 0 )

#define SVG_DBG( MSG_ ) \
  do \
  { \
    std::cerr << MSG_ << std::endl; \
  } while ( 0 )

namespace SVG {

  class U;
  class Object;

  typedef enum { MinX, MidX, MaxX } AnchorX;
  typedef enum { MinY, MidY, MaxY } AnchorY;

  typedef enum {
    Black, Red, Green, Blue, Yellow, Magenta, Cyan, White,
    Brown, Orange, Purple, Pink
  } ColorName;

  // Collision is determined by object boundary box alone, so it tends to be
  // quite conservative.
  bool Collides( Object* obj1, Object* obj2 );
  bool Collides( Object* obj1, Object* obj2, U margin_x, U margin_y );

}
