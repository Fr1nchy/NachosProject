# NachosProject
System project - Team H

email for professors : cse-nachos@lists.forge.imag.fr
[NachOS/Team H] to precise in the mail object.


# Biblio
http://www.groupes.polymtl.ca/inf2610/documentation/notes/chap4.pdf : terminaison des threads - multithreading<br/>

# À chaque commit !
Pensez à donner un message détaillé <strong>EN PLUS DE CELUI DU COMMIT</strong> précisant ce qui a été implémenté, les bugs rencontrés, pourquoi ils ont été rencontrés et comment ils ont été résolus.
Dans le cas ou un fonctionnalité demandée n'a pas été implémentée OU a été implémentée différemment par rapport à ce qui était demandé, il faut justifier et préciser les limitations du choix conceptuel.
Chaque fonctionnalité doit être testée et ces trois questions doivent avoir des réponses :
-> Qu'est-ce qui était attendu ?
-> Qu'est-ce qui a été obtenu ?
-> Pourquoi cela a été obtenu ?
Les tests doivent rester disponibles afin de les expliciter dans le rapport.

Le respect de ces consignes facilitera <strong>grandement</strong> la rédaction du compte rendu et fera gagner du temps à tous (puisque le besoin de redemander les choix conceptuels et les tests ne serait plus nécessaire).

# Suivi de projet

<h2>Réunion de groupe n°1 : 18/12</h2>

  <h3>Etape 2 :</h3> Plus ou moins finie
  <p>Préciser pourquoi cette implémentation.<br/>
  Possibilité d'améliorer le programme d'après le prof ? (Partie 6)<br/>
  FONCTIONNEL</p>


  <h3>Rapport :</h3> 
  Intro<br/>
  Détailler chaque étape : <ul><li>contenu (entier) </li>
  <li>difficultés </li>
  <li>améliorations possibles </li>
  </ul>
  Gestion du temps : diagramme Gantt <br/>         

 <h3>Etape 3 :</h3> Commencée<br/>
  Problème de terminaison d'un thread.<br/><br/>

<h2>Réunion de groupe n°2 : 22/12</h2>
  <h3>Remarques de V.Danjean :</h3>
  <ul><li>
  Piles des threads à mettre en place rapidement.</li>
  <li>Terminaison implicite propre des threads à faire avec ThreadExit.</li>
  <li> Valeur des variables du noyau modifiables. Seule chose modifiable côté hardware : numPhysPages</li>
  </ul>
  
  <h3>Répartition des tâches pour vendredi + vacances</h3>
  <ul><li>Peio : Modifier rapport + tests des fonctions des parties 2 et 3 avec Thaqif. Notamment retester que les threads retournent bien la valeur attendue.</li>
  <li>Thaqif : Tests des fonctions des parties 2 et 3 avec Peio</li>
  <li>Cédric : Implémentation des piles des threads en utilisant le Bitmap et les tid.<br/> 
               Modification des fonctions comme UserThreadJoin() en conséquence.<br/>
               Avec Florian</li>
  <li>Hosseim : Début de l'étape 4 sur la pagination : familiarisation avec les partie I.2 et I.3 sur ReadAt</li>
  <li>Florian : Implémentation des piles des threads en utilisant le Bitmap et les tid.<br/> 
               Modification des fonctions comme UserThreadJoin() en conséquence.<br/>
               Avec Cédric</li>
  </ul>
  Tâche en plus pour tout le groupe : Avoir lu les étapes 3 et 4 (sur les threads et la pagination) et savoir comment ça marche (surtout pour les threads).


