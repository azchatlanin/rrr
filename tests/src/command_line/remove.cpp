#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, command_line_trash)
{
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 4);

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('t');
  manager.trigger('r');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "trash");

  manager.trigger(rrr::config::key::ENTER); 
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 3);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_meson_private_dir);
}
