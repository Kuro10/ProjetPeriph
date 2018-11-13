#ifndef CAPTEUR_H
#define CAPTEUR_H

/* Permet d'initialiser le convertisseur A > D. */
void initADC(void);


/* Renvoie la valeur du voltage stock�e.
 * Une nouvelle mesure est effectu�e � chaque appel.
 * @return Valeur du voltage stock�e
 */
int getVoltage(void);





// TODO
// Calcule la distance au capteur (en fonction du voltage retourn�)
int getDistance(void);

#endif
