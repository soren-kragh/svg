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

#include <map>

#include <cmath>
#include <svg_color.h>

using namespace SVG;

////////////////////////////////////////////////////////////////////////////////

Color::Color( void )
{
  Undef();
}

Color::Color( uint8_t r, uint8_t g, uint8_t b ) : Color()
{
  Set( r, g, b );
}

Color::Color( ColorName color, double lighten ) : Color()
{
  Set( color, lighten );
}

Color::Color( std::string_view color_name, double lighten ) : Color()
{
  Set( color_name, lighten );
}

Color::Color( const Color* color )
{
  Set( color );
}

//------------------------------------------------------------------------------

Color* Color::Set( uint8_t r, uint8_t g, uint8_t b )
{
  col.rgb_defined = true;
  col.rgb_none = false;
  col.r = r;
  col.g = g;
  col.b = b;
  col.stop_ofs_auto = true;
  col.stop_ofs = 0.0;
  col.stop_opacity = 1.0;
  col_list.clear();
  grad = {};
  return this;
}

Color* Color::Set( ColorName color, double lighten )
{
  struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  };
  static std::map< ColorName, RGB > color2rgb = {
    { ColorName::black               , { 0x00, 0x00, 0x00 } },
    { ColorName::navy                , { 0x00, 0x00, 0x80 } },
    { ColorName::darkblue            , { 0x00, 0x00, 0x8B } },
    { ColorName::mediumblue          , { 0x00, 0x00, 0xCD } },
    { ColorName::blue                , { 0x00, 0x00, 0xFF } },
    { ColorName::darkgreen           , { 0x00, 0x64, 0x00 } },
    { ColorName::green               , { 0x00, 0x80, 0x00 } },
    { ColorName::teal                , { 0x00, 0x80, 0x80 } },
    { ColorName::darkcyan            , { 0x00, 0x8B, 0x8B } },
    { ColorName::deepskyblue         , { 0x00, 0xBF, 0xFF } },
    { ColorName::darkturquoise       , { 0x00, 0xCE, 0xD1 } },
    { ColorName::mediumspringgreen   , { 0x00, 0xFA, 0x9A } },
    { ColorName::lime                , { 0x00, 0xFF, 0x00 } },
    { ColorName::springgreen         , { 0x00, 0xFF, 0x7F } },
    { ColorName::cyan                , { 0x00, 0xFF, 0xFF } },
    { ColorName::aqua                , { 0x00, 0xFF, 0xFF } },
    { ColorName::midnightblue        , { 0x19, 0x19, 0x70 } },
    { ColorName::dodgerblue          , { 0x1E, 0x90, 0xFF } },
    { ColorName::lightseagreen       , { 0x20, 0xB2, 0xAA } },
    { ColorName::forestgreen         , { 0x22, 0x8B, 0x22 } },
    { ColorName::seagreen            , { 0x2E, 0x8B, 0x57 } },
    { ColorName::darkslategray       , { 0x2F, 0x4F, 0x4F } },
    { ColorName::darkslategrey       , { 0x2F, 0x4F, 0x4F } },
    { ColorName::limegreen           , { 0x32, 0xCD, 0x32 } },
    { ColorName::mediumseagreen      , { 0x3C, 0xB3, 0x71 } },
    { ColorName::turquoise           , { 0x40, 0xE0, 0xD0 } },
    { ColorName::royalblue           , { 0x41, 0x69, 0xE1 } },
    { ColorName::steelblue           , { 0x46, 0x82, 0xB4 } },
    { ColorName::darkslateblue       , { 0x48, 0x3D, 0x8B } },
    { ColorName::mediumturquoise     , { 0x48, 0xD1, 0xCC } },
    { ColorName::indigo              , { 0x4B, 0x00, 0x82 } },
    { ColorName::darkolivegreen      , { 0x55, 0x6B, 0x2F } },
    { ColorName::cadetblue           , { 0x5F, 0x9E, 0xA0 } },
    { ColorName::cornflowerblue      , { 0x64, 0x95, 0xED } },
    { ColorName::mediumaquamarine    , { 0x66, 0xCD, 0xAA } },
    { ColorName::dimgrey             , { 0x69, 0x69, 0x69 } },
    { ColorName::dimgray             , { 0x69, 0x69, 0x69 } },
    { ColorName::slateblue           , { 0x6A, 0x5A, 0xCD } },
    { ColorName::olivedrab           , { 0x6B, 0x8E, 0x23 } },
    { ColorName::slategrey           , { 0x70, 0x80, 0x90 } },
    { ColorName::slategray           , { 0x70, 0x80, 0x90 } },
    { ColorName::lightslategray      , { 0x77, 0x88, 0x99 } },
    { ColorName::lightslategrey      , { 0x77, 0x88, 0x99 } },
    { ColorName::mediumslateblue     , { 0x7B, 0x68, 0xEE } },
    { ColorName::lawngreen           , { 0x7C, 0xFC, 0x00 } },
    { ColorName::chartreuse          , { 0x7F, 0xFF, 0x00 } },
    { ColorName::aquamarine          , { 0x7F, 0xFF, 0xD4 } },
    { ColorName::maroon              , { 0x80, 0x00, 0x00 } },
    { ColorName::purple              , { 0x80, 0x00, 0x80 } },
    { ColorName::olive               , { 0x80, 0x80, 0x00 } },
    { ColorName::gray                , { 0x80, 0x80, 0x80 } },
    { ColorName::grey                , { 0x80, 0x80, 0x80 } },
    { ColorName::skyblue             , { 0x87, 0xCE, 0xEB } },
    { ColorName::lightskyblue        , { 0x87, 0xCE, 0xFA } },
    { ColorName::blueviolet          , { 0x8A, 0x2B, 0xE2 } },
    { ColorName::darkred             , { 0x8B, 0x00, 0x00 } },
    { ColorName::darkmagenta         , { 0x8B, 0x00, 0x8B } },
    { ColorName::saddlebrown         , { 0x8B, 0x45, 0x13 } },
    { ColorName::darkseagreen        , { 0x8F, 0xBC, 0x8F } },
    { ColorName::lightgreen          , { 0x90, 0xEE, 0x90 } },
    { ColorName::mediumpurple        , { 0x93, 0x70, 0xDB } },
    { ColorName::darkviolet          , { 0x94, 0x00, 0xD3 } },
    { ColorName::palegreen           , { 0x98, 0xFB, 0x98 } },
    { ColorName::darkorchid          , { 0x99, 0x32, 0xCC } },
    { ColorName::yellowgreen         , { 0x9A, 0xCD, 0x32 } },
    { ColorName::sienna              , { 0xA0, 0x52, 0x2D } },
    { ColorName::brown               , { 0xA5, 0x2A, 0x2A } },
    { ColorName::darkgray            , { 0xA9, 0xA9, 0xA9 } },
    { ColorName::darkgrey            , { 0xA9, 0xA9, 0xA9 } },
    { ColorName::lightblue           , { 0xAD, 0xD8, 0xE6 } },
    { ColorName::greenyellow         , { 0xAD, 0xFF, 0x2F } },
    { ColorName::paleturquoise       , { 0xAF, 0xEE, 0xEE } },
    { ColorName::lightsteelblue      , { 0xB0, 0xC4, 0xDE } },
    { ColorName::powderblue          , { 0xB0, 0xE0, 0xE6 } },
    { ColorName::firebrick           , { 0xB2, 0x22, 0x22 } },
    { ColorName::darkgoldenrod       , { 0xB8, 0x86, 0x0B } },
    { ColorName::mediumorchid        , { 0xBA, 0x55, 0xD3 } },
    { ColorName::rosybrown           , { 0xBC, 0x8F, 0x8F } },
    { ColorName::darkkhaki           , { 0xBD, 0xB7, 0x6B } },
    { ColorName::silver              , { 0xC0, 0xC0, 0xC0 } },
    { ColorName::mediumvioletred     , { 0xC7, 0x15, 0x85 } },
    { ColorName::indianred           , { 0xCD, 0x5C, 0x5C } },
    { ColorName::peru                , { 0xCD, 0x85, 0x3F } },
    { ColorName::chocolate           , { 0xD2, 0x69, 0x1E } },
    { ColorName::tan                 , { 0xD2, 0xB4, 0x8C } },
    { ColorName::lightgray           , { 0xD3, 0xD3, 0xD3 } },
    { ColorName::lightgrey           , { 0xD3, 0xD3, 0xD3 } },
    { ColorName::thistle             , { 0xD8, 0xBF, 0xD8 } },
    { ColorName::orchid              , { 0xDA, 0x70, 0xD6 } },
    { ColorName::goldenrod           , { 0xDA, 0xA5, 0x20 } },
    { ColorName::palevioletred       , { 0xDB, 0x70, 0x93 } },
    { ColorName::crimson             , { 0xDC, 0x14, 0x3C } },
    { ColorName::gainsboro           , { 0xDC, 0xDC, 0xDC } },
    { ColorName::plum                , { 0xDD, 0xA0, 0xDD } },
    { ColorName::burlywood           , { 0xDE, 0xB8, 0x87 } },
    { ColorName::lightcyan           , { 0xE0, 0xFF, 0xFF } },
    { ColorName::lavender            , { 0xE6, 0xE6, 0xFA } },
    { ColorName::darksalmon          , { 0xE9, 0x96, 0x7A } },
    { ColorName::violet              , { 0xEE, 0x82, 0xEE } },
    { ColorName::palegoldenrod       , { 0xEE, 0xE8, 0xAA } },
    { ColorName::lightcoral          , { 0xF0, 0x80, 0x80 } },
    { ColorName::khaki               , { 0xF0, 0xE6, 0x8C } },
    { ColorName::aliceblue           , { 0xF0, 0xF8, 0xFF } },
    { ColorName::honeydew            , { 0xF0, 0xFF, 0xF0 } },
    { ColorName::azure               , { 0xF0, 0xFF, 0xFF } },
    { ColorName::sandybrown          , { 0xF4, 0xA4, 0x60 } },
    { ColorName::wheat               , { 0xF5, 0xDE, 0xB3 } },
    { ColorName::beige               , { 0xF5, 0xF5, 0xDC } },
    { ColorName::whitesmoke          , { 0xF5, 0xF5, 0xF5 } },
    { ColorName::mintcream           , { 0xF5, 0xFF, 0xFA } },
    { ColorName::ghostwhite          , { 0xF8, 0xF8, 0xFF } },
    { ColorName::salmon              , { 0xFA, 0x80, 0x72 } },
    { ColorName::antiquewhite        , { 0xFA, 0xEB, 0xD7 } },
    { ColorName::linen               , { 0xFA, 0xF0, 0xE6 } },
    { ColorName::lightgoldenrodyellow, { 0xFA, 0xFA, 0xD2 } },
    { ColorName::oldlace             , { 0xFD, 0xF5, 0xE6 } },
    { ColorName::red                 , { 0xFF, 0x00, 0x00 } },
    { ColorName::fuchsia             , { 0xFF, 0x00, 0xFF } },
    { ColorName::magenta             , { 0xFF, 0x00, 0xFF } },
    { ColorName::deeppink            , { 0xFF, 0x14, 0x93 } },
    { ColorName::orangered           , { 0xFF, 0x45, 0x00 } },
    { ColorName::tomato              , { 0xFF, 0x63, 0x47 } },
    { ColorName::hotpink             , { 0xFF, 0x69, 0xB4 } },
    { ColorName::coral               , { 0xFF, 0x7F, 0x50 } },
    { ColorName::darkorange          , { 0xFF, 0x8C, 0x00 } },
    { ColorName::lightsalmon         , { 0xFF, 0xA0, 0x7A } },
    { ColorName::orange              , { 0xFF, 0xA5, 0x00 } },
    { ColorName::lightpink           , { 0xFF, 0xB6, 0xC1 } },
    { ColorName::pink                , { 0xFF, 0xC0, 0xCB } },
    { ColorName::gold                , { 0xFF, 0xD7, 0x00 } },
    { ColorName::peachpuff           , { 0xFF, 0xDA, 0xB9 } },
    { ColorName::navajowhite         , { 0xFF, 0xDE, 0xAD } },
    { ColorName::moccasin            , { 0xFF, 0xE4, 0xB5 } },
    { ColorName::bisque              , { 0xFF, 0xE4, 0xC4 } },
    { ColorName::mistyrose           , { 0xFF, 0xE4, 0xE1 } },
    { ColorName::blanchedalmond      , { 0xFF, 0xEB, 0xCD } },
    { ColorName::papayawhip          , { 0xFF, 0xEF, 0xD5 } },
    { ColorName::lavenderblush       , { 0xFF, 0xF0, 0xF5 } },
    { ColorName::seashell            , { 0xFF, 0xF5, 0xEE } },
    { ColorName::cornsilk            , { 0xFF, 0xF8, 0xDC } },
    { ColorName::lemonchiffon        , { 0xFF, 0xFA, 0xCD } },
    { ColorName::floralwhite         , { 0xFF, 0xFA, 0xF0 } },
    { ColorName::snow                , { 0xFF, 0xFA, 0xFA } },
    { ColorName::yellow              , { 0xFF, 0xFF, 0x00 } },
    { ColorName::lightyellow         , { 0xFF, 0xFF, 0xE0 } },
    { ColorName::ivory               , { 0xFF, 0xFF, 0xF0 } },
    { ColorName::white               , { 0xFF, 0xFF, 0xFF } },
  };
  RGB rgb = color2rgb[ color ];
  Set( rgb.r, rgb.g, rgb.b );
  Lighten( lighten );
  return this;
}

