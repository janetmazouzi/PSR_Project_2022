
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

# Les requêtes accessibles à l'utilisateur

Pour lancer le programme : 

>_VEUILLEZ RESPECTER L'ORDRE DES ARGUMENTS AINSI QUE LA SYNTAXE:_
- un temps : HHMM  exemple _`1230`_
- une date : M-J   exemple _`12-4`_
- un code IATA : AAA pour un aeroport, AA pour une compagnie aérienne
- une limite de donnée à afficher : limit=x exemple _`limit=3`_

Projet de Système et Réseau, Semestre 8
