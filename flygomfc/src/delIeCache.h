/**

���ܣ�����IE���棬Cookie

**/

#ifndef __DELECACHE_H__
#define __DELECACHE_H__
#define SWEEP_BUFFER_SIZE 10000

 //Ҫɾ�������͡�
enum DEL_CACHE_TYPE
{
	File,//��ʾinternet��ʱ�ļ�
	Cookie //��ʾCookie
};

BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni, BOOL bWipeIndexDat);
BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);

#endif // DELECACHE_H
