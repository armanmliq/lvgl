void callbackBtnEnter(lv_event_t *e)
{
    debugln("callbackBtnEnter");
    ui_Screen2_screen_init();
    lv_scr_load(ui_Screen2);
    lv_obj_del_async(ui_Screen1);
}

void callbackBtnBack(lv_event_t *e)
{
    debugln("callbackBtnBack");
    ui_Screen1_screen_init();
    lv_scr_load(ui_Screen1);
    lv_obj_del_async(ui_Screen2);
}

void callbackBtnDetail(lv_event_t *e)
{
    debugln("callbackBtnDetail");
    ui_Screen3_screen_init();
    lv_scr_load(ui_Screen3);
    lv_obj_del_async(ui_Screen2);
}

void callbackBtnBackTab2(lv_event_t *e)
{
    debugln("callbackBtnBackTab2");
    ui_Screen2_screen_init();
    lv_scr_load(ui_Screen2);
    lv_obj_del_async(ui_Screen3);
}

void createBtnEnter(void)
{
    // ADD BUTTON ENTER
    ui_btnEnter = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_btnEnter, 202);
    lv_obj_set_height(ui_btnEnter, 49);
    lv_obj_set_x(ui_btnEnter, 2);
    lv_obj_set_y(ui_btnEnter, 11);
    lv_obj_set_align(ui_btnEnter, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_btnEnter, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_btnEnter, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_add_event_cb(ui_btnEnter, callbackBtnEnter, LV_EVENT_PRESSED, ui_btnEnter);

    ui_btnEnterLabel = lv_label_create(ui_btnEnter);
    lv_obj_set_width(ui_btnEnterLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_btnEnterLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_btnEnterLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_btnEnterLabel, "Sign In");
}

void createBtnBack(void)
{
    // ADD BUTTON ENTER
    ui_btnBack = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_btnBack, 100);
    lv_obj_set_height(ui_btnBack, 50);
    lv_obj_set_x(ui_btnBack, 64);
    lv_obj_set_y(ui_btnBack, 197);
    lv_obj_set_align(ui_btnBack, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_btnBack, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_btnBack, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_add_event_cb(ui_btnBack, callbackBtnBack, LV_EVENT_PRESSED, ui_btnBack);

    ui_btnBackLabel = lv_label_create(ui_btnBack);
    lv_obj_set_width(ui_btnBackLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_btnBackLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_btnBackLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_btnBackLabel, "Log Out");
}

void createBtnDetail(void)
{
    // ADD BUTTON ENTER
    ui_btnDetail = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_btnDetail, 100);
    lv_obj_set_height(ui_btnDetail, 50);
    lv_obj_set_x(ui_btnDetail, -64);
    lv_obj_set_y(ui_btnDetail, 197);
    lv_obj_set_align(ui_btnDetail, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_btnDetail, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_btnDetail, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_add_event_cb(ui_btnDetail, callbackBtnDetail, LV_EVENT_PRESSED, ui_btnDetail);

    ui_btnDetailLabel = lv_label_create(ui_btnDetail);
    lv_obj_set_width(ui_btnDetailLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_btnDetailLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_btnDetailLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_btnDetailLabel, "Detail");
}

void createBtnBackTabview2(void)
{
    // ADD BUTTON ENTER
    ui_btnBackTab2 = lv_btn_create(tab2);
    lv_obj_set_width(ui_btnBackTab2, 100);
    lv_obj_set_height(ui_btnBackTab2, 50);
    lv_obj_set_x(ui_btnBackTab2, -64);
    lv_obj_set_y(ui_btnBackTab2, 197);
    lv_obj_set_align(ui_btnBackTab2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_btnBackTab2, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_btnBackTab2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_add_event_cb(ui_btnBackTab2, callbackBtnBackTab2, LV_EVENT_PRESSED, ui_btnBackTab2);

    ui_btnBackTab2Label = lv_label_create(ui_btnBackTab2);
    lv_obj_set_width(ui_btnBackTab2Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_btnBackTab2Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_btnBackTab2Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_btnBackTab2Label, "Back");
}