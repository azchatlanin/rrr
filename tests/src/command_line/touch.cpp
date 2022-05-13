#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, command_line_touch_uniq)
{
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('t');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "touch");

  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('m');
  manager.trigger('y');
  manager.trigger('_');
  manager.trigger('t');
  manager.trigger('e');
  manager.trigger('s');
  manager.trigger('t');
  manager.trigger('_');
  manager.trigger('f');
  manager.trigger('i');
  manager.trigger('l');
  manager.trigger('e');
  manager.trigger('.');
  manager.trigger('t');
  manager.trigger('x');
  manager.trigger('t');
  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir_after_touch);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 13);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  ASSERT_EQ(browser->win_preview->get_file_content(), "is empty");

  manager.trigger(':');
  manager.trigger('d');
  manager.trigger('e');
  manager.trigger(rrr::config::key::TAB); 
  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 12);
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir);
}
