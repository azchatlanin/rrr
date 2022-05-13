#include <gtest/gtest.h>

#include "src/config.hpp"

TEST(rrr, command_line_autofill)
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

  manager.trigger(rrr::config::key::BACKSPACE); 
  manager.trigger(rrr::config::key::BACKSPACE); 
  manager.trigger(rrr::config::key::BACKSPACE); 
  manager.trigger(rrr::config::key::BACKSPACE); 
  manager.trigger('r');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "trash");
}
