#define OCTET unsigned char
#define OFF 0
#define ON 1
#define NIBBLE 0
#define NB_SERPENT 21
#define OBST_FOND 0
#define OBST_NIBBLE 1
#define OBST_NIBBLEX 2
#define OBST_MUR 3
#define LG_SERPENT_MAXI 50
#define LG_SERPENT_MINI 1
#define TAILLE_PLUS +1
#define TAILLE_MOINS -1
#define TAILLE_NULLE 0
#define CODE_SERPENT_FOND 255
void Activer_Taille_Plus (OCTET);
void Activer_Taille_Moins (OCTET);
void Desactiver_Taille (OCTET);
char Lire_Taille (OCTET);
OCTET Lire_Souplesse (OCTET);
void Activer_Souplesse (OCTET);
void Desactiver_Souplesse (OCTET);
OCTET Lire_Mortalite (OCTET);
void Activer_Mortalite (OCTET);
void Desactiver_Mortalite (OCTET);
OCTET Lire_Fluidite (OCTET);
void Activer_Fluidite (OCTET);
void Desactiver_Fluidite (OCTET);
OCTET Lire_Longueur (OCTET);
void Init_Vitesse (OCTET,OCTET);
OCTET Lire_Vitesse (OCTET);
void Init_Compteur_Vitesse (OCTET,OCTET);
OCTET Lire_Compteur_Vitesse (OCTET);
void Decrementer_Compteur_Vitesse (OCTET);
void Init_Compteur_Tempo_Direction (OCTET);
short Lire_Compteur_Tempo_Direction (OCTET);
void Decrementer_Compteur_Tempo_Direction (OCTET);
void Init_Tous_Serpents (void);
void Sauver_Donnees_Serpent (OCTET,OCTET);
void Sauver_Toutes_Donnees_Serpent (OCTET);
void Effacer_Serpent (OCTET,OCTET,OCTET,OCTET);
void Effacer_Tous_Serpents (OCTET);
void Avancer_Serpent (OCTET);
void Afficher_Serpent (OCTET,OCTET,OCTET);
void Afficher_Tous_Serpents (OCTET);
OCTET Tester_Coords_Tete_Queue (OCTET,OCTET);
OCTET Choisir_Direction_NibbleX (OCTET,OCTET);
OCTET Determiner_Obstacle (OCTET,OCTET);
OCTET Verifier_Impasse (OCTET,OCTET);
OCTET Lire_Obstacle_Tableau (OCTET,OCTET);
void Ecrire_Obstacle_Tableau (OCTET,OCTET,OCTET);
void Afficher_Obstacle_Tableau (OCTET,OCTET,OCTET);
OCTET Lire_Direction (OCTET);
OCTET Lire_Direction_Opposee (OCTET);
OCTET Lire_Direction_Tete (OCTET);
void Ecrire_Direction (OCTET,OCTET);
void Init_Code_Serpent (OCTET);
OCTET Lire_Obstacle_Serpent (OCTET,OCTET);
void Ecrire_Obstacle_Serpent (OCTET,OCTET,OCTET);
OCTET Verifier_Porte_Mobile_Tableau (OCTET,OCTET);
void Afficher_Porte_Mobile_Tableau (OCTET,OCTET);
OCTET Determiner_Direction (void);
void Clignoter_Serpent_Blanc (OCTET,OCTET);
void Clignoter_Tous_Serpent (OCTET,OCTET);
