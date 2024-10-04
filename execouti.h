#define NB_OPTION 8
#define LG_OPTION 20
typedef struct
{
    char page;
    char select;
    OCTET cl_car1;
    OCTET cl_car2;
    OCTET cl_fond;
    short y_ecran;
    short largeur_ecran;
    short hauteur_option_maxi;
    char nombre_option;
    char echelle_x;
    char echelle_y;
    short xgt [NB_OPTION];
    short xdt [NB_OPTION];
    short yt [NB_OPTION];
    char option [NB_OPTION][LG_OPTION];
} enreg_menu;
void Afficher_Menu (enreg_menu*);
void Select_Option (char,enreg_menu*);
void Marquer_Option_Serpent (char,enreg_menu*,char);