Color* Color::Set( std::string_view color_name, double lighten )
{
  static std::map< std::string_view, ColorName > name2color = {
    { "black"               , ColorName::black                },
    { "navy"                , ColorName::navy                 },
    { "darkblue"            , ColorName::darkblue             },
    { "mediumblue"          , ColorName::mediumblue           },
    { "blue"                , ColorName::blue                 },
    { "darkgreen"           , ColorName::darkgreen            },
    { "green"               , ColorName::green                },
    { "teal"                , ColorName::teal                 },
    { "darkcyan"            , ColorName::darkcyan             },
    { "deepskyblue"         , ColorName::deepskyblue          },
    { "darkturquoise"       , ColorName::darkturquoise        },
    { "mediumspringgreen"   , ColorName::mediumspringgreen    },
    { "lime"                , ColorName::lime                 },
    { "springgreen"         , ColorName::springgreen          },
    { "cyan"                , ColorName::cyan                 },
    { "aqua"                , ColorName::aqua                 },
    { "midnightblue"        , ColorName::midnightblue         },
    { "dodgerblue"          , ColorName::dodgerblue           },
    { "lightseagreen"       , ColorName::lightseagreen        },
    { "forestgreen"         , ColorName::forestgreen          },
    { "seagreen"            , ColorName::seagreen             },
    { "darkslategray"       , ColorName::darkslategray        },
    { "darkslategrey"       , ColorName::darkslategrey        },
    { "limegreen"           , ColorName::limegreen            },
    { "mediumseagreen"      , ColorName::mediumseagreen       },
    { "turquoise"           , ColorName::turquoise            },
    { "royalblue"           , ColorName::royalblue            },
    { "steelblue"           , ColorName::steelblue            },
    { "darkslateblue"       , ColorName::darkslateblue        },
    { "mediumturquoise"     , ColorName::mediumturquoise      },
    { "indigo"              , ColorName::indigo               },
    { "darkolivegreen"      , ColorName::darkolivegreen       },
    { "cadetblue"           , ColorName::cadetblue            },
    { "cornflowerblue"      , ColorName::cornflowerblue       },
    { "mediumaquamarine"    , ColorName::mediumaquamarine     },
    { "dimgrey"             , ColorName::dimgrey              },
    { "dimgray"             , ColorName::dimgray              },
    { "slateblue"           , ColorName::slateblue            },
    { "olivedrab"           , ColorName::olivedrab            },
    { "slategrey"           , ColorName::slategrey            },
    { "slategray"           , ColorName::slategray            },
    { "lightslategray"      , ColorName::lightslategray       },
    { "lightslategrey"      , ColorName::lightslategrey       },
    { "mediumslateblue"     , ColorName::mediumslateblue      },
    { "lawngreen"           , ColorName::lawngreen            },
    { "chartreuse"          , ColorName::chartreuse           },
    { "aquamarine"          , ColorName::aquamarine           },
    { "maroon"              , ColorName::maroon               },
    { "purple"              , ColorName::purple               },
    { "olive"               , ColorName::olive                },
    { "gray"                , ColorName::gray                 },
    { "grey"                , ColorName::grey                 },
    { "skyblue"             , ColorName::skyblue              },
    { "lightskyblue"        , ColorName::lightskyblue         },
    { "blueviolet"          , ColorName::blueviolet           },
    { "darkred"             , ColorName::darkred              },
    { "darkmagenta"         , ColorName::darkmagenta          },
    { "saddlebrown"         , ColorName::saddlebrown          },
    { "darkseagreen"        , ColorName::darkseagreen         },
    { "lightgreen"          , ColorName::lightgreen           },
    { "mediumpurple"        , ColorName::mediumpurple         },
    { "darkviolet"          , ColorName::darkviolet           },
    { "palegreen"           , ColorName::palegreen            },
    { "darkorchid"          , ColorName::darkorchid           },
    { "yellowgreen"         , ColorName::yellowgreen          },
    { "sienna"              , ColorName::sienna               },
    { "brown"               , ColorName::brown                },
    { "darkgray"            , ColorName::darkgray             },
    { "darkgrey"            , ColorName::darkgrey             },
    { "lightblue"           , ColorName::lightblue            },
    { "greenyellow"         , ColorName::greenyellow          },
    { "paleturquoise"       , ColorName::paleturquoise        },
    { "lightsteelblue"      , ColorName::lightsteelblue       },
    { "powderblue"          , ColorName::powderblue           },
    { "firebrick"           , ColorName::firebrick            },
    { "darkgoldenrod"       , ColorName::darkgoldenrod        },
    { "mediumorchid"        , ColorName::mediumorchid         },
    { "rosybrown"           , ColorName::rosybrown            },
    { "darkkhaki"           , ColorName::darkkhaki            },
    { "silver"              , ColorName::silver               },
    { "mediumvioletred"     , ColorName::mediumvioletred      },
    { "indianred"           , ColorName::indianred            },
    { "peru"                , ColorName::peru                 },
    { "chocolate"           , ColorName::chocolate            },
    { "tan"                 , ColorName::tan                  },
    { "lightgray"           , ColorName::lightgray            },
    { "lightgrey"           , ColorName::lightgrey            },
    { "thistle"             , ColorName::thistle              },
    { "orchid"              , ColorName::orchid               },
    { "goldenrod"           , ColorName::goldenrod            },
    { "palevioletred"       , ColorName::palevioletred        },
    { "crimson"             , ColorName::crimson              },
    { "gainsboro"           , ColorName::gainsboro            },
    { "plum"                , ColorName::plum                 },
    { "burlywood"           , ColorName::burlywood            },
    { "lightcyan"           , ColorName::lightcyan            },
    { "lavender"            , ColorName::lavender             },
    { "darksalmon"          , ColorName::darksalmon           },
    { "violet"              , ColorName::violet               },
    { "palegoldenrod"       , ColorName::palegoldenrod        },
    { "lightcoral"          , ColorName::lightcoral           },
    { "khaki"               , ColorName::khaki                },
    { "aliceblue"           , ColorName::aliceblue            },
    { "honeydew"            , ColorName::honeydew             },
    { "azure"               , ColorName::azure                },
    { "sandybrown"          , ColorName::sandybrown           },
    { "wheat"               , ColorName::wheat                },
    { "beige"               , ColorName::beige                },
    { "whitesmoke"          , ColorName::whitesmoke           },
    { "mintcream"           , ColorName::mintcream            },
    { "ghostwhite"          , ColorName::ghostwhite           },
    { "salmon"              , ColorName::salmon               },
    { "antiquewhite"        , ColorName::antiquewhite         },
    { "linen"               , ColorName::linen                },
    { "lightgoldenrodyellow", ColorName::lightgoldenrodyellow },
    { "oldlace"             , ColorName::oldlace              },
    { "red"                 , ColorName::red                  },
    { "fuchsia"             , ColorName::fuchsia              },
    { "magenta"             , ColorName::magenta              },
    { "deeppink"            , ColorName::deeppink             },
    { "orangered"           , ColorName::orangered            },
    { "tomato"              , ColorName::tomato               },
    { "hotpink"             , ColorName::hotpink              },
    { "coral"               , ColorName::coral                },
    { "darkorange"          , ColorName::darkorange           },
    { "lightsalmon"         , ColorName::lightsalmon          },
    { "orange"              , ColorName::orange               },
    { "lightpink"           , ColorName::lightpink            },
    { "pink"                , ColorName::pink                 },
    { "gold"                , ColorName::gold                 },
    { "peachpuff"           , ColorName::peachpuff            },
    { "navajowhite"         , ColorName::navajowhite          },
    { "moccasin"            , ColorName::moccasin             },
    { "bisque"              , ColorName::bisque               },
    { "mistyrose"           , ColorName::mistyrose            },
    { "blanchedalmond"      , ColorName::blanchedalmond       },
    { "papayawhip"          , ColorName::papayawhip           },
    { "lavenderblush"       , ColorName::lavenderblush        },
    { "seashell"            , ColorName::seashell             },
    { "cornsilk"            , ColorName::cornsilk             },
    { "lemonchiffon"        , ColorName::lemonchiffon         },
    { "floralwhite"         , ColorName::floralwhite          },
    { "snow"                , ColorName::snow                 },
    { "yellow"              , ColorName::yellow               },
    { "lightyellow"         , ColorName::lightyellow          },
    { "ivory"               , ColorName::ivory                },
    { "white"               , ColorName::white                },
  };
  auto it = name2color.find( color_name );
  if ( it != name2color.end() ) {
    Set( it->second, lighten );
    return this;
  } else {
    return nullptr;
  }
}

