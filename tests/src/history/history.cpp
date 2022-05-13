#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, win_history)
{
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  // в самомо начале страта курсор стоит на чем-то 
  ASSERT_EQ(browser->win_history->get_cursor_pos(), 3);
  ASSERT_EQ(browser->win_history->get_current_files(), rrr_dir);

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  ASSERT_EQ(browser->win_history->get_cursor_pos(), 3);
  ASSERT_EQ(browser->win_history->get_current_files(), rrr_dir);

  manager.trigger('l');
  ASSERT_EQ(browser->win_history->get_cursor_pos(), 4);
  ASSERT_EQ(browser->win_history->get_current_files(), build_dir);
}
