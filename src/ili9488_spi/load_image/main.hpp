#include "WiFi.h"
#include <lvgl.h>
#include <vector>
#include <TFT_eSPI.h>
#include "hero_100_100.h"
#include "jiaraiya.h"
#include "facebook.h"
#include "water_pump.h"
#include "sdcard.hpp"
#include "other_setup.hpp"
#include "ui.hpp"

void setup()
{
  Serial.begin(115200);
  lvgl_setup();
  display_setup();
  sdcard_setup();
  // load_image_hero();
  // load_image_jiraiya();
  // load_image_facebook();
  // buildStatusBar();
  buildBody();
}

void loop()
{
  lv_timer_handler();
  delay(5);
}