Color* Color::Set( const Color* color )
{
  *this = *color;
  return this;
}

Color* Color::Set( const Color* color1, const Color* color2, double f )
{
  Undef();
  if ( color1->col.rgb_defined && color2->col.rgb_defined ) {
    Set(
      color1->col.r * (1 - f) + color2->col.r * f,
      color1->col.g * (1 - f) + color2->col.g * f,
      color1->col.b * (1 - f) + color2->col.b * f
    );
  }
  return this;
}

void Color::ComputeAutoStopOfs()
{
  size_t i = 0;
  for ( size_t j = 1; j < col_list.size(); j++ ) {
    if ( !col_list[ j ].stop_ofs_auto || j == col_list.size() - 1 ) {
      if ( col_list[ i ].stop_ofs_auto ) col_list[ i ].stop_ofs = 0.0;
      if ( col_list[ j ].stop_ofs_auto ) col_list[ j ].stop_ofs = 1.0;
      double d = 1.0 / (j - i);
      for ( size_t k = i + 1; k < j; k++ ) {
        col_list[ k ].stop_ofs =
          col_list[ i ].stop_ofs +
          (col_list[ j ].stop_ofs - col_list[ i ].stop_ofs) * (k - i) * d;
      }
      i = j;
    }
  }
  col = {};
  col.rgb_defined = true;
  col.rgb_none = false;
  col.r = col_list.back().r;
  col.g = col_list.back().g;
  col.b = col_list.back().b;
}

