# Architecture
Nous avons décidé de diviser notre programme selon les modules suivants :

## Lecture des paramètres
### Parser

## Moteur de recherche
### Crawler
Le Crawler est le module qui va s'occuper de lister tous les fichiers présents dans le dossier de recherche.
Nous pensons utiliser la lib `ftw.h` pour cela. Elle dispose de deux fonctions : 
`int ftw(const char *path, int (*fn)(const char *, const struct stat *ptr, int flag), int ndirs)` et 
`int nftw(const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd_limit, int flags)`.
La différence entre ces deux fonctions est que `nftw` prend un argument supplémentaire, un flag.
Ces fonctions parcourent la hiérarchie des fichiers à partir du dossier `path`. Pour chaque "objet" (dossier ou fichier), 
elles appellent la fonction `fn`, fonction que nous devrons implémenter. Cette fonction `fn` attend plusieurs paramètres :
un pointer sur le tableau de char constituant le nom de l'objet et un pointeur sur une structure de type `stat` 
(c'est ici que nous trouvons les infos sur l'objet).
Dans `fn` et `nftw` nous trouvons aussi un argument "flag", qui permet de changer plusieurs options de parcours 
ou de connaître le type de l'objet parcouru. Pour plus de détails :
[page de manuel ftw.h sur opengroup.org](http://pubs.opengroup.org/onlinepubs/9699919799/) et 
[celle de linux.die.net](https://linux.die.net/man/3/ftw)

### Filter

### Linker
Le rôle du Linker sera plus simple en comparaison des autres modules : il devra créer les liens symboliques 
(avec `int symlink (const char *oldname, const char *newname)`, `man 2 symlink`) des fichiers reçus du Filter 
et les stocker dans le search folder créé à cet effet.

### Daemon
Toute cette partie Moteur de recherche devra tourner en tâche de fond. Une fois que le Parser aura terminé son 
travail, il n'aura plus de raison de s'exécuter.

## Couche système 
### Logger

### Wrapper
Ce module sert de "lien" entre les appels systèmes et les fonctions du programme. En effet, plutôt que d'appeler 
directement les fonctions système, nous ferons appel aux fonctions du module qui elles-mêmes appeleront les fonctions 
système. Ainsi, le programme pourrait être porté sur un autre système (il n'y aurait que le Wrapper à adapter 
pratiquement) et il gagne en modularité et lisibilité.
