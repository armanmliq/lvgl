#include "WiFi.h"
#include <lvgl.h>
#include <vector>
#include <TFT_eSPI.h>

#include "sdcard.hpp"
#include "other_setup.hpp"
#include "ui.hpp"

void setup()
{
  Serial.begin(115200);
  lvgl_setup();
  display_setup();
  sdcard_setup();
  buildStatusBar();
}

void loop()
{
  lv_timer_handler();
  delay(5);
}