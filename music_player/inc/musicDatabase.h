#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <stdio.h>
#include <kompex/KompexSQLiteDatabase.h>
#include <kompex/KompexSQLiteStatement.h>
#include <kompex/KompexSQLiteException.h>

using namespace std;
using namespace Kompex;
using namespace TagLib;

typedef enum {
    META_TYPE_TITLE,
    META_TYPE_ARTIST,
    META_TYPE_ALBUM
} meta_type_t;

typedef enum {
    META_SORT_TITLE,
    META_SORT_ARTIST,
    META_SORT_ALBUM,
    META_SORT_FILENAME
} meta_sort_t;

class musicDatabase
{
    public:
        musicDatabase(string sDatabase, string sTable);
        ~musicDatabase();

        // musicDatabase methods get functions
        string getDatabase() const { return Database; }
        string getTable() const { return Table; }
        vector<vector<string> >& getMusicMetaData(string SqlCmd);
        vector<vector<string> >& getMusicMetaData(meta_sort_t MetaSort);
        vector<vector<string> >& getMusicMetaDataSearch(meta_sort_t MetaSort, string Search);
        // musicDatabase methods set functions
        void setDatabase(string sDatabase) { Database = sDatabase; }
        void setTable(string sTable) { Table = sTable; }

        // musicDatabase methods functions
        void TableCreate();
        int TableAddData();
        void PrintData();

    protected:

    private:
        void SqlDataToVector(string SqlCmd);
        string getMetaData(string MusicFile, meta_type_t MetaDataType);
        string SortToSqlCmd(meta_sort_t MetaSort);
        vector<string> readMusicFilenames(string File);
        string ReplaceString(string subject, const string& search, const string& replace);
        string Database;
        string Table;
        vector<vector<string> > MusicMetaData;
        SQLiteDatabase *pDb;
        SQLiteStatement *pDbStmt;
};

#endif // MUSICDATABASE_H
