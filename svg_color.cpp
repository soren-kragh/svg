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

#include <map>

#include <cmath>
#include <svg_color.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

Color::Color( void )
{
  Undef();
}

Color::Color( uint8_t r, uint8_t g, uint8_t b ) : Color()
{
  Set( r, g, b );
}

Color::Color( ColorName color, float lighten ) : Color()
{
  Set( color, lighten );
}

Color::Color( const std::string& color_name, float lighten ) : Color()
{
  Set( color_name, lighten );
}

Color::Color( Color* color )
{
  Set( color );
}

//------------------------------------------------------------------------------

Color* Color::Set( uint8_t r, uint8_t g, uint8_t b )
{
  this->r = r;
  this->g = g;
  this->b = b;
  rgb_defined = true;
  rgb_none = false;
  return this;
}

Color* Color::Set( ColorName color, float lighten )
{
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

Color* Color::Set( const std::string& color_name, float lighten )
{
  static std::map< std::string, ColorName > name2color = {
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

Color* Color::Set( Color* color )
{
  *this = *color;
  return this;
}

Color* Color::Set( Color* color1, Color* color2, float f )
{
  this->Undef();
  if ( !color1->IsClear() && !color2->IsClear() ) {
    this->Set(
      color1->r * (1 - f) + color2->r * f,
      color1->g * (1 - f) + color2->g * f,
      color1->b * (1 - f) + color2->b * f
    );
  }
  return this;
}

Color* Color::SetOpacity( float opacity )
{
  if ( opacity < 0.0 ) opacity = 0.0;
  if ( opacity > 1.0 ) opacity = 1.0;
  this->opacity = opacity;
  opacity_defined = true;
  return this;
}

Color* Color::Lighten( float f )
{
  if ( f < 0 ) {
    r *= 1 + f;
    g *= 1 + f;
    b *= 1 + f;
  } else {
    r += (0xFF - r) * f;
    g += (0xFF - g) * f;
    b += (0xFF - b) * f;
  }
  return this;
}

Color* Color::Darken( float f )
{
  Lighten( -f );
  return this;
}

Color* Color::Undef( void )
{
  rgb_defined = false;
  rgb_none = true;
  r = 0;
  g = 0;
  b = 0;
  opacity_defined = false;
  opacity = 1.0;
  return this;
}

Color* Color::Clear( void )
{
  rgb_defined = true;
  rgb_none = true;
  opacity_defined = false;
  return this;
}

std::string Color::SVG( const std::string& name )
{
  std::ostringstream oss;
  if ( rgb_defined ) {
    if ( !name.empty() ) {
      oss << ' ' << name << '=';
    }
    if ( rgb_none ) {
      oss << "\"none\"";
    } else {
      oss
        << "\"#"
        << std::hex << std::setfill( '0' ) << std::uppercase
        << std::setw( 2 ) << (0xFF & r)
        << std::setw( 2 ) << (0xFF & g)
        << std::setw( 2 ) << (0xFF & b)
        << '"';
    }
  }
  if ( !name.empty() && opacity_defined && !(rgb_defined && rgb_none) ) {
    oss
      << std::dec
      << ' ' << name << "-opacity=\""
      << std::setprecision( 3 ) << opacity << '"';
  }
  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////

float Color::Diff( Color* color1, Color* color2 )
{
  if ( color1->IsClear() || color2->IsClear() ) return 0.0;

  int delta_r = static_cast<int>( color1->r ) - static_cast<int>( color2->r );
  int delta_g = static_cast<int>( color1->g ) - static_cast<int>( color2->g );
  int delta_b = static_cast<int>( color1->b ) - static_cast<int>( color2->b );

  float r_mean = (static_cast<float>( color1->r ) + color2->r) / 2.0;

  float term_r = (2.0 + r_mean / 256.0) * delta_r * delta_r;
  float term_g = 4.0 * delta_g * delta_g;
  float term_b = (2.0 + (255.0 - r_mean) / 256.0) * delta_b * delta_b;

  float distance = std::sqrt( term_r + term_g + term_b );

  const float max_distance = 764.833;
  float result = distance / max_distance;

  return (result > 1.0) ? 1.0 : (result < 0.0) ? 0.0 : result;
}

///////////////////////////////////////////////////////////////////////////////

bool Color::operator==( const Color& other ) const {
  if ( rgb_defined != other.rgb_defined ) return false;
  if ( opacity_defined != other.opacity_defined ) return false;

  if ( rgb_defined ) {
    if ( rgb_none != other.rgb_none ) return false;
    if ( !rgb_none && (r != other.r || g != other.g || b != other.b) ) {
      return false;
    }
  }

  if ( opacity_defined && opacity != other.opacity ) {
    return false;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////
