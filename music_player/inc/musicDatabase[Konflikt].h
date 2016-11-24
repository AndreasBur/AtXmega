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

using namespace std;
using namespace Kompex;
using namespace TabLib;

typedef enum {
    TITLE,
    ARTIST,
    ALBUM
} meta_type_t;

class musicDatabase
{
    public:
        musicDatabase(string sDatabase, string sTable);
        ~musicDatabase();

        void TableCreate();
        int TableAddData();
        void PrintData();
    protected:
    private:
        string getMetaData(string MusicFile, meta_type_t MetaDataType);
        vector<string> readMusicFilenames(string File);
        string Database;
        string Table;
        vector<string> readMusicFilenames(string MusicFile);
        vector<vector<string> > MusicMetaData;
        SQLiteDatabase *pDb;
        SQLiteStatement *pDbStmt;

};

#endif // MUSICDATABASE_H