Color* Color::AddGradientStop( const Color* color, double stop_ofs )
{
  if ( !color->IsClear() ) {
    col_t col{ color->col };
    col.stop_ofs_auto = stop_ofs < 0.0 || stop_ofs > 1.0;
    col.stop_ofs = stop_ofs;
    if ( color->opacity_defined ) col.stop_opacity = color->opacity;
    col_list.emplace_back( col );
    ComputeAutoStopOfs();
  }
  return this;
}

Color* Color::SetGradientDir(
  double x1, double y1, double x2, double y2, bool group
)
{
  grad.group = group;
  return SetGradientDir( x1, y1, x2, y2 );
}

Color* Color::SetGradientDir(
  double x1, double y1, double x2, double y2
)
{
  grad.x1 = x1;
  grad.y1 = y1;
  grad.x2 = x2;
  grad.y2 = y2;
  return this;
}

Color* Color::SetStopOfs( size_t i, double stop_ofs )
{
  if ( i < col_list.size() ) {
    col_list[ i ].stop_ofs_auto = stop_ofs < 0.0 || stop_ofs > 1.0;
    col_list[ i ].stop_ofs = stop_ofs;
    ComputeAutoStopOfs();
  }
  return this;
}

Color* Color::SetOpacity( double opacity, bool gradient )
{
  opacity = std::min( std::max( opacity, 0.0 ), 1.0 );
  if ( gradient ) {
    for ( auto& col : col_list ) {
      col.stop_opacity = gradient;
    }
  } else {
    this->opacity = opacity;
    this->opacity_defined = true;
  }
  return this;
}

