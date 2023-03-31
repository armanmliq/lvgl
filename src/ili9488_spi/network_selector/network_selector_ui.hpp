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

  lv_obj_add_event_cb(settingBtn, btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_t *label = lv_label_create(settingBtn); /*Add a label to the button*/
  lv_label_set_text(label, LV_SYMBOL_SETTINGS);  /*Set the labels text*/
  lv_obj_center(label);
}

void btn_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *btn = lv_event_get_target(e);

  if (code == LV_EVENT_CLICKED)
  {
    if (btn == settingBtn)
    {
      lv_obj_clear_flag(settings, LV_OBJ_FLAG_HIDDEN);
    }
    else if (btn == settingCloseBtn)
    {
      lv_obj_add_flag(settings, LV_OBJ_FLAG_HIDDEN);
    }
    else if (btn == mboxConnectBtn)
    {
      ssidPW = String(lv_textarea_get_text(mboxPassword));
      networkConnector();
      lv_obj_move_background(mboxConnect);
      popupMsgBox("Connecting!", "Attempting to connect to the selected network.");
    }
    else if (btn == mboxCloseBtn)
    {
      lv_obj_move_background(mboxConnect);
    }
    else if (btn == popupBoxCloseBtn)
    {
      lv_obj_move_background(popupBox);
    }
  }
  else if (code == LV_EVENT_VALUE_CHANGED)
  {
    if (btn == settingWiFiSwitch)
    {
      if (lv_obj_has_state(btn, LV_STATE_CHECKED))
      {
        if (ntScanTaskHandler == NULL)
        {
          networkStatus = NETWORK_SEARCHING;
          networkScanner();
          timer = lv_timer_create(timerForNetwork, 1000, wfList);
          lv_list_add_text(wfList, "WiFi: Looking for Networks...");
        }
      }
      else
      {
        if (ntScanTaskHandler != NULL)
        {
          networkStatus = NONE;
          vTaskDelete(ntScanTaskHandler);
          ntScanTaskHandler = NULL;
          lv_timer_del(timer);
          lv_obj_clean(wfList);
        }

        if (WiFi.status() == WL_CONNECTED)
        {
          WiFi.disconnect(true);
          lv_label_set_text(timeLabel, "WiFi Not Connected!    " LV_SYMBOL_CLOSE);
        }
      }
    }
  }
}
void showingFoundWiFiList()
{
  if (foundWifiList.size() == 0 || foundNetworks == foundWifiList.size())
    return;

  lv_obj_clean(wfList);
  lv_list_add_text(wfList, foundWifiList.size() > 1 ? "WiFi: Found Networks" : "WiFi: Not Found!");

  for (std::vector<String>::iterator item = foundWifiList.begin(); item != foundWifiList.end(); ++item)
  {
    lv_obj_t *btn = lv_list_add_btn(wfList, LV_SYMBOL_WIFI, (*item).c_str());
    lv_obj_add_event_cb(btn, list_event_handler, LV_EVENT_CLICKED, NULL);
    delay(1);
  }

  foundNetworks = foundWifiList.size();
}

void buildBody()
{
  lv_obj_t *bodyScreen = lv_obj_create(lv_scr_act());
  lv_obj_add_style(bodyScreen, &border_style, 0);
  lv_obj_set_size(bodyScreen, tft.width(), tft.height() - 34);
  lv_obj_align(bodyScreen, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_t *label = lv_label_create(bodyScreen);
  lv_label_set_text(label, "Your Contents");
  lv_obj_center(label);
}

void buildSettings()
{
  settings = lv_obj_create(lv_scr_act());
  lv_obj_add_style(settings, &border_style, 0);
  lv_obj_set_size(settings, tft.width() - 100, tft.height() - 40);
  lv_obj_align(settings, LV_ALIGN_TOP_RIGHT, -20, 20);

  settinglabel = lv_label_create(settings);
  lv_label_set_text(settinglabel, "Settings " LV_SYMBOL_SETTINGS);
  lv_obj_align(settinglabel, LV_ALIGN_TOP_LEFT, 0, 0);

  settingCloseBtn = lv_btn_create(settings);
  lv_obj_set_size(settingCloseBtn, 30, 30);
  lv_obj_align(settingCloseBtn, LV_ALIGN_TOP_RIGHT, 0, -10);
  lv_obj_add_event_cb(settingCloseBtn, btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_t *btnSymbol = lv_label_create(settingCloseBtn);
  
  lv_label_set_text(btnSymbol, LV_SYMBOL_CLOSE);
  lv_obj_center(btnSymbol);

  settingWiFiSwitch = lv_switch_create(settings);
  lv_obj_add_event_cb(settingWiFiSwitch, btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_align_to(settingWiFiSwitch, settinglabel, LV_ALIGN_TOP_RIGHT, 60, -10);
  lv_obj_add_flag(settings, LV_OBJ_FLAG_HIDDEN);

  wfList = lv_list_create(settings);
  lv_obj_set_size(wfList, tft.width() - 140, 210);
  lv_obj_align_to(wfList, settinglabel, LV_ALIGN_TOP_LEFT, 0, 30);
}

void list_event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED)
  {
    String selectedItem = String(lv_list_get_btn_text(wfList, obj));
    for (int i = 0; i < selectedItem.length() - 1; i++)
    {
      if (selectedItem.substring(i, i + 2) == " (")
      {
        ssidName = selectedItem.substring(0, i);
        lv_label_set_text_fmt(mboxTitle, "Selected WiFi SSID: %s", ssidName);
        lv_obj_move_foreground(mboxConnect);
        break;
      }
    }
  }
}

void lv_example_dropdown_3(void)
{
    /*Create a drop down list*/
    lv_obj_t * dropdown = lv_dropdown_create(lv_scr_act());
    lv_obj_align(dropdown, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_dropdown_set_options(dropdown, "New project\n"
                            "New file\n"
                            "Save\n"
                            "Save as ...\n"
                            "Open project\n"
                            "Recent projects\n"
                            "Preferences\n"
                            "Exit");

    /*Set a fixed text to display on the button of the drop-down list*/
    lv_dropdown_set_text(dropdown, "Menu");

    /*Use a custom image as down icon and flip it when the list is opened*/
    LV_IMG_DECLARE(img_caret_down)
    lv_dropdown_set_symbol(dropdown, &img_caret_down);
    lv_obj_set_style_transform_angle(dropdown, 1800, LV_PART_INDICATOR | LV_STATE_CHECKED);

    /*In a menu we don't need to show the last clicked item*/
    lv_dropdown_set_selected_highlight(dropdown, false);

    // lv_obj_add_event_cb(dropdown, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}