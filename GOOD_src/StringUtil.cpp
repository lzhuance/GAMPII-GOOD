/*------------------------------------------------------------------------------
* StringUtil.cpp : string functions
*
* Copyright (C) 2020-2099 by SpAtial SurveyIng and Navigation (SASIN) Group, all rights reserved.
*    This file is part of GAMP II - iPPP-RTK (intelligent PPP and RTK processing software)
*
* References:
*    
*
* history : 2020/09/25 1.0  new (by Feng Zhou)
*-----------------------------------------------------------------------------*/
#include "GOOD.h"
#include "StringUtil.h"


/* function definition -------------------------------------------------------*/

/**
* @brief   : wwww2str - convert from integer week to string week
* @param[I]: wwww (3- or 4-digit GPS week)
* @param[O]: none
* @return  : wwww in string format
* @note    :
**/
string StringUtil::wwww2str(int wwww)
{
    string sWwww("0000"), xWwww(to_string(wwww));
    sWwww.replace(4 - xWwww.size(), xWwww.size(), xWwww);

    return sWwww;
} /* end of wwww2str */

/**
* @brief   : yyyy2str - convert from integer yyyy to string yyyy
* @param[I]: yyyy (4-digit year)
* @param[O]: none
* @return  : yyyy in string format
* @note    :
**/
string StringUtil::yyyy2str(int yyyy)
{
    string sYyyy("0000"), xYyyy(to_string(yyyy));
    sYyyy.replace(4 - xYyyy.size(), xYyyy.size(), xYyyy);

    return sYyyy;
} /* end of yyyy2str */

/**
* @brief   : yy2str - convert from integer yy to string yy
* @param[I]: yy (2-digit year)
* @param[O]: none
* @return  : yy in string format
* @note    :
**/
string StringUtil::yy2str(int yy)
{
    string sYy("00"), xYy(to_string(yy));
    sYy.replace(2 - xYy.size(), xYy.size(), xYy);

    return sYy;
} /* end of yy2str */

/**
* @brief   : doy2str - convert from integer DOY to string DOY
* @param[I]: doy (day of year)
* @param[O]: none
* @return  : DOY in string format
* @note    :
**/
string StringUtil::doy2str(int doy)
{
    string sDoy("000"), xDoy(to_string(doy));
    sDoy.replace(3 - xDoy.size(), xDoy.size(), xDoy);

    return sDoy;
} /* end of doy2str */

/**
* @brief   : mm2str - convert from integer month to string month
* @param[I]: mm (1 - or 2-digit month)
* @param[O]: none
* @return  : mm in string format
* @note    :
**/
string StringUtil::mm2str(int mm)
{
    string sMm("00"), xMm(to_string(mm));
    sMm.replace(2 - xMm.size(), xMm.size(), xMm);

    return sMm;
} /* end of mm2str */

/**
* @brief   : hh2str - convert from integer hour to string hour
* @param[I]: hh (1 - or 2-digit hour)
* @param[O]: none
* @return  : hh in string format
* @note    :
**/
string StringUtil::hh2str(int hh)
{
    string sHh("00"), xHh(to_string(hh));
    sHh.replace(2 - xHh.size(), xHh.size(), xHh);

    return sHh;
} /* end of hh2str */

/**
* @brief     : ToUpper - convert the string from lower case to upper case
* @param[I/O]: str (string)
* @return    : none
* @note      :
**/
void StringUtil::ToUpper(string &str)
{
    for (int i = 0; i < str.size(); i++) str[i] = toupper(str[i]);
} /* end of ToUpper */

/**
* @brief     : ToLower - convert the string from upper case to lower case
* @param[I/O]: str (string)
* @return    : none
* @note      :
**/
void StringUtil::ToLower(string &str)
{
    for (int i = 0; i < str.size(); i++) str[i] = tolower(str[i]);
} /* end of ToLower */