Color* Color::Lighten( double f )
{
  f = std::min( std::max( f, -1.0 ), +1.0 );
  if ( f < 0 ) {
    col.r *= 1 + f;
    col.g *= 1 + f;
    col.b *= 1 + f;
  } else {
    col.r += (0xFF - col.r) * f;
    col.g += (0xFF - col.g) * f;
    col.b += (0xFF - col.b) * f;
  }

  for ( auto& c : col_list ) {
    if ( f < 0 ) {
      c.r *= 1 + f;
      c.g *= 1 + f;
      c.b *= 1 + f;
    } else {
      c.r += (0xFF - c.r) * f;
      c.g += (0xFF - c.g) * f;
      c.b += (0xFF - c.b) * f;
    }
  }

  return this;
}

Color* Color::Opacify( double f, bool gradient )
{
  f = std::min( std::max( f, -1.0 ), +1.0 );
  if ( gradient ) {
    for ( auto& col : col_list ) {
      if ( f < 0 ) {
        col.stop_opacity *= 1 + f;
      } else {
        col.stop_opacity += (1 - col.stop_opacity) * f;
      }
    }
  } else {
    if ( !opacity_defined ) opacity = 1.0;
    if ( f < 0 ) {
      opacity *= 1 + f;
    } else {
      opacity += (1 - opacity) * f;
    }
    opacity_defined = true;
  }
  return this;
}

