/**
 * @file wrapper.c
 * @brief      Implémentation d'un wrapper pour les appels systèmes utilisés.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "wrapper.h"
#include "logger.h"

/**
 * @brief      Appelle symlink (création de liens symboliques).
 *
 * @param[in]  oldpath  Le nom du fichier à linker.
 * @param[in]  newpath  Le chemin du lien.
 *
 * @return     0 si réussite, -1 si échec.
 */
int _symlink(const char* oldpath, const char* newpath) {
	int s = symlink(oldpath, newpath);

	return s;
}

/**
 * @brief      Wrapper de la fonction fork. Crée un processus enfant.
 *
 * @return     Le pid de l'enfant dans le parent et 0 dans l'enfant. -1 si
 *             erreur.
 */
pid_t _fork() {
	pid_t pid = fork();

	if (pid == -1) {
		logger(LOG_ERROR, stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	}

	return pid;
}

/**
 * @brief      Wrapper de la fonction access. Vérifie l'existence d'un fichier.
 *
 * @param[in]  name  Le nom du fichier.
 * @param[in]  mode  Le mode d'ouverture.
 *
 * @return     0 si le fichier existe, -1 sinon.
 */
int _access(const char* name, int mode) {
	return access(name, mode);
}

/**
 * @brief      Wrapper de la fonction kill. Envoie un signal au processus ayant
 *             le pid indiqué.
 *
 * @param[in]  pid   Le pid du processus.
 * @param[in]  sig   Le signal à envoyer.
 *
 * @return     0 si succès, -1 si erreur.
 */
int _kill(pid_t pid, int sig) {
	int k = kill(pid, sig);

	if (k == -1) {
		logger(LOG_ERROR, stderr, "kill failed\n");
		exit(EXIT_FAILURE);
	}

	return k;
}

/**
 * @brief      Wrapper de la fonction rmdir. Supprime un dossier vide.
 *
 * @param[in]  path  Le chemin du fichier.
 *
 * @return     0 si succès, -1 si erreur.
 */
int _rmdir(const char* path) {
	int r = rmdir(path);

	if (r == -1) {
		logger(LOG_ERROR, stderr, "rmdir failed\n");
		exit(EXIT_FAILURE);
	}

	return r;
}

/**
 * @brief      Wrapper de la fonction unlink. Supprime un fichier.
 *
 * @param[in]  path  Le chemin du fichier.
 *
 * @return     0 si succès, -1 si erreur.
 */
int _unlink(const char* path) {
	int u = unlink(path);

	if (u == -1) {
		logger(LOG_ERROR, stderr, "unlink failed\n");
		exit(EXIT_FAILURE);
	}

	return u;
}
