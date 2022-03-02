//
// Created by tpasl on 02/03/2022.
//

#ifndef ASGEGAME_TILERECT_H
#define ASGEGAME_TILERECT_H

class TileRect
{
 public:
  TileRect(unsigned int _l, unsigned int _t, unsigned int _r, unsigned int _b);
  ~TileRect();
  unsigned int top();
  unsigned int left();
  unsigned int width();
  unsigned int height();

 private:
  unsigned int l;
  unsigned int t;
  unsigned int r;
  unsigned int b;
};

#endif // ASGEGAME_TILERECT_H
