#include "PathUtils.h"
#ifdef __linux__
#include <libgen.h>
#include <linux/limits.h>
#include <unistd.h>
#elif __APPLE__
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#elif _WIN32
#include <shlwapi.h>
#endif

std::string PathUtils::GetModuleFolder()
{
#ifdef __linux__
    char result[PATH_MAX];
    if (readlink("/proc/self/exe", result, PATH_MAX) > 0) {
      return std::string(dirname(result)).append("/");
    } else {
      return "";
    }
#elif __APPLE__
    char buf[0];
    uint32_t size = 0;
    int res = _NSGetExecutablePath(buf, &size);
    
    char* path = (char*)malloc(size+1);
    path[size] = 0;
    res = _NSGetExecutablePath(path, &size);
    
    char* p = strrchr(path, '/');
    *(p+1) = 0;
    
    std::string resultPath(path);
    free(path);
    
    return resultPath;
#elif _WIN32
    char szPath[MAX_PATH];
    char szBuffer[MAX_PATH];
    char * pszFile;

    ::GetModuleFileName(NULL, (LPTCH)szPath, sizeof(szPath) / sizeof(*szPath));
    ::GetFullPathName((LPTSTR)szPath, sizeof(szBuffer) / sizeof(*szBuffer), (LPTSTR)szBuffer, (LPTSTR*)&pszFile);
    *pszFile = 0;

    return std::string(szBuffer);
#endif
}

bool PathUtils::FileExists(const std::string& fname)
{
#ifdef __linux__
    return access(fname.c_str(), F_OK) != -1;
#elif __APPLE__
    return access(fname.c_str(), F_OK) != -1;
#elif _WIN32
    return PathFileExists(fname.c_str()) == TRUE;
#endif
}
