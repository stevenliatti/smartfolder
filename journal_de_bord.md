# Journal de bord

## Find
- Nom
- Taille
- Date
- Propriétaire
- Droits d'accès
- Boolean

## Parser
Analyse les arguments en entrée du programme

## Parcours
Tous les sous-dossiers et fichiers
  * Si fichier -> appel de `find`
  * Si dossier -> rappelle récursif

## Create_link
Test si doublon

## HashTable - 09.01.17
On devrait changer un poil l'architecture : lorsque le Crawler parcoure les fichiers, 
il check pour chaque fichier s'il est présent dans la table de hash. Si oui, pas besoin 
de le refiler au Filter puis Linker. Si non, on fait l'étape "traditionnelle" : 
Crawler -> Filter -> Linker. Comme ça on économise le "détour" par le Filter.
