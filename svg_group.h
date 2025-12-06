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

#include <deque>

#include <svg_object.h>

namespace SVG {

class Group : public Object
{
  friend class Canvas;
  friend class Object;

public:

  Group() {}
  ~Group();

  Object* Add( Object* object );

  void DeleteFront();
  void DeleteBack();

  // Send current front object to the back.
  void FrontToBack();

  // Creates new group, adds it, then returns it.
  Group* AddNewGroup();

  // Returns last added object.
  Object* Last() { return last; }

  bool Empty() override;

  // Recursively remove all empty groups; return true if this group thus became
  // empty itself.
  bool Prune() override;

private:

  void UpdateBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms
  );

  void UpdateAbsBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms,
    std::vector< Object* >& obj_path, size_t obj_idx
  ) override;

  void UpdateNoTransBB(
    BoundaryBox& boundary_box, std::vector< Transform >& transforms
  ) override;

  void GenSVG(
    std::ostringstream& oss,
    std::string& indent
  );

  std::deque< Object* > objects;

  Object* last = nullptr;

};

}
