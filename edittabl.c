#include <IO.H>
#include <DIR.H>
#include <STDIO.H>
#include <STRING.H>
#include <STDLIB.H>
#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITBOIT.H"
void Former_Nom_Fichier (short,char*,char*,char*);
char NOM_TABLEAU [30];
struct infotableau
{
    OCTET buffertableau [X_MAX*Y_MAX];
    short nbpastille;
    short cppastille;
    short temps;
    short tempsplus;
    short tempsmoins;
    short vlbonus;
    short xfond;
    short yfond;
    short xbordure;
    short ybordure;
    OCTET nbdessin;
    OCTET nbnibblex;
    short xfcdessin [NB_DESSIN_TABLEAU];
    short yfcdessin [NB_DESSIN_TABLEAU];
    OCTET xdessin [NB_DESSIN_TABLEAU];
    OCTET ydessin [NB_DESSIN_TABLEAU];
    OCTET lgdessin [NB_DESSIN_TABLEAU];
    OCTET htdessin [NB_DESSIN_TABLEAU];
    OCTET lgnibble;
    OCTET spnibble;
    OCTET drnibble;
    OCTET vtnibble;
    OCTET mtnibble;
    OCTET flnibble;
    OCTET xnibble;
    OCTET ynibble;
    OCTET lgnibblex [NB_SERPENT-1];
    OCTET drnibblex [NB_SERPENT-1];
    short tpnibblex [NB_SERPENT-1];
    OCTET vtnibblex [NB_SERPENT-1];
    OCTET clnibblex [NB_SERPENT-1];
    OCTET xnibblex [NB_SERPENT-1];
    OCTET ynibblex [NB_SERPENT-1];
    OCTET xporterouge [NB_PORTERVB];
    OCTET yporterouge [NB_PORTERVB];
    OCTET xporteverte [NB_PORTERVB];
    OCTET yporteverte [NB_PORTERVB];
    OCTET xportebleue [NB_PORTERVB];
    OCTET yportebleue [NB_PORTERVB];
    short nbporterouge;
    short nbporteverte;
    short nbportebleue;
};
struct infotableau tableau;
struct infotableau backup1;
struct infotableau backup2;
char nomfichier [TAILLE_CHEMINFICHIER];
OCTET couleurs [30] =
{
    252,
    98,
    20,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    96,
    3,
    3,
    3,
    240,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3
};
void Lire_Buftab_Avec_Cadre (OCTET *ad_buffer)
{
    short cpt;
    for (cpt = 0;
            cpt < (X_MAX*Y_MAX);
            cpt ++)
        *(ad_buffer+cpt)=tableau.buffertableau[cpt];
}
void Lire_Buftab_Sans_Cadre (OCTET *ad_buffer)
{
    OCTET cpty;
    OCTET cptx;
    short cpt_buffer;
    short cpt_tableau;
    cpt_buffer = 0;
    cpt_tableau = 0;
    for (cpty = 0;
            cpty < Y_MAX;
            cpty ++)
    {
        for (cptx = 0;
                cptx < X_MAX;
                cptx ++)
        {
            if ( (cptx >0) & (cptx < (X_MAX - 1)) )
            {
                if ( (cpty >0) & (cpty < (Y_MAX - 1)) )
                {
                    *(ad_buffer+cpt_buffer)=tableau.buffertableau[cpt_tableau];
                    cpt_buffer ++;
                }
            }
            cpt_tableau ++;
        }
    }
}
void Ecrire_Buftab_Sans_Cadre (OCTET *ad_buffer)
{
    OCTET cpty;
    OCTET cptx;
    short cpt_buffer;
    short cpt_tableau;
    cpt_buffer = 0;
    cpt_tableau = 0;
    for (cpty = 0;
            cpty < Y_MAX;
            cpty ++)
    {
        for (cptx = 0;
                cptx < X_MAX;
                cptx ++)
        {
            if ( (cptx >0) & (cptx < (X_MAX - 1)) )
            {
                if ( (cpty >0) & (cpty < (Y_MAX - 1)) )
                {
                    tableau.buffertableau[cpt_tableau]=*(ad_buffer+cpt_buffer);
                    cpt_buffer ++;
                }
            }
            cpt_tableau ++;
        }
    }
}
short Lire_Nombre_Pastille (void)
{
    return (tableau.nbpastille) ;
}
void Ecrire_Nombre_Pastille (short a)
{
    tableau.nbpastille = a;
}
short Lire_Temps (void)
{
    return(tableau.temps);
}
void Ecrire_Temps (short a)
{
    tableau.temps = a ;
}
short Lire_Temps_Plus (void)
{
    return(tableau.tempsplus );
}
void Ecrire_Temps_Plus (short a)
{
    tableau.tempsplus = a;
}
short Lire_Temps_Moins (void)
{
    return(tableau.tempsmoins);
}
void Ecrire_Temps_Moins (short a)
{
    tableau.tempsmoins = a;
}
short Lire_Vlbonus (void)
{
    return(tableau.vlbonus);
}
void Ecrire_Vlbonus (short a)
{
    tableau.vlbonus = a;
}
short Lire_Xfond (void)
{
    return(tableau.xfond);
}
void Ecrire_Xfond (short a)
{
    tableau.xfond = a;
}
short Lire_Yfond (void)
{
    return(tableau.yfond);
}
void Ecrire_Yfond (short a)
{
    tableau.yfond = a;
}
short Lire_Xbordure (void)
{
    return(tableau.xbordure);
}
void Ecrire_Xbordure (short a)
{
    tableau.xbordure = a;
}
short Lire_Ybordure (void)
{
    return(tableau.ybordure);
}
void Ecrire_Ybordure (short a)
{
    tableau.ybordure = a;
}
OCTET Lire_Nbdessin (void)
{
    return(tableau.nbdessin);
}
void Ecrire_Nbdessin (OCTET a)
{
    tableau.nbdessin = a;
}
short Lire_Xfcdessin (OCTET a)
{
    return(tableau.xfcdessin [a]);
}
void Ecrire_Xfcdessin (OCTET a,short b)
{
    tableau.xfcdessin [a] = b;
}
short Lire_Yfcdessin (OCTET a)
{
    return(tableau.yfcdessin [a]);
}
void Ecrire_Yfcdessin (OCTET a,short b)
{
    tableau.yfcdessin [a] = b;
}
OCTET Lire_Xdessin (OCTET a)
{
    return(tableau.xdessin [a]);
}
void Ecrire_Xdessin (OCTET a,OCTET b)
{
    tableau.xdessin [a] = b;
}
OCTET Lire_Ydessin (OCTET a)
{
    return(tableau.ydessin [a]);
}
void Ecrire_Ydessin (OCTET a,OCTET b)
{
    tableau.ydessin [a] = b;
}
OCTET Lire_Lgdessin (OCTET a)
{
    return(tableau.lgdessin [a]);
}
void Ecrire_Lgdessin (OCTET a,OCTET b)
{
    tableau.lgdessin [a] = b;
}
OCTET Lire_Htdessin (OCTET a)
{
    return(tableau.htdessin [a]);
}
void Ecrire_Htdessin (OCTET a,OCTET b)
{
    tableau.htdessin [a] = b;
}
OCTET Lire_Lgnibble (void)
{
    return(tableau.lgnibble);
}
void Ecrire_Lgnibble (OCTET a)
{
    tableau.lgnibble = a;
}
OCTET Lire_Spnibble (void)
{
    return(tableau.spnibble);
}
void Ecrire_Spnibble (OCTET a)
{
    tableau.spnibble = a;
}
OCTET Lire_Drnibble (void)
{
    return(tableau.drnibble);
}
void Ecrire_Drnibble (OCTET a)
{
    tableau.drnibble = a;
}
OCTET Lire_Vtnibble (void)
{
    return(tableau.vtnibble);
}
void Ecrire_Vtnibble (OCTET a)
{
    tableau.vtnibble = a;
}
OCTET Lire_Mtnibble (void)
{
    return(tableau.mtnibble);
}
void Ecrire_Mtnibble (OCTET a)
{
    tableau.mtnibble = a;
}
OCTET Lire_Flnibble (void)
{
    return(tableau.flnibble);
}
void Ecrire_Flnibble (OCTET a)
{
    tableau.flnibble = a;
}
OCTET Lire_Xnibble (void)
{
    return(tableau.xnibble );
}
void Ecrire_Xnibble (OCTET a)
{
    tableau.xnibble = a;
}
OCTET Lire_Ynibble (void)
{
    return(tableau.ynibble );
}
void Ecrire_Ynibble (OCTET a)
{
    tableau.ynibble = a;
}
OCTET Lire_Nbnibble_X (void)
{
    return(tableau.nbnibblex);
}
void Ecrire_Nbnibble_X (OCTET a)
{
    tableau.nbnibblex = a;
}
OCTET Lire_Lgnibble_X (OCTET a)
{
    return(tableau.lgnibblex [a]);
}
void Ecrire_Lgnibble_X (OCTET a,OCTET b)
{
    tableau.lgnibblex [a] = b;
}
OCTET Lire_Drnibble_X (OCTET a)
{
    return(tableau.drnibblex [a]);
}
void Ecrire_Drnibble_X (OCTET a,OCTET b)
{
    tableau.drnibblex [a] = b;
}
short Lire_Tpnibble_X (OCTET a)
{
    return(tableau.tpnibblex [a]);
}
void Ecrire_Tpnibble_X (OCTET a,short b)
{
    tableau.tpnibblex [a] = b;
}
OCTET Lire_Vtnibble_X (OCTET a)
{
    return(tableau.vtnibblex [a]);
}
void Ecrire_Vtnibble_X (OCTET a,OCTET b)
{
    tableau.vtnibblex [a] = b;
}
OCTET Lire_Clnibble_X (OCTET a)
{
    return(tableau.clnibblex [a]);
}
void Ecrire_Clnibble_X (OCTET a,OCTET b)
{
    tableau.clnibblex [a] = b;
}
OCTET Lire_Xnibble_X (OCTET a)
{
    return(tableau.xnibblex [a]);
}
void Ecrire_Xnibble_X (OCTET a,OCTET b)
{
    tableau.xnibblex [a] = b;
}
OCTET Lire_Ynibble_X (OCTET a)
{
    return(tableau.ynibblex [a]);
}
void Ecrire_Ynibble_X (OCTET a,OCTET b)
{
    tableau.ynibblex [a] = b;
}
OCTET Lire_Xporterouge (short a)
{
    return(tableau.xporterouge [a]);
}
void Ecrire_Xporterouge (short a,OCTET b)
{
    tableau.xporterouge [a] = b;
}
OCTET Lire_Yporterouge (short a)
{
    return(tableau.yporterouge [a]);
}
void Ecrire_Yporterouge (short a,OCTET b)
{
    tableau.yporterouge [a] = b;
}
OCTET Lire_Xporteverte (short a)
{
    return(tableau.xporteverte [a]);
}
void Ecrire_Xporteverte (short a,OCTET b)
{
    tableau.xporteverte [a] = b;
}
OCTET Lire_Yporteverte (short a)
{
    return(tableau.yporteverte [a]);
}
void Ecrire_Yporteverte (short a,OCTET b)
{
    tableau.yporteverte [a] = b;
}
OCTET Lire_Xportebleue (short a)
{
    return(tableau.xportebleue [a]);
}
void Ecrire_Xportebleue (short a,OCTET b)
{
    tableau.xportebleue [a] = b;
}
OCTET Lire_Yportebleue (short a)
{
    return(tableau.yportebleue [a]);
}
void Ecrire_Yportebleue (short a,OCTET b)
{
    tableau.yportebleue [a] = b;
}
short Lire_Nbporterouge (void)
{
    return(tableau.nbporterouge);
}
void Ecrire_Nbporterouge (short a)
{
    tableau.nbporterouge = a;
}
short Lire_Nbporteverte (void)
{
    return(tableau.nbporteverte);
}
void Ecrire_Nbporteverte (short a)
{
    tableau.nbporteverte = a;
}
short Lire_Nbportebleue (void)
{
    return(tableau.nbportebleue);
}
void Ecrire_Nbportebleue (short a)
{
    tableau.nbportebleue = a;
}
void Lire_Tableau (short num_tableau)
{
    FILE *flux;
    Former_Nom_Fichier (num_tableau,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"rb");
    fread (&tableau.buffertableau[0],
           sizeof (struct infotableau),
           1,flux);
    fclose (flux);
}
void Sauver_Tableau (short num_tableau)
{
    FILE *flux;
    Former_Nom_Fichier (num_tableau,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"wb");
    fwrite (&tableau.buffertableau[0],
            sizeof (struct infotableau),
            1,flux);
    fclose (flux);
}
void Former_Nom_Fichier (short nf,
                         char *nomfichier,
                         char *nomchemin,
                         char *nomextension)
{
    char nbbuffer [3];
    char zero [3][3] = { {"00"},{"0"},{""} };
    memset (nomfichier,0,TAILLE_CHEMINFICHIER);
    strcpy (nomfichier,nomchemin);
    if (nf != -1)
    {
        itoa (nf,nbbuffer,10);
        strcat (nomfichier,
                zero[strlen(nbbuffer)-1]);
        strcat (nomfichier,nbbuffer);
    }
    strcat (nomfichier,nomextension);
}
void Verifier_Tableaux (OCTET page)
{
    short cpttab;
    for (cpttab = 1;
            cpttab <= 48;
            cpttab ++)
    {
        Former_Nom_Fichier (cpttab,
                            nomfichier,
                            NOM_TABLEAU,
                            EXT_CODAGE);
        if (access (nomfichier,0) != 0)
            Initialiser_Tableau (cpttab);
    }
    for (cpttab = 1;
            cpttab <= 48;
            cpttab ++)
        Afficher_Mini_Tableau (page,cpttab);
}
void Afficher_Mini_Tableau (OCTET page,short num_tableau)
{
    FILE *flux;
    OCTET cptx;
    OCTET cpty;
    short cptind;
    OCTET couleur;
    OCTET col;
    OCTET lig;
    short x;
    short y;
    lig = ( num_tableau - 1 ) / NB_TABLEAU_X;
    col = ( num_tableau - 1 ) - ( NB_TABLEAU_X * lig );
    x = X_TABLEAUX + ( col * X_ECART );
    y = Y_TABLEAUX + ( lig * Y_ECART );
    cptind = 0;
    Former_Nom_Fichier (num_tableau,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"rb");
    fread (&backup1.buffertableau[0],(X_MAX * Y_MAX),1,flux);
    fclose (flux);
    for (cpty = 0;
            cpty < Y_MAX;
            cpty ++)
    {
        for (cptx = 0;
                cptx < X_MAX;
                cptx ++)
        {
            couleur = couleurs [backup1.buffertableau [cptind]];
            Afficher_Point (page,(x + cptx),(y + cpty),couleur);
            cptind ++;
        }
    }
}
void Initialiser_Tableau (short num_tableau)
{
    FILE *flux;
    short cpt;
    short taille;
    short numero;
    short x,y;
    taille = sizeof (struct infotableau);
    for (cpt = 0;
            cpt < taille;
            cpt ++)
        *( &backup1.buffertableau [0] + cpt ) = 0;
    for (cpt = 0;
            cpt < X_MAX;
            cpt ++)
    {
        backup1.buffertableau [ cpt ] = 1;
        backup1.buffertableau [ (X_MAX * (Y_MAX - 1)) + cpt] = 1;
    }
    for (cpt = 0;
            cpt < Y_MAX;
            cpt ++)
    {
        backup1.buffertableau [ X_MAX * cpt ] = 1;
        backup1.buffertableau [ (X_MAX * cpt) + (X_MAX - 1) ] = 1;
    }
    backup1.temps = 150;
    backup1.vlbonus = 1;
    backup1.tempsplus = 1;
    backup1.tempsmoins = 1;
    numero = random (60)+1;
    Conv_Num_Coord (BORDURES,numero,&x,&y);
    backup1.xbordure = x;
    backup1.ybordure = y;
    numero = random (300)+1;
    Conv_Num_Coord (FONDS,numero,&x,&y);
    backup1.xfond = x;
    backup1.yfond = y;
    backup1.drnibble = 1;
    backup1.vtnibble = 2;
    backup1.mtnibble = 1;
    backup1.spnibble = 1;
    backup1.flnibble = 1;
    for (cpt = 0;
            cpt < NB_SERPENT_RVB;
            cpt ++)
    {
        backup1.tpnibblex [cpt] = 5000;
        backup1.vtnibblex [cpt] = 2;
    }
    Former_Nom_Fichier (num_tableau,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"wb");
    fwrite (&backup1.buffertableau[0],taille,1,flux);
    fclose (flux);
}
void Copier_Tableau (short source,short destination)
{
    FILE *flux;
    short taille;
    taille = sizeof (struct infotableau);
    Former_Nom_Fichier (source,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"rb");
    fread (&backup1.buffertableau[0],taille,1,flux);
    fclose (flux);
    Former_Nom_Fichier (destination,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"wb");
    fwrite (&backup1.buffertableau[0],taille,1,flux);
    fclose (flux);
}
void Permuter_Tableau (short tableau_1,short tableau_2)
{
    FILE *flux;
    short taille;
    taille = sizeof (struct infotableau);
    Former_Nom_Fichier (tableau_1,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"rb");
    fread (&backup1.buffertableau[0],taille,1,flux);
    fclose (flux);
    Former_Nom_Fichier (tableau_2,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"rb");
    fread (&backup2.buffertableau[0],taille,1,flux);
    fclose (flux);
    Former_Nom_Fichier (tableau_1,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"wb");
    fwrite (&backup2.buffertableau[0],taille,1,flux);
    fclose (flux);
    Former_Nom_Fichier (tableau_2,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"wb");
    fwrite (&backup1.buffertableau[0],taille,1,flux);
    fclose (flux);
}
BOOL Verifier_Jouabilite_Tableau (short tab)
{
    BOOL boule;
    BOOL sortie;
    FILE *flux;
    short cpt;
    short taille;
    boule = FAUX;
    sortie = VRAI;
    taille = sizeof (struct infotableau);
    Former_Nom_Fichier (tab,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"rb");
    fread (&backup1.buffertableau[0],taille,1,flux);
    fclose (flux);
    if (backup1.lgnibble == 0)
        sortie = FAUX;
    for (cpt = 0;
            cpt < (X_MAX*Y_MAX);
            cpt ++)
    {
        if (backup1.buffertableau [cpt] == OBST_BOULE_BLEU)
        {
            boule = VRAI;
            break;
        }
    }
    if (boule == FAUX) sortie = FAUX;
    return (sortie);
}
void Afficher_Mini_Tableau_Isole (OCTET page,short num_tableau,
                                  short x,short y)
{
    FILE *flux;
    OCTET cptx;
    OCTET cpty;
    short cptind;
    OCTET couleur;
    cptind = 0;
    Former_Nom_Fichier (num_tableau,
                        nomfichier,
                        NOM_TABLEAU,
                        EXT_CODAGE);
    flux = fopen(nomfichier,"rb");
    fread (&backup1.buffertableau[0],(X_MAX * Y_MAX),1,flux);
    fclose (flux);
    for (cpty = 0;
            cpty < Y_MAX;
            cpty ++)
    {
        for (cptx = 0;
                cptx < X_MAX;
                cptx ++)
        {
            couleur = couleurs [backup1.buffertableau [cptind]];
            Afficher_Point (page,(x + cptx),(y + cpty),couleur);
            cptind ++;
        }
    }
}
BOOL Verifier_Repertoire_Tableaux (OCTET page,char *bufrep)
{
    int etat;
    BOOL sortie;
    OCTET reponse;
    sortie = VRAI;
    if ( access (bufrep,0) == -1)
    {
        Afficher_Boite_Message (page,INFO15);
        reponse = RIEN;
        do
        {
            if ( Test_Option (INFO15_OUI) == ON )
            {
                reponse = OUI;
                Option (OFF,page,INFO15_OUI);
                WAIT_NO_CLIC;
                Option (ON,page,INFO15_OUI);
            }
            if ( Test_Option (INFO15_NON) == ON )
            {
                reponse = NON;
                Option (OFF,page,INFO15_NON);
                WAIT_NO_CLIC;
                Option (ON,page,INFO15_NON);
            }
        }
        while (reponse == RIEN);
        Effacer_Boite (page);
        if (reponse == NON)
            sortie = FAUX;
        else
        {
            etat = mkdir (bufrep);
            if (etat == -1)
                sortie = FAUX;
        }
    }
    return (sortie);
}
