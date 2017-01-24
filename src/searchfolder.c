/**
 * @file searchfolder.c
 * @brief      Main
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "wrapper.h"
#include "logger.h"
#include "crawler.h"
#include "filter.h"
#include "parser.h"

/**
 * @brief      Le temps écoulé entre 2 scans. (secondes)
 */
#define CRAWL_TIME 15

/**
 * @brief      Point d'entrée du programme.
 *
 * @param[in]  argc  Le nombre d'arguements.
 * @param      argv  Le tableau d'arguments.
 *
 * @return     Codes de sortie.
 */
int main(int argc, char** argv) {
	if (argc > 1) {
		char existing_folder[PATH_MAX];
		sprintf(existing_folder, "/tmp/%s.searchfolder", argv[2]);
		logger(LOG_DEBUG, stderr, "existing_folder (1) : %s\n", existing_folder);

		// Option de suppression
		if (strcmp(argv[1], "-d") == 0) {
			logger(LOG_DEBUG, stderr, "In delete mode\n");
			// Si le searchfolder n'existe pas
			if (_access(existing_folder, F_OK) != 0) {
				logger(LOG_ERROR, stderr, "This searchfolder do not exist !\n");
				return EXIT_FAILURE;
			}
			else {
				// supprimer processus, fichier dans tmp et dossier de recherche
				FILE* fp = fopen(existing_folder, "r");
				char content[PATH_MAX];
				fgets(content, PATH_MAX, fp);
				logger(LOG_DEBUG, stderr, "content (1) : %s\n", content);
				_kill(atoi(content), SIGTERM);
				fgets(content, PATH_MAX, fp);
				logger(LOG_DEBUG, stderr, "content (2) : %s\n", content);
				remove(content);
				remove(existing_folder);
				return EXIT_SUCCESS;
			}
		}
		// Mode normal
		else {
			logger(LOG_DEBUG, stderr, "In normal mode\n");
			sprintf(existing_folder, "/tmp/%s.searchfolder", argv[1]);
			logger(LOG_DEBUG, stderr, "existing_folder (3) : %s\n", existing_folder);

			// Si le dossier existe déjà, pas de création d'un nouveau avec même nom
			if (_access(existing_folder, F_OK) == 0) {
				logger(LOG_ERROR, stderr, "This searchfolder already exists !\n");
				return EXIT_FAILURE;
			}
			else {
				pid_t pid = _fork();

				// Dans l'enfant, on appelle le parser et le crawler normalement
				if (pid == 0) {
					logger(LOG_DEBUG, stderr, "In child processus\n");
					hash_table_t* files_to_link  = init(CAPACITY, LOAD_FACTOR);
					hash_table_t* paths_traveled = init(CAPACITY, LOAD_FACTOR);
					int args_size = 0;

					// Faut faire une copie profonde de argv
					char** new_argv = malloc((argc + 1) * sizeof(*new_argv));
					for(int i = 0; i < argc; i++) {
						size_t length = strlen(argv[i]) + 1;
						new_argv[i] = malloc(length);
						memcpy(new_argv[i], argv[i], length);
					}
					new_argv[argc] = NULL;

					argument_t* arguments = parse_arg(argc, new_argv, &args_size);
					int result = mkdir(argv[1], 0777);
					logger(LOG_DEBUG, stderr, "mkdir %s\n", result == 0 ? "success" : "fail");

					while (1) {
						crawler(argv[2], argv[1], paths_traveled, files_to_link, arguments, args_size);
						sleep(CRAWL_TIME);
					}

					/*
					// On pourrait se passer de tous les free finalement, car on y entre jamais.
					logger(LOG_DEBUG, stderr, "sizeof arguments : %d\n", sizeof(arguments));

					// IL FAUT FREE arguments !!!

					for(int i = 0; i < argc; i++)
						free(new_argv[i]);
					free(new_argv);
					free_table(files_to_link);
					free_table(paths_traveled);
					*/

					return EXIT_SUCCESS;
				}
				// Dans le parent, on crée un fichier qui contient les données concernant le folder
				else {
					logger(LOG_DEBUG, stderr, "In parent processus\n");
					FILE* fp;
					char path[PATH_MAX];
					logger(LOG_DEBUG, stderr, "existing_folder (3) : %s\n", existing_folder);
					sprintf(existing_folder, "/tmp/%s.searchfolder", argv[1]);
					logger(LOG_DEBUG, stderr, "file to be created : %s\n", existing_folder);
					fp = fopen(existing_folder, "w");
					fprintf(fp, "%d\n%s\n", pid, realpath(argv[1], path));
					fclose(fp);
					exit(EXIT_SUCCESS);
				}
			}
		}
	}
	else {
		logger(LOG_WARNING, stderr, "For launch a searchfolder :\nsearchfolder <dir_name> <search_path> [expression]\n");
		logger(LOG_WARNING, stderr, "For delete a searchfolder :\nsearchfolder -d <dir_name>\n");
		return EXIT_FAILURE;
	}
}
