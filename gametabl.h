#define PT_FOND 0
#define PT_BORDURE 0
#define PT_DESSIN 0
#define PT_PORTE_BLANCHE_MOBILE 0
#define PT_PORTE_ROUGE_FERMEE 0
#define PT_PORTE_VERTE_FERMEE 0
#define PT_PORTE_BLEU_FERMEE 0
#define PT_PORTE_ROUGE_OUVERTE 0
#define PT_PORTE_VERTE_OUVERTE 0
#define PT_PORTE_BLEU_OUVERTE 0
#define PT_CLE_ROUGE 1
#define PT_CLE_VERTE 1
#define PT_CLE_BLEU 1
#define PT_BOULE_BLEU 2
#define PT_DIAMANT 0
#define PT_BOULE_VERTE 2
#define PT_BOULE_ROUGE 4
#define PT_ETOILE_VIE 1
#define PT_ETOILE_MORT 0
#define PT_SERPENT_SOUPLE 2
#define PT_SERPENT_RAIDE 4
#define PT_TEMPS_PLUS 2
#define PT_TEMPS_MOINS 4
#define PT_IMMORTALITE 2
#define PT_MORTALITE 4
#define PT_AVANCE_LENTE 2
#define PT_AVANCE_RAPIDE 4
#define PT_VITESSE_RAPIDE 4
#define PT_VITESSE_MOYENNE 3
#define PT_VITESSE_LENTE 2
#define PT_STOP_SERPENT_ROUGE 1
#define PT_STOP_SERPENT_VERT 1
#define PT_STOP_SERPENT_BLEU 1
#define PT_SENS_SERPENT_ROUGE 4
#define PT_SENS_SERPENT_VERT 4
#define PT_SENS_SERPENT_BLEU 4
#define PT_VITESSE_SERPENT_ROUGE 4
#define PT_VITESSE_SERPENT_VERT 4
#define PT_VITESSE_SERPENT_BLEU 4
#define X_MIN 0
#define Y_MIN 0
#define X_MAX 45
#define Y_MAX 35
#define NB_PORTERVB 1419
#define NB_SERPENT 21
#define NB_DESSIN_TABLEAU 32
#define EXT_CODAGE ".DAT"
#define TAILLE_CHEMINFICHIER 32
#define NB_TABLEAU_X 6
#define X_TABLEAUX 8
#define Y_TABLEAUX 48
#define LG_TABLEAU 44
#define HT_TABLEAU 34
#define X_ECART 52
#define Y_ECART 44
#define OBST_FOND 0
#define OBST_BORDURE 1
#define OBST_DESSIN 2
#define OBST_PORTE_BLANCHE_MOBILE 3
#define OBST_PORTE_ROUGE_FERMEE 4
#define OBST_PORTE_VERTE_FERMEE 5
#define OBST_PORTE_BLEU_FERMEE 6
#define OBST_PORTE_ROUGE_OUVERTE 7
#define OBST_PORTE_VERTE_OUVERTE 8
#define OBST_PORTE_BLEU_OUVERTE 9
#define OBST_CLE_ROUGE 10
#define OBST_CLE_VERTE 11
#define OBST_CLE_BLEU 12
#define OBST_BOULE_BLEU 13
#define OBST_DIAMANT 14
#define OBST_BOULE_VERTE 15
#define OBST_BOULE_ROUGE 16
#define OBST_ETOILE_VIE 17
#define OBST_ETOILE_MORT 18
#define OBST_SERPENT_SOUPLE 19
#define OBST_SERPENT_RAIDE 20
#define OBST_TEMPS_PLUS 21
#define OBST_TEMPS_MOINS 22
#define OBST_IMMORTALITE 23
#define OBST_MORTALITE 24
#define OBST_AVANCE_LENTE 25
#define OBST_AVANCE_RAPIDE 26
#define OBST_VITESSE_RAPIDE 27
#define OBST_VITESSE_MOYENNE 28
#define OBST_VITESSE_LENTE 29
#define OBST_STOP_SERPENT_ROUGE 30
#define OBST_STOP_SERPENT_VERT 31
#define OBST_STOP_SERPENT_BLEU 32
#define OBST_SENS_SERPENT_ROUGE 33
#define OBST_SENS_SERPENT_VERT 34
#define OBST_SENS_SERPENT_BLEU 35
#define OBST_VITESSE_SERPENT_ROUGE 36
#define OBST_VITESSE_SERPENT_VERT 37
#define OBST_VITESSE_SERPENT_BLEU 38
OCTET Lire_Code_Tableau (short,short);
void Ecrire_Code_Tableau (short,short,OCTET);
OCTET Lire_Code_Buffer (short);
short Lire_Nombre_Pastille (void);
void Initialiser_Compteur_Pastille (short);
short Lire_Compteur_Pastille (void);
void Incrementer_Compteur_Pastille (short);
short Lire_Temps (void);
void Ecrire_Temps (short);
short Lire_Temps_Plus (void);
void Ecrire_Temps_Plus (short);
short Lire_Temps_Moins (void);
void Ecrire_Temps_Moins (short);
short Lire_Vlbonus (void);
void Ecrire_Vlbonus (short);
short Lire_Xfond (void);
void Ecrire_Xfond (short);
short Lire_Yfond (void);
void Ecrire_Yfond (short);
short Lire_Xbordure (void);
void Ecrire_Xbordure (short);
short Lire_Ybordure (void);
void Ecrire_Ybordure (short);
OCTET Lire_Nbdessin (void);
void Ecrire_Nbdessin (OCTET);
short Lire_Xfcdessin (OCTET);
void Ecrire_Xfcdessin (OCTET,short);
short Lire_Yfcdessin (OCTET);
void Ecrire_Yfcdessin (OCTET,short);
OCTET Lire_Xdessin (OCTET);
void Ecrire_Xdessin (OCTET,OCTET);
OCTET Lire_Ydessin (OCTET);
void Ecrire_Ydessin (OCTET,OCTET);
OCTET Lire_Lgdessin (OCTET);
void Ecrire_Lgdessin (OCTET,OCTET);
OCTET Lire_Htdessin (OCTET);
void Ecrire_Htdessin (OCTET,OCTET);
OCTET Lire_Lgnibble (void);
void Ecrire_Lgnibble (OCTET);
OCTET Lire_Spnibble (void);
void Ecrire_Spnibble (OCTET);
OCTET Lire_Drnibble (void);
void Ecrire_Drnibble (OCTET);
OCTET Lire_Vtnibble (void);
void Ecrire_Vtnibble (OCTET);
OCTET Lire_Mtnibble (void);
void Ecrire_Mtnibble (OCTET);
OCTET Lire_Flnibble (void);
void Ecrire_Flnibble (OCTET);
OCTET Lire_Xnibble (void);
void Ecrire_Xnibble (OCTET);
OCTET Lire_Ynibble (void);
void Ecrire_Ynibble (OCTET);
OCTET Lire_Nbnibble_X (void);
void Ecrire_Nbnibble_X (OCTET);
OCTET Lire_Lgnibble_X (OCTET);
void Ecrire_Lgnibble_X (OCTET,OCTET);
OCTET Lire_Drnibble_X (OCTET);
void Ecrire_Drnibble_X (OCTET,OCTET);
short Lire_Tpnibble_X (OCTET);
void Ecrire_Tpnibble_X (OCTET,short);
OCTET Lire_Vtnibble_X (OCTET);
void Ecrire_Vtnibble_X (OCTET,OCTET);
OCTET Lire_Clnibble_X (OCTET);
void Ecrire_Clnibble_X (OCTET,OCTET);
OCTET Lire_Xnibble_X (OCTET);
void Ecrire_Xnibble_X (OCTET,OCTET);
OCTET Lire_Ynibble_X (OCTET);
void Ecrire_Ynibble_X (OCTET,OCTET);
OCTET Lire_Xporterouge (short);
void Ecrire_Xporterouge (short,OCTET);
OCTET Lire_Yporterouge (short);
void Ecrire_Yporterouge (short,OCTET);
OCTET Lire_Xporteverte (short);
void Ecrire_Xporteverte (short,OCTET);
OCTET Lire_Yporteverte (short);
void Ecrire_Yporteverte (short,OCTET);
OCTET Lire_Xportebleue (short);
void Ecrire_Xportebleue (short,OCTET);
OCTET Lire_Yportebleue (short);
void Ecrire_Yportebleue (short,OCTET);
short Lire_Nbporterouge (void);
void Ecrire_Nbporterouge (short);
short Lire_Nbporteverte (void);
void Ecrire_Nbporteverte (short);
short Lire_Nbportebleue (void);
void Ecrire_Nbportebleue (short);
void Lire_Tableau (short);
void Sauver_Tableau (short);
BOOL Verifier_Jouabilite_Tableau (short);
void Clignoter_Tableau (OCTET,OCTET);
void Afficher_Pastilles (OCTET,OCTET);
void Afficher_Bordures (OCTET,OCTET);
void Afficher_Fond_Dessins (OCTET);
void Afficher_Dessin (OCTET,OCTET);
void Calquer_Dessin (OCTET,OCTET,OCTET);
void Appeler_Tableau (short,OCTET,OCTET);
void Rappeler_Tableau (short,OCTET,OCTET);
BOOL Sauver_Filedata (ULONG,short);
char Prochain_Tableau (char*,char*);
void Trier_Nombre_Aleatoire (char*,short);
