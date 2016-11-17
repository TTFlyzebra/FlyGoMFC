/**

功能：清理IE缓存，Cookie

**/

#ifndef __DELECACHE_H__
#define __DELECACHE_H__
#define SWEEP_BUFFER_SIZE 10000

 //要删除的类型。
enum DEL_CACHE_TYPE
{
	File,//表示internet临时文件
	Cookie //表示Cookie
};

BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni, BOOL bWipeIndexDat);
BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);

#endif // DELECACHE_H
