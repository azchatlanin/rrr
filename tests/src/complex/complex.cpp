#include <gtest/gtest.h>

#include "src/config.hpp"

// 1. создаем директория my_test_dir
// 2. создаем еще раз с темже именем
// 3. создаем еще раз с темже именем
// 4. копикуем 2  в 1
// 5. копикуем 3  в 1
// 6. удаляем 1
// 7. переименовываем 2 в 1
// 8. удаляем 3 и 2
//
// 1.1 создаем директория my_test_dir
// 2.1 создаем еще раз с темже именем
// 3.1 создаем еще раз с темже именем
// 4.1 перемещаем 2  в 1
// 5.1 перемещаем 3  в 1
// 6.1 удаляем 1
//
// 1.2 создаем директория my_test_dir
// 2.2 создаем еще раз с темже именем
// 3.2 удаляем 1
// 4.2 переименовываем 2 в 1
// 5.2 удаляем 2
//

TEST(rrr, complex)
{
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };

  // в самомо начале страта курсор стоит на чем-то и идет превью
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_bin_dir);
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir);

  // 1
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
  // end 1

  // 2
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
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), build_dir_after_mkdir.size() + 1);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 5);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 2

  // 3
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
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), build_dir_after_mkdir.size() + 2);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 6);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 3

  // 4.
  manager.trigger('k');
  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('k');
  manager.trigger('l');

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('p');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "paste");

  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), 1);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 4

  // 5
  manager.trigger('h');
  manager.trigger('j');
  manager.trigger('j');
  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('k');
  manager.trigger('k');
  manager.trigger(rrr::config::key::ENTER);

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('p');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "paste");

  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), 2);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 5

  // 6
  manager.trigger('h');
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), build_dir_after_mkdir.size() + 2);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 4);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 2);

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('t');
  manager.trigger('r');
  manager.trigger(rrr::config::key::TAB);
  ASSERT_EQ(command_line->get_cmd(), "trash");

  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), build_dir.size() + 2);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 3);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_meson_private_dir);
  ASSERT_EQ(command_line->get_cmd(), "");
  // end 6
  
  // 7
  manager.trigger('j');
  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('r');
  manager.trigger('e');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "rename");

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
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 4);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  ASSERT_EQ(browser->win_preview->get_content(), "is empty");
  // end 7

  // 8
  manager.trigger('j');
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 5);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('d');
  manager.trigger('e');
  manager.trigger(rrr::config::key::TAB);
  ASSERT_EQ(command_line->get_cmd(), "delete");
  manager.trigger(rrr::config::key::ENTER);

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('d');
  manager.trigger('e');
  manager.trigger(rrr::config::key::TAB);
  ASSERT_EQ(command_line->get_cmd(), "delete");
  manager.trigger(rrr::config::key::ENTER);

  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 3);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_meson_private_dir);
  ASSERT_EQ(command_line->get_cmd(), "");
  // end 8
  //
  //
  // -----------------------------------------------------------------------
  //
  // 1.1
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
  // end 1

  // 2.1
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
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), build_dir_after_mkdir.size() + 1);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 5);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 2

  // 3.1
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
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), build_dir_after_mkdir.size() + 2);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 6);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 3

  // 4.1
  manager.trigger('k');
  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('k');
  manager.trigger('l');

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('m');
  manager.trigger('o');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "move");

  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), 1);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 4

  // 5.1
  manager.trigger('h');
  manager.trigger('j');
  manager.trigger(rrr::config::key::SPACE);
  manager.trigger('k');
  manager.trigger(rrr::config::key::ENTER);

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('m');
  manager.trigger('o');
  manager.trigger(rrr::config::key::TAB); 
  ASSERT_EQ(command_line->get_cmd(), "move");

  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files().size(), 2);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 0);
  // end 5

  // 6.1
  manager.trigger('h');
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir_after_mkdir);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 4);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files().size(), 2);

  manager.trigger(':');
  ASSERT_EQ(rrr::state_manager::instance().cmd, ':');

  manager.trigger('t');
  manager.trigger('r');
  manager.trigger(rrr::config::key::TAB);
  ASSERT_EQ(command_line->get_cmd(), "trash");

  const std::vector<std::filesystem::path> p;
  ASSERT_EQ(rrr::state_manager::instance().buffer_path, p);

  // HERE
  // запусить тэсты и увидеть ошибку при удалении
  manager.trigger(rrr::config::key::ENTER);
  ASSERT_EQ(browser->win_navigation->get_current_files(), build_dir);
  ASSERT_EQ(browser->win_navigation->get_cursor_pos(), 3);
  ASSERT_EQ(browser->win_preview->get_cursor_pos(), 0);
  ASSERT_EQ(browser->win_preview->get_current_files(), build_meson_private_dir);
  ASSERT_EQ(command_line->get_cmd(), "");
  // end 6

}

