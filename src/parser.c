#include "parser.h"
#include "argument.h"
#include "list_arg.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

//http://stackoverflow.com/questions/2723888/where-does-getopt-long-store-an-unrecognized-option

#define EQUAL 0
#define LESS -1
#define GREATER 1
#define NOT 2

#define CREATION 0
#define MODIFICATION 1
#define UTILISATION 2

#define NAME_EXACT 0
#define NAME_CONTAINS 1

/* Flag set by ‘--verbose’. */
static int verbose_flag;

int parse_arg(int argc, char** argv) {
	int c;

	int arg_length;
	char arg_flag;
	unsigned long int size;
	int arg_modificator;
   argument_t* arg;

	list_t* arg_list = larg_new_list();

	while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          {"brief",   no_argument,       &verbose_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"and",     no_argument,       0, 'a'},
          {"or",  no_argument,       0, 'b'},
			 {"not",  no_argument,       0, 'c'},
          {"name",  required_argument, 0, 'd'},
          {"name_contain",  required_argument, 0, 'e'},
          {"size",    required_argument, 0, 'f'},
			 {"date",    required_argument, 0, 'g'},
			 {"owner",    required_argument, 0, 'h'},
			 {"perm",    required_argument, 0, 'i'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long_only (argc, argv, "abcd:e:f:g:h:i:", long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'a':
			 arg = malloc(sizeof(argument_t));
			 arg->type = and_op_arg;
			 arg_list = larg_insert_tail(arg_list, arg);
          printf ("(Parser) Logical operator found : -and\n");			 
          break;

        case 'b':
			 arg = malloc(sizeof(argument_t));
			 arg->type = or_op_arg;
			 arg_list = larg_insert_tail(arg_list, arg);
          printf ("(Parser) Logical operator found : -or\n");
          break;

        case 'c':			 
			 arg = malloc(sizeof(argument_t));
			 arg->type = not_op_arg;
			 arg_list = larg_insert_tail(arg_list, arg);
          printf ("(Parser) Logical operator : -not\n");
          break;

 		 case 'd':
			 arg = malloc(sizeof(argument_t));
			 arg->type = name_exact_arg;
			 sprintf(arg->string,"%s",optarg);
			 arg_list = larg_insert_tail(arg_list, arg);
          printf("(Parser) Option found : -name with value `%s'\n", optarg);	
				 
          break;
        case 'e':
			 arg = malloc(sizeof(argument_t));
			 arg->type = name_contain_arg;
			 sprintf(arg->string,"%s",optarg);
			 arg_list = larg_insert_tail(arg_list, arg);
          printf("(Parser) Option found : -name_contain with value `%s'\n", optarg);
				//optarg, 			 
          break;
        case 'f':

			 arg = malloc(sizeof(argument_t));
			 arg->type = size_arg;			
          printf ("(Parser) Option found : -size with value `%s'\n", optarg);
			 arg_length=strlen(optarg); 			

			 arg_flag=optarg[0]; // First char, modificator
			 switch(arg_flag) {
				case '+':
					 arg->oper = more_op;
					printf("(Parser) Option -size : modificator more found\n");
				break;
				case '-':
					arg->oper = less_op;
					printf("(Parser) Option -size : modificator less foud\n");				
				break;
				default:
					arg->oper = none_op;
					printf("(Parser) Option -size : modificator equal found\n");
				break;
          }

			size = abs(atoi(optarg)); //Valeur absolue, pour eviter les erreurs lors de l'utilisation du modificateur -					

			 arg_flag = optarg[arg_length-1]; // Last char, unit
			 switch(arg_flag) {
			 	case 'b':
					printf("(Parser) Option -size : unit byte found\n");
				break;
				case 'k':
					size*=1000; //10⁶
					printf("(Parser) Option -size : unit kilobyte found\n");
				break;
				case 'm':
					size*=1000000; // 10⁶
				 	printf("(Parser) Option -size : unit megabyte found\n");
				break;
				case 'g':
					size*=1000000000; //10⁹
				 	printf("(Parser) Option -size : unit gigabyte found\n");
				break;
				default:
				 printf("(Parser) Option -size : no unit found, assuming byte\n");
				break;	
          }

			printf("(Parser) Option -size : size in byte = %lu\n", size);


			sprintf(arg->string, "%lu", size);
			 
			 arg_list = larg_insert_tail(arg_list, arg);

			
          break;
		 case 'g':
         printf ("(Parser) Option found : -date with value `%s'\n", optarg);
			 arg_length=strlen(optarg); 			

			 arg_flag=optarg[0]; // First char, modificator
			 switch(arg_flag) {
				case '+':
					arg_modificator=GREATER;
				   optarg[0]=' ';
					printf("(Parser) Option -date : modificator more found\n");
				break;
				case '-':
					arg_modificator=LESS;
					optarg[0]=' ';
					printf("(Parser) Option -date : modificator less foud\n");				
				break;
				default:
					arg_modificator=EQUAL;
					printf("(Parser) Option -date : modificator equal found\n");
				break;
          }


			arg_flag = optarg[arg_length-1]; // Last char, unit
			 switch(arg_flag) {
			 	case 'c':
					optarg[arg_length-1]=' ';
					printf("(Parser) Option -date : flag creation found\n");
				break;
				case 'm':			
					optarg[arg_length-1]=' ';		
					printf("(Parser) Option -date : flag modification found\n");
				break;
				case 'u':		
					optarg[arg_length-1]=' ';			
				 	printf("(Parser) Option -date : flag utilisation found\n");
				break;				
				default:
				 printf("(Parser) Option -date : no flag found, assuming creation\n");
				break;	

				 }
				printf("(Parser) Option -date : date = %s\n",optarg);
          break;
		case 'h':
          printf ("(Parser) option found :-owner with value `%s'\n", optarg);
			arg_length=strlen(optarg); 			

			 arg_flag=optarg[0]; // First char, modificator
			 switch(arg_flag) {
				case '!':
					arg_modificator=GREATER;
				   optarg[0]=' ';
					printf("(Parser) Option -owner : modificator not found\n");
				break;
				default:
					arg_modificator=EQUAL;
					printf("(Parser) Option -owner : modificator equal found\n");
				break;
          }

			arg_flag = optarg[arg_length-1]; // Last char, unit
			 switch(arg_flag) {
			 	case 'u':
					optarg[arg_length-1]=' ';
					printf("(Parser) Option -owner : flag user found\n");
				break;
				case 'g':			
					optarg[arg_length-1]=' ';		
					printf("(Parser) Option -owner : flag group found\n");
				break;		
				default:
				 	printf("(Parser) Option -owner : no flag found, assuming user\n");
				break;	

				 }


          break;
		case 'i':
          printf ("option -perm with value `%s'\n", optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

	//APPELER SUITE ICI

	list_t* next = arg_list;
	while(next != NULL) {
		argument_t* val = next->value;
		printf("(Parser)Type=%d|Op=%d|Flag=%d|String=%s\n",val->type,val->oper,val->flag,val->string);
		next = next->next;
 }


	
 /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
   if (verbose_flag)
    puts ("verbose flag is set");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("(Parser) Unknown argument found : ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    } 
	
	return 1;
}
