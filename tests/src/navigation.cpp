#include <gtest/gtest.h>

#include <fstream>

#include "logger/logger.hpp"

#include "services/managers/manager/manager.hpp"
#include "services/ui/browser/browser.hpp"
#include "services/ui/info_bar/info_bar.hpp"
#include "services/ui/system_bar/system_bar.hpp"
#include "services/ui/command_line/command_line.hpp"

std::filesystem::path test_pwd { "/mnt/develop/projects/cpp/rrr/build/for_test" };

TEST(rrr, up_down_navigation)
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

TEST(rrr, right_left_navigation)
{
  std::vector<rrr::file> f_test { 
    { "/mnt/develop/projects/cpp/rrr/build/for_test/dir_2/dir_2_1", true },
    { "/mnt/develop/projects/cpp/rrr/build/for_test/dir_2/dir_2_2", true }
  };

  std::filesystem::current_path(test_pwd);

  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  manager.trigger('j');
  manager.trigger('l');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);
  
  // go to the empty dir
  manager.trigger('j');
  manager.trigger('l');
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), 2);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 1);

  manager.trigger('h');
  manager.trigger('h');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 1);
  
  manager.trigger('l');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 1);
}
