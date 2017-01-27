Pour lancer un searchfolder :
cd src
make

puis :
searchfolder <dir_name> <search_path> [expression]

Pour supprimer un searchfolder :
searchfolder -d <dir_name>

Exemple :
searchfolder big_videos user/videos -name_contain .mkv -name_contain .mp4 -or -size +10g -and

Pour plus de détails, voir la doc dans le dossier doxygen (lien vers index.html)