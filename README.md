# Zappy GUI - Raylib Setup & Submodule Guide

## 1. 📥 Installer Raylib localement (si vous ne l'avez pas déjà)

Clonez et installez raylib depuis le dépôt GitHub officiel :

```bash
git clone https://github.com/raysan5/raylib.git raylib
```
```bash
cd raylib
```
```bash
mkdir build && cd build
```
```bash
cmake -DBUILD_SHARED_LIBS=ON ..
```
```bash
make
```
```bash
sudo make install
```
```bash
sudo ldconfig && ldconfig -p | grep raylib
```

## 2. 🚀 Ajouter et pousser le sous-module raylib (uniquement pour la première fois)

À faire uniquement par la personne qui ajoute raylib en tant que sous-module au projet.

```bash
git submodule add https://github.com/raysan5/raylib.git raylib
```
```bash
git submodule update --init --recursive
```
```bash
git add .gitmodules raylib
```
```bash
git commit -m "Ajout de raylib comme sous-module"
```
```bash
git push
```

## 3. 🛠️ Récupérer raylib depuis le sous-module (pour tous les autres contributeurs)

À faire après avoir cloné le dépôt ou après un changement de branche.

```bash
git clone git@github.com:muscularbird/zappy_mirroring.git
```
```bash
cd zappy_mirroring
```
```bash
git submodule update --init --recursive
```
installez raylib:
```bash
cd raylib
```
```bash
mkdir build && cd build
```
```bash
cmake -DBUILD_SHARED_LIBS=ON ..
```
```bash
make
```
```bash
sudo make install
```
```bash
sudo ldconfig && ldconfig -p | grep raylib
```