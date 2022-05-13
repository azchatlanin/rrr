#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, right_left_navigation)
{
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);

  manager.trigger('j');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 1);

  manager.trigger('l');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_meson_info_dir);

  manager.trigger('j');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 1);

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 9);

  manager.trigger('k');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 8);
  ASSERT_EQ(buffer::state[rrr::state_manager::instance().PWD].filename(), "intro-tests.json");

  manager.trigger('h');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 1);
  ASSERT_EQ(buffer::state[rrr::state_manager::instance().PWD].filename(), "meson-info");

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  ASSERT_EQ(buffer::state[rrr::state_manager::instance().PWD].filename(), "src");

  manager.trigger('k');
  manager.trigger('k');
  manager.trigger('k');
  manager.trigger('l');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 8);
  ASSERT_EQ(buffer::state[rrr::state_manager::instance().PWD].filename(), "intro-tests.json");
}
