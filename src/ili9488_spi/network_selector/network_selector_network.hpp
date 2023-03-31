
void timerForNetwork(lv_timer_t *timer)
{
  LV_UNUSED(timer);

  switch (networkStatus)
  {
  case NETWORK_SEARCHING:
    showingFoundWiFiList();
    break;
  case NETWORK_CONNECTED_POPUP:
    popupMsgBox("WiFi Connected!", "Now you'll get the current time soon.");
    networkStatus = NETWORK_CONNECTED;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    break;

  case NETWORK_CONNECTED:
    showingFoundWiFiList();
    updateLocalTime();
    break;

  case NETWORK_CONNECT_FAILED:
    networkStatus = NETWORK_SEARCHING;
    popupMsgBox("Oops!", "Please check your wifi password and try again.");
    break;

  default:
    break;
  }
}

void buildPWMsgBox()
{
  mboxConnect = lv_obj_create(lv_scr_act());
  lv_obj_add_style(mboxConnect, &border_style, 0);
  lv_obj_set_size(mboxConnect, tft.width() * 2 / 3, tft.height() / 2);
  lv_obj_center(mboxConnect);
  mboxTitle = lv_label_create(mboxConnect);
  lv_label_set_text(mboxTitle, "Selected WiFi SSID: ThatProject");
  lv_obj_align(mboxTitle, LV_ALIGN_TOP_LEFT, 0, 0);

  mboxPassword = lv_textarea_create(mboxConnect);
  lv_obj_set_size(mboxPassword, tft.width() / 2, 40);
  lv_obj_align_to(mboxPassword, mboxTitle, LV_ALIGN_TOP_LEFT, 0, 30);
  lv_textarea_set_placeholder_text(mboxPassword, "Password?");
  lv_obj_add_event_cb(mboxPassword, text_input_event_cb, LV_EVENT_ALL, keyboard);

  mboxConnectBtn = lv_btn_create(mboxConnect);
  lv_obj_add_event_cb(mboxConnectBtn, btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_align(mboxConnectBtn, LV_ALIGN_BOTTOM_LEFT, 0, 0);
  lv_obj_t *btnLabel = lv_label_create(mboxConnectBtn);
  lv_label_set_text(btnLabel, "Connect");
  lv_obj_center(btnLabel);

  mboxCloseBtn = lv_btn_create(mboxConnect);
  lv_obj_add_event_cb(mboxCloseBtn, btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_align(mboxCloseBtn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_t *btnLabel2 = lv_label_create(mboxCloseBtn);
  lv_label_set_text(btnLabel2, "Cancel");
  lv_obj_center(btnLabel2);
}

void text_input_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);

  if (code == LV_EVENT_FOCUSED)
  {
    lv_obj_move_foreground(keyboard);
    lv_keyboard_set_textarea(keyboard, ta);
    lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
  }

  if (code == LV_EVENT_DEFOCUSED)
  {
    lv_keyboard_set_textarea(keyboard, NULL);
    lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
  }
}

void makeKeyboard()
{
  keyboard = lv_keyboard_create(lv_scr_act());
  lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
}

void popupMsgBox(String title, String msg)
{
  if (popupBox != NULL)
  {
    lv_obj_del(popupBox);
  }

  popupBox = lv_obj_create(lv_scr_act());
  lv_obj_add_style(popupBox, &popupBox_style, 0);
  lv_obj_set_size(popupBox, tft.width() * 2 / 3, tft.height() / 2);
  lv_obj_center(popupBox);

  lv_obj_t *popupTitle = lv_label_create(popupBox);
  lv_label_set_text(popupTitle, title.c_str());
  lv_obj_set_width(popupTitle, tft.width() * 2 / 3 - 50);
  lv_obj_align(popupTitle, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_t *popupMSG = lv_label_create(popupBox);
  lv_obj_set_width(popupMSG, tft.width() * 2 / 3 - 50);
  lv_label_set_text(popupMSG, msg.c_str());
  lv_obj_align(popupMSG, LV_ALIGN_TOP_LEFT, 0, 40);

  popupBoxCloseBtn = lv_btn_create(popupBox);
  lv_obj_add_event_cb(popupBoxCloseBtn, btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_align(popupBoxCloseBtn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_t *btnLabel = lv_label_create(popupBoxCloseBtn);
  lv_label_set_text(btnLabel, "Okay");
  lv_obj_center(btnLabel);
}

void networkScanner()
{
  xTaskCreate(scanWIFITask,
              "ScanWIFITask",
              4096,
              NULL,
              1,
              &ntScanTaskHandler);
}

void networkConnector()
{
  xTaskCreate(beginWIFITask,
              "beginWIFITask",
              2048,
              NULL,
              1,
              &ntConnectTaskHandler);
}

void scanWIFITask(void *pvParameters)
{
  while (1)
  {
    foundWifiList.clear();
    int n = WiFi.scanNetworks();
    vTaskDelay(10);
    for (int i = 0; i < n; ++i)
    {
      String item = WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") " + ((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      foundWifiList.push_back(item);
      vTaskDelay(10);
    }
    vTaskDelay(5000);
  }
}

void beginWIFITask(void *pvParameters)
{
  unsigned long startingTime = millis();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  vTaskDelay(100);

  WiFi.begin(ssidName.c_str(), ssidPW.c_str());
  while (WiFi.status() != WL_CONNECTED && (millis() - startingTime) < networkTimeout)
  {
    vTaskDelay(250);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    networkStatus = NETWORK_CONNECTED_POPUP;
    saveWIFICredentialEEPROM(1, ssidName + " " + ssidPW);
  }
  else
  {
    networkStatus = NETWORK_CONNECT_FAILED;
    saveWIFICredentialEEPROM(0, "");
  }

  vTaskDelete(NULL);
}
