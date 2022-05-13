#include "browser.hpp"

#include <algorithm>

#include "services/managers/state_manager/state_manager.hpp"

// hack
#include "logger/logger.hpp"
#include "utils/utils.hpp"

namespace rrr
{
  browser::browser()
  {
    MAIN_KEYS = { 'F' };
    title = " File browser ";

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

    getmaxyx(stdscr, state_manager::instance().max_y, state_manager::instance().max_x);

    win = newwin(state_manager::instance().max_y - 12, state_manager::instance().max_x, 0, 0);
    box(win, 0 , 0);	
    set_title();

    win_history = std::make_shared<history>(win, state_manager::instance().max_y - 14, state_manager::instance().max_x / 3, 1, 1);
    win_navigation = std::make_shared<navigation>(win, state_manager::instance().max_y - 14, state_manager::instance().max_x / 3 + 1, 1, state_manager::instance().max_x / 3);
    win_preview = std::make_shared<preview>(win, state_manager::instance().max_y - 14, state_manager::instance().max_x / 3 - 1, 1, state_manager::instance().max_x * 2 / 3);

    win_history->fill();
    win_navigation->fill();
    win_preview->fill();
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
    if (win_preview->get_current_files().empty()) return;
    state_manager::instance().PWD = buffer::state[state_manager::instance().PWD];
    update();
  }

  // HERE
  // сделать скролл
  void browser::up()
  {
    win_navigation->cursor_up();
    win_navigation->buffer_update();
    win_preview->fill();
    BOARD->execute(event::CHANGE_PWD, state_manager::instance().PWD / buffer::state[state_manager::instance().PWD]);
  }

  void browser::down()
  {
    win_navigation->cursor_down();
    win_navigation->buffer_update();
    win_preview->fill();
    BOARD->execute(event::CHANGE_PWD, state_manager::instance().PWD / buffer::state[state_manager::instance().PWD]);
  }

  void browser::update()
  {
    win_navigation->fill();
    win_navigation->set_cursor_pos();
    win_navigation->buffer_update();
    win_history->fill();
    win_preview->fill();
    BOARD->execute(event::CHANGE_PWD, state_manager::instance().PWD / buffer::state[state_manager::instance().PWD]);
  }

  void browser::draw()
  {
    win_history->draw();
    win_navigation->draw();
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
        down();
        break;
      case KEY_DOWN:
        down();
        break;
      case 'k':
        up();
        break;
      case KEY_UP:
        up();
        break;
      default:
        break;
    }

    erise();
  }

  void browser::execute(event e, std::any data) 
  {
    switch (e)
    {
      case COMMAND_COMPLETED:
        erise();
        win_navigation->fill();
        win_navigation->set_cursor_pos();
        break;
      case COMMAND_CREATED_COMPLETED:
        erise();
        {
          auto pwd = std::any_cast<std::filesystem::path>(data);
          win_navigation->fill();
          win_navigation->set_cursor_pos(pwd);
          win_navigation->buffer_update();
          win_preview->fill();
        }
        break;
      case COMMAND_REMOVE_COMPLETED:
        erise();
        win_navigation->fill();
        win_navigation->cursor_up();
        win_navigation->buffer_update();
        win_preview->fill();
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
