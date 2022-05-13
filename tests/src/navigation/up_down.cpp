#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, up_down_navigation)
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

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 5);

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
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 12);

  manager.trigger('k');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 11);

  manager.trigger('k');
  manager.trigger('k');
  manager.trigger('k');
  manager.trigger('k');
  ASSERT_EQ(buffer::state[rrr::state_manager::instance().PWD].filename(), ".gitignore");

  ASSERT_EQ(rrr::state_manager::instance().PWD, test_pwd);
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), 13);
}
