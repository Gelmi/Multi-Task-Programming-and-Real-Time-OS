# Multi-Task Programming and Real-Time OS

To compile all tasks, run
```bash
cd build
make all
```

# TD1
## 1a) Gestion simplifiée du temps Posix - DONE
## 1b) Classe Chrono - DONE

# TD2
## 2a) Timers avec callback - DONE
## 2b) Classe Timer - DONE

Les methodes publiques sont lesquelles que seront utilisées dehors la classe.
Le seule methode privé c'est "call_callback()", parce qu'il doit etre appellé que dedans la classe.
Et le methode virtuel pure "callback()" est protegé parce qu'il sera accedé par les classe especialisé de Timer.

## 2c) Fonction simple consommant du CPU - DONE

Le seule methode qui peut être déclarée const c'est getSample() parce que elle ne change pas aucun donnée de la classe.
La courbe des valeurs de temps d'exécution est dans le dossie build et s'appelle "td2c.png" (Execution sur processeur x86).

## 2d) Échantillonage du temps d'exécution d'une fonction - DONE

## 2e) Classe consommatrice de CPU durant un temps donné - DONE

# TD3
## 3a) Création et utilisation de tâches et de mutex Posix - DONE

1) Valeur du compteur au tour de 10^9
2) Le valeur du compteur avec 3 taches sans mutex est au tour de 10^9 mais avec beaucoup de variabilité
3) Le valeur du compteur avec 3 taches et mutex est au tour de 10^9 mais plus important que celui d'avant et plus stable.

## 3b) Classe Mutex - DONE

## 3c) Classe Thread - DONE

## 3d) Accès concurrent à des données partagées - DONE


