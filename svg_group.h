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

#include <deque>

#include <svg_line.h>
#include <svg_rect.h>
#include <svg_poly.h>
#include <svg_circle.h>
#include <svg_ellipse.h>
#include <svg_text.h>

namespace SVG {

class Group : public Object
{
  friend Canvas;

public:

  Group( void );
  ~Group( void );

  Object* Add( Object* object );

  void DeleteFront( void );
  void DeleteBack( void );

  // Send current front object to the back.
  void FrontToBack( void );

  // Creates new group, adds it, then returns it.
  Group* AddNewGroup( void );

  // Returns last added object.
  Object* Last( void ) { return last; }

  bool Empty( void ) override;

private:

  void UpdateBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms
  );

  void GenSVG(
    std::ostringstream& oss,
    std::string& indent
  );

  std::deque< Object* > objects;

  Object* last;

};

}
