#include "sqlAdmin.h"

sqlAdmin::sqlAdmin(string sDatabase, string sTable)
{
    Database = sDatabase;
    Table = sTable;
}

sqlAdmin::~sqlAdmin()
{
    //dtor
}
