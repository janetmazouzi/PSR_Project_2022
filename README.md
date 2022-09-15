
# FR
# Projet de création d'un proxy DNS étape par étape
>_Cours de Projet Système et réseau du semestre 8 à Polytech Lille. Encadré par [Thomas Vantroys](https://tvantroys.plil.fr/mediawiki/index.php/Accueil) et [Xavier Redon](https://rex.plil.fr/)_

Ce dépôt `GitLab` contient un  projet codé en`C` pour lequel la compilation, les tests... ont été automatisés.

Ce type de service logiciel est utilisé en cybersécurité aussi bien d'un point de vue défensif que offensif. En
mode défensif, il sera utilisé pour enregistrer toutes les demandes de résolution de noms réalisées par une cible et ainsi
étudier son comportement. Cela permet également de filtrer certaines requêtes. De manière offensive, un proxy DNS
permet de leurrer une machine pour la rediriger vers une autre destination.

## Contenu du dépôt

- `README.md` le fichier que vous être en train de lire
- `Makefile` permet la compilation du code de manière recursive
- `ProjetPSR_ConsigneFR.pdf` Le fichier avec la consigne initiale
- le répertoire `includes` contient les déclarations de fonctions
- le répertoire `src` contient les sources du projet
- le répertoire `data` contient  les fichiers `cvs` à analyser

# Les requêtes accessibles à l'utilisateur

- `show-airports <airline_id>`  : affiche tous les aéroports depuis lesquels la compagnie aérienne `<airline_id>` opère des vols
- `show-airlines <port_id>`: affiche les compagnies aériens qui ont des vols qui partent de l'aéroport `<port_id>`
- `show-flights <port_id> <date> [<time>] [limit=<xx>]` : affiche les vols qui partent de l'aéroport à la date, avec optionnellement une heure de début, et limité à xx vols
- `most-delayed-flights`     : donne les 5 vols qui ont subis les plus longs retards à l'arrivée
- `most-delayed-airlines`    : donne les 5 compagnies aériennes qui ont, en moyenne, le plus de retards
- `delayed-airline <airline_id>`    : donne le retard moyen de la compagnie aérienne passée en paramètre
- `most-delayed-airlines-at-airport <airport_id>`    : donne les 3 compagnies aériennes avec le plus de retard d'arrivé à l'aéroport passée en paramètre
- `changed-flights <date>` : les vols annulés ou déviés à la date <date> (format M-D)
- `avg-flight-duration <port_id> <port_id>`: calcule le temps de vol moyen entre deux aéroports
- `find-itinerary <port_id> <port_id> <date> [<time>] [limit=<xx>]`: trouve un ou plusieurs itinéraires entre deux aéroports à une date donnée (l'heure est optionnel, requête peut être limité à `xx` propositions, il peut y avoir des escales)
- `find-multicity-itinerary <port_id_depart> <port_id_dest1> <date> [<time>] <port_id_dest2> <date> [<time>] ... <port_id_destN> <date> [<time>]`: trouve un itinéraire multiville qui permet de visiter plusieurs villes (il peut y avoir des escales pour chaque vol intermediaire)
- `quit`       : quitter l'application

>_VEUILLEZ RESPECTER L'ORDRE DES ARGUMENTS AINSI QUE LA SYNTAXE:_
- un temps : HHMM  exemple _`1230`_
- une date : M-J   exemple _`12-4`_
- un code IATA : AAA pour un aeroport, AA pour une compagnie aérienne
- une limite de donnée à afficher : limit=x exemple _`limit=3`_

Projet de Système et Réseau, Semestre 8
