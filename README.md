# ConnectedFlowers

## Sommaire :
- Objectif du projet
- Technologies utilisées
- Solutions apportée
- Axes d'amélioration pour la suite du projet


## Objectif du projet

Notre société souhaite développer une application permettant àn'importe quel débutant de commencer une culture de plante, sans aucune connaissance préalable. Pour cela, l'application détectera les différents paramètres nécéssaires à la bonne croissance de la plante et conseillera à l'utilisateur la bonne démarche à suivre (par exemple, l'utilisateur sera informé si il doit placer une plante dans un milieu plus humide)


## Technologies / Matériel utilisées

- Arduino uno rev 2
- Capteur de luminosité : Apds 9301 spark fun
- Capteur d'humidité : Dht 11
- Capteur de température : 

- Arduino / C++
- Serveur de données thinger.io 
- API de thinger.io
- python


## Solution apportée


- Afin de récupérer les informations de nos capteurs, on utilise un code arduino qui récupère les informations.
- Ensuite, ce code envoie les informations des capteurs sur un serveur de données Thinger.io .
- Ce serveur de données nous permet d'otenir régulièrement les nouvelles données des capteurs et stock cette information, qui devient accessible lorsque l'on se connecte aux bon réseau wifi.
- Enfin, un programme python récupère les données de ce serveur (grâce à l'API de celui-ci), et va pouvoir comparer ces valeurs avec celle d'une base de données de notre société (le fichier bdd_plante.csv sur git).
Le code s'occupe aussi de gérer notre interface utilisateur et permet de donner les conseils finaux à l'utilisateur.


## Axes d'amélioration

Le projet est en v1 est peu donc encore être grandement améliorer. Voici les quelques points que la société compte retravailler :

- Création d'une interface android / IOS 
- Réalisation d'un design de pot connecté
- Création d'un écosystème ConnectedFlowers
