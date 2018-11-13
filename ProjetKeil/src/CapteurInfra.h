#ifndef CAPTEUR_H
#define CAPTEUR_H

/* Permet d'initialiser le convertisseur A > D. */
void initADC(void);


/* Renvoie la valeur du voltage stockée.
 * Une nouvelle mesure est effectuée à chaque appel.
 * @return Valeur du voltage stockée
 */
int getVoltage(void);





// TODO
// Calcule la distance au capteur (en fonction du voltage retourné)
int getDistance(void);

#endif
