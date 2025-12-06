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

#include <unordered_map>

namespace SVG {

class Canvas
{

public:

  Canvas( void );
  ~Canvas( void );

  Group* TopGroup() { return top_group; }

  Color* Background() { return &background; }

  // Extra attributes may optionally be added to the SVG.
  std::string GenSVG( U margin = 0, std::string_view attr = "" );

  // Various global settings.
  struct Settings {
    // Controls whether lines in the SVG Will be indented.
    bool indent = true;
  } settings;

private:

  std::unordered_map< std::string, uint32_t > grad_map;

  uint32_t grad_id = 0;

  void GenDefObject(
    std::ostringstream& oss, std::string& indent, Object* obj
  );
  void GenDefsGroup(
    std::ostringstream& oss, std::string& indent, Group* g
  );
  void GenDefs(
   std::ostringstream& oss, std::string& indent
  );

  Color background;

  Group* top_group;

  U canvas_w;
  U canvas_h;
  U margin_x;
  U margin_y;

};

}
