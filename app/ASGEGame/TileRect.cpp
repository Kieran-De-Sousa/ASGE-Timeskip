//
// Created by tpasl on 02/03/2022.
//

#include "TileRect.h"
TileRect::TileRect(unsigned int _l, unsigned int _t, unsigned int _r, unsigned int _b)
{
  l = _l;
  t = _t;
  r = _r;
  b = _b;
}
unsigned int TileRect::top()
{
  return t;
}
unsigned int TileRect::left()
{
  return l;
}
unsigned int TileRect::width()
{
  return r;
}
unsigned int TileRect::height()
{
  return b;
}