Color* Color::Undef( void )
{
  col = {};
  col_list.clear();
  grad = {};
  opacity_defined = false;
  opacity = 1.0;
  return this;
}

Color* Color::Clear( void )
{
  Undef();
  col.rgb_defined = true;
  return this;
}

////////////////////////////////////////////////////////////////////////////////

std::string Color::col_t::StopOffsetSVG()
{
  std::ostringstream oss;
  if ( rgb_defined && !rgb_none ) {
    oss
      << " offset=\"" << stop_ofs << '"'
      << " stop-color="
      << "\"#"
      << std::hex << std::setfill( '0' ) << std::uppercase
      << std::setw( 2 ) << (0xFF & r)
      << std::setw( 2 ) << (0xFF & g)
      << std::setw( 2 ) << (0xFF & b)
      << '"';
    if ( stop_opacity < 1.0 ) {
      oss
        << " stop-opacity=\""
        << std::dec << std::setprecision( 3 ) << stop_opacity << '"';
    }
  }
  return oss.str();
}

std::string Color::SVG( std::string_view name )
{
  std::ostringstream oss;
  if ( IsDefined() ) {
    oss << ' ' << name << '=';
    if ( grad.id > 0 ) {
      oss << "\"url(#grad" << grad.id << ")\"";
    } else {
      oss << SVG();
    }
  }
  if ( opacity_defined && !(col.rgb_defined && col.rgb_none) ) {
    oss
      << ' ' << name << "-opacity=\""
      << std::dec << std::setprecision( 3 ) << opacity << '"';
  }
  return oss.str();
}

