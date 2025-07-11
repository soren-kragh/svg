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

#pragma once

#include <svg_group.h>
#include <svg_line.h>
#include <svg_rect.h>
#include <svg_poly.h>
#include <svg_circle.h>
#include <svg_ellipse.h>
#include <svg_text.h>

namespace SVG {

class Canvas
{

public:

  Canvas( void );
  ~Canvas( void );

  Group* TopGroup( void );

  Color* Background( void );

  // Extra attributes may optionally be added to the SVG.
  std::string GenSVG( U margin = 0, const std::string& attr = "" );

private:

  Color background;

  Group* top_group;

  U canvas_w;
  U canvas_h;
  U margin_x;
  U margin_y;

};

}
