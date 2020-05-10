/** \mainpage ScrabbleTXT

\author
	Hana Sebia \n
	Tarik Boumaza \n

\version 1.0

\date 12 Mai 2020

\n
\section Introduction
		    ScrabbleTXT est une simulation du jeu de scrabble réalisée dans le cadre de l’UE LIFAP6 au cours du printemps 2020.\n
		    En utilisant la technique de Gordon, le joueur automatique cherche les coups jouables à partir d'un dictionnaire
        et des lettres piochées afin de jouer le coup le plus intelligent.\n
		    Le code est écrit en C++.\n \n

	<H3><B>ATTENTION</B></H3>Toutes les commandes doivent être exécutées depuis le répertoire courant de l'application !

\n
\section Compilation
		<B>Note</B> : La compilation est réalisable sous <B>LINUX</B>, à condition d'avoir installé <B>g++</B>\n \n

	Pour compiler le projet, éxecuter la commande pour génerer la cible <B>bin/scrabbleTXT</B> :

		$ make


  Pour supprimer les fichiers objets dans <B>obj/</B>, exécuter :

      $ make clean

  Pour supprimer l'éxecutable dans <B>bin/</B> ainsi que les fichiers objets dans <B>obj/</B>, exécuter :

  	   $ make veryclean

    Egalement, vous pouvez générer la documentation avec <B>Doxygen</B> :

     	 $ make doc


\n
\section Exécution

  Pour exécuter le projet normalement, exécuter :

		$ bin/scrabbleTXT

  Pour exécuter le projet en slow motion, exécuter :

    	$ bin/scrabbleTXT --sm

    Pour exécuter le projet avec un joueur intelligent, exécuter :

        $ bin/scrabbleTXT --ia


\n
\section Documentation
	Afin de fournir de la documentation de ce programme, nous avons utilisé l’outil <B>Doxygen</B>.\n
	Le fichier de configuration <B>Doxygen</B> se trouve dans le répertoire <B>doc/scra.doxy</B>\n
	La documentation est automatiquement générée grâce à la commande :

		$ doxygen doc/scrabbleTXT.doxy

	Ou bien comme mentionné plus haut :

		$ make doc

  Cette commande requiert l'installation de l'outil <B>doxygen</B> via la commande :

		$ sudo apt-get install doxygen

\n
    \section Remerciements
    Vincent Nivoliers
    \n Christophe Crespelle
    \n pas Suzette
*/
