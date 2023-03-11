static void set_angle_arc_1(void *obj, int32_t v)
{
    lv_arc_set_value(arc1, v);
}

static void set_angle_arc_2(void *obj, int32_t v)
{
    lv_arc_set_value(arc2, v);
}

void lv_example_arc_1(void)
{
    arc1Label = lv_label_create(ui_Screen2);
    lv_obj_set_width(arc1Label, LV_SIZE_CONTENT);
    lv_obj_set_height(arc1Label, LV_SIZE_CONTENT);
    lv_obj_set_x(arc1Label, -78);
    lv_obj_set_y(arc1Label, -98);
    lv_obj_set_align(arc1Label, LV_ALIGN_CENTER);
    lv_label_set_text(arc1Label, "arc 1");
    lv_obj_set_style_text_color(arc1Label, lv_color_hex(0xA1AFB8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(arc1Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(arc1Label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Create an Arc1*/
    arc1 = lv_arc_create(ui_Screen2);
    lv_arc_set_rotation(arc1, 270);
    lv_arc_set_bg_angles(arc1, 0, 360);
    lv_obj_set_size(arc1, 100, 100);
    lv_obj_set_x(arc1, -78);
    lv_obj_set_y(arc1, -158);
    lv_obj_set_align(arc1, LV_ALIGN_CENTER);
    lv_obj_remove_style(arc1, NULL, LV_PART_KNOB);  /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc1, LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc1);
    lv_anim_set_exec_cb(&a, set_angle_arc_1);
    lv_anim_set_time(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
}

void lv_example_arc_2(void)
{
    arc2Label = lv_label_create(ui_Screen2);
    lv_obj_set_width(arc2Label, LV_SIZE_CONTENT);
    lv_obj_set_height(arc2Label, LV_SIZE_CONTENT);
    lv_obj_set_x(arc2Label, 78);
    lv_obj_set_y(arc2Label, -98);
    lv_obj_set_align(arc2Label, LV_ALIGN_CENTER);
    lv_label_set_text(arc2Label, "arc 2");
    lv_obj_set_style_text_color(arc2Label, lv_color_hex(0xA1AFB8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(arc2Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(arc2Label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Create an Arc1*/
    arc2 = lv_arc_create(ui_Screen2);
    lv_arc_set_rotation(arc2, 270);
    lv_arc_set_bg_angles(arc2, 0, 360);
    lv_obj_set_size(arc2, 100, 100);
    lv_obj_set_x(arc2, 77);
    lv_obj_set_y(arc2, -158);
    lv_obj_set_align(arc2, LV_ALIGN_CENTER);
    lv_obj_remove_style(arc2, NULL, LV_PART_KNOB);  /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc2, LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc2);
    lv_anim_set_exec_cb(&a, set_angle_arc_2);
    lv_anim_set_time(&a, 200);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
}