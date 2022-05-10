#include "browser.hpp"

#include <algorithm>

#include "services/managers/state_manager/state_manager.hpp"

// hack
#include "logger/logger.hpp"
#include "utils/utils.hpp"

namespace rrr
{
  browser::browser() : board { { 'F' }, " File browser " }
  {
    try 
    {
      std::string tmp_pwd = hack::utils::exec("pwd");
      tmp_pwd.erase(std::remove(tmp_pwd.begin(), tmp_pwd.end(), '\n'), tmp_pwd.end());
      state_manager::instance().PWD = std::filesystem::path(tmp_pwd);
    } 
    catch (std::exception& e) 
    {
      hack::error()(e.what());
      hack::log()("pwd", state_manager::instance().PWD);
    }

    getmaxyx(stdscr, ft.height, ft.width);
    state_manager::instance().max_y = ft.height;
    state_manager::instance().max_x = ft.width;

    ft.height -= ft.height / 7;

    win = newwin(ft.height, ft.width, ft.start_y, ft.start_x);
    box(win, 0 , 0);	
    set_title();

    win_history = std::make_shared<history>(win, ft.height - 2, ft.width / 3, 1, 1);
    win_navigation = std::make_shared<navigation>(win, ft.height - 2, ft.width / 3 + 1, 1, ft.width / 3);
    win_preview = std::make_shared<preview>(win, ft.height - 2, ft.width / 3 - 1, 1, ft.width * 2 / 3);

    win_navigation->fill();
    win_history->fill();
  };
  
  void browser::set_title()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void browser::prew()
  {
    buffer::state[state_manager::instance().PWD.parent_path()] = state_manager::instance().PWD;
    state_manager::instance().PWD = state_manager::instance().PWD.parent_path();
    update();
  }

  void browser::next()
  {
    state_manager::instance().PWD = buffer::state[state_manager::instance().PWD];
    update();
  }

  void browser::move(int i)
  {
    win_navigation->set_cursor_pos(i);
    win_navigation->buffer_update();
    BOARD->execute(event::CHANGE_PWD, state_manager::instance().PWD / buffer::state[state_manager::instance().PWD]);
    BOARD->execute(event::SPACE_INFO, state_manager::instance().PWD / buffer::state[state_manager::instance().PWD]);
  }

  void browser::update()
  {
    win_navigation->fill();
    win_navigation->set_cursor_pos();
    win_navigation->buffer_update();
    win_history->fill();
    BOARD->execute(event::CHANGE_PWD, state_manager::instance().PWD / buffer::state[state_manager::instance().PWD]);
    BOARD->execute(event::SPACE_INFO, state_manager::instance().PWD / buffer::state[state_manager::instance().PWD]);
  }

  void browser::draw()
  {
    win_history->draw();

    win_navigation->buffer_update();
    win_navigation->draw();

    win_preview->fill();
    win_preview->draw();
  }

  void browser::trigger(int k)
  {
    if (!on_this()) return;
    key = k;

    switch (key) 
    {
      // selsect
      case 'h':
        prew();
        break;
      case config::key::SPACE:
        select();
        break;
      case 'l':
        next();
        break;
      case KEY_ENTER:
        next();
        break;
      // this is a key enter too
      case 10: 
        next();
        break;
        
      // navigation
      case 'j':
        move(1);
        break;
      case KEY_DOWN:
        move(1);
        break;
      case 'k':
        move(-1);
        break;
      case KEY_UP:
        move(-1);
        break;
      default:
        break;
    }

    erise();
  }

  void browser::execute(event e, std::any) 
  {
    switch (e)
    {
      case COMMAND_COMPLETED:
        erise();
        win_navigation->fill();
        win_history->fill();
        break;
      default:
        break;
    }
  }

  void browser::refresh()
  {
    wrefresh(win);
    wrefresh(win_history->win.get());
    wrefresh(win_navigation->win.get());
    wrefresh(win_preview->win.get());
  }

  void browser::select()
  {
    win_navigation->select();
  }

  void browser::erise()
  {
    werase(win_navigation->win.get());
    werase(win_history->win.get());
    werase(win_preview->win.get());
  }
}
