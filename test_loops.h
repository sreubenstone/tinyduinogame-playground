#define LOOP_PROG loopCircles

#include "images_test.h"
#include "images_grasstile.h"
#include "images_ground_mud.h"
#include "images_tileset.h"

void loopRects() {
  for (int r = 0; r < 4;r+=1) {
    for (int g = 0; g < 8; g+=1) {
      for (int b = 0; b<8;b+=1) {
        int col = r|(g<<2)|(b<<5);
        TinyScreenC_drawRectC((r+b*4)*4,g*4,4,3, 1, col);
        TinyScreenC_drawRectC((r+b*4)*4,g*4+3,3,1, 1, col);
      }
    }
  }
}

void loopCircles() {
  RenderScreen_drawCircle(32,32,(micros()>>17)%240+10,0xff);
}

static const char simpleTownMapData[] PROGMEM = {
  0x10,0x11,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10,
  0x10,0x11,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10,
  0x10,0x10,0x11,0x09, 0x10,0x10,0x22,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10,
  0x10,0x10,0x10,0x09, 0x05,0x00,0x04,0x02, 0x06,0x10,0x10,0x10, 0x10,0x10,0x10,0x10,
  
  0x10,0x10,0x10,0x07, 0x08,0x08,0x08,0x08, 0x08,0x08,0x10,0x10, 0x10,0x10,0x10,0x10,
  0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10,
  0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10,
  0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x10,
};
static const char simpleTownMapDataLayer[] PROGMEM = {
  0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff, 0x20,0x21,0xff,0x28, 0x29,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0x18,0x13,0xff,0xff, 0xff,0xff,0xff,0xff,
  
  0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0x16, 0x17,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0x16,0x17,0xff,0xff, 0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,
};
static unsigned int simpleTownMapPosX;
static unsigned int simpleTownMapPosY;
int loopSimpleTownMoveTest() {
  _renderScreen.flags|=RENDERSCREEN_FLAG_NOCLEAR;
  int n = 0;
  _renderScreen.imageIncludes[0] = &_image_tileset_opaque;
  _renderScreen.imageIncludes[1] = &_image_tileset;
  
  simpleTownMapPosX += rightStick.normX >>4;
  simpleTownMapPosY += rightStick.normY >>4;
  char screenX = -((simpleTownMapPosX >> 4)&0xf);
  char screenY = -((simpleTownMapPosY >> 4)&0xf);
  char limy = micros()/500000%6;
  char limx = micros()/500000%9;
  for (char y = 0;y<5;y+=1) {
    unsigned char mapY = ((simpleTownMapPosY >> 8) + y)&0x7;
    for (char x = 0;x<7;x+=1) {
      unsigned char mapX = ((simpleTownMapPosX >> 8) + x)&0xf;
      unsigned char mapPos = (mapY << 4) + mapX;
      unsigned char uv = pgm_read_byte(&simpleTownMapData[mapPos]);
      unsigned char v = uv & 0xf0;
      unsigned char u = (uv & 0xf)<<4;
      RenderScreen_drawRectTexturedUV(screenX + x*16,screenY + y*16,16,16,0,u,v);
      uv = pgm_read_byte(&simpleTownMapDataLayer[mapPos]);
      if (uv != 0xff) {
        v = uv & 0xf0;
        u = (uv & 0xf)<<4;
        RenderScreen_drawRectTexturedUV(screenX + x*16,screenY + y*16,16,16,1,u,v);
          
      }
      n++;
    }
    
  }
  return n;
}