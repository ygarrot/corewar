# corewar

Le corewar est un jeu, un jeu très particulier.
Il consiste à opposer de petits programmes dans une machine virtuelle.

  •Le but du jeu est d’empêcher les autres programmes de fonctionner correctement, et ce par tous les moyens disponibles.

  •Le jeu va donc créer une machine virtuelle dans laquelle les programmes (écrits par les joueurs) s’afrontent. L’objectif de chaque programme est de "survivre".

  •Par"survivre" on entend exécuter une instruction spéciale (live) qui veut dire "je suisen vie".
Ces programmes s’exécutent simultanément dans la machine virtuelle et ce dans un même espace mémoire, et peuvent donc écrire les uns sur les autres.Le gagnant du jeu est le dernier a avoir exécuté l’instruction "live".

# Comment ça marche ?
Le projet va se découper en trois parties :

  •L’assembleur: Il va permettre d’écrire des programmes destinés à se battre. Il devra donc comprendre le langage assembleur et générer des programmes en binaire compréhensibles par la machine virtuelle.

  •La machine virtuelle: Elle va héberger les programmes binaires que sont les champions et leur fournir un environnement d’exécution standard. Elle offre tout un tas de fonctionnalités utiles aux combats des champions. Il va de soit qu’elle doit pouvoir exécuter plusieurs programmes à la fois (sinon, les combats ne vont pas être passionnants ...)

  •Le champion: C’est votre oeuvre personnelle. Il devra pouvoir se battre et sortir vainqueur de l’arène qu’est la machine virtuelle. Il sera donc écrit dansle langage assembleur propre à notre machine virtuelle .
  
![alt text](https://github.com/GentleOrea/corewar/blob/master/screenshot/exemple.png)
