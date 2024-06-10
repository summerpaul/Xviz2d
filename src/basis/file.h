/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 20:14:45
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-28 20:17:57
 */
#include <stdint.h>

#ifndef __FILE_H__
#define __FILE_H__
//#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>
#include <cstdio>
#include <fstream>
#include <string>
namespace basis
{
    inline bool FileExists(const std::string &filePath)
    {
        struct stat info;
        return stat(filePath.c_str(), &info) == 0;
    }

    inline bool DirectoryExists(const std::string &directoryPath)
    {
        struct stat info;
        if (stat(directoryPath.c_str(), &info) != 0)
        {
            return false;
        }

        if (info.st_mode & S_IFDIR)
        {
            return true;
        }

        return false;
    }

    //inline bool CreateDirectory(const std::string &directoryPath)
    //{
    //    std::string path = directoryPath;
    //    for (size_t i = 1; i < directoryPath.size(); ++i)
    //    {
    //        if (directoryPath[i] == '/')
    //        {
    //            // Whenever a '/' is encountered, create a temporary view from
    //            // the start of the path to the character right before this.
    //            path[i] = 0;
    //            if (mkdir(path.c_str(), S_IRWXU) != 0)
    //            {
    //                if (errno != EEXIST)
    //                {
    //                    return false;
    //                }
    //            }
    //            // Revert the temporary view back to the original.
    //            path[i] = '/';
    //        }
    //    }

    //    // Make the final (full) directory.
    //    if (mkdir(path.c_str(), S_IRWXU) != 0)
    //    {
    //        if (errno != EEXIST)
    //        {
    //            return false;
    //        }
    //    }

    //    return true;
    //}

    inline std::string GetAbsolutePath(const std::string &prefix,
                                       const std::string &relativePath)
    {
        if (relativePath.empty())
        {
            return prefix;
        }
        // If prefix is empty or relative_path is already absolute.
        if (prefix.empty() || relativePath.front() == '/')
        {
            return relativePath;
        }

        if (prefix.back() == '/')
        {
            return prefix + relativePath;
        }

        return prefix + "/" + relativePath;
    }

    inline bool CopyFile(const std::string &from, const std::string &to)
    {
        std::ifstream src(from, std::ios::binary);
        if (!src)
        {
            return false;
        }

        std::ofstream dst(to, std::ios::binary);
        if (!dst)
        {
            return false;
        }

        dst << src.rdbuf();
        return true;
    }

    inline std::string GetFileTag(const std::string &file)
    {
        return file.substr(file.find_last_of('.') + 1);
    }

    inline std::string GetFileName(const std::string &file)
    {
        std::string::size_type iPos = (file.find_last_of('\\') + 1) == 0 ? file.find_last_of('/') + 1 : file.find_last_of('\\') + 1;
        std::string fileName = file.substr(iPos, file.length() - iPos);
        return fileName.substr(0, fileName.rfind('.'));
    }

    inline std::string GetFilePath(const std::string &file)
    {
        std::string::size_type iPos = (file.find_last_of('\\') + 1) == 0 ? file.find_last_of('/') + 1 : file.find_last_of('\\') + 1;
        return file.substr(0, iPos);
    }

} // namespace basis

#endif /* __FILE_H__ */
