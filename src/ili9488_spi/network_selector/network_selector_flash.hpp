void tryPreviousNetwork()
{
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    delay(1000);
    ESP.restart();
  }
  loadWIFICredentialEEPROM();
}

void saveWIFICredentialEEPROM(int flag, String ssidpw)
{
  EEPROM.writeInt(EEPROM_ADDR_WIFI_FLAG, flag);
  EEPROM.writeString(EEPROM_ADDR_WIFI_CREDENTIAL, flag == 1 ? ssidpw : "");
  EEPROM.commit();
}

void loadWIFICredentialEEPROM()
{
  int wifiFlag = EEPROM.readInt(EEPROM_ADDR_WIFI_FLAG);
  String wifiCredential = EEPROM.readString(EEPROM_ADDR_WIFI_CREDENTIAL);

  if (wifiFlag == 1 && wifiCredential.length() != 0 && wifiCredential.indexOf(" ") != -1)
  {
    char preSSIDName[30], preSSIDPw[30];
    if (sscanf(wifiCredential.c_str(), "%s %s", preSSIDName, preSSIDPw) == 2)
    {

      lv_obj_add_state(settingWiFiSwitch, LV_STATE_CHECKED);
      lv_event_send(settingWiFiSwitch, LV_EVENT_VALUE_CHANGED, NULL);

      popupMsgBox("Welcome Back!", "Attempts to reconnect to the previously connected network.");
      ssidName = String(preSSIDName);
      ssidPW = String(preSSIDPw);
      networkConnector();
    }
    else
    {
      saveWIFICredentialEEPROM(0, "");
    }
  }
}