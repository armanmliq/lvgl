/////////////////////////////////////////////////////////////////
/*
  ESP32 | LVGL8 | Ep 3. Base Project for WiFi Settings
  Video Tutorial: https://youtu.be/r62vfOhWXeo
  Created by Eric N. (ThatProject)
*/
/////////////////////////////////////////////////////////////////

// This project was made with a resolution of 480x320.
// If your display's size is different from this,
// you'll need to adjust the size and position of each widget a bit to fit it.

// 0. Setup your display LovyanGFX or TFT_eSPI
// 1. Setup your Touch driver
// 1. Setup your LVGL Config(lv_conf.h)
// 2. Setup your Timezone

#include "WiFi.h"
#include <lvgl.h>
#include <vector>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include "network_selector_sdcard.hpp"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library with default width and height d
#include "time.h"
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 60 * 60; // Set your timezone here
const int daylightOffset_sec = 0;

#include <EEPROM.h>
#define EEPROM_SIZE 128
#define EEPROM_ADDR_WIFI_FLAG 0
#define EEPROM_ADDR_WIFI_CREDENTIAL 4

lv_obj_t *mainScreen;
static lv_style_t border_style;
static lv_style_t popupBox_style;
static lv_obj_t *timeLabel;
static lv_obj_t *settings;
static lv_obj_t *settingBtn;
static lv_obj_t *settingCloseBtn;
static lv_obj_t *settingWiFiSwitch;
static lv_obj_t *wfList;
static lv_obj_t *settinglabel;
static lv_obj_t *mboxConnect;
static lv_obj_t *mboxTitle;
static lv_obj_t *mboxPassword;
static lv_obj_t *mboxConnectBtn;
static lv_obj_t *mboxCloseBtn;
static lv_obj_t *keyboard;
static lv_obj_t *popupBox;
static lv_obj_t *popupBoxCloseBtn;
static lv_timer_t *timer;

static int foundNetworks = 0;
unsigned long networkTimeout = 10 * 1000;
String ssidName, ssidPW;
lv_obj_t *titleImage;

TaskHandle_t ntScanTaskHandler, ntConnectTaskHandler;
std::vector<String> foundWifiList;

void btn_event_cb(lv_event_t *e);
void timerForNetwork(lv_timer_t *timer);
void showingFoundWiFiList();
void buildBody();
void buildSettings();
void list_event_handler(lv_event_t *e);
void networkScanner();
void networkConnector();
void scanWIFITask(void *pvParameters);
void beginWIFITask(void *pvParameters);
void buildPWMsgBox();
void text_input_event_cb(lv_event_t *e);
void makeKeyboard();
void popupMsgBox(String title, String msg);
void setStyle();
void buildStatusBar();
void tryPreviousNetwork();
void updateLocalTime();
void loadWIFICredentialEEPROM();

void debugCb(const char *buf)
{
  Serial.print(String(buf));
}

typedef enum
{
  NONE,
  NETWORK_SEARCHING,
  NETWORK_CONNECTED_POPUP,
  NETWORK_CONNECTED,
  NETWORK_CONNECT_FAILED
} Network_Status_t;
Network_Status_t networkStatus = NONE;

/*Change to your screen resolution*/
static const uint32_t screenWidth = 480;
static const uint32_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];
static lv_style_t label_style;
static lv_obj_t *headerLabel;

#include "initial_register.hpp"
#include "network_selector_network.hpp"
#include "network_selector_flash.hpp"
#include "network_selector_ui.hpp"

#define SD_CS 15

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  uint32_t wh = w * h;
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  while (wh--)
    tft.pushColor(color_p++->full);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

// ###########################################################################################################

// ###########################################################################################################
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t x, y;
  bool pressed = tft.getTouch(&x, &y);

  if (pressed)
  {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void setup()
{
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);
  uint16_t calData[5] = {260, 3653, 224, 3465, 7};
  tft.setTouch(calData);

  lv_init();
  lv_split_jpeg_init();
  lv_log_register_print_cb(debugCb);

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  static lv_fs_drv_t drv; /*Needs to be static or global*/
  drv.cache_size = sizeof(File);
  lv_fs_drv_init(&drv);       /*Basic initialization*/
  drv.letter = 'S';           /*An uppercase letter to identify the drive */
  drv.ready_cb = sd_ready_cb; /*Callback to tell if the drive is ready to use */
  drv.open_cb = sd_open_cb;   /*Callback to open a file */
  drv.close_cb = sd_close_cb; /*Callback to close a file */
  drv.read_cb = sd_read_cb;   /*Callback to read a file */
  drv.write_cb = NULL;        /*Callback to write a file */
  drv.seek_cb = sd_seek_cb;   /*Callback to seek in a file (Move cursor) */
  drv.tell_cb = sd_tell_cb;   /*Callback to tell the cursor position  */
  drv.dir_open_cb = NULL;     /*Callback to open directory to read its content */
  drv.dir_read_cb = NULL;     /*Callback to read a directory's content */
  drv.dir_close_cb = NULL;    /*Callback to close a directory */

  // drv.user_data = my_user_data; /*Any custom data if required*/
  lv_fs_drv_register(&drv);
  Serial.println("I registered drv!");

  setStyle();
  buildStatusBar();
  buildBody();
  buildSettings();
}

void loop()
{
  lv_timer_handler();
  delay(5);
}

void updateLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return;
  }
  char hourMin[6];
  strftime(hourMin, 6, "%H:%M", &timeinfo);
  String hourMinWithSymbol = String(hourMin);
  hourMinWithSymbol += "   ";
  hourMinWithSymbol += LV_SYMBOL_BATTERY_1;
  lv_label_set_text(timeLabel, hourMinWithSymbol.c_str());
}
