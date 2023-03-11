// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: lvgl_1_test

#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"
#include "Arduino.h"

void ui_init(void);
void ui_Screen3_screen_init(void);
void ui_Screen2_screen_init(void);
void ui_Screen1_screen_init(void);
void callbackTextArea(lv_event_t *e);
void lv_example_chart_1(void);
void createBtnBackTabview2(void);

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_btnDetail;
lv_obj_t *ui_btnBack;
lv_obj_t *ui_btnEnter;
lv_obj_t *ui_btnEnterLabel;
lv_obj_t *ui_btnDetailLabel;
lv_obj_t *ui_btnBackLabel;
lv_obj_t *ui_Screen1;
lv_obj_t *ui_Screen2;
lv_obj_t *ui_Screen3;
lv_obj_t *ui_Screen2_Panel1;
lv_obj_t *ui_textPrimaryTitle;
lv_obj_t *ui_textSecondaryTitle;
lv_obj_t *ui_textEmail;
lv_obj_t *ui_textPass;
lv_obj_t *ui_spinner1;
lv_obj_t *ui_kb;
lv_obj_t *arc1;
lv_obj_t *arc2;
lv_obj_t *lmeter;
lv_obj_t *lmeter2;
lv_obj_t *ui_chart1;
lv_obj_t *arc1Label;
lv_obj_t *arc2Label;
lv_obj_t *tabview;
lv_obj_t *tab1;
lv_obj_t *tab2;
lv_obj_t *tab3;
lv_obj_t *label;
lv_obj_t *ui_btnBackTab2;
lv_obj_t *ui_btnBackTab2Label;
///////////////////// TEST LVGL SETTINGS ////////////////////

#include "service/debug.hpp"
#include "widget/chart.hpp"
#include "widget/button.hpp"
#include "widget/arc.hpp"
#include "widget/tabs.hpp"
#include "service/timer.hpp"

#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 0
#error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

void callbackDebug(const char *buf)
{
    debug(String(buf));
}

void lv_example_chart_1(void)
{
    /*Create a chart*/
    lv_obj_t *chart;
    chart = lv_chart_create(ui_Screen2);
    lv_obj_set_size(chart, 200, 150);
    lv_obj_center(chart);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE); /*Show lines and points too*/

    /*Add two data series*/
    lv_chart_series_t *ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t *ser2 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);

    /*Set the next points on 'ser1'*/
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 30);
    lv_chart_set_next_value(chart, ser1, 70);
    lv_chart_set_next_value(chart, ser1, 90);

    /*Directly set points on 'ser2'*/
    ser2->y_points[0] = 90;
    ser2->y_points[1] = 70;
    ser2->y_points[2] = 65;
    ser2->y_points[3] = 65;
    ser2->y_points[4] = 65;
    ser2->y_points[5] = 65;
    ser2->y_points[6] = 65;
    ser2->y_points[7] = 65;
    ser2->y_points[8] = 65;
    ser2->y_points[9] = 65;

    lv_chart_refresh(chart); /*Required after direct set*/
}

///////////////////// ANIMATIONS ////////////////////
void callbackTextArea(lv_event_t *e)
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

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    // ADD TEXT
    ui_textPrimaryTitle = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_textPrimaryTitle, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_textPrimaryTitle, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_textPrimaryTitle, -88);
    lv_obj_set_y(ui_textPrimaryTitle, -205);
    // lv_obj_set_pos(arc1, -88, -205);
    lv_obj_set_align(ui_textPrimaryTitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_textPrimaryTitle, "Farm io");
    lv_obj_set_style_text_color(ui_textPrimaryTitle, lv_color_hex(0xA1AFB8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textPrimaryTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_textPrimaryTitle, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ADD SPINNER
    ui_spinner1 = lv_spinner_create(ui_Screen1, 1000, 90);
    lv_obj_set_width(ui_spinner1, 40);
    lv_obj_set_height(ui_spinner1, 42);
    lv_obj_set_x(ui_spinner1, 116);
    lv_obj_set_y(ui_spinner1, -189);
    lv_obj_set_align(ui_spinner1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_spinner1, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_obj_set_style_arc_width(ui_spinner1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_spinner1, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_spinner1, LV_OBJ_FLAG_HIDDEN);

    // ADD TEXT SIGN IN
    ui_textSecondaryTitle = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_textSecondaryTitle, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_textSecondaryTitle, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_textSecondaryTitle, -119);
    lv_obj_set_y(ui_textSecondaryTitle, -177);
    lv_obj_set_align(ui_textSecondaryTitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_textSecondaryTitle, "sign in");
    lv_obj_set_style_text_color(ui_textSecondaryTitle, lv_color_hex(0xA1AFB8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textSecondaryTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_textSecondaryTitle, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ADD BTN SIGN IN
    createBtnEnter();

    // ADD KEYBOARD
    ui_kb = lv_keyboard_create(ui_Screen1);
    lv_obj_set_width(ui_kb, 318);
    lv_obj_set_height(ui_kb, 211);
    lv_obj_set_x(ui_kb, -1);
    lv_obj_set_y(ui_kb, 117);
    lv_obj_set_align(ui_kb, LV_ALIGN_CENTER);
    lv_keyboard_set_textarea(ui_kb, NULL);
    lv_obj_add_flag(ui_kb, LV_OBJ_FLAG_HIDDEN);

    // ADD EMAIL
    ui_textEmail = lv_textarea_create(ui_Screen1);
    lv_obj_set_width(ui_textEmail, 296);
    lv_obj_add_event_cb(ui_textEmail, callbackTextArea, LV_EVENT_ALL, ui_kb);
    lv_obj_set_height(ui_textEmail, LV_SIZE_CONTENT); /// 33
    lv_obj_set_x(ui_textEmail, 0);
    lv_obj_set_y(ui_textEmail, -119);
    lv_obj_set_align(ui_textEmail, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_textEmail, "Email");
    lv_textarea_set_one_line(ui_textEmail, true);

    // ADD PASS
    ui_textPass = lv_textarea_create(ui_Screen1);
    lv_obj_add_event_cb(ui_textPass, callbackTextArea, LV_EVENT_ALL, ui_kb);
    lv_obj_set_width(ui_textPass, 296);
    lv_obj_set_height(ui_textPass, LV_SIZE_CONTENT); /// 33
    lv_obj_set_x(ui_textPass, 0);
    lv_obj_set_y(ui_textPass, -66);
    lv_obj_set_align(ui_textPass, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_textPass, "Pass");
    lv_textarea_set_one_line(ui_textPass, true);
    lv_textarea_set_password_mode(ui_textPass, true);
}

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_example_arc_1();
    lv_example_arc_2();
    lv_create_chart1();
    createBtnBack();
    createBtnDetail();
}

void ui_Screen3_screen_init(void)
{
    ui_Screen3 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen3, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    createTabViewSc3();
}

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();
    lv_log_register_print_cb(callbackDebug);
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}