#include <gtest/gtest.h>

#include <fstream>

#include "logger/logger.hpp"

#include "services/managers/manager/manager.hpp"
#include "services/ui/browser/browser.hpp"
#include "services/ui/info_bar/info_bar.hpp"
#include "services/ui/system_bar/system_bar.hpp"
#include "services/ui/command_line/command_line.hpp"

std::filesystem::path test_pwd { "/mnt/develop/projects/cpp/rrr/build/for_test" };

// HERE
// сделать все тэсты для preview
TEST(rrr, create_preview)
{
  auto browser = rrr::board::make<rrr::browser>();
  rrr::manager manager { browser };

  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);

  manager.trigger('j');
  manager.trigger('l');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);

  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger('j');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 2);

  manager.trigger('k');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 1);

  manager.trigger('k');
  manager.trigger('k');
  manager.trigger('k');
  manager.trigger('k');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);

  ASSERT_EQ(rrr::state_manager::instance().PWD, test_pwd);
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), 3);
}
