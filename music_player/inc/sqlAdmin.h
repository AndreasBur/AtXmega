#ifndef SQLADMIN_H
#define SQLADMIN_H

#include <sqlite3.h>
#include <string>

using namespace std;

class sqlAdmin
{
    public:
        sqlAdmin(string Database, string Table);
        ~sqlAdmin();

        DatabaseOpen();
        PrintData();
        SendSqlCmd();
    protected:
    private:
        string Database;
        string Table;


};

#endif // SQLADMIN_H
