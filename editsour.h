#define BOOL unsigned char
#define OCTET unsigned char
#define ULONG unsigned long
#define NO_CLIC 0
#define CLIC_GAUCHE 1
#define CLIC_DROITE 2
#define CLIC_GAUCHE_DROITE 3
#define FLECHE 0
#define CROIX 1
#define RELIEF_CLAIR 96
#define RELIEF_FONCE 128
#define WAIT_NO_CLIC do {} while (Clic_Souris () == CLIC_GAUCHE)
#define WAIT_CLIC_GAUCHE do {} while (Clic_Souris () != CLIC_GAUCHE)
#define WAIT_CLIC_DROITE do {} while (Clic_Souris () != CLIC_DROITE)
void far Installer_Timer_Interruption (void);
void far Desinstaller_Timer_Interruption (void);
OCTET Lire_Panneau_Demande (void);
void Ecrire_Panneau_Demande (OCTET);
OCTET Lire_Panneau_Encours (void);
void Ecrire_Panneau_Encours (OCTET);
short X_Fleche (void);
short Y_Fleche (void);
short X_Croix (void);
short Y_Croix (void);
void Souris (OCTET);
BOOL Activer_Souris (void);
BOOL Desactiver_Souris (void);
void Afficher_Souris (void);
void Sauver_Fond (void);
void Restaurer_Fond (void);
void Repositionner_Souris (short,short);
short Clic_Souris (void);
OCTET Test_Zone (short,short,short,short,short,short);
OCTET Test_Clic_Zone (short,short,short,short,short,short);
void Activer_Zone_Croix (short,short,short,short);
void Desactiver_Zone_Croix (void);
void Pause (unsigned short);