/**
* @brief   : str2num - convert substring in string to number
* @param[I]: s (string ("... nnn.nnn ..."))
* @param[I]: i,n (substring position and width)
* @param[O]: none
* @return  : converted number (0.0:error)
* @note    :
**/
double StringUtil::str2num(const char *s, int i, int n)
{
    double value;
    char str[MAXCHARS], *p = str;

    if (i < 0 || (int)strlen(s) < i || (int)sizeof(str) - 1 < n) return 0.0;
    for (s += i; *s && --n >= 0; s++) *p++ = *s == 'd' || *s == 'D' ? 'E' : *s; *p = '\0';
    return sscanf(str, "%lf", &value) == 1 ? value : 0.0;
} /* end of str2num */

/**
* @brief   : num2str - convert number to string
* @param[I]: num (integer number)
* @param[I]: len (length of the string)
* @param[O]: str (string)
* @return  : none
* @note    :
**/
void StringUtil::num2str(int num, char *str, int len)
{
    int n = len - (int)(log10((float)num)) - 1;
    char tmp[MAXCHARS] = { '\0' };
    if (n < 0)
    {
        tmp[0] = '\0';
        return;
    }

    int j = 0;
    for (int i = 0; i < n; i++) SetStr(&tmp[j++], "0", 2);
    
    char str_tmp[MAXCHARS] = { '\0' };
    sprintf(str_tmp, "%s%d%c", tmp, num, '\0');
    SetStr(str, str_tmp, MAXCHARS);
} /* end of num2str */

/**
* @brief   : SetStr - set string without tail space
* @param[O]: dst (destination string)
* @param[I]: src (source string)
* @param[I]: n (substring width)
* @return  : none
* @note    :
**/
void StringUtil::SetStr(char *dst, const char *src, int n)
{
    char *p = dst;
    const char *q = src;
    while (*q && q < src + n) *p++ = *q++;
    *p-- = '\0';
    while (p >= dst && *p == ' ') *p-- = '\0';
} /* end of SetStr */

/**
* @brief   : StrMid - string clipping
* @param[O]: dst (destination string)
* @param[I]: src (source string)
* @param[I]: nPos (start position)
* @param[I]: nCount (number of selected characters)
* @return  : none
* @note    :
**/
void StringUtil::StrMid(char *dst, const char *src, int nPos, int nCount)
{
    int n = (int)strlen(src);
    if (n <= 0) return;

    const char *str = src + nPos;
    for (int i = 0; i < nCount; i++)
    {
        char c = *(str + i);
        if (c) *(dst + i) = c;
        else
        {
            *(dst + i) = '\0';
            break;
        }
    }
    *(dst + nCount) = '\0';
} /* end of StrMid */

/**
* @brief     : TrimSpace4String - trim head and tail space of the string
* @param[I/O]: s (input string with head and tail space; output string without head and tail space)
* @return    : none
* @note      :
**/
void StringUtil::TrimSpace4String(string &s)
{
    if (s.empty()) return;

    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
} /* end of TrimSpace4String */

/**
* @brief     : TrimSpace4Char - trim head and tail space of the string
* @param[I/O]: dstsrc (destination string (may be with head and tail space) and 
*              source string (without head and tail space))
* @return    : none
* @note      :
**/
void StringUtil::TrimSpace4Char(char *dstsrc)
{
    int len = (int)strlen(dstsrc);
    char str[MAXCHARS + 1];

    if (len <= 0) return;

    str[0] = '\0';
    SetStr(str, dstsrc, (int)strlen(dstsrc) + 1);

    int ps = 0;
    for (int i = 0; i < len; i++)
    {
        if (*(str + i) != ' '&&*(str + i) != '\t')
        {
            ps = i;
            break;
        }
    }

    int pe = ps;
    for (int j = len - 1; j >= 0; j--)
    {
        if (*(str + j) != ' '&&*(str + j) != '\t'&&*(str + j) != '\n')
        {
            pe = j;
            break;
        }
    }

    if (pe == ps) *(str + pe) = '\0';
    else *(str + pe + 1) = '\0';

    SetStr(dstsrc, str + ps, (int)strlen(str + ps) + 1);
} /* end of TrimSpace4Char */

/**
* @brief     : CutFilePathSep - 
* @param[I/O]: strPath (input/output path string)
* @return    : none
* @note      :
**/
void StringUtil::CutFilePathSep(char *strPath)
{
    for (int i = 0; i < 4; i++)
    {
        int len = (int)strlen(strPath);
        if (len <= 0) break;

        if (strPath[len - 1] == FILEPATHSEP) strPath[len - 1] = '\0';
        else break;
    }
} /* end of CutFilePathSep */

