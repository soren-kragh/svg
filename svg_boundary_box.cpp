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

#include <svg_boundary_box.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

BoundaryBox::BoundaryBox( void )
{
  Reset();
}

void BoundaryBox::Update( U x, U y )
{
  if ( defined ) {
    if ( min.x > x ) min.x = x;
    if ( min.y > y ) min.y = y;
    if ( max.x < x ) max.x = x;
    if ( max.y < y ) max.y = y;
  } else {
    min.x = x; min.y = y;
    max.x = x; max.y = y;
    defined = true;
  }
}

void BoundaryBox::Reset( void )
{
  defined = false;
  min.x = 0;
  min.y = 0;
  max.x = 0;
  max.y = 0;
}

///////////////////////////////////////////////////////////////////////////////
