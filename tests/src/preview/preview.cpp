#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, win_preview)
{
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  // в самомо начале страта курсор стоит на чем-то и идет превью
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_bin_dir);

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_dir);

  manager.trigger('l');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_services_dir);

  manager.trigger('l');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_services_managers_dir);
  
  manager.trigger('j');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_services_ui_dir);

  manager.trigger('h');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 1);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_services_dir);

  manager.trigger('h');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_dir);

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('h');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 6);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_dir);

  manager.trigger('l');
  manager.trigger('k');
  manager.trigger('k');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_dir);

  manager.trigger('l');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 1);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_services_dir);

  manager.trigger('l');
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_src_services_ui_dir);
}
