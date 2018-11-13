#ifndef CAPTEUR_H
#define CAPTEUR_H

/* Permet d'initialiser le convertisseur A > D. */
void initADC(void);

/*
 * Renvoie la valeur du voltage stockée.
 * Une nouvelle mesure est effectuée à chaque appel.
 * @return Valeur du voltage stockée
 */
int getVoltage(void);

/*
 * Renvoie la distance au capteur
 * Elle est calculée en fonction du voltage retourné (expérimental !)
 * @return Valeur de la distance calculée
 */
int getDistance(void);

#endif
