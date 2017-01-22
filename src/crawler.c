/**
 * @file crawler.c
 * @brief      Module Crawler, parcoure le dossier et les sous-dossiers de
 *             recherche donné en argument du programme.
 * @author     Steven Liatti
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "crawler.h"
#include "argument.h"

/**
 * @brief      Détermine si entry est dossier ou non.
 *
 * @param      entry  Un pointeur sur une struct dirent
 *
 * @return     Un booléan, vrai si c'est dossier (ou un lien symbolique vers un
 *             dossier), faux dans les autres cas.
 */
bool is_dir(struct dirent* entry) {
	return entry->d_type == DT_DIR || entry->d_type == DT_LNK;
}

/**
 * @brief      Parcoure le dossier path et ses sous-dossiers. Évite les boucles
 *             infinies grâce à une table de hash (paths_traveled). Si un
 *             fichier est déjà contenu dans la table de hash des fichiers, le
 *             Filter n'est pas appelé. Si path est un dossier, se rappelle
 *             elle-même avec ce dossier comme nouveau path.
 *
 * @param      path            Le chemin du dossier/fichier.
 * @param      folder_path     Le chemin du dossier de destination des éventuels
 *                             liens.
 * @param      paths_traveled  La table de hash nécessaire pour éviter les
 *                             boucles au sein de l'arborescence de path (pour
 *                             mémoriser le chemin parcouru).
 * @param      files_to_link   La table de hash qui contient les fichiers qui
 *                             ont été linkés par le Linker, pour ne pas
 *                             repasser par les tests du filtre.
 * @param      arguments       Les arguments fournis en ligne de commande, à
 *                             transmettre au filtre.
 * @param[in]  args_size       Le nombre de ces arguments.
 */
void crawler(char* path, char* folder_path, hash_table_t* paths_traveled, 
	hash_table_t* files_to_link, argument_t* arguments, int args_size) {
	DIR* dir = _opendir(path);
	if (dir == NULL) return;
	struct dirent* entry = NULL;
	bool inserted;
	int hash;
	char entry_path[PATH_MAX], resolved_path[PATH_MAX];
	while ((entry = readdir(dir)) != NULL) {
		if (!(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)) {
			strcpy(entry_path, path);
			logger(LOG_DEBUG, stderr, "entry_path (1) : %s\n", entry_path);
			strcat(entry_path, "/");
			logger(LOG_DEBUG, stderr, "entry_path (2) : %s\n", entry_path);
			strcat(entry_path, entry->d_name);
			logger(LOG_DEBUG, stderr, "entry_path (3) : %s\n", entry_path);
			realpath(entry_path, resolved_path);
			logger(LOG_DEBUG, stderr, "\nd_name : %s\n", entry->d_name);
			logger(LOG_DEBUG, stderr, "resolved_path : %s\n", resolved_path);

			if (is_dir(entry)) {
				logger(LOG_DEBUG, stderr, "is_dir : %s\n", resolved_path);
				paths_traveled = insert(resolved_path, paths_traveled, &inserted);
				if (inserted) {
					crawler(entry_path, folder_path, paths_traveled, files_to_link, arguments, args_size);
				}
			}
			else {
				logger(LOG_DEBUG, stderr, "NOT is_dir : %s\n", resolved_path);
				if (!contains(resolved_path, files_to_link, &hash)) {
					logger(LOG_DEBUG, stderr, "hash : %d\n", hash);
					//files_to_link = insert_with_hash(resolved_path, files_to_link, &inserted, &hash);
					// call the FILTER
					files_to_link = filter(resolved_path, folder_path, arguments, args_size, files_to_link, &hash);
				}
			}
		}
	}
	_closedir(dir);
}
