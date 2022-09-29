
# FR
# Projet de création d'un proxy DNS étape par étape
>_Cours de Projet Système et réseau du semestre 8 à Polytech Lille. Encadré par [Thomas Vantroys](https://tvantroys.plil.fr/mediawiki/index.php/Accueil) et [Xavier Redon](https://rex.plil.fr/)_

Ce dépôt `GitLab` contient un  projet codé en`C` pour lequel la compilation, les tests... ont été automatisés.

Ce type de service logiciel est utilisé en cybersécurité aussi bien d'un point de vue défensif que offensif. En
mode défensif, il sera utilisé pour enregistrer toutes les demandes de résolution de noms réalisées par une cible et ainsi
étudier son comportement. Cela permet également de filtrer certaines requêtes. De manière offensive, un proxy DNS
permet de leurrer une machine pour la rediriger vers une autre destination.

## Principe Pedagogique 
  Ce projet a pour objectif de solidifier nos compétences en C, en réseaux et en systèmes acquises tout au long de la formation de systèmes embarqués.
  Voici les différents concepts utilisé dans ce projet:
- Programmation orientée réseau : creation, gestion et envoi de sockets, addressage,..
- Organisation d'un projet en dossiers et bibliotheques statiques et dynamiques
- Factorisation du code et encapsulation, permettant une indépendance entre les bibliothèques
- L'automatisation de la compilation : utilisation de Makefile recursifs
- Gestion d'arguments durant l'appel au programme 
- MultiThreading 
- Gestion de Log pour suivre les accès au Proxy
- Patron de conception "strategie" pour changer le comportement du programme sans recompiler
- Tests unitaires
- Redirection et modification de paquets reseau

## Contenu du dépôt

- `README.md` le fichier que vous être en train de lire
- `Makefile` permet la compilation du code de manière recursive
- `ProjetPSR_ConsigneFR.pdf` Le fichier avec la consigne initiale
- le répertoire `bin` pour stocker les fichiers binaires lors de la compilation
- le répertoire `libs` contient les repertoires de librairies : Log, Memoire, Redirection, Reseau, Threads et les repertoires static et dynamic pour stocker les fichiers objets des librairies. 
- le répertoire `src` contient  les fichiers sources principaux.

# Lancement de l'application
- compilation : _`make`_
- lancement de l'application : _`sudo ./bin/main <options>`_
- lancement de la fonctionnalité de modification des redirections : _`sudo ./bin/dnsproxy_mgr`_


>_ARGUMENTS DISPONIBLES POUR LE main.c:_
- _`-h`_ et _`--help`_ : affiche le message d'aide du programme qui explique toutes les options possibles
- _`-p PORT`_ et _`--port=PORT`_ : permet de modifier le port par défaut (53) utilisé par le programme pour recevoir les
questions DNS
- _`-s SERVEUR`_ et _`--serveur=SERVEUR`_ : permet de spécifier un serveur DNS particulier à la place du serveur DNS
par défaut
- _`-l STRATEGIE`_ et _`--logstrategy=STRATEGIE`_ : permet de choisir la stratégie à charger
- _`-i INIT_ARGS_STRATEGIE`_ et _`--initlogstrategie=INIT_ARGS_STRATEGIE`_ : permet de passer des paramètres
d'initialisation à la stratégie choisie
- `_-c CONFIG_FILE`_ et _`--configfile==CONFIG_FILE`_

>_ARGUMENTS DISPONIBLES POUR LE dnsproxy_mgr.c:_
- _`-h`_ et _`--help`_ : affiche le message d'aide du programme qui explique toutes les options possibles
- _`-a NEWLINE`_ et _`--ajout=NEWLINE`_ : permet d'ajouter une ligne au fichier de configuration
- _`-s DOMAIN_NAME`_ et _`--suppression=DOMAIN_NAME`_ : spécifier le nom de domaine à supprimer des spécifications
- _`-m LINE`_ et _`--modification=LINE`_ : permet de spécifier le domaine à modifier. Le format à respecter est le suivant : domain_name=ipv4,ipv6,MX\n. Mettre le champ à 0 si vous ne voulez pas le modifier

Projet de Système et Réseau, Semestre 8
