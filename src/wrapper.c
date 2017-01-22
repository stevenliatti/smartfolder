/**
 * @file wrapper.c
 * @brief      Implémentation d'un wrapper pour les appels systèmes utilisés.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "wrapper.h"

/**
 * @brief      Appelle symlink (création de liens symboliques).
 *
 * @param[in]  oldpath  Le nom du fichier à linker.
 * @param[in]  newpath  Le chemin du lien.
 *
 * @return     0 si réussite, -1 si échec.
 */
int _symlink(const char* oldpath, const char* newpath) {
	return symlink(oldpath, newpath);
}

/**
 * @brief      Ouvre un répertoire selon le path.
 *
 * @param[in]  path  Le chemin d'accès au dossier.
 *
 * @return     Un pointeur sur le flux du dossier ouvert.
 */
DIR* _opendir(const char* path) {
	return opendir(path);
}

/**
 * @brief      Ferme un dossier ouvert.
 *
 * @param      dir   Le répertoire en question.
 *
 * @return     0 si réussite, -1 si échec.
 */
int _closedir(DIR* dir) {
	return closedir(dir);
}
