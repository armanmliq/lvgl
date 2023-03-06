// ###########################################################################################################
//
// ###########################################################################################################
#include <lvgl.h>

// ###########################################################################################################
#define TFT_eSPIlib // comment out to use MCUFRIEND_kbv

#ifdef TFT_eSPIlib
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#else
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#endif

#include <TouchScreen.h> // some colours to play with
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
// adjust pressure sensitivity - note works 'backwards'
#define MINPRESSURE 100
#define MAXPRESSURE 16000
const int coords[] = {3600, 370, 80, 4000}; // portrait - left, right, top, bottom

const int rotation = 0; //  in rotation order - portrait, landscape, etc

const int XP = 21, XM = 12, YP = 14, YM = 22; // default ESP32 Uno touchscreen pins
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 500);
// ###########################################################################################################
/*Change to your screen resolution*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];
 
boolean Touch_getXY(uint16_t *x, uint16_t *y, boolean showTouch)
{
  // TSPoint p = tft.getPoint2(tft.height(), tft.width());
  TSPoint p = ts.getPoint();

  pinMode(YP, OUTPUT); // restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH); // because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed)
  {
    switch (rotation)
    {
    case 0: // portrait
      *x = map(p.x, coords[0], coords[1], 0, tft.width());
      *y = map(p.y, coords[2], coords[3], 0, tft.height());
      break;
    case 1: // landscape
      *x = map(p.y, coords[1], coords[0], 0, tft.width());
      *y = map(p.x, coords[2], coords[3], 0, tft.height());
      break;
    case 2: // portrait inverted
      *x = map(p.x, coords[1], coords[0], 0, tft.width());
      *y = map(p.y, coords[3], coords[2], 0, tft.height());
      break;
    case 3: // landscape inverted
      *x = map(p.y, coords[0], coords[1], 0, tft.width());
      *y = map(p.x, coords[3], coords[2], 0, tft.height());
      break;
    }
    if (showTouch)
      tft.fillCircle(*x, *y, 2, YELLOW);
    Serial.printf("z:%d,x:%d,y:%d,px:%d,py:%d\n", p.z, *x, *y, p.x, p.y);
  }
  return pressed;
}
// ###########################################################################################################
/* Display flushing */
// ###########################################################################################################
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

// ###########################################################################################################
//
// ###########################################################################################################
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;

  TSPoint p = ts.getPoint();

  pinMode(YP, OUTPUT); // restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH); // because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed)
  {
    data->state = LV_INDEV_STATE_PR;
    switch (rotation)
    {
    case 0: // portrait
      data->point.x = map(p.x, coords[0], coords[1], 0, tft.width());
      data->point.y = map(p.y, coords[2], coords[3], 0, tft.height());  
      break;
    case 1: // landscape
      data->point.x = map(p.y, coords[1], coords[0], 0, tft.width());
      data->point.y = map(p.x, coords[2], coords[3], 0, tft.height());
      break;
    case 2: // portrait inverted
      data->point.x = map(p.x, coords[1], coords[0], 0, tft.width());
      data->point.y = map(p.y, coords[3], coords[2], 0, tft.height());
      break;
    case 3: // landscape inverted
      data->point.x = map(p.y, coords[0], coords[1], 0, tft.width());
      data->point.y = map(p.x, coords[3], coords[2], 0, tft.height());
      break;
    }
    // if (showTouch)
    //   tft.fillCircle(data->point.x, data->point.y, 2, YELLOW);
    Serial.printf("z:%d,x:%d,y:%d,px:%d,py:%d\n", p.z, data->point.x, data->point.y, p.x, p.y);
  }else{
    data->state = LV_INDEV_STATE_REL;
  }
}

// ###########################################################################################################

// ###########################################################################################################
static void ta_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);
  lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);
  if (code == LV_EVENT_FOCUSED)
  {
    lv_keyboard_set_textarea(kb, ta);
    lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
  }

  if (code == LV_EVENT_DEFOCUSED)
  {
    lv_keyboard_set_textarea(kb, NULL);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
  }
}

// ###########################################################################################################
//
// ###########################################################################################################
void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */

  tft.begin();        /* TFT init */
  tft.setRotation(1); /* Landscape orientation, flipped */

  tft.begin();
  tft.setRotation(rotation);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  /*Create a keyboard to use it with an of the text areas*/
  lv_obj_t *kb = lv_keyboard_create(lv_scr_act());

  /*Create a text area. The keyboard will write here*/
  lv_obj_t *ta;
  ta = lv_textarea_create(lv_scr_act());
  lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, 10);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
  lv_textarea_set_placeholder_text(ta, "Hello");
  lv_obj_set_size(ta, 140, 80);

  ta = lv_textarea_create(lv_scr_act());
  lv_obj_align(ta, LV_ALIGN_TOP_RIGHT, -10, 10);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
  lv_obj_set_size(ta, 140, 80);

  lv_keyboard_set_textarea(kb, ta);
}

// ###########################################################################################################
//
// ###########################################################################################################
void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}