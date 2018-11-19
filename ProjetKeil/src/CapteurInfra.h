#ifndef CAPTEUR_H
#define CAPTEUR_H

/* Permet d'initialiser le convertisseur A > D. */
void initADC(void);

/*
 * Renvoie la valeur du voltage stock�e.
 * Une nouvelle mesure est effectu�e � chaque appel.
 * @return Valeur du voltage stock�e
 */
int getVoltage(void);

/*
 * Renvoie la distance au capteur
 * Elle est calcul�e en fonction du voltage retourn� (exp�rimental !)
 * @return Valeur de la distance calcul�e
 *		ou DISTANCE_TROP_PRES si distance < 6 cm
 *		ou DISTANCE_TROP_LOIN si distance > 36 cm
 */
#define DISTANCE_TROP_PRES 0xFFFF
#define DISTANCE_TROP_LOIN 1000
int getDistance(void);

#endif
