/**
 * @file parser.c
 * @brief      Module du parser, lis les arguments et les prépare pour la suite.
 *             du traitement
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "parser.h"

/**
 * @brief      Test si une chaine de caractères correspond à l'expression
 *             régulière.
 *
 * @param      request  La chaine a tester.
 * @param      regex    L'expression régulière.
 *
 * @return     Si la chaine correspond à l'expression régulière.
 */
bool regex_match(char* request, char* regex) {
	regex_t preg;

	if (regcomp (&preg, regex, REG_NOSUB | REG_EXTENDED) == 0) {
		int match = regexec (&preg, request, 0, NULL, 0);
		regfree (&preg);
		if (match == 0) {
			return true; //Regex OK
		}
		else if (match == REG_NOMATCH) {
			return false; //Regex KO
		}
	}
	return false; //Erreur lors du test de l'expression régulière
}


/**
 * @brief      Lis et traite les arguments donnés en entrée
 *
 * @param      argc       Le nombre d'arguments
 * @param      argv       Les arguments
 * @param      args_size  La taille du tableau des arguments, pointeur qui sera
 *                        mis à jour.
 *
 * @return     Le tableau des arguments traités
 */
argument_t* parse_arg(int argc, char** argv, int* args_size) {
	int c;

	int arg_length;
	char arg_flag;
	unsigned long int size;
	argument_t* arg;

	argument_t* arguments_array; //Le tableau des arguments

	list_arg_t* arg_list = larg_new_list(); //La liste des arguments

	while (1) {
		static struct option long_options[] =
		{
			{"and", no_argument, 0, 'a'},
			{"or", no_argument, 0, 'b'},
			{"not", no_argument, 0, 'c'},
			{"name", required_argument, 0, 'd'},
			{"name_contain", required_argument, 0, 'e'},
			{"size", required_argument, 0, 'f'},
			{"date", required_argument, 0, 'g'},
			{"owner", required_argument, 0, 'h'},
			{"perm", required_argument, 0, 'i'}
		};

		// getopt_long stock l'option index ici
		int option_index = 0;

		c = getopt_long_only (argc, argv, "abcd:e:f:g:h:i:", long_options, &option_index); //Lis le prochain argument

		if (c == -1) {
			break; //Détecte la fin des options
		}

		switch (c) {
			case 'a': //--and
			arg = malloc(sizeof(argument_t));
			arg->type = and_op_arg;
			arg->oper = none_op;
			arg->flag = none_flag;
			arg->string[0]='\0';
			arg_list = larg_insert_tail(arg_list, arg);
			logger(LOG_DEBUG, stderr, "(Parser) Logical operator found : -and\n");
			break;

			case 'b': //--or
			arg = malloc(sizeof(argument_t));
			arg->type = or_op_arg;
			arg->oper = none_op;
			arg->flag = none_flag;
			arg->string[0]='\0';
			arg_list = larg_insert_tail(arg_list, arg);
			logger(LOG_DEBUG, stderr, "(Parser) Logical operator found : -or\n");
			break;

			case 'c': //--not
			arg = malloc(sizeof(argument_t));
			arg->type = not_op_arg;
			arg->oper = none_op;
			arg->flag = none_flag;
			arg->string[0]='\0';
			arg_list = larg_insert_tail(arg_list, arg);
			logger(LOG_DEBUG, stderr, "(Parser) Logical operator : -not\n");
			break;

			case 'd': //--name
			arg = malloc(sizeof(argument_t));
			arg->type = name_exact_arg;
			arg->oper = egal_op;
			arg->flag = none_flag;
			sprintf(arg->string,"%s",optarg);
			arg_list = larg_insert_tail(arg_list, arg);
			logger(LOG_DEBUG, stderr, "(Parser) Option found : -name with value `%s'\n", optarg);
			break;

			case 'e': //--name_contain
			arg = malloc(sizeof(argument_t));
			arg->type = name_contain_arg;
			arg->oper = egal_op;
			arg->flag = none_flag;
			sprintf(arg->string,"%s",optarg);
			arg_list = larg_insert_tail(arg_list, arg);
			logger(LOG_DEBUG, stderr, "(Parser) Option found : -name_contain with value `%s'\n", optarg);
			break;

			case 'f': //--size
			arg = malloc(sizeof(argument_t));
			arg->type = size_arg;
			arg->flag = none_flag;
			logger(LOG_DEBUG, stderr, "(Parser) Option found : -size with value `%s'\n", optarg);

			arg_flag=optarg[0]; // First char, modificator
			switch(arg_flag) {
				case '+': //More
				arg->oper = more_op;
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : modificator more found\n");
				break;
				case '-': //Less
				arg->oper = less_op;
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : modificator less foud\n");
				break;
				default: //Equal
				arg->oper = egal_op;
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : modificator equal found\n");
				break;
			}

			size = abs(atoi(optarg)); //Valeur absolue, pour eviter les erreurs lors de l'utilisation du modificateur -

			arg_flag = optarg[strlen(optarg)-1]; // Last char, unit
			switch(arg_flag) {
				case 'b':
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : unit byte found\n");
				break;
				case 'k':
				size*=1000; //10\u2076
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : unit kilobyte found\n");
				break;
				case 'm':
				size*=1000000; // 10\u2076
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : unit megabyte found\n");
				break;
				case 'g':
				size*=1000000000; //10\u2079
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : unit gigabyte found\n");
				break;
				default:
				logger(LOG_DEBUG, stderr, "(Parser) Option -size : no unit or unknow unit found, assuming byte\n");
				break;
			}

			logger(LOG_DEBUG, stderr, "(Parser) Option -size : size in byte = %lu\n", size);
			sprintf(arg->string, "%lu", size);
			arg_list = larg_insert_tail(arg_list, arg);
			break;

			case 'g': //--date
			logger(LOG_DEBUG, stderr, "(Parser) Option found : -date with value `%s'\n", optarg);

			arg = malloc(sizeof(argument_t));
			arg->type = date_arg;

			arg_flag=optarg[0]; // First char, modificator
			switch(arg_flag) {
				case '+': //More
				arg->oper = more_op;
				//optarg[0]=' ';				
    			memmove(optarg, optarg+1, strlen(optarg)); //On supprime le premier caractère en déplacant la chaine 
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : modificator more found\n");
				break;
				case '-': //Less
				arg->oper = less_op;
				//optarg[0]=' ';
				memmove(optarg, optarg+1, strlen(optarg));
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : modificator less foud\n");
				break;
				default: //Equal
				arg->oper = egal_op;
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : modificator equal found\n");
				break;
			}
			arg_flag = optarg
			[strlen(optarg)-1]; // Last char, unit
			switch(arg_flag) {
				case 'c':
				arg->flag = date_create_flag;
				optarg[strlen(optarg)-1]='\0';
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : flag creation found\n");
				break;
				case 'm':
				arg->flag = date_modif_flag;
				optarg[strlen(optarg)-1]='\0';
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : flag modification found\n");
				break;
				case 'u':
				arg->flag = date_access_flag;
				optarg[strlen(optarg)-1]='\0';
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : flag access found\n");
				break;
				default:
				arg->flag = date_access_flag;
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : no flag or unknown flag found, assuming access\n");
				break;
			}
			
			if(regex_match(optarg,"[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$")) {
				arg_list = larg_insert_tail(arg_list, arg);
				sprintf(arg->string,"%s",optarg);
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : date matching regex (%s)\n", optarg);
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : date = %s\n",optarg);
			} else {
				free(arg);
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : date not matching regex (%s)\n", optarg);
				logger(LOG_DEBUG, stderr, "(Parser) Option -date : Don't adding this option in arglist (%s)\n", optarg);
			}
		
			break;

			case 'h': //--Owner
			logger(LOG_DEBUG, stderr, "(Parser) option found :-owner with value `%s'\n", optarg);
			arg_length=strlen(optarg);

			arg = malloc(sizeof(argument_t));
			arg->type = owner_arg;      

			arg_flag=optarg[0]; // First char, modificator
			switch(arg_flag) {
				case '!':
				arg->oper = not_op;
				optarg[0]=' ';
				logger(LOG_DEBUG, stderr, "(Parser) Option -owner : modificator not found\n");
				break;
				default:
				arg->oper = egal_op;
				logger(LOG_DEBUG, stderr, "(Parser) Option -owner : modificator equal found\n");
				break;
			}

			arg_flag = optarg[arg_length-1]; // Last char, unit
			switch(arg_flag) {
				case 'u':
				optarg[arg_length-1]=' ';
				arg->flag = user_flag;
				logger(LOG_DEBUG, stderr, "(Parser) Option -owner : flag user found\n");
				break;
				case 'g':
				optarg[arg_length-1]=' ';
				arg->flag = group_flag;
				logger(LOG_DEBUG, stderr, "(Parser) Option -owner : flag group found\n");
				break;
				default:
				arg->flag = user_flag;
				logger(LOG_DEBUG, stderr, "(Parser) Option -owner : no flag or unknown flag found, assuming user\n");
				break;
			}
			size = atoi(optarg); //Owner is a number, to avoid error
			sprintf(arg->string,"%lu",size); 
			arg_list = larg_insert_tail(arg_list, arg);
			break;

			case 'i': //--perm

			if(regex_match(optarg,"[r|w|x|n|*]{9}")) {
				logger(LOG_DEBUG, stderr, "(Parser) Option -perm : perm matching regex (%s)\n", optarg);
				logger(LOG_DEBUG, stderr, "(Parser) Option -perm with value `%s'\n", optarg);
				arg = malloc(sizeof(argument_t));
			arg->type = perm_arg;
			arg->oper = egal_op;
			arg->flag = none_flag;
				sprintf(arg->string,"%s",optarg);
			arg_list = larg_insert_tail(arg_list, arg); //On ajoute dans la liste
			} else {
				logger(LOG_DEBUG, stderr, "(Parser) Option -perm : perm not matching regex (%s)\n", optarg);
				logger(LOG_DEBUG, stderr, "(Parser) Option -perm : Don't adding this option in arglist (%s)\n", optarg);
			}
			break;

			case '?':
			//getopt_long a déja affiché un message d'erreur
			break;

			default:
			logger(LOG_DEBUG, stderr, "(Parser) Error, abort");
			abort();
		}
	}

	arguments_array = malloc(larg_count(arg_list) * sizeof(argument_t));
	int i = 0;

	//Need vérification que la polonaise inverse soit correcte
	logger(LOG_DEBUG, stderr, "(Parser) Args after parsing\n");
	//Affichage du tableau d'arguments
	list_arg_t* next = arg_list;
	while(next != NULL) {
		arguments_array[i] = *next->value;
		i++;
		argument_t* val = next->value;
		logger(LOG_DEBUG, stderr, "(Parser)Type=%d|Op=%d|Flag=%d|String=%s\n",val->type,val->oper,val->flag,val->string);
		next = next->next;
	}

	larg_free_all_list(arg_list);

	*args_size = i;
	return arguments_array;
}
