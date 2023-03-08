// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: lvgl_1_test


#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

uint32_t LV_EVENT_GET_COMP_CHILD;

typedef struct {
    uint32_t child_idx;
    lv_obj_t * child;
} ui_comp_get_child_t;

lv_obj_t * ui_comp_get_child(lv_obj_t * comp, uint32_t child_idx)
{
    ui_comp_get_child_t info;
    info.child = NULL;
    info.child_idx = child_idx;
    lv_event_send(comp, LV_EVENT_GET_COMP_CHILD, &info);
    return info.child;
}

void get_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    ui_comp_get_child_t * info = lv_event_get_param(e);
    info->child = c[info->child_idx];
}

void del_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    lv_mem_free(c);
}


// COMPONENT button1

lv_obj_t * ui_button1_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_button1;
    cui_button1 = lv_label_create(comp_parent);
    lv_obj_set_width(cui_button1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_button1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_button1, LV_ALIGN_CENTER);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_BUTTON1_NUM);
    children[UI_COMP_BUTTON1_BUTTON1] = cui_button1;
    lv_obj_add_event_cb(cui_button1, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_button1, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_button1;
}

