#include <any>
#include <memory>
#include <vector>


#include "../../state_manager/state_manager.hpp"

/*
 * это класс часть реализации manager.
 * по сути это реализация паттерна медиатор для обмена сообщениями между разными компонентами.
 */
namespace rrr
{
  enum event 
  {
    CHANGE_PWD, SPACE_INFO, RENAME_COMPLETED, DROP
  };

  struct i_board
  {
    virtual ~i_board() = default;
    virtual void execute(event, std::any) const = 0;
  };

  class board 
  {
    public: 
      explicit board(std::initializer_list<int>, std::string);
      virtual ~board() = default;

    public: 
      virtual void draw() = 0;
      virtual void trigger(int) = 0;
      virtual void execute(event, std::any) = 0;

      template<typename T, typename... Args>
      static std::shared_ptr<T> make(Args... args)
      {
        static std::shared_ptr<T> instance = std::make_shared<T>(args...);
        return instance;
      }

      void set(i_board* b_);
      bool on_this();

    protected: 
      // главная клавиша каждой доски по которой эта доска активируется
      std::vector<int> MAIN_KEYS;
      i_board* BOARD;
      std::string title;
      struct features
      {
        int start_x = 0; 
        int start_y = 0; 
        int width = 0; 
        int height = 0;
      } ft;

  };
}
