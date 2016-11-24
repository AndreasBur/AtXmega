#!/bin/sh 



for file in *

do 
  format=${file#*.}	# Dateiendung extrahieren

    
    # Falls Datei mp3 oder ogg oder wma oder aac
    if [ "$format" = "mp3" ] || [ "$format" = "ogg" ] || [ "$format" = "wma" ] || [ "$format" = "aac" ]
    then
      data_input="${file}"							# Metainformationnen zusammenfügen
      echo "$data_input" > music_filenames.txt		# Metainformationnen in Datenbank speichern
    fi

done