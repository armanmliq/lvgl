static lv_obj_t *settingBtn;
static lv_obj_t *timeLabel;
lv_obj_t *mainScreen;
static lv_style_t border_style;
static lv_style_t popupBox_style;

void buildStatusBar()
{
  static lv_style_t style_btn;
  lv_style_init(&style_btn);
  lv_style_set_bg_color(&style_btn, lv_color_hex(0xC5C5C5));
  lv_style_set_bg_opa(&style_btn, LV_OPA_50);

  lv_obj_t *statusBar = lv_obj_create(lv_scr_act());
  lv_obj_set_size(statusBar, tft.width(), 30);
  lv_obj_align(statusBar, LV_ALIGN_TOP_MID, 0, 0);

  lv_obj_remove_style(statusBar, NULL, LV_PART_SCROLLBAR | LV_STATE_ANY);

  timeLabel = lv_label_create(statusBar);
  lv_obj_set_size(timeLabel, tft.width() - 50, 30);

  lv_label_set_text(timeLabel, "WiFi Not Connected!    ");
  lv_obj_align(timeLabel, LV_ALIGN_LEFT_MID, 8, 4);

  settingBtn = lv_btn_create(statusBar);
  lv_obj_set_size(settingBtn, 30, 30);
  lv_obj_align(settingBtn, LV_ALIGN_RIGHT_MID, 0, 0);

  lv_obj_t *label = lv_label_create(settingBtn); /*Add a label to the button*/
  lv_label_set_text(label, LV_SYMBOL_SETTINGS);  /*Set the labels text*/
  lv_obj_center(label);
}
void setStyle()
{
  lv_style_init(&border_style);
  lv_style_set_border_width(&border_style, 2);
  lv_style_set_border_color(&border_style, lv_color_black());
  lv_style_init(&popupBox_style);
  lv_style_set_radius(&popupBox_style, 10);
  lv_style_set_bg_opa(&popupBox_style, LV_OPA_COVER);
  lv_style_set_border_color(&popupBox_style, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_border_width(&popupBox_style, 5);
}
void load_image_jiraiya(lv_obj_t *screen)
{
  LV_IMG_DECLARE(jiaraiya);
  lv_obj_t *img = lv_img_create(screen);
  lv_img_set_src(img, &jiaraiya);
  lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_size(img, 480, 320);
}
void load_image_facebook(lv_obj_t *screen)
{
  LV_IMG_DECLARE(facebook);
  lv_obj_t *img = lv_img_create(screen);
  lv_img_set_src(img, &facebook);
  lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_size(img, 50, 50);
}
void load_image_water(lv_obj_t *screen)
{
  LV_IMG_DECLARE(water_pump);
  lv_obj_t *img = lv_img_create(screen);
  lv_obj_align(img, LV_ALIGN_CENTER, 50, 100);
  lv_img_set_src(img, &water_pump);
  lv_obj_set_size(img, 200, 200);
  // lv_label_set_text(timeLabel, "WiFi Not Connected!    ");
  // lv_obj_align(timeLabel, LV_ALIGN_LEFT_MID, 8, 4);
}
void load_image_hero(lv_obj_t *screen)
{
  LV_IMG_DECLARE(hero);
  lv_obj_t *img = lv_img_create(screen);
  lv_img_set_src(img, &hero);
  lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_size(img, 100, 100);
}

void buildBody()
{
  lv_obj_t *bodyScreen = lv_obj_create(lv_scr_act());
  lv_obj_add_style(bodyScreen, &border_style, 0);
  lv_obj_set_size(bodyScreen, tft.width(), tft.height());
  lv_obj_align(bodyScreen, LV_ALIGN_BOTTOM_MID, 0, 0);
  load_image_hero(bodyScreen);
}