/**
 * @file filter.c
 * @brief      Module Filter, décide si un fichier correspond aux critères
 *             demandés ou non.
 * @author     Steven Liatti
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "filter.h"

void log_stat(char* path, struct stat* buf) {
	logger(LOG_DEBUG, stderr, "Information for %s\n", path);
	logger(LOG_DEBUG, stderr, "---------------------------\n");
	logger(LOG_DEBUG, stderr, "File Size: \t\t%d bytes\n",buf->st_size);
	logger(LOG_DEBUG, stderr, "Number of Links: \t%d\n",buf->st_nlink);
	logger(LOG_DEBUG, stderr, "File inode: \t\t%d\n",buf->st_ino);

	logger(LOG_DEBUG, stderr, "File Permissions: \t");
	logger(LOG_DEBUG, stderr, (S_ISDIR(buf->st_mode)) ? "d" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IRUSR) ? "r" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IWUSR) ? "w" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IXUSR) ? "x" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IRGRP) ? "r" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IWGRP) ? "w" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IXGRP) ? "x" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IROTH) ? "r" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IWOTH) ? "w" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IXOTH) ? "x" : "-");
	logger(LOG_DEBUG, stderr, "\n\n");

	logger(LOG_DEBUG, stderr, "The file %s a symbolic link\n", (S_ISLNK(buf->st_mode)) ? "is" : "is not");

	logger(LOG_DEBUG, stderr, "Access time %d\n\n", buf->st_atime);
}

/**
 * @brief      Test si le nom du fichier courant correspond exactement ou
 *             partiellement au nom de recherche.
 *
 * @param      path      Le fichier à évaluer.
 * @param      argument  Le critère à évaluer.
 *
 * @return     Un boolean, vrai si le nom correspond, faux sinon.
 */
bool eval_name(char* path, argument_t* argument) {
	logger(LOG_DEBUG, stderr, "path, in eval_name : %s\n", path);
	char copy_path[255];
	strcpy(copy_path, path);
	logger(LOG_DEBUG, stderr, "copy_path : %s\n", copy_path);
	char* filename = strrchr(copy_path, '/'); // ici on récupère le nom du fichier avec le slash, ex : /test.txt
	strncpy(filename, filename + 1, strlen(filename) - 0); // ici on retire le slash de filename, ex : test.txt
	filename[strlen(filename)] = '\0'; // on met à NULL le dernier caractère de filename
	logger(LOG_DEBUG, stderr, "in eval_name, filename : %s\n", filename);
	logger(LOG_DEBUG, stderr, "argument->string : %s\n", argument->string);

	switch(argument->type) {
		case name_exact_arg:
			logger(LOG_DEBUG, stderr, "in switch, name_exact_arg\n");
			return strcmp(filename, argument->string) == 0;
		case name_contain_arg:
			logger(LOG_DEBUG, stderr, "in switch, name_contain_arg\n");
			return strcasestr(filename, argument->string) != NULL || strcasestr(argument->string, filename) != NULL;
		default:
			logger(LOG_DEBUG, stderr, "in switch, default\n");
			return false;
	}
}

/**
 * @brief      Test la taille du fichier courant selon les critères demandés
 *             pour la taille.
 *
 * @param      path      Le fichier à évaluer.
 * @param      argument  Le critère à évaluer.
 * @param      buf       Un pointeur sur une structure stat, pour récupérer les
 *                       infos du fichier à tester.
 *
 * @return     Un boolean, vrai si les critères sont remplis, faux sinon.
 */
bool eval_size(char* path, argument_t* argument, struct stat* buf) {
	logger(LOG_DEBUG, stderr, "path, in eval_size : %s\n", path);
	logger(LOG_DEBUG, stderr, "argument string, type, oper, flag : %s, %d, %d, %d\n", argument->string, argument->type, argument->oper, argument->flag);
	
	if(stat(path, buf) < 0)
		return false;

	long size_criterion = atol(argument->string);
	logger(LOG_DEBUG, stderr, "size_criterion = %ld\n", size_criterion);
	long size_path = (long) buf->st_size;
	logger(LOG_DEBUG, stderr, "size_path = %ld\n", size_path);

	switch(argument->oper) {
		case egal_op:
			logger(LOG_DEBUG, stderr, "in switch, egal_op\n");
			return size_path == size_criterion;
		case less_op:
			logger(LOG_DEBUG, stderr, "in switch, less_op\n");
			return size_path < size_criterion;
		case more_op:
			logger(LOG_DEBUG, stderr, "in switch, more_op\n");
			return size_path > size_criterion;	
		default:
			logger(LOG_DEBUG, stderr, "in switch, default\n");
			return false;
	}
}

