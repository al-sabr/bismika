#include <filesystem>

class PathInformer
{
public:
  static std::filesystem::path abs_exe_path();
  static std::filesystem::path abs_exe_directory();
  // ...

  // Disallow creating an instance of this object
  // (Making all constructors private also works but is not ideal and does not
  // convey your intent as well)
  PathInformer() = delete;
};



