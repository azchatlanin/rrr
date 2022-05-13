#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, command_line_mkdir_uniq)
{
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('m');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "mkdir");

  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('m');
  manager.trigger('y');
  manager.trigger('_');
  manager.trigger('t');
  manager.trigger('e');
  manager.trigger('s');
  manager.trigger('t');
  manager.trigger('_');
  manager.trigger('d');
  manager.trigger('i');
  manager.trigger('r');
  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir_after_mkdir);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 4);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
}

TEST(rrr, command_line_mkdir_exist)
{
  // auto browser = rrr::board::make<rrr::browser>();
  // auto info_bar = rrr::board::make<rrr::info_bar>();
  // auto system_bar = rrr::board::make<rrr::system_bar>();
  // auto command_line = rrr::board::make<rrr::command_line>();
  //
  // rrr::manager manager { browser, info_bar, system_bar, command_line };
  //
  // manager.trigger(':');
  // ASSERT_EQ(rrr::state_manager::instance().cmd, ':');
  //
  // manager.trigger('m');
  // manager.trigger(rrr::config::key::TAB); 
  // ASSERT_EQ(command_line->get_cmd(), "mkdir");
  //
  // manager.trigger(rrr::config::key::SPACE);
  // manager.trigger('m');
  // manager.trigger('y');
  // manager.trigger('_');
  // manager.trigger('t');
  // manager.trigger('e');
  // manager.trigger('s');
  // manager.trigger('t');
  // manager.trigger('_');
  // manager.trigger('d');
  // manager.trigger('i');
  // manager.trigger('r');
  // manager.trigger(rrr::config::key::ENTER);
  // ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 5);
  // ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  // ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
}
