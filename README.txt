********************************************************************************
********************************************************************************
  **                                                                        **
  **                           README ScrabbleTXT                           **
  **                                                                        **
********************************************************************************
********************************************************************************

******** DEVELOPPEURS *******

Hana SEBIA - p1716451
Tarik BOUMAZA - p1712760


********************************************************************************
********************************************************************************

/!\ TOUTES LES COMMANDES DE CE README SE LANCENT DEPUIS LA RACINE DU MODULE ( Ce répertoire ) /!\

/!\ Pour une documentation plus complète, veuillez consulter le fichier 'doc/html/index.html' /!\

________________________________________________________________________________


******** DESCRIPTION DE L'APPLICATION ********

    ScrabbleTXT est une simulation du jeu de scrabble réalisée dans le cadre de l’UE LIFAP6 au cours du printemps 2020.\n
    En utilisant la technique de Gordon, le joueur automatique cherche les coups jouables à partir d'un dictionnaire
  et des lettres piochées afin de jouer le coup le plus intelligent.\n
    Le code est écrit en C++.\n


________________________________________________________________________________


******** ARBORESCENCE GÉNÉRALE ******** :

	P1716451_P1712760/

		Makefile


		README.txt


		src/

      bag.cpp
      bag.hpp
      board.cpp
      board.hpp
      bonus.cpp
      bonus.hpp
      documentation.h
      gaddag.cpp
      gaddag.hpp
      game.cpp
      main.cpp
      node.cpp
      node.hpp
      player.cpp
      player.hpp
      scrabbleTXT.cpp
      scrabbleTXT.hpp
      spot.cpp
      spot.hpp


		obj/


		bin/


		data/

      dico.txt
      letters.txt
      logo.jpg
      points.txt


		doc/

      scrabbleTXT.doxy
      html/






________________________________________________________________________________


******** COMPILATION / MAKEFILE ********


	Compilation du projet :
		-> Commande "make" depuis ce répertoire courant génèrera les cibles suivantes :
			bin/scrabbleTXT


	Autres Cibles du Makefile :
	-> Commande "make clean" supprimera TOUS fichiers générés par la commande "make"
	-> Commande "make doc" générera la documentation du module.


________________________________________________________________________________

******** EXECUTION ********

	"./bin/scrabbleTXT" -> Execute MatriXMiX en version graphique


________________________________________________________________________________


******** DOCUMENTATION ********

	-> Afin de fournir de la documentation pour ce programme, nous utilisons l’outil Doxygen.
	Le fichier de configuration (doxyfile) se trouve dans le répertoire doc/scrabbleTXT.doxy
	La documentation est automatiquement générée grâce à la commande :

	"doxygen doc/scrabbleTXT.doxy" ( nécessite l'installation de Doxygen : 'apt-get doxygen')

	-> La documentation peut être générée aussi via une cible du Makefile : "make doc"

________________________________________________________________________________


********** NOTE AUX DEVELOPPEURS **********

Sous Linux, il faudra installer
- g++ (sudo apt install g++)
- doxygen (sudo apt install doxygen)
