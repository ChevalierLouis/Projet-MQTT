





  # Projet MQTT

Ce projet contient 3 programmes en C++ pour la communication en MQTT: 

- `pub.cpp`: programme pour publier un message sur un topic MQTT.
- `sub.cpp`: programme pour souscrire à un topic MQTT et afficher les messages reçus.
- `joke.cpp`: programme pour souscrire à un topic MQTT et répondre à certains messages avec une blague.

## Prérequis

- CMake version 3.5 ou supérieure.
- Bibliothèque [paho](https://github.com/eclipse/paho.mqtt.cpp). ou `sudo apt-get install libpaho-mqtt-dev`

## Installation

1. Cloner le projet à partir du repo Github: `git clone https://github.com/username/mqtt-project.git`
2. Naviguer vers le dossier du projet: `cd pub` ou `cd sub` ou `cd joke` 
3. Naviguer vers le dossier `build`: `cd build`
4. Générer les fichiers de configuration pour le projet avec CMake: `cmake ..`
5. Compiler le projet: `make`
6. Les exécutables générés (`pub`, `sub`, et `joke`) se trouvent dans les dossier `build`.

## Utilisation

Avant d'exécuter les programmes, assurez-vous que votre broker MQTT est en cours d'exécution et accessible depuis le réseau. Les programmes sont utilisables de la manière suivante:

### `pub`

- Syntaxe: `./pub`
- Le programme vous invite à saisir le message à publier.
- Une fois le message saisi, le programme le publie sur le topic `/ynov/bordeaux/`.
- Le programme continue jusqu'à ce que l'utilisateur l'arrête (en appuyant sur Ctrl-C).

### `sub`

- Syntaxe: `./sub`
- Le programme se connecte au broker MQTT et souscrit au topic `/ynov/bordeaux/`.
- Le programme affiche tous les messages reçus sur ce topic jusqu'à ce que l'utilisateur l'arrête (en appuyant sur Ctrl-C).

### `joke`

- Syntaxe: `./joke`
- Le programme se connecte au broker MQTT et souscrit au topic `/ynov/bordeaux/`.
- Le programme répond avec une blague à tout message reçu contenant le mot "qui".
- Le programme se termine après avoir répondu à un message.


## Auteur

[Louis CHEVALIER](https://github.com/ChevalierLouis)

