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

  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('j');
  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('j');
  manager.trigger(rrr::config::key::SPACE);
  ASSERT_EQ(rrr::state_manager::instance().buffer_path, buffer_path);

  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('k');
  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('k');
  manager.trigger(rrr::config::key::SPACE);
  ASSERT_EQ(rrr::state_manager::instance().buffer_path.size(), 0);
}