/**
 * @brief      Convertit une date sous le format "yyyy-mm-jj" en timestamp
 *             (nombre de secondes après le 1er janvier 1970).
 *
 * @param      date  La date, sous le format "yyyy-mm-jj"
 *
 * @return     Le timestamp, en long.
 */
long date_to_timestamp(char* date) {
	char str[11]; // 10 + '\0'
	strcpy(str, date);
	const char s[] = "-";

	struct tm t;
	t.tm_year = atoi(strtok(str, s)) - 1900;
	t.tm_mon = atoi(strtok(NULL, s));
	t.tm_mday = atoi(strtok(NULL, s));
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;
	t.tm_isdst = -1;

	return mktime(&t);
}

/**
 * @brief      Test la date du fichier courant selon les critères demandés pour
 *             la date.
 *
 * @param      path      Le fichier à évaluer.
 * @param      argument  Le critère à évaluer.
 * @param      buf       Un pointeur sur une structure stat, pour récupérer les
 *                       infos du fichier à tester.
 *
 * @return     Un boolean, vrai si les critères sont remplis, faux sinon.
 */
bool eval_date(char* path, argument_t* argument, struct stat* buf) {
	logger(LOG_DEBUG, stderr, "path, in eval_date : %s\n", path);
	logger(LOG_DEBUG, stderr, "argument string, type, oper, flag : %s, %d, %d, %d\n", argument->string, argument->type, argument->oper, argument->flag);
	
	if(stat(path, buf) < 0)
		return false;
	
	long date_criterion = date_to_timestamp(argument->string);
	logger(LOG_DEBUG, stderr, "date_criterion   = %ld\n", date_criterion);
	long date_access_path = buf->st_atime;
	logger(LOG_DEBUG, stderr, "date_access_path = %ld\n", date_access_path);
	long date_modif_path  = buf->st_mtime;
	logger(LOG_DEBUG, stderr, "date_modif_path  = %ld\n", date_modif_path);
	long date_create_path = buf->st_ctime;
	logger(LOG_DEBUG, stderr, "date_create_path = %ld\n", date_create_path);

	switch(argument->oper) {
		case egal_op:
			logger(LOG_DEBUG, stderr, "in switch, egal_op\n");
			switch(argument->flag) {
				case date_create_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_create_flag\n");
					return date_create_path == date_criterion;
				case date_modif_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_modif_flag\n");
					return date_modif_path == date_criterion;
				case date_access_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_access_flag\n");
					return date_access_path == date_criterion;
				default:
					logger(LOG_DEBUG, stderr, "in switch, default\n");
					return false;
			}
		case less_op:
			logger(LOG_DEBUG, stderr, "in switch, less_op\n");
			switch(argument->flag) {
				case date_create_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_create_flag\n");
					return date_create_path < date_criterion;
				case date_modif_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_modif_flag\n");
					return date_modif_path < date_criterion;
				case date_access_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_access_flag\n");
					return date_access_path < date_criterion;
				default:
					logger(LOG_DEBUG, stderr, "in switch, default\n");
					return false;
			}
		case more_op:
			logger(LOG_DEBUG, stderr, "in switch, more_op\n");
			switch(argument->flag) {
				case date_create_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_create_flag\n");
					return date_create_path > date_criterion; 
				case date_modif_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_modif_flag\n");
					return date_modif_path > date_criterion;
				case date_access_flag:
					logger(LOG_DEBUG, stderr, "in switch, date_access_flag\n");
					return date_access_path > date_criterion;
				default:
					logger(LOG_DEBUG, stderr, "in switch, default\n");
					return false;
			}
		default:
			logger(LOG_DEBUG, stderr, "in switch, default\n");
			return false;
	}
}

/**
 * @brief      Test le propriétaire du fichier courant selon les critères
 *             demandés pour le propriétaire.
 *
 * @param      path      Le fichier à évaluer.
 * @param      argument  Le critère à évaluer.
 * @param      buf       Un pointeur sur une structure stat, pour récupérer les
 *                       infos du fichier à tester.
 *
 * @return     Un boolean, vrai si les critères sont remplis, faux sinon.
 */
