//
//  MIT No Attribution License
//
//  Copyright 2025, Soren Kragh
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the
//  “Software”), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so.
//

#include <svg_common.h>
#include <svg_object.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

std::string SVG::ToFixed( double d, uint32_t decimals )
{
  std::ostringstream oss;
  oss << std::fixed << std::setprecision( decimals ) << d;
  std::string s = oss.str();
  if ( decimals > 0 ) s.erase(s.find_last_not_of( '0' ) + 1);
  if ( !s.empty() && s.back() == '.' ) s.pop_back();
  if ( s == "-0" ) s = "0";
  return s;
}

///////////////////////////////////////////////////////////////////////////////

bool SVG::Collides( Object* obj1, Object* obj2, U margin_x, U margin_y )
{
  if ( obj1 == nullptr || obj2 == nullptr ) return false;
  if ( obj1->Empty() || obj2->Empty() ) return false;
  BoundaryBox b1 = obj1->GetBB();
  BoundaryBox b2 = obj2->GetBB();

  b1.min.x -= margin_x;
  b1.max.x += margin_x;
  b1.min.y -= margin_y;
  b1.max.y += margin_y;

  if (
    b1.max.x <= b2.min.x || b1.min.x >= b2.max.x ||
    b1.max.y <= b2.min.y || b1.min.y >= b2.max.y
  )
    return false;

  return true;
}

bool SVG::Collides( Object* obj1, Object* obj2 )
{
  return Collides( obj1, obj2, 0, 0 );
}

///////////////////////////////////////////////////////////////////////////////
