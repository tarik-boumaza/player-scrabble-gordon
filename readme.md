# Projet Scrabble

## Introduction

Le but de ce projet est la programmation d'un joueur automatique au scrabble,
qui déterminera le coup rapportant le plus de points étant donné un plateau de
jeu, l'ensemble des lettres du joueur, et un dictionnaire. Vous pourrez
retrouver les règles du jeu et des tutoriels [facilement sur le
web](https://duckduckgo.com/?q=scrabble+how+to+play&t=h_&ia=web).

Ce projet s'appuie sur la structure de
[GADDAG](https://en.wikipedia.org/wiki/GADDAG) qui permet de déterminer
efficacement étant donné un point de départ sur le plateau les mots qui peuvent
être ajoutés en passant par ce point. Votre rôle consistera à implémenter une
version simplifiée de cette structure, puis de la mettre en œuvre pour chercher
le meilleur coup.

![solver](data/solver.gif)

## Dépôt de base

Ce dépôt constitue une base pour votre projet. Vous y trouverez le nécessaire
pour créer un plateau de jeu vierge, en charger un depuis un fichier, le remplir
et l'afficher. **Vous n'êtes pas obligés d'utiliser ce dépôt**. Libre à vous de
vous créer votre propre code de zéro si vous le préférez, ou de modifier le code
fourni autant que vous le souhaitez pour correspondre à vos besoins. L'important
reste néanmoins que vous rendiez un travail qui soit compilable et lisible par
votre encadrant.

La compilation de ce dépôt se fait à l'aide de `premake`, qui vous permet de
générer à la fois un Makefile, ou un projet codeblocks. Premake est déjà
installé sur les machines en salles de TP, et des paquets sont disponibles pour
la plupart des distributions linux. Pour générer des projets codeblocks, la
version 4 est nécessaire [à télécharger
ici](https://premake.github.io/download.html#v4) si elle n'est pas disponible
sur votre système. Il est normalement également possible de générer des projets
Visual Studio et Xcode.

La configuration de Premake est réalisée dans le fichier `premake4.lua`. Vous y
trouverez en commentaire comment ajouter de nouveaux fichiers à votre projet, et
comment compiler de multiples exécutables.

#### Générer un Makefile (premake 4 ou 5)
```
premake4 gmake
```

Une fois le `Makefile` créé, utilisez make comme d'habitude pour lancer la
compilation.

#### Générer un projet Codeblocks (premake 4 uniquement)
```
premake4 codeblocks
```

Une fois le projet généré, ouvrez le fichier `.workspace` dans Codeblocks, et
vous pourrez travailler.

## Gestion du joueur

Votre première tâche consiste à mettre en place le nécessaire pour qu'un joueur
puisse jouer. Vous devez pour celà créer des structures de données pour
matérialiser le sac des lettres et les lettre possédées par les joueurs. Vous
fournirez aussi également des fonctions pour obtenir rapidement le nombre de
points correspondant à une lettre.

En français, le sac de lettres contient initialement les lettres avec les points
suivants :

|      | A | B | C | D | E | F | G | H | I | J | K | L | M |
|------|---|---|---|---|---|---|---|---|---|---|---|---|---|
|Nombre| 9 | 2 | 2 | 3 | 15| 2 | 2 | 2 | 8 | 1 | 1 | 5 | 3 |
|Points| 1 | 3 | 3 | 2 | 1 | 4 | 2 | 4 | 1 | 8 | 10| 1 | 2 |

|      | N | O | P | Q | R | S | T | U | V | W | X | Y | Z |
|------|---|---|---|---|---|---|---|---|---|---|---|---|---|
|Nombre| 6 | 6 | 2 | 3 | 6 | 6 | 6 | 6 | 2 | 1 | 1 | 1 | 1 |
|Points| 1 | 1 | 3 | 2 | 1 | 1 | 1 | 1 | 4 | 10| 10| 10| 10|

#### Sac de lettres

Créez une structure de données matérialisant le sac de lettres. Cette structures
sera initialisée avec les lettres dans les quantités données ci-dessus. Cette
structure devra permettre de pouvoir facilement piocher une lettre au hasard
parmis les lettres restantes, c'est à dire que chaque lettre a une probabilité
de tirage proportionnelle au nombre d'exemplaires restant dans le sac. 

En terme de complexité, une structure bien réalisée devra permettre de piocher
une lettre en temps constant.

#### Lettres du joueur

Créez une structure de données pour matérialiser les lettre d'un joueur. Sauf
quand il n'y en a plus dans le sac pur recharger, un joueur a toujours 7 lettres
à sa disposition. Votre structure devra être adaptées à l'exploration que vous
ferez par la suite des mots qui sont jouable sur un plateau. Prévoyez également
de pouvoir recharcger les lettres d'un joueur depuis le sac de lettres.

#### Points des lettres

Fournissez une fonction qui étant donné une lettre fournit le nombre de points
associés.