bool eval_owner(char* path, argument_t* argument, struct stat* buf) {
	logger(LOG_DEBUG, stderr, "path, in eval_owner : %s\n", path);
	logger(LOG_DEBUG, stderr, "argument string, type, oper, flag : %s, %d, %d, %d\n", argument->string, argument->type, argument->oper, argument->flag);
	
	if(stat(path, buf) < 0)
		return false;
	
	int id_criterion = atoi(argument->string);
	logger(LOG_DEBUG, stderr, "id_criterion = %d\n", id_criterion);
	int uid_path = buf->st_uid;
	logger(LOG_DEBUG, stderr, "uid_path = %d\n", uid_path);
	int gid_path = buf->st_gid;
	logger(LOG_DEBUG, stderr, "gid_path = %d\n", gid_path);

	switch(argument->oper) {
		case egal_op:
			logger(LOG_DEBUG, stderr, "in switch, egal_op\n");
			switch(argument->flag) {
				case user_flag:
					logger(LOG_DEBUG, stderr, "in switch, user_flag\n");
					return id_criterion == uid_path;
				case group_flag:
					logger(LOG_DEBUG, stderr, "in switch, group_flag\n");
					return id_criterion == gid_path;
				default:
					logger(LOG_DEBUG, stderr, "in switch, default\n");
					return false;
			}
		case not_op:
			logger(LOG_DEBUG, stderr, "in switch, not_op\n");
			switch(argument->flag) {
				case user_flag:
					logger(LOG_DEBUG, stderr, "in switch, user_flag\n");
					return id_criterion != uid_path;
				case group_flag:
					logger(LOG_DEBUG, stderr, "in switch, group_flag\n");
					return id_criterion != gid_path;
				default:
					logger(LOG_DEBUG, stderr, "in switch, default\n");
					return false;
			}
		default:
			logger(LOG_DEBUG, stderr, "in switch, default\n");
			return false;
	}
}

/**
 * @brief      Test les droits d'accès du fichier courant selon les critères
 *             demandés ceux-ci.
 *
 * @param      path      Le fichier à évaluer.
 * @param      argument  Le critère à évaluer.
 * @param      buf       Un pointeur sur une structure stat, pour récupérer les
 *                       infos du fichier à tester.
 *
 * @return     Un boolean, vrai si les critères sont remplis, faux sinon.
 */
bool eval_perm(char* path, argument_t* argument, struct stat* buf) {
	bool perm = true;
	char perm_char[9];

	//On copie toutes les permissions du fichier dans un tableau de caractères.
	perm_char[0] = ((buf->st_mode & S_IRUSR) ? 'r' : '-');
	perm_char[1] = ((buf->st_mode & S_IWUSR) ? 'w' : '-');
	perm_char[2] = ((buf->st_mode & S_IXUSR) ? 'x' : '-');
	perm_char[3] = ((buf->st_mode & S_IRGRP) ? 'r' : '-');
	perm_char[4] = ((buf->st_mode & S_IWGRP) ? 'w' : '-');
	perm_char[5] = ((buf->st_mode & S_IXGRP) ? 'x' : '-');
	perm_char[6] = ((buf->st_mode & S_IROTH) ? 'r' : '-');
	perm_char[7] = ((buf->st_mode & S_IWOTH) ? 'w' : '-');
	perm_char[8] = ((buf->st_mode & S_IXOTH) ? 'x' : '-');

	//On compare chaque permission du fichier avec les permission données en paramètres.
	for (int i=0;i<9;i++) {
		if(argument->string[i] != perm_char[i]) {
			perm = false;
			break; //Plus besoin de controler les permissions suivantes
		}			
	}	

	logger(LOG_DEBUG, stderr,"(Filter) Verification des permissions : %d\n",perm) ;
	logger(LOG_DEBUG, stderr,"(Filter) Path=%s\n",path) ;
	
	return perm;
}

/**
 * @brief      Fonction d'évaluation principale. Elle prend en argument le
 *             fichier courant et la liste de tous les critères. Pour chaque
 *             critère, elle appelle la bonne sous-fonction d'évaluation. Stocke
 *             le sous-résultat dans une pile. Étant donné que les arguments
 *             sont attendus sous la notation polonaise inverse, si un opérateur
 *             arrive, le ou les éléments précédents sont dépilés et l'opérateur
 *             leur est appliqué. Si tout se passe bien, il ne reste plus qu'un
 *             élément dans la pile, qui indique si le fichier correspond aux
 *             critères de recherche ou non.
 *
 * @param      path       Le fichier à évaluer.
 * @param      arguments  Les critères à évaluer.
 * @param[in]  args_size  La taille des arguments.
 *
 * @return     Un boolean, vrai si les critères sont remplis, faux sinon.
 */
