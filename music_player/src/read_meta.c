/*************************************************************************************************************************************
*   I N C L U D E
*************************************************************************************************************************************/
#include "read_meta.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

/*************************************************************************************************************************************
*   I N I T
*************************************************************************************************************************************/
void meta_init(const char *database_path, struct meta *smeta)
{
    read_metinfo_from_file(database_path, smeta);
}


/*************************************************************************************************************************************/
/*! \fn void add_metainfo(struct meta *pmeta, const char *column1, const char *column2, const char *column3)
*
*   \brief Adds 3 strings to the array of the struct meta
*
*   \return
*
*************************************************************************************************************************************/
void add_metainfo(struct meta *pmeta, const char *column1, const char *column2, const char *column3)
{
    // Anzahl der Zeilen erh�hen
    pmeta->rows++;

    // Speicher f�r eine Zeile allokieren
    pmeta->meta_array = (char ***) realloc(pmeta->meta_array, (pmeta->rows) * sizeof(char **));
    // Speicher f�r 3 Spalten allokieren
    pmeta->meta_array[pmeta->rows-1] = (char ** ) malloc(COLUMBS * sizeof(char *));

    // Speicher f�r Stringl�nge des FILENAMEN allokieren
    pmeta->meta_array[pmeta->rows-1][FILENAME] = (char *) malloc((strlen(column1)+1) * sizeof(char));
    strcpy(pmeta->meta_array[pmeta->rows-1][FILENAME],column1);
    // Speicher f�r Stringl�nge des ARTISTEN allokieren
    pmeta->meta_array[pmeta->rows-1][ARTIST] = (char *) malloc((strlen(column2)+1) * sizeof(char));
    strcpy(pmeta->meta_array[pmeta->rows-1][ARTIST],column2);
    // Speicher f�r Stringl�nge des TITEL allokieren
    pmeta->meta_array[pmeta->rows-1][TITLE] = (char *) malloc((strlen(column3)+1) * sizeof(char));
    strcpy(pmeta->meta_array[pmeta->rows-1][TITLE],column3);
}


/*************************************************************************************************************************************/
/*! \fn void read_metinfo_from_file(const char *file_path, struct meta *pmeta)
*
*   \brief Reads the metainfo file and adds the infos to the array of meta
*
*   \return
*
*************************************************************************************************************************************/
void read_metinfo_from_file(const char *file_path, struct meta *pmeta)
{
    char delimiter[] = ";";
    char *ptr;
    int split_counter;
    int string_length;
    FILE *database;
    // Zwischenspeicher
    char buffer[DATABASE_MAX_LINE_SIZE]="";
    char filename_tmp[DATABASE_MAX_LINE_SIZE]="";
    char artist_tmp[DATABASE_MAX_LINE_SIZE]="";
    char title_tmp[DATABASE_MAX_LINE_SIZE]="";

    // Datenbank Datei �ffnen
    database = fopen (file_path, "r");

   // Konnte Datenbank ge�ffnet werden?
   if (database != NULL)
     {
	    // Lese jede einzelne Zeile ein
	    while(fgets(buffer, sizeof(buffer), database)!=0)
	    {
		  // String (jede Zeile) bei jedem ";" teilen und speichern
		  ptr = strtok(buffer, delimiter);
		  split_counter = 0;

		    // Solange Einlesen bis Zeile zu Ende
		    while(ptr != NULL)
		    { // Stringl�nge zaehlen und speichern
			  string_length = strlen(ptr);

			  // Zeilenumbruch entfernen, falls vorhanden
			  if( ptr[string_length-1] == '\n' ) { ptr[string_length-1] = 0;}

			  // Erster Abschnitt entspricht Dateinamen
			  if(split_counter == FILENAME) { strcpy(filename_tmp, ptr); }

			  // Zweitem Abschnitt entspricht K�nstler
			  if(split_counter == ARTIST) { strcpy(artist_tmp, ptr); }

			  // Drittem Abschnitt entspricht Titel
			  if(split_counter == TITLE) { strcpy(title_tmp, ptr); }

			  // String bis zum n�chsten ";" einlesen
			  ptr = strtok(NULL, delimiter);
			  split_counter++;
		    }
        // Eigelesene Meta Infos zum Array hinzuf�gen
        add_metainfo(pmeta, filename_tmp, artist_tmp, title_tmp);
        // TMP loeschen
        filename_tmp[0] = 0;
        artist_tmp[0] = 0;
        title_tmp[0] = 0;
	    }
	// Datenbankdatei schlie�en
	fclose (database);
   }
   else
   {
        printf("Konnte Datenbank nicht oeffnen\n");
   }
}


/*************************************************************************************************************************************/
/*! \fn void sort_meta(struct meta *pmeta, int sort_type)
*
*   \brief sorts string arrays according to alphabet
*
*   \return
*
*************************************************************************************************************************************/
void sort_meta(struct meta *pmeta, int sort_type)
{
    int i, swapped;
    int elements=pmeta->rows;

    if(pmeta == NULL) return;
    // Sort array alphabetically with Bubblesort
    while(elements-- || swapped!=0)
    {
		swapped = 0;
        for(i = 1; i <= elements; i++)
        {
            if(strcasecmp(pmeta->meta_array[i-1][sort_type], pmeta->meta_array[i][sort_type])>0)
            {
                swap_entry(pmeta, i);
				swapped = 1;
            }
        }
    }
}


/************************************************************************************************************************************/
/*! \fn void swap_entry(struct meta *pmeta, int row)
*
*   \brief swaps two neighbouring entries of the string array
*
*   \return
*
************************************************************************************************************************************/
void swap_entry(struct meta *pmeta, int row)
{
    char **tmp;

    if(pmeta == NULL) return;
    tmp = pmeta->meta_array[row-1];
    pmeta->meta_array[row-1] = pmeta->meta_array[row];
    pmeta->meta_array[row] = tmp;
}