/**
* @brief   : GetFile - get the full name of a specific file from the current directory
* @param[I]: dir (the current directory)
* @param[I]: str (string to match)
* @param[O]: fileName (the full name of a specific file)
* @return  : true: found, false: NOT found
* @note    :
**/
bool StringUtil::GetFile(string dir, string str, string &fileName)
{
    /* change directory */
#ifdef _WIN32   /* for Windows */
    _chdir(dir.c_str());
#else           /* for Linux or Mac */
    chdir(dir.c_str());
#endif

    string cmd, fileList = "files.list";
#ifdef _WIN32   /* for Windows */
    cmd = "dir /b | find \"" + str + "\"" + " > " + fileList;
#else           /* for Linux or Mac */
    cmd = "ls *" + str + "* > " + fileList;
#endif
    std::system(cmd.c_str());

    bool isFound = false;
    if (access(fileList.c_str(), 0) == 0)
    {
        ifstream filLst(fileList.c_str());
        if (!filLst.is_open())
        {
            cerr << "*** ERROR(StringUtil::GetFile): open files.list = " << fileList << " file failed, please check it" << endl;

            return false;
        }

        string fil;
        getline(filLst, fil);
        TrimSpace4String(fil);
        if (fil.size() > 0)
        {
            fileName = fil;
            isFound = true;
        }
        else isFound = false;

        /* close 'files.list' */
        filLst.close();
    }

    /* delete 'files.list' */
#ifdef _WIN32   /* for Windows */
    cmd = "del " + fileList;
#else           /* for Linux or Mac */
    cmd = "rm -rf " + fileList;
#endif
    std::system(cmd.c_str());

    return isFound;
} /* end of GetFile */

/**
* @brief   : GetFilesAll - get the name list of all the files from the current directory
* @param[I]: dir (the current directory)
* @param[I]: suffix (file suffix)
* @param[O]: files (the name list of all the files)
* @return  : none
* @note    :
**/
void StringUtil::GetFilesAll(string dir, string suffix, vector<string> &files)
{
    /* change directory */
#ifdef _WIN32   /* for Windows */
    _chdir(dir.c_str());
#else           /* for Linux or Mac */
    chdir(dir.c_str());
#endif

    string cmd, fileList = "files.list";
#ifdef _WIN32   /* for Windows */
    cmd = "dir /b | find \"" + suffix + "\"" + " > " + fileList;
#else           /* for Linux or Mac */
    cmd = "ls *" + suffix + "* > " + fileList;
#endif
    std::system(cmd.c_str());

    if (access(fileList.c_str(), 0) == 0)
    {
        ifstream filLst(fileList.c_str());
        if (!filLst.is_open())
        {
            cerr << "*** ERROR(StringUtil::GetFilesAll): open files.list = " << fileList << " file failed, please check it" << endl;

            return;
        }

        string fileName;
        while (getline(filLst, fileName))
        {
            files.push_back(fileName);
        }

        /* close 'files.list' */
        filLst.close();
    }

    /* delete 'files.list' */
#ifdef _WIN32   /* for Windows */
    cmd = "del " + fileList;
#else           /* for Linux or Mac */
    cmd = "rm -rf " + fileList;
#endif
    std::system(cmd.c_str());
} /* end of GetFilesAll */

/**
* @brief   : GetSubStr - get sub-string in a vector from a string
* @param[I]: str (string)
* @param[I]: sep (delimiter)
* @param[O]: subStrs (sub strings)
* @return  : none
* @note    :
**/
void StringUtil::GetSubStr(string str, string sep, vector<string> &subStrs)
{
    std::string::size_type pos1, pos2;
    pos2 = str.find(sep);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        subStrs.push_back(str.substr(pos1, pos2 - pos1));

        pos1 = pos2 + sep.size();
        pos2 = str.find(sep, pos1);
    }
    if (pos1 != str.length()) subStrs.push_back(str.substr(pos1));
} /* end of GetSubStr */