std::string Color::SVG()
{
  std::ostringstream oss;
  if ( col.rgb_none ) {
    oss << "\"none\"";
  } else {
    oss
      << "\"#"
      << std::hex << std::setfill( '0' ) << std::uppercase
      << std::setw( 2 ) << (0xFF & col.r)
      << std::setw( 2 ) << (0xFF & col.g)
      << std::setw( 2 ) << (0xFF & col.b)
      << '"';
  }
  return oss.str();
}

////////////////////////////////////////////////////////////////////////////////

double Color::Diff( const Color* color1, const Color* color2 )
{
  if ( color1->IsClear() || color2->IsClear() ) return 0.0;

  int delta_r =
    static_cast<int>( color1->col.r ) - static_cast<int>( color2->col.r );
  int delta_g =
    static_cast<int>( color1->col.g ) - static_cast<int>( color2->col.g );
  int delta_b =
    static_cast<int>( color1->col.b ) - static_cast<int>( color2->col.b );

  double r_mean = (static_cast<double>( color1->col.r ) + color2->col.r) / 2.0;

  double term_r = (2.0 + r_mean / 256.0) * delta_r * delta_r;
  double term_g = 4.0 * delta_g * delta_g;
  double term_b = (2.0 + (255.0 - r_mean) / 256.0) * delta_b * delta_b;

  double distance = std::sqrt( term_r + term_g + term_b );

  const  double max_distance = 764.833;
  double result = distance / max_distance;

  return (result > 1.0) ? 1.0 : (result < 0.0) ? 0.0 : result;
}

////////////////////////////////////////////////////////////////////////////////

bool Color::col_t::operator==( const Color::col_t& other ) const
{
  if ( rgb_defined != other.rgb_defined ) return false;
   if ( rgb_defined ) {
    if ( rgb_none != other.rgb_none ) return false;
    if ( !rgb_none ) {
      if ( r != other.r || g != other.g || b != other.b ) return false;
      if ( stop_ofs_auto != other.stop_ofs_auto ) return false;
      if ( !stop_ofs_auto && stop_ofs != other.stop_ofs ) return false;
      if ( stop_opacity != other.stop_opacity ) return false;
    }
  }
  return true;
}

bool Color::operator==( const Color& other ) const
{
  if ( col != other.col ) return false;
  if ( IsGradient() ) {
    if ( col_list   != other.col_list   ) return false;
    if ( grad.x1    != other.grad.x1    ) return false;
    if ( grad.y1    != other.grad.y1    ) return false;
    if ( grad.x2    != other.grad.x2    ) return false;
    if ( grad.y2    != other.grad.y2    ) return false;
    if ( grad.group != other.grad.group ) return false;
  }
  if ( opacity_defined != other.opacity_defined ) return false;
  if ( opacity_defined && opacity != other.opacity ) return false;
  return true;
}

////////////////////////////////////////////////////////////////////////////////
