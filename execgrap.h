#define BOOL unsigned char
#define OCTET unsigned char
#define ULONG unsigned long
#define SPR 0
#define PCX 1
#define MASK_ON 1
#define MASK_OFF 0
#define FAUX 0
#define VRAI 1
#define LIBRE 0
#define OCCUPE 1
#define PAGE0 0
#define PAGE1 1
#define LG_BOB 7
#define HT_BOB 11
#define LIMITE_X_ECRAN 320
#define LIMITE_Y_ECRAN 400
#define OFF 0
#define ON 1
#define SAISIE_OFF 0
#define SAISIE_ON 1
OCTET Lire_Page (void);
void Activer_Ecran (void);
void Desactiver_Ecran (void);
void Afficher_Page (OCTET);
void Afficher_Point (OCTET,short,short,OCTET);
OCTET Lire_Point (OCTET,short,short);
void Tracer_Droite (OCTET,short,short,short,short,OCTET);
void Tracer_Carre_Plein (OCTET,short,short,short,short,OCTET);
void Tracer_Rectangle (OCTET,short,short,short,short,OCTET);
void Cls (OCTET,OCTET);
void Lire_Palette (char*);
BOOL Lire_Image_Pcx (char*,OCTET,short,short,OCTET,
                     short,short,short,short);
BOOL Creer_Bob (short,short,short);
BOOL Lire_Bob (short,OCTET,short,short);
BOOL Afficher_Bob (OCTET,short,short,short,OCTET);
BOOL Detruire_Bob (short);
void Afficher_Nombre (OCTET,OCTET,OCTET,ULONG,short,short,OCTET);
void Definir_Bobs (void);
void Supprimer_Bobs (void);
