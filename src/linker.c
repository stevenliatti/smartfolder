/**
 * @file linker.c
 * @brief      Ce fichier contient la partie création des liens du projet.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "linker.h"

/**
 * @brief      Fonction qui crée un lien symbolique link_path vers file_linked.
 *             Elle gère le cas ou un lien ayant le même nom, mais pointant vers
 *             un autre fichier, existe déjà : elle rajoute un nombre aléatoire
 *             entre 0 et 9999 au nom du fichier.
 *
 * @param[in]  file_linked  Le fichier à lier
 * @param[in]  link_path    Le nom du lien (le nom de file_linked)
 *
 * @return     0 en cas de succès de la création du lien, -1 sinon
 */
int linker(const char* file_linked, const char* link_path) {
	char copy_file_linked[255];
	strcpy(copy_file_linked, file_linked);
	logger(LOG_DEBUG, stderr, "copy_file_linked : %s\n", copy_file_linked);
	char* filename_only = strrchr(copy_file_linked, '/'); // ici on récupère le nom du fichier avec le slash, ex : /test.txt
	filename_only[strlen(filename_only)] = '\0'; // on met à NULL le dernier caractère de filename_only

	char resolved_file_linked[PATH_MAX], resolved_link_name[PATH_MAX];
	realpath(file_linked, resolved_file_linked); // je crée les path complets pour symlink
	realpath(link_path, resolved_link_name);
	strcat(resolved_link_name, filename_only); // à ce moment dans resolved_link_name, il n'y que le dossier de destination
	logger(LOG_DEBUG, stderr, "in linker, resolved_file_linked, resolved_link_name : \n");
	logger(LOG_DEBUG, stderr, "%s,\t%s\n", resolved_file_linked, resolved_link_name);
	int res = _symlink(resolved_file_linked, resolved_link_name);

	// Si un link ayant le même nom existe déjà, je concatène un nombre aléatoire au nouveau nom
	while (res != 0) {
		srand(time(NULL));
		int i = rand() % 10000;
		char str[5];
		sprintf(str, "%d", i);
		char copy_link_name[PATH_MAX];
		strcpy(copy_link_name, link_path);
		strcat(copy_link_name, filename_only);
		logger(LOG_DEBUG, stderr, "copy_link_name : %s\n", copy_link_name);
		strcat(copy_link_name, str);
		realpath(copy_link_name, resolved_link_name);
		logger(LOG_DEBUG, stderr, "new resolved_link_name : %s\n", resolved_link_name);
		res = _symlink(resolved_file_linked, resolved_link_name);
	}

	return res;
}
