#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

//http://stackoverflow.com/questions/2723888/where-does-getopt-long-store-an-unrecognized-option

/* Flag set by ‘--verbose’. */
static int verbose_flag;

int parse_arg(int argc, char** argv) {
	int c;

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

      c = getopt_long_only (argc, argv, "abc:d:f:", long_options, &option_index);

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
          puts ("option -a\n");
          break;

        case 'b':
          puts ("option -b\n");
          break;

        case 'c':
          printf ("option -name with value `%s'\n", optarg);
          break;

        case 'd':
          printf ("option -name_contain with value `%s'\n", optarg);
          break;

        case 'f':
          printf ("option -f with value `%s'\n", optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }


	bool name_exact_flag;
	
 /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
   if (verbose_flag)
    puts ("verbose flag is set");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    } 
	
	return 1;
}
