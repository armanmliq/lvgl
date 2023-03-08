
void createTabView()
{
  lv_obj_t *tabview;
  tabview = lv_tabview_create(ui_Screen3, LV_DIR_TOP, 50);

  lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
  lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
  lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");

  lv_obj_t *label = lv_label_create(tab1);
  lv_label_set_text(label, "This the first tab\n\n"
                           "If the content\n"
                           "of a tab\n"
                           "becomes too\n"
                           "longer\n"
                           "than the\n"
                           "container\n"
                           "then it\n"
                           "automatically\n"
                           "becomes\n"
                           "scrollable.\n"
                           "\n"
                           "\n"
                           "\n"
                           "Can you see it?"
                           "Where can I get some?"
                           "There are many variations of passages of Lorem Ipsum available,\n"
                           "but the majority have suffered alteration in some form,\n"
                           "by injected humour, or randomised words which don't look \n"
                           "even slightly believable. If you are going to use a passage\n"
                           "of Lorem Ipsum, you need to be sure there isn't anything \n"
                           "embarrassing hidden in the middle of text. \n"
                           "All the Lorem Ipsum generators on the Internet tend to repeat\n"
                           "predefined chunks as necessary, making this the first true\n"
                           "generator on the Internet. It uses a dictionary of over 200\n"
                           "Latin words, combined with a handful of model sentence structures,\n"
                           "to generate Lorem Ipsum which looks reasonable.\n"
                           "The generated Lorem Ipsum is therefore always free from repetition,\n"
                           "injected humour, or non-characteristic words etc.");
  label = lv_label_create(tab2);
  lv_label_set_text(label, "Second tab");
  label = lv_label_create(tab3);
  lv_label_set_text(label, "Third tab");
  lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);
}