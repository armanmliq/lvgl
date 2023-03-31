#define SD_CS 15

TFT_eSPI tft = TFT_eSPI();
static const uint32_t screenWidth = 480;
static const uint32_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];
static lv_style_t label_style;
static lv_obj_t *headerLabel;

void debugCb(const char *buf)
{
  Serial.print(String(buf));
}

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

void sdcard_setup()
{
  if (!SD.begin(SD_CS))
  {
    Serial.println("Card Mount Failed");
    return;
  }
  else
  {
    Serial.println("SD CARD SUCCESSFUL");
  }

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

  lv_fs_drv_register(&drv);
  Serial.println("I registered drv!");
}

void display_setup()
{
  tft.begin();
  tft.setRotation(1);
  uint16_t calData[5] = {260, 3653, 224, 3465, 7};
  tft.setTouch(calData);
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
}

void lvgl_setup()
{
  lv_init();
  lv_split_jpeg_init();
  lv_log_register_print_cb(debugCb);
}