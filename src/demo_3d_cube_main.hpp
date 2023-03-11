#include "Demo_3D_cube/Demo_3D_cube.hpp"
/***********************************************************************************************************************************/
void setup()
{

  tft.init();

  h = tft.height();
  w = tft.width();

  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);

  cube();

  fact = 180 / 3.14159259; // conversion from degrees to radians.

  Xoff = 240; // Position the centre of the 3d conversion space into the centre of the TFT screen.
  Yoff = 160;
  Zoff = 550; // Z offset in 3D space (smaller = closer and bigger rendering)
}

/***********************************************************************************************************************************/
void loop()
{

  // Rotate around x and y axes in 1 degree increments
  Xan++;
  Yan++;

  Yan = Yan % 360;
  Xan = Xan % 360; // prevents overflow.

  SetVars(); // sets up the global vars to do the 3D conversion.

  // Zoom in and out on Z axis within limits
  // the cube intersects with the screen for values < 160
  Zoff += inc;
  if (Zoff > 500)
    inc = -1; // Switch to zoom in
  else if (Zoff < 160)
    inc = 1; // Switch to zoom out

  for (int i = 0; i < LinestoRender; i++)
  {
    ORender[i] = Render[i];            // stores the old line segment so we can delete it later.
    ProcessLine(&Render[i], Lines[i]); // converts the 3d line segments to 2d.
  }
  RenderImage(); // go draw it!

  delay(14); // Delay to reduce loop rate (reduces flicker caused by aliasing with TFT screen refresh rate)
}