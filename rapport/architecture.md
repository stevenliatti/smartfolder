# Architecture
Nous avons décidé de diviser notre programme selon les modules suivants :


## Parser

## Crawler
Le Crawler est le module qui va s'occuper de lister tous les fichiers présents dans le dossier de recherche.
Nous pensons utiliser la lib `ftw.h` pour cela. Elle dispose de deux fonctions : 
`int ftw(const char *path, int (*fn)(const char *, const struct stat *ptr, int flag), int ndirs)` et 
`int nftw(const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd_limit, int flags)`.
La différence entre ces deux fonctions est que `nftw` prend un argument supplémentaire, un flag.
Ces fonctions parcourent la hiérarchie des fichiers à partir du dossier `path`. Pour chaque "objet" (dossier ou fichier), 
elles appellent la fonction `fn`, fonction que nous devrons implémenter. Cette fonction `fn` attend plusieurs paramètres :
un pointer sur le tableau de char constituant le nom de l'objet et un pointeur sur une structure de type `stat` 
(c'est ici que nous trouvons les infos sur l'objet).
Dans `fn` et `nftw` nous trouvons aussi des arguments "flag", qui permettent de changer plusieurs options de parcours 
ou de connaître le type de l'objet parcouru. Pour plus de détails : [page de manuel ftw.h sur opengroup.org](http://pubs.opengroup.org/onlinepubs/9699919799/)

## Filter

## Linker

## Logger

## Wrapper
