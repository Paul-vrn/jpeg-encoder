# team18

Membres : Paul Vernin, Axel Perrin, Marc Henry-Félix

[https://formationc.pages.ensimag.fr/projet/jpeg/jpeg/](https://formationc.pages.ensimag.fr/projet/jpeg/jpeg/).

# Expression fonctionnelle du besoin

## Lecture du fichier

Prérequis : - 

Entrée : `argv`

Sortie : `uint8_t[]` (tableaux contenant les pixels (data))

Description : Fonction qui récupérer les paramètres lus en stdin puis s'occupe de récuperer les informations du header de l'image et du data

## Conversion RGB vers YCbCr

Prérequis : Lecture du fichier

Entrée : `uint8_t[]`

Sortie : `uint8_t[]`

## Découpage de l'image en MCUs

Prérequis : Conversion RGB vers YCbCr

Entrée : `uint8_t[]`

Sortie : (liste chainée de matrice (une matrice correspond à un MCU))

## Sous-échantillonnage de l'image

Prérequis : Découpage de l'image en MCUs

Entrée :

Sortie :

## Transformation DCT

Prérequis : ...

Entrée : liste de MCU (uint8_t)

Sortie : liste de MCU (int8_t)

## Quantification et zig-zag

Prérequis : Transformation DCT

# Structures de données choisies

img

# Gantt

img

# Progression

- [ ] invader.pgm
- [ ] gris.pgm
- [ ] bisou.pgm
- [ ] complexite.pgm
- [ ] zig-zag.ppm
- [ ] thumbs.ppm
- [ ] horizontal.ppm
- [ ] vertical.ppm
- [ ] shaun_the_sheep.ppm
- [ ] biiiiiig.ppm
