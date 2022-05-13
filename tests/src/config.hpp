#pragma once

#include <vector>
#include <filesystem>

#include "logger/logger.hpp"

#include "services/managers/manager/manager.hpp"
#include "services/ui/browser/browser.hpp"
#include "services/ui/info_bar/info_bar.hpp"
#include "services/ui/system_bar/system_bar.hpp"
#include "services/ui/command_line/command_line.hpp"

inline std::filesystem::path test_pwd { "/mnt/develop/projects/cpp/rrr/build" };

inline std::vector<rrr::file> build_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/bin", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-logs", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private", true },
  { "/mnt/develop/projects/cpp/rrr/build/src", true },
  { "/mnt/develop/projects/cpp/rrr/build/subprojects", true },
  { "/mnt/develop/projects/cpp/rrr/build/tests", true },
  { "/mnt/develop/projects/cpp/rrr/build/.gitignore", false },
  { "/mnt/develop/projects/cpp/rrr/build/.hgignore", false },
  { "/mnt/develop/projects/cpp/rrr/build/.ninja_deps", false },
  { "/mnt/develop/projects/cpp/rrr/build/.ninja_log", false },
  { "/mnt/develop/projects/cpp/rrr/build/build.ninja", false },
  { "/mnt/develop/projects/cpp/rrr/build/compile_commands.json", false }
};

inline std::vector<rrr::file> build_dir_after_mkdir { 
  { "/mnt/develop/projects/cpp/rrr/build/bin", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-logs", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private", true },
  { "/mnt/develop/projects/cpp/rrr/build/my_test_dir", true },
  { "/mnt/develop/projects/cpp/rrr/build/src", true },
  { "/mnt/develop/projects/cpp/rrr/build/subprojects", true },
  { "/mnt/develop/projects/cpp/rrr/build/tests", true },
  { "/mnt/develop/projects/cpp/rrr/build/.gitignore", false },
  { "/mnt/develop/projects/cpp/rrr/build/.hgignore", false },
  { "/mnt/develop/projects/cpp/rrr/build/.ninja_deps", false },
  { "/mnt/develop/projects/cpp/rrr/build/.ninja_log", false },
  { "/mnt/develop/projects/cpp/rrr/build/build.ninja", false },
  { "/mnt/develop/projects/cpp/rrr/build/compile_commands.json", false }
};

inline std::vector<rrr::file> build_dir_after_touch { 
  { "/mnt/develop/projects/cpp/rrr/build/bin", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-logs", true },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private", true },
  { "/mnt/develop/projects/cpp/rrr/build/src", true },
  { "/mnt/develop/projects/cpp/rrr/build/subprojects", true },
  { "/mnt/develop/projects/cpp/rrr/build/tests", true },
  { "/mnt/develop/projects/cpp/rrr/build/.gitignore", false },
  { "/mnt/develop/projects/cpp/rrr/build/.hgignore", false },
  { "/mnt/develop/projects/cpp/rrr/build/.ninja_deps", false },
  { "/mnt/develop/projects/cpp/rrr/build/.ninja_log", false },
  { "/mnt/develop/projects/cpp/rrr/build/build.ninja", false },
  { "/mnt/develop/projects/cpp/rrr/build/compile_commands.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/my_test_file.txt", false }
};

inline std::vector<rrr::file> build_bin_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/bin/rrr.p", true },
  { "/mnt/develop/projects/cpp/rrr/build/bin/rrr", false }
 };

inline std::vector<rrr::file> build_meson_info_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-benchmarks.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-buildoptions.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-buildsystem_files.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-dependencies.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-install_plan.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-installed.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-projectinfo.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-targets.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/intro-tests.json", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-info/meson-info.json", false }
 };

inline std::vector<rrr::file> build_meson_private_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/build.dat", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/cmd_line.txt", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/coredata.dat", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/coredata.dat.prev", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/install.dat", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/meson.lock", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/meson_benchmark_setup.dat", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/meson_test_setup.dat", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/sanitycheckcpp.cc", false },
  { "/mnt/develop/projects/cpp/rrr/build/meson-private/sanitycheckcpp.exe", false }
};

inline std::vector<std::filesystem::path> buffer_path {
  "/mnt/develop/projects/cpp/rrr/build/bin", 
  "/mnt/develop/projects/cpp/rrr/build/meson-info", 
  "/mnt/develop/projects/cpp/rrr/build/meson-logs"
};

inline std::vector<rrr::file> build_src_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/src/services", true }
};

inline std::vector<rrr::file> build_src_services_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/src/services/managers", true },
  { "/mnt/develop/projects/cpp/rrr/build/src/services/ui", true }
};

inline std::vector<rrr::file> build_src_services_managers_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/src/services/managers/libmanagers.so.p", true },
  { "/mnt/develop/projects/cpp/rrr/build/src/services/managers/libmanagers.so", false }
};

inline std::vector<rrr::file> build_src_services_ui_dir { 
  { "/mnt/develop/projects/cpp/rrr/build/src/services/ui/browser", true },
  { "/mnt/develop/projects/cpp/rrr/build/src/services/ui/command_line", true },
  { "/mnt/develop/projects/cpp/rrr/build/src/services/ui/info_bar", true },
  { "/mnt/develop/projects/cpp/rrr/build/src/services/ui/system_bar", true }
};

inline std::vector<rrr::file> rrr_dir { 
  { "/mnt/develop/projects/cpp/rrr/.cache", true },
  { "/mnt/develop/projects/cpp/rrr/.git", true },
  { "/mnt/develop/projects/cpp/rrr/bin", true },
  { "/mnt/develop/projects/cpp/rrr/build", true },
  { "/mnt/develop/projects/cpp/rrr/src", true },
  { "/mnt/develop/projects/cpp/rrr/subprojects", true },
  { "/mnt/develop/projects/cpp/rrr/tests", true },
  { "/mnt/develop/projects/cpp/rrr/README.md", false },
  { "/mnt/develop/projects/cpp/rrr/img_logo.png", false },
  { "/mnt/develop/projects/cpp/rrr/meson.build", false },
  { "/mnt/develop/projects/cpp/rrr/run", false }
};