bool eval(char* path, argument_t* arguments, int args_size) {
	struct stat buf;
	if(stat(path, &buf) < 0)
		return false;

	list_t* stack = new_list();
	for (int i = 0; i < args_size; i++) {
		switch((&arguments[i])->type) {
			case name_exact_arg:
				stack = insert_head(stack, eval_name(path, &arguments[i]));
				break;
			case name_contain_arg:
				stack = insert_head(stack, eval_name(path, &arguments[i]));
				break;
			case size_arg:
				stack = insert_head(stack, eval_size(path, &arguments[i], &buf));
				break;
			case date_arg:
				stack = insert_head(stack, eval_date(path, &arguments[i], &buf));
				break;
			case owner_arg:
				stack = insert_head(stack, eval_owner(path, &arguments[i], &buf));
				break;
			case perm_arg:
				stack = insert_head(stack, eval_perm(path, &arguments[i], &buf));
				break;
			case and_op_arg:
			case or_op_arg:
				if (is_empty(stack)) {
					logger(LOG_ERROR, stderr, "La pile est vide, erreur dans les arguments\n");
					return false;
				}
				bool criterion_one;
				bool criterion_two;
				stack = remove_head_list_bool(stack, &criterion_two);
				if (is_empty(stack)) {
					logger(LOG_ERROR, stderr, "La pile est vide, erreur dans les arguments\n");
					return false;
				}
				stack = remove_head_list_bool(stack, &criterion_one);

				switch((&arguments[i])->type) {
					case and_op_arg:
						stack = insert_head(stack, criterion_one && criterion_two);
						break;
					case or_op_arg:
						stack = insert_head(stack, criterion_one || criterion_two);
						break;
					default:
						break;
				}
				break;
			case not_op_arg:
				if (is_empty(stack)) {
					logger(LOG_ERROR, stderr, "La pile est vide, erreur dans les arguments\n");
					return false;
				}
				stack->value = !(stack)->value;
				break;
			default:
				break;
		}
	}

	if (is_empty(stack) || count(stack) != 1) {
		logger(LOG_ERROR, stderr, "La pile est vide ou a plus que 1 élément, erreur dans les arguments\n");
		return false;
	}
	bool eval;
	stack = remove_head_list_bool(stack, &eval);
	free_all_list(stack);
	return eval;
}

/**
 * @brief      Fonction de filtre, décide si le fichier en argument doit être
 *             linké. Appelle la fonction eval, si eval == true alors le filtre
 *             appelle le linker et ajoute le fichier courante à la table de
 *             hash des fichiers ayant un lien. Sinon, elle retourne la table de
 *             hash inchangée.
 *
 * @param      path         Le fichier courant.
 * @param      folder_path  Le dossier de destination des liens créés, transmis
 *                          au Linker.
 * @param      arguments    La liste des arguments fournis en ligne de commande.
 * @param[in]  args_size    La taille des arguments.
 * @param      hash_table   La table de hash contenant les fichiers ayant un
 *                          lien.
 * @param      hash         La position dans la table, déjà calculée dans le
 *                          Crawler au moment de tester si le fichier y était
 *                          déjà contenu.
 *
 * @return     La table de hash contenant les fichiers ayant un lien.
 */
hash_table_t* filter(char* path, char* folder_path, argument_t* arguments, int args_size, hash_table_t* hash_table, int* hash) {
	logger(LOG_DEBUG, stderr, "In filter, path, hash : %s, %d\n", path, *hash);
	bool inserted;
	
	if (eval(path, arguments, args_size)) {
		logger(LOG_DEBUG, stderr, "+++++ fichier %s GARDÉ DANS LA TABLE +++++\n", path);
		// appeler le linker ici
		logger(LOG_DEBUG, stderr, "folder_path : %s\n", folder_path);
		linker(path, folder_path);
		return insert_with_hash(path, hash_table, &inserted, hash);
	}
	logger(LOG_DEBUG, stderr, "Fin de filter\n");
	return hash_table;
}
