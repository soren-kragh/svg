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
  class Point;
  class BoundaryBox;
  class Transform;
  class Color;
  class Font;
  class Attributes;
  class Object;
  class Group;
  class Line;
  class Rect;
  class Text;
  class Poly;
  class Circle;
  class Ellipse;
  class Canvas;

  enum class AnchorX { Min, Mid, Max };
  enum class AnchorY { Min, Mid, Max };

  // Colors defined by the Scalable Vector Graphics (SVG) Specification.
  enum class ColorName {
    none                ,
    black               ,
    navy                ,
    darkblue            ,
    mediumblue          ,
    blue                ,
    darkgreen           ,
    green               ,
    teal                ,
    darkcyan            ,
    deepskyblue         ,
    darkturquoise       ,
    mediumspringgreen   ,
    lime                ,
    springgreen         ,
    cyan                ,
    aqua                ,
    midnightblue        ,
    dodgerblue          ,
    lightseagreen       ,
    forestgreen         ,
    seagreen            ,
    darkslategray       ,
    darkslategrey       ,
    limegreen           ,
    mediumseagreen      ,
    turquoise           ,
    royalblue           ,
    steelblue           ,
    darkslateblue       ,
    mediumturquoise     ,
    indigo              ,
    darkolivegreen      ,
    cadetblue           ,
    cornflowerblue      ,
    mediumaquamarine    ,
    dimgrey             ,
    dimgray             ,
    slateblue           ,
    olivedrab           ,
    slategrey           ,
    slategray           ,
    lightslategray      ,
    lightslategrey      ,
    mediumslateblue     ,
    lawngreen           ,
    chartreuse          ,
    aquamarine          ,
    maroon              ,
    purple              ,
    olive               ,
    gray                ,
    grey                ,
    skyblue             ,
    lightskyblue        ,
    blueviolet          ,
    darkred             ,
    darkmagenta         ,
    saddlebrown         ,
    darkseagreen        ,
    lightgreen          ,
    mediumpurple        ,
    darkviolet          ,
    palegreen           ,
    darkorchid          ,
    yellowgreen         ,
    sienna              ,
    brown               ,
    darkgray            ,
    darkgrey            ,
    lightblue           ,
    greenyellow         ,
    paleturquoise       ,
    lightsteelblue      ,
    powderblue          ,
    firebrick           ,
    darkgoldenrod       ,
    mediumorchid        ,
    rosybrown           ,
    darkkhaki           ,
    silver              ,
    mediumvioletred     ,
    indianred           ,
    peru                ,
    chocolate           ,
    tan                 ,
    lightgray           ,
    lightgrey           ,
    thistle             ,
    orchid              ,
    goldenrod           ,
    palevioletred       ,
    crimson             ,
    gainsboro           ,
    plum                ,
    burlywood           ,
    lightcyan           ,
    lavender            ,
    darksalmon          ,
    violet              ,
    palegoldenrod       ,
    lightcoral          ,
    khaki               ,
    aliceblue           ,
    honeydew            ,
    azure               ,
    sandybrown          ,
    wheat               ,
    beige               ,
    whitesmoke          ,
    mintcream           ,
    ghostwhite          ,
    salmon              ,
    antiquewhite        ,
    linen               ,
    lightgoldenrodyellow,
    oldlace             ,
    red                 ,
    fuchsia             ,
    magenta             ,
    deeppink            ,
    orangered           ,
    tomato              ,
    hotpink             ,
    coral               ,
    darkorange          ,
    lightsalmon         ,
    orange              ,
    lightpink           ,
    pink                ,
    gold                ,
    peachpuff           ,
    navajowhite         ,
    moccasin            ,
    bisque              ,
    mistyrose           ,
    blanchedalmond      ,
    papayawhip          ,
    lavenderblush       ,
    seashell            ,
    cornsilk            ,
    lemonchiffon        ,
    floralwhite         ,
    snow                ,
    yellow              ,
    lightyellow         ,
    ivory               ,
    white               ,
  };

  enum class LineCap { Butt, Round, Square };
  enum class LineJoin { Sharp, Round };

  std::string ToFixed( double d, uint32_t decimals );

  // Collision is determined by object boundary box alone, so it tends to be
  // quite conservative.
  bool Collides( Object* obj1, Object* obj2 );
  bool Collides( Object* obj1, Object* obj2, U margin_x, U margin_y );
}
