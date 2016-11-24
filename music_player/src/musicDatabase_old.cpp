/*************************************************************************************************************************************
*   I N C L U D E
*************************************************************************************************************************************/
#include "musicDatabase.h"
#include <iostream>
#include <fstream>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <sqlite3.h>
#include <stdio.h>


/*************************************************************************************************************************************/
/*! \fn int initMusicDatabase(const char *MusicFilePath)
*
*   \brief
*
*   \return
*
*************************************************************************************************************************************/
int DBInit()
{
    const char* sql;

    // Create SQL statement
    sql = "CREATE TABLE MUSIC("  \
          "ID INT PRIMARY    KEY NOT NULL," \
          "TITLE             VARCHAR(255)," \
          "ARTIST            VARCHAR(255)," \
          "ALBUM             VARCHAR(255)," \
          "FILENAME          VARCHAR(255));";

    if (sendSqlCommand(sql, NULL)) {
        cout << "Database Error" << endl;
        return 1;
    }
    else {
        cout << "Database OK" << endl;
        return 0;
    }
}


/*************************************************************************************************************************************/
/*! \fn int initMusicDatabase(const char *MusicFilePath)
*
*   \brief
*
*   \return
*
*************************************************************************************************************************************/
int DBAddData()
{
    const char *sql;
    vector<string> MusicFilenames;
/*
    sql = "INSERT INTO MUSIC (ID,TITLE,ARTIST,ALBUM,FILENAME) " \
         "VALUES (1, 'Pride', 'U2', '360 Tour', 'U2-Pride.mp3'); ";

    if (sendSqlCommand(sql, NULL)) {
        cout << "Database Error" << endl;
        return 1;
    }
    else {
        cout << "Database OK" << endl;
        return 0;
    }
*/
    MusicFilenames = readMusicFilenames(NULL);
    for(int i=0; i<MusicFilenames.size(); i++)
    {
        cout << MusicFilenames[i] << endl;
    }

    return 0;
}


/*************************************************************************************************************************************/
/*! \fn int sendSqlCommand(const char *sql)
*
*   \brief
*
*   \return
*
*************************************************************************************************************************************/
int sendSqlCommand(const char *sql, int (*callback)(void*,int,char**,char**))
{
    sqlite3 *db;
    int rc;
    char *zErrMsg = NULL;

    rc = sqlite3_open("MusicFiles.db", &db);
    // something went wrong?
    if(rc) {
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }
    // if there is no error fill the tables
    cout << "Opened database successfully" << endl;

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
    // something went wrong?
    if(rc != SQLITE_OK) {
        cout << "SQL ERROR: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}


/*************************************************************************************************************************************/
/*! \fn int sendSqlCommand(const char *sql)
*
*   \brief
*
*   \return
*
*************************************************************************************************************************************/
void DBPrint()
{
    const char *sql;

    sql = "SELECT * from MUSIC";

    if (sendSqlCommand(sql, callback)) cout << "Database Error" << endl;
    else cout << "Database OK" << endl;
}


/*************************************************************************************************************************************/
/*! \fn int sendSqlCommand(const char *sql)
*
*   \brief
*
*   \return
*
*************************************************************************************************************************************/
int callback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


/*************************************************************************************************************************************/
/*! \fn int sendSqlCommand(const char *sql)
*
*   \brief
*
*   \return
*
*************************************************************************************************************************************/
vector<string> readMusicFilenames(const char* Path)
{
    ifstream MusicFilenamesFile;
    string Line;
    vector<string> MusicFilenames;

    MusicFilenamesFile.open("music_filenames.txt", ios::in);
    if(!MusicFilenamesFile) {
        cout << "Error Cannot read file" << endl;
        return MusicFilenames;
    }

    while (!MusicFilenamesFile.eof())   // read until end of file
    {
        getline(MusicFilenamesFile, Line);           // read a line
        MusicFilenames.push_back(Line);              // save line in vector
    }

    MusicFilenamesFile.close(); // close file
    return MusicFilenames;      // return vector
}
