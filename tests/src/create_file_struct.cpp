#include <gtest/gtest.h>

#include <fstream>

#include "logger/logger.hpp"

#include "services/managers/manager/manager.hpp"
#include "services/managers/state_manager/state_manager.hpp"
#include "services/ui/browser/browser.hpp"

TEST(rrr, create_file_struct_for_test)
{
  std::vector<rrr::file> f_test { 
    { "/mnt/develop/projects/cpp/rrr/build/for_test/dir_1", true }, 
    { "/mnt/develop/projects/cpp/rrr/build/for_test/dir_2", true }, 
    { "/mnt/develop/projects/cpp/rrr/build/for_test/file_0.txt", false }
  };

  std::filesystem::path test_pwd { "/mnt/develop/projects/cpp/rrr/build" };
  std::filesystem::current_path(test_pwd);

  std::filesystem::remove_all("for_test");
  
  std::filesystem::create_directories("for_test/dir_1");
  std::filesystem::create_directories("for_test/dir_2/dir_2_1");
  std::filesystem::create_directories("for_test/dir_2/dir_2_2");

  std::ofstream ofs_1("for_test/dir_1/file_1.txt");
  std::ofstream ofs_2("for_test/dir_1/file_2.txt");
  std::ofstream ofs_3("for_test/file_0.txt");
  ofs_1 << "this text for test file_1.txt\n";
  ofs_1.close();
  ofs_2 << "this text for test file_2.txt\n";
  ofs_2.close();
  ofs_3 << "this text for test file_0.txt\n";
  ofs_3.close();

  test_pwd /= "for_test";
  auto files = rrr::file_utils::fill(test_pwd);

  ASSERT_EQ(files, f_test);
}
