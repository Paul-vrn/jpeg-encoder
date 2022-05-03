# team18

Membres : Paul Vernin, Axel Perrin, Marc Felix-Henry

[https://formationc.pages.ensimag.fr/projet/jpeg/jpeg/](https://formationc.pages.ensimag.fr/projet/jpeg/jpeg/).

# Expression fonctionnelle du besoin

## Lecture paramètre (stdin)

Prérequis : -

Entrée : `argv`

Sortie : `void`

Description : La fonction va réaliser les actions données en paramètre et remplir des variables globales (si besoin).

## Lecture du fichier

Prérequis : Lecture paramètre

Entrée : `void` (variable global contenant nom du fichier ppm)

Sortie : `uint8_t[]` (tableaux contenant les pixels (data))

Description : La fonction lit le fichier ppm/pgm et va changer des variables globales en fonction de l'entête de l'image,  puis  il va lire la partie "data" et la mettre  dans un  tableau qu'il va retourner.

## Conversion RGB vers YCbCr

Prérequis : Lecture du fichier

Entrée : `*uint8_t[]`

Sortie : `void`

Description : Change  tous les pixels de RGB vers YCbCr

## Découpage de l'image en MCUs

Prérequis : Conversion RGB vers YCbCr

Entrée : `uint8_t[]`

Sortie : (liste chainée de matrice (une matrice correspond à un MCU))

Description : En fonction du fichier (PPM/PGM) découper les pixels en MCUs, en fonction de l'échantillonage le MCU contient 1, 2 ou 4 bloc (Y, Cr, Cb).
```
struct MCU {
    Y0 -> Y1 -> Y2
    Cr0 -> Cr1...
    Cb0...
}
```

## Sous-échantillonnage de l'image

Prérequis : Découpage de l'image en MCUs

Entrée : `*MCU[]`

Sortie : `void`

Description : Dans chaque MCU, en  fonction  de l'échantillonage,  on va fusionner les Cb0, Cb1,... en un  unique Cb0 (pareil pour Cr). On fera  des free des anciens blocs pour pas gaspiller de la mémoire.

## Transformation DCT

Prérequis : ...

Entrée : `*MCU[]`

Sortie : `void`

Description : Fait la DCT sur les MCUs un à un.

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
