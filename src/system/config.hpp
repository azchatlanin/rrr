#pragma once

#include <string>

namespace rrr::config
{
  inline const std::string MAIN_PG = "postgres://chatlanin:3yT5fc102736afbdde733302f79c7691db39596d82d4c283de435e3143564aef@main_pg:5432/main_pg?sslmode=disable";
  inline const std::string RESULTS_PG = "postgres://chatlanin:3yT5fc102736afbdde733302f79c7691db39596d82d4c283de435e3143564aef@results_pg:5432/results_pg?sslmode=disable";
  inline const std::string LOGS_PG = "postgres://chatlanin:3yT5fc102736afbdde733302f79c7691db39596d82d4c283de435e3143564aef@logs_pg:5432/logs_pg?sslmode=disable";
}
