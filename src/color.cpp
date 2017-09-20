//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Color.cpp
// Created   : 2017/08/18 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

static glm::vec4 colorfromhex(const unsigned int hex)
{
	return glm::vec4(float((hex >> 16) & 0xFF) / 255.0f, float((hex >> 8) & 0xFF) / 255.0f, float((hex >> 0) & 0xFF) / 255.0f, 1.0f);
}

const glm::vec4 VzColor::AliceBlue = colorfromhex(0xF0F8FF);
const glm::vec4 VzColor::AntiqueWhite = colorfromhex(0xFAEBD7);
const glm::vec4 VzColor::Aqua = colorfromhex(0x00FFFF);
const glm::vec4 VzColor::Aquamarine = colorfromhex(0x7FFFD4);
const glm::vec4 VzColor::Azure = colorfromhex(0xF0FFFF);
const glm::vec4 VzColor::Beige = colorfromhex(0xF5F5DC);
const glm::vec4 VzColor::Bisque = colorfromhex(0xFFE4C4);
const glm::vec4 VzColor::Black = colorfromhex(0x000000);
const glm::vec4 VzColor::BlanchedAlmond = colorfromhex(0xFFEBCD);
const glm::vec4 VzColor::Blue = colorfromhex(0x0000FF);
const glm::vec4 VzColor::BlueViolet = colorfromhex(0x8A2BE2);
const glm::vec4 VzColor::Brown = colorfromhex(0xA52A2A);
const glm::vec4 VzColor::BurlyWood = colorfromhex(0xDEB887);
const glm::vec4 VzColor::CadetBlue = colorfromhex(0x5F9EA0);
const glm::vec4 VzColor::Chartreuse = colorfromhex(0x7FFF00);
const glm::vec4 VzColor::Chocolate = colorfromhex(0xD2691E);
const glm::vec4 VzColor::Coral = colorfromhex(0xFF7F50);
const glm::vec4 VzColor::CornflowerBlue = colorfromhex(0x6495ED);
const glm::vec4 VzColor::Cornsilk = colorfromhex(0xFFF8DC);
const glm::vec4 VzColor::Crimson = colorfromhex(0xDC143C);
const glm::vec4 VzColor::Cyan = colorfromhex(0x00FFFF);
const glm::vec4 VzColor::DarkBlue = colorfromhex(0x00008B);
const glm::vec4 VzColor::DarkCyan = colorfromhex(0x008B8B);
const glm::vec4 VzColor::DarkGoldenRod = colorfromhex(0xB8860B);
const glm::vec4 VzColor::DarkGray = colorfromhex(0x303030);
const glm::vec4 VzColor::DarkGreen = colorfromhex(0x006400);
const glm::vec4 VzColor::DarkKhaki = colorfromhex(0xBDB76B);
const glm::vec4 VzColor::DarkMagenta = colorfromhex(0x8B008B);
const glm::vec4 VzColor::DarkOliveGreen = colorfromhex(0x556B2F);
const glm::vec4 VzColor::DarkOrange = colorfromhex(0xFF8C00);
const glm::vec4 VzColor::DarkOrchid = colorfromhex(0x9932CC);
const glm::vec4 VzColor::DarkRed = colorfromhex(0x8B0000);
const glm::vec4 VzColor::DarkSalmon = colorfromhex(0xE9967A);
const glm::vec4 VzColor::DarkSeaGreen = colorfromhex(0x8FBC8F);
const glm::vec4 VzColor::DarkSlateBlue = colorfromhex(0x483D8B);
const glm::vec4 VzColor::DarkSlateGray = colorfromhex(0x2F4F4F);
const glm::vec4 VzColor::DarkTurquoise = colorfromhex(0x00CED1);
const glm::vec4 VzColor::DarkViolet = colorfromhex(0x9400D3);
const glm::vec4 VzColor::DeepPink = colorfromhex(0xFF1493);
const glm::vec4 VzColor::DeepSkyBlue = colorfromhex(0x00BFFF);
const glm::vec4 VzColor::DimGray = colorfromhex(0x696969);
const glm::vec4 VzColor::DodgerBlue = colorfromhex(0x1E90FF);
const glm::vec4 VzColor::FireBrick = colorfromhex(0xB22222);
const glm::vec4 VzColor::FloralWhite = colorfromhex(0xFFFAF0);
const glm::vec4 VzColor::ForestGreen = colorfromhex(0x228B22);
const glm::vec4 VzColor::Fuchsia = colorfromhex(0xFF00FF);
const glm::vec4 VzColor::Gainsboro = colorfromhex(0xDCDCDC);
const glm::vec4 VzColor::GhostWhite = colorfromhex(0xF8F8FF);
const glm::vec4 VzColor::Gold = colorfromhex(0xFFD700);
const glm::vec4 VzColor::GoldenRod = colorfromhex(0xDAA520);
const glm::vec4 VzColor::Gray = colorfromhex(0x808080);
const glm::vec4 VzColor::Green = colorfromhex(0x008000);
const glm::vec4 VzColor::GreenYellow = colorfromhex(0xADFF2F);
const glm::vec4 VzColor::HoneyDew = colorfromhex(0xF0FFF0);
const glm::vec4 VzColor::HotPink = colorfromhex(0xFF69B4);
const glm::vec4 VzColor::IndianRed = colorfromhex(0xCD5C5C);
const glm::vec4 VzColor::Indigo = colorfromhex(0x4B0082);
const glm::vec4 VzColor::Ivory = colorfromhex(0xFFFFF0);
const glm::vec4 VzColor::Khaki = colorfromhex(0xF0E68C);
const glm::vec4 VzColor::Lavender = colorfromhex(0xE6E6FA);
const glm::vec4 VzColor::LavenderBlush = colorfromhex(0xFFF0F5);
const glm::vec4 VzColor::LawnGreen = colorfromhex(0x7CFC00);
const glm::vec4 VzColor::LemonChiffon = colorfromhex(0xFFFACD);
const glm::vec4 VzColor::LightBlue = colorfromhex(0xADD8E6);
const glm::vec4 VzColor::LightCoral = colorfromhex(0xF08080);
const glm::vec4 VzColor::LightCyan = colorfromhex(0xE0FFFF);
const glm::vec4 VzColor::LightGoldenRodYellow = colorfromhex(0xFAFAD2);
const glm::vec4 VzColor::LightGray = colorfromhex(0xD3D3D3);
const glm::vec4 VzColor::LightGreen = colorfromhex(0x90EE90);
const glm::vec4 VzColor::LightPink = colorfromhex(0xFFB6C1);
const glm::vec4 VzColor::LightSalmon = colorfromhex(0xFFA07A);
const glm::vec4 VzColor::LightSeaGreen = colorfromhex(0x20B2AA);
const glm::vec4 VzColor::LightSkyBlue = colorfromhex(0x87CEFA);
const glm::vec4 VzColor::LightSlateGray = colorfromhex(0x778899);
const glm::vec4 VzColor::LightSteelBlue = colorfromhex(0xB0C4DE);
const glm::vec4 VzColor::LightYellow = colorfromhex(0xFFFFE0);
const glm::vec4 VzColor::Lime = colorfromhex(0x00FF00);
const glm::vec4 VzColor::LimeGreen = colorfromhex(0x32CD32);
const glm::vec4 VzColor::Linen = colorfromhex(0xFAF0E6);
const glm::vec4 VzColor::Magenta = colorfromhex(0xFF00FF);
const glm::vec4 VzColor::Maroon = colorfromhex(0x800000);
const glm::vec4 VzColor::MediumAquaMarine = colorfromhex(0x66CDAA);
const glm::vec4 VzColor::MediumBlue = colorfromhex(0x0000CD);
const glm::vec4 VzColor::MediumOrchid = colorfromhex(0xBA55D3);
const glm::vec4 VzColor::MediumPurple = colorfromhex(0x9370DB);
const glm::vec4 VzColor::MediumSeaGreen = colorfromhex(0x3CB371);
const glm::vec4 VzColor::MediumSlateBlue = colorfromhex(0x7B68EE);
const glm::vec4 VzColor::MediumSpringGreen = colorfromhex(0x00FA9A);
const glm::vec4 VzColor::MediumTurquoise = colorfromhex(0x48D1CC);
const glm::vec4 VzColor::MediumVioletRed = colorfromhex(0xC71585);
const glm::vec4 VzColor::MidnightBlue = colorfromhex(0x191970);
const glm::vec4 VzColor::MintCream = colorfromhex(0xF5FFFA);
const glm::vec4 VzColor::MistyRose = colorfromhex(0xFFE4E1);
const glm::vec4 VzColor::Moccasin = colorfromhex(0xFFE4B5);
const glm::vec4 VzColor::NavajoWhite = colorfromhex(0xFFDEAD);
const glm::vec4 VzColor::Navy = colorfromhex(0x000080);
const glm::vec4 VzColor::OldLace = colorfromhex(0xFDF5E6);
const glm::vec4 VzColor::Olive = colorfromhex(0x808000);
const glm::vec4 VzColor::OliveDrab = colorfromhex(0x6B8E23);
const glm::vec4 VzColor::Orange = colorfromhex(0xFFA500);
const glm::vec4 VzColor::OrangeRed = colorfromhex(0xFF4500);
const glm::vec4 VzColor::Orchid = colorfromhex(0xDA70D6);
const glm::vec4 VzColor::PaleGoldenRod = colorfromhex(0xEEE8AA);
const glm::vec4 VzColor::PaleGreen = colorfromhex(0x98FB98);
const glm::vec4 VzColor::PaleTurquoise = colorfromhex(0xAFEEEE);
const glm::vec4 VzColor::PaleVioletRed = colorfromhex(0xDB7093);
const glm::vec4 VzColor::PapayaWhip = colorfromhex(0xFFEFD5);
const glm::vec4 VzColor::PeachPuff = colorfromhex(0xFFDAB9);
const glm::vec4 VzColor::Peru = colorfromhex(0xCD853F);
const glm::vec4 VzColor::Pink = colorfromhex(0xFFC0CB);
const glm::vec4 VzColor::Plum = colorfromhex(0xDDA0DD);
const glm::vec4 VzColor::PowderBlue = colorfromhex(0xB0E0E6);
const glm::vec4 VzColor::Purple = colorfromhex(0x800080);
const glm::vec4 VzColor::RebeccaPurple = colorfromhex(0x663399);
const glm::vec4 VzColor::Red = colorfromhex(0xFF0000);
const glm::vec4 VzColor::RosyBrown = colorfromhex(0xBC8F8F);
const glm::vec4 VzColor::RoyalBlue = colorfromhex(0x4169E1);
const glm::vec4 VzColor::SaddleBrown = colorfromhex(0x8B4513);
const glm::vec4 VzColor::Salmon = colorfromhex(0xFA8072);
const glm::vec4 VzColor::SandyBrown = colorfromhex(0xF4A460);
const glm::vec4 VzColor::SeaGreen = colorfromhex(0x2E8B57);
const glm::vec4 VzColor::SeaShell = colorfromhex(0xFFF5EE);
const glm::vec4 VzColor::Sienna = colorfromhex(0xA0522D);
const glm::vec4 VzColor::Silver = colorfromhex(0xC0C0C0);
const glm::vec4 VzColor::SkyBlue = colorfromhex(0x87CEEB);
const glm::vec4 VzColor::SlateBlue = colorfromhex(0x6A5ACD);
const glm::vec4 VzColor::SlateGray = colorfromhex(0x708090);
const glm::vec4 VzColor::Snow = colorfromhex(0xFFFAFA);
const glm::vec4 VzColor::SpringGreen = colorfromhex(0x00FF7F);
const glm::vec4 VzColor::SteelBlue = colorfromhex(0x4682B4);
const glm::vec4 VzColor::Tan = colorfromhex(0xD2B48C);
const glm::vec4 VzColor::Teal = colorfromhex(0x008080);
const glm::vec4 VzColor::Thistle = colorfromhex(0xD8BFD8);
const glm::vec4 VzColor::Tomato = colorfromhex(0xFF6347);
const glm::vec4 VzColor::Turquoise = colorfromhex(0x40E0D0);
const glm::vec4 VzColor::Violet = colorfromhex(0xEE82EE);
const glm::vec4 VzColor::Wheat = colorfromhex(0xF5DEB3);
const glm::vec4 VzColor::White = colorfromhex(0xFFFFFF);
const glm::vec4 VzColor::WhiteSmoke = colorfromhex(0xF5F5F5);
const glm::vec4 VzColor::Yellow = colorfromhex(0xFFFF00);
const glm::vec4 VzColor::YellowGreen = colorfromhex(0x9ACD32);