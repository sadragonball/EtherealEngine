#pragma once

#include <filesystem>
namespace fs
{
using namespace std::filesystem;
using error_code = std::error_code;
inline file_time_type now()
{
    return file_time_type::clock::now();
}
} // namespace fs
