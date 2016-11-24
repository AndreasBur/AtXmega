#include "musicDatabase.h"

musicDatabase::musicDatabase(string sDatabase, string sTable)
{
    Database = sDatabase;
    Table = sTable;
    // open database
    //SQLiteDatabase *pMusicDb = new SQLiteDatabase("MusicFiles.db", SQLITE_OPEN_READWRITE, 0);
    pDb = new SQLiteDatabase(sDatabase.c_str(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
    // create statement instance for sql queries/statements
    pDbStmt = new SQLiteStatement(pDb);
}

musicDatabase::~musicDatabase()
{

}

vector<vector<string> >& musicDatabase::getMusicMetaData(string SqlCmd)
{
    SqlDataToVector(SqlCmd);
    return MusicMetaData;
}

vector<vector<string> >& musicDatabase::getMusicMetaData(meta_sort_t MetaSort)
{
    string Sql;

    Sql = "SELECT * FROM " + Table + SortToSqlCmd(MetaSort) + ";";
    SqlDataToVector(Sql);
    return MusicMetaData;
}

vector<vector<string> >& musicDatabase::getMusicMetaDataSearch(meta_sort_t MetaSort, string Search)
{
    string Sql;

    Sql = "SELECT * FROM " + Table + " WHERE (TITLE LIKE '%" + Search + "%') OR (ARTIST LIKE '%" + Search + "%') OR (ALBUM LIKE '%" + Search + "%')" + SortToSqlCmd(MetaSort) + ";";
    SqlDataToVector(Sql);
    return MusicMetaData;
}

void musicDatabase::TableCreate()
{
    try
    {
        pDbStmt->SqlStatement("CREATE TABLE MUSIC(  ID INT PRIMARY    KEY NOT NULL, \
                                                    TITLE             VARCHAR(255), \
                                                    ARTIST            VARCHAR(255), \
                                                    ALBUM             VARCHAR(255), \
                                                    FILENAME          VARCHAR(255))");
    }
    catch(SQLiteException &exception)
    {
        cerr << "Exception Occured" << std::endl;
        exception.Show();
    }
}

void musicDatabase::PrintData()
{
    string Sql;

    Sql = "SELECT * FROM " + Table;
    pDbStmt->Sql(Sql);

    // process all results
    cout << "Table: " << Table << endl;
    while(pDbStmt->FetchRow())
    {
        cout << "ID: " << pDbStmt->GetColumnInt(0) << endl;
        cout << "Title: " << pDbStmt->GetColumnString(1) << endl;
        cout << "Artist: " << pDbStmt->GetColumnString(2) << endl;
        cout << "Album: " << pDbStmt->GetColumnString(3) << endl;
        cout << "Filename: " << pDbStmt->GetColumnString(4) << endl;
    }
    // do not forget to clean-up
    pDbStmt->FreeQuery();
}

int musicDatabase::TableAddData()
{
    vector<string> MusicFilenames;
    string SqlCmd;

    MusicFilenames = readMusicFilenames("music_filenames.txt");
    for(int i=0; i<(int) MusicFilenames.size()-1; i++)
    {
        string File = "/home/pi/music/" + MusicFilenames[i]; // Musikpfad ändern!!!!
        string Title = getMetaData(File.c_str(), META_TYPE_TITLE);
        string Artist = getMetaData(File.c_str(), META_TYPE_ARTIST);
        string Album = getMetaData(File.c_str(), META_TYPE_ALBUM);

        Title = ReplaceString(Title, "'", "''");
        Artist = ReplaceString(Artist, "'", "''");
        Album = ReplaceString(Album, "'", "''");
        MusicFilenames[i] = ReplaceString(MusicFilenames[i], "'", "''");

        SqlCmd = "INSERT INTO MUSIC (ID,TITLE,ARTIST,ALBUM,FILENAME) VALUES (" + to_string(i+1) + ", ";
        SqlCmd.append("'" + Title + "', ");
        SqlCmd.append("'" + Artist + "', ");
        SqlCmd.append("'" + Album + "', ");
        SqlCmd.append("'" + MusicFilenames[i] + "');");
        cout << SqlCmd << endl;
        try
        {
            pDbStmt->SqlStatement(SqlCmd.c_str());
        }
        catch(SQLiteException &exception)
        {
            cerr << "Exception Occured" << std::endl;
            exception.Show();
        }
    }
    return 0;
}

string musicDatabase::ReplaceString(string subject, const string& search, const string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos)
    {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

void musicDatabase::SqlDataToVector(string SqlCmd)
{
    int i=0;

    MusicMetaData.clear();

    pDbStmt->Sql(SqlCmd);
    // process all results
    while(pDbStmt->FetchRow())
    {
        MusicMetaData.push_back(vector<string>(5));
        // ID
        MusicMetaData[i][0] = pDbStmt->GetColumnString(0);
        // Title
        MusicMetaData[i][1] = pDbStmt->GetColumnString(1);
        // Artist
        MusicMetaData[i][2] = pDbStmt->GetColumnString(2);
        // Album
        MusicMetaData[i][3] = pDbStmt->GetColumnString(3);
        // Filename
        MusicMetaData[i][4] = pDbStmt->GetColumnString(4);
        i++;
    }
    // do not forget to clean-up
    pDbStmt->FreeQuery();
}

string musicDatabase::SortToSqlCmd(meta_sort_t MetaSort)
{
    string Sql;

    if(MetaSort == META_SORT_TITLE) Sql = " ORDER BY TITLE ";
    if(MetaSort == META_SORT_ARTIST) Sql = " ORDER BY ARTIST ";
    if(MetaSort == META_SORT_ALBUM) Sql = " ORDER BY ALBUM ";
    if(MetaSort == META_SORT_FILENAME) Sql = " ORDER BY FILENAME ";

    return Sql;
}

string musicDatabase::getMetaData(string File, meta_type_t MetaDataType)
{
    FileRef MusicFile(File.c_str());

    if(MetaDataType == META_TYPE_TITLE) {
        String Title = MusicFile.tag()->title();
        return Title.to8Bit();
    }
    if(MetaDataType == META_TYPE_ARTIST) {
        String Artist = MusicFile.tag()->artist();
        return Artist.to8Bit();
    }
    if(MetaDataType == META_TYPE_ALBUM) {
        String Album = MusicFile.tag()->album();
        return Album.to8Bit();
    }
    return "";
}

vector<string> musicDatabase::readMusicFilenames(string File)
{
    ifstream MusicFilenamesFile;
    string Line;
    vector<string> MusicFilenames;

    MusicFilenamesFile.open(File.c_str(), ios::in);
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
