//
//  Copyright (C) 2023, S. Kragh
//
//  This file is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This file is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//  See the GNU General Public License for more details.
//  <http://www.gnu.org/licenses/>.
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
