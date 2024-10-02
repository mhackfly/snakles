#include <DOS.H>
#include <STDIO.H>
#include <STRING.H>
#include <STDLIB.H>
#include "SOURGAME/GAMESERP.H"
#include "SOURGAME/GAMEGRAP.H"
#include "SOURGAME/GAMETABL.H"
#include "SOURGAME/GAMEBOIT.H"
#include "SOURGAME/GAMEINFO.H"
#include "SOURGAME/GAMETIME.H"
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
OCTET Lire_Code_Tableau (short x,short y)
{
    return (tableau.buffertableau[((y/HT_BOB)*X_MAX)+(x/LG_BOB)]);
}
void Ecrire_Code_Tableau (short x,short y,OCTET c)
{
    tableau.buffertableau[((y/HT_BOB)*X_MAX)+(x/LG_BOB)]=c;
}
OCTET Lire_Code_Buffer (short indice)
{
    return (tableau.buffertableau[indice]);
}
short Lire_Nombre_Pastille (void)
{
    return (tableau.nbpastille) ;
}
void Initialiser_Compteur_Pastille (short vl)
{
    tableau.cppastille = vl ;
}
short Lire_Compteur_Pastille (void)
{
    return (tableau.cppastille) ;
}
void Incrementer_Compteur_Pastille (short vl)
{
    tableau.cppastille += vl;
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
    if (flux == NULL) return (FAUX);
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
void Afficher_Pastilles (OCTET pg,OCTET nm)
{
    OCTET y,x;
    OCTET code;
    short cptcode = 0;
    for (y=Y_MIN; y<Y_MAX; y++)
    {
        for (x=X_MIN; x<X_MAX; x++)
        {
            code=tableau.buffertableau[cptcode];
            if (code == 0)
                Afficher_Bob (pg,BOB_FOND,x*LG_BOB,y*HT_BOB,MASK_ON);
            if (code >= OBST_PORTE_BLANCHE_MOBILE)
            {
                Afficher_Bob (pg,BOB_FOND,x*LG_BOB,y*HT_BOB,MASK_ON);
                Afficher_Bob (pg,nm+code-1,x*LG_BOB,y*HT_BOB,MASK_ON);
            }
            cptcode++;
        }
    }
}
void Afficher_Bordures (OCTET pg,OCTET nm)
{
    OCTET coddr;
    OCTET codga;
    OCTET codha;
    OCTET codba;
    OCTET resul;
    OCTET y,x;
    OCTET code;
    short cptcode = 0;
    for (y=Y_MIN; y<Y_MAX; y++)
    {
        for (x=X_MIN; x<X_MAX; x++)
        {
            code=tableau.buffertableau[cptcode];
            if (code==OBST_BORDURE)
            {
                coddr = ( (cptcode+1) >= (X_MAX*(y+1)) ) ? 0 :tableau.buffertableau[cptcode+1];
                codba = ( (cptcode+X_MAX) > (X_MAX*Y_MAX-1) ) ? 0 :tableau.buffertableau[cptcode+X_MAX];
                codga = ( (cptcode-1) < (X_MAX*y) ) ? 0 :tableau.buffertableau[cptcode-1];
                codha = ( (cptcode-X_MAX) < 0 ) ? 0 :tableau.buffertableau[cptcode-X_MAX];
                resul=0;
                resul += (coddr==OBST_BORDURE) ? 1 : 0;
                resul += (codba==OBST_BORDURE) ? 2 : 0;
                resul += (codga==OBST_BORDURE) ? 4 : 0;
                resul += (codha==OBST_BORDURE) ? 8 : 0;
                Afficher_Bob (pg,BOB_FOND,x*LG_BOB,y*HT_BOB,MASK_ON);
                Afficher_Bob (pg,nm+resul,x*LG_BOB,y*HT_BOB,MASK_ON);
            }
            cptcode++;
        }
    }
}
void Afficher_Fond_Dessins (OCTET pg)
{
    OCTET y,x;
    OCTET code;
    short cptcode = 0;
    for (y=Y_MIN; y<Y_MAX; y++)
    {
        for (x=X_MIN; x<X_MAX; x++)
        {
            code = tableau.buffertableau [cptcode];
            if (code == OBST_DESSIN)
                Afficher_Bob (pg,BOB_FOND,x*LG_BOB,y*HT_BOB,MASK_ON);
            cptcode++;
        }
    }
}
void Afficher_Dessin (OCTET page_video,OCTET num_dessin)
{
    short xecran;
    short yecran;
    short xfichier;
    short yfichier;
    short lgfichier;
    short htfichier;
    xecran = (short)(Lire_Xdessin (num_dessin) * LG_BOB);
    yecran = (short)(Lire_Ydessin (num_dessin) * HT_BOB);
    xfichier = Lire_Xfcdessin (num_dessin);
    yfichier = Lire_Yfcdessin (num_dessin);
    lgfichier = (short)( (Lire_Lgdessin (num_dessin) * LG_BOB) - 1);
    htfichier = (short)( (Lire_Htdessin (num_dessin) * HT_BOB) - 1);
    Lire_Image_Pcx ("SPRFILES/DESSINS",
                    page_video,
                    xecran,yecran,
                    MASK_OFF,
                    xfichier,yfichier,
                    lgfichier,htfichier);
}
void Calquer_Dessin (OCTET page_active,OCTET page_cachee,OCTET num_dessin)
{
    short xecran;
    short yecran;
    short cptx;
    short cpty;
    short lgfichier;
    short htfichier;
    OCTET couleur;
    xecran = (short)(Lire_Xdessin (num_dessin) * LG_BOB);
    yecran = (short)(Lire_Ydessin (num_dessin) * HT_BOB);
    lgfichier = (short)( (Lire_Lgdessin (num_dessin) * LG_BOB) - 1);
    htfichier = (short)( (Lire_Htdessin (num_dessin) * HT_BOB) - 1);
    for (cpty = 0;
            cpty <= htfichier;
            cpty ++)
    {
        for (cptx = 0;
                cptx <= lgfichier;
                cptx ++)
        {
            couleur = Lire_Point (page_active,xecran + cptx,yecran + cpty);
            Afficher_Point (page_cachee,xecran + cptx,yecran + cpty,couleur);
        }
    }
}
void Clignoter_Tableau (OCTET page_active,OCTET page_cachee)
{
    short cpty,cptx;
    OCTET y,x;
    OCTET code;
    short cpt;
    Afficher_Tous_Serpents (page_active);
    for (cpty = 0;
            cpty < Y_MAX * HT_BOB;
            cpty ++)
    {
        for (cptx = 0;
                cptx < X_MAX * LG_BOB;
                cptx ++)
        {
            code = Lire_Point (page_active,cptx,cpty);
            Afficher_Point (page_cachee,cptx,cpty,code);
        }
    }
    cpt = 0;
    for (y = Y_MIN;
            y < Y_MAX;
            y ++)
    {
        for ( x = X_MIN;
                x < X_MAX;
                x ++)
        {
            code = tableau.buffertableau[cpt];
            if ( code == OBST_BORDURE )
                Afficher_Bob (page_cachee,BOB_FOND,x*LG_BOB,y*HT_BOB,MASK_ON);
            cpt ++;
        }
    }
    for (cpt = 0;
            cpt < 10;
            cpt ++)
    {
        Afficher_Page (page_cachee);
        Pause (50);
        Afficher_Page (page_active);
        Pause (50);
    }
    Afficher_Page (page_active);
}
void Appeler_Tableau (short nm,OCTET page_active,OCTET page_cachee)
{
    OCTET cpt;
    OCTET nbdes;
    short xb,yb;
    short xf,yf;
    Cls (page_active);
    Cls (page_cachee);
    Afficher_Boite_Info (page_active,LECTURE_TABLEAU);
    Pause (1000);
    Effacer_Boite (page_active);
    Lire_Tableau (nm);
    Initialiser_Compteur_Pastille (0);
    Init_Code_Serpent (CODE_SERPENT_FOND);
    Init_Tous_Serpents ();
    Sauver_Toutes_Donnees_Serpent (0);
    Sauver_Toutes_Donnees_Serpent (1);
    Lire_Image_Pcx ("SPRFILES/DECORS",
                    page_cachee,
                    6,33,
                    MASK_OFF,6,33,307,360);
    xb = Lire_Xbordure ();
    yb = Lire_Ybordure ();
    xf = Lire_Xfond ();
    yf = Lire_Yfond ();
    for (cpt = 0;
            cpt < NB_BOB_BORDURE;
            cpt ++)
        Lire_Bob (BOB_BORDURE + cpt,
                  page_cachee,
                  xb + (cpt * BORDURE_LONG),
                  yb);
    Lire_Bob (BOB_FOND,page_cachee,xf,yf);
    Effacer_Ecran (page_cachee,0);
    Afficher_Bordures (page_cachee,BOB_BORDURE);
    Afficher_Pastilles (page_cachee,BOB_PASTILLE);
    Afficher_Fond_Dessins (page_cachee);
    nbdes = Lire_Nbdessin();
    for (cpt = 0;
            cpt < nbdes;
            cpt ++)
        Afficher_Dessin (page_cachee,cpt);
    Afficher_Tous_Serpents (page_cachee);
    Afficher_Page (page_cachee);
    Afficher_Bordures (page_active,BOB_BORDURE);
    Afficher_Pastilles (page_active,BOB_PASTILLE);
    Afficher_Fond_Dessins (page_active);
    nbdes = Lire_Nbdessin();
    for (cpt = 0;
            cpt < nbdes;
            cpt ++)
        Calquer_Dessin (page_cachee,page_active,cpt);
    Afficher_Tous_Serpents (page_active);
    Afficher_Page (page_active);
    Ini_Tableau (nm);
    Ini_Temps (Lire_Temps ());
    Afficher_Infos ();
}
void Rappeler_Tableau (short nm,OCTET page_active,OCTET page_cachee)
{
    Lire_Tableau (nm);
    Initialiser_Compteur_Pastille (0);
    Init_Code_Serpent (CODE_SERPENT_FOND);
    Init_Tous_Serpents ();
    Sauver_Toutes_Donnees_Serpent (0);
    Sauver_Toutes_Donnees_Serpent (1);
    Afficher_Pastilles (page_cachee,BOB_PASTILLE);
    Afficher_Tous_Serpents (page_cachee);
    Afficher_Page (page_cachee);
    Afficher_Pastilles (page_active,BOB_PASTILLE);
    Afficher_Tous_Serpents (page_active);
    Afficher_Page (page_active);
    Ini_Temps (Lire_Temps ());
    Aff_Temps ();
}
#define FICHIER_FILEDATA "donnees.dat"
BOOL Sauver_Filedata (ULONG score,short tableau)
{
    typedef struct
    {
        ULONG score;
        short tableau;
    } enreg_filedata;
    enreg_filedata filedata;
    BOOL sortie;
    FILE *flux;
    flux = fopen(FICHIER_FILEDATA,"wb");
    if (flux == NULL)
        sortie = FAUX;
    else
    {
        filedata.score = score;
        filedata.tableau = tableau;
        fwrite (&filedata.score,sizeof (enreg_filedata),1,flux);
        fclose (flux);
        sortie = VRAI;
    }
    return (sortie);
}
char Prochain_Tableau (char *buffer,char *pt_cpttab)
{
    BOOL jouable;
    do
    {
        *pt_cpttab = *pt_cpttab + 1;
        if (*pt_cpttab > 48) break;
        jouable = Verifier_Jouabilite_Tableau (*(buffer + *pt_cpttab));
    }
    while (jouable == FAUX);
    return (*pt_cpttab);
}
void Trier_Nombre_Aleatoire (char *table_nb_aleatoire,short nb_valeur)
{
    short i;
    short cpt_nb;
    short nb_aleatoire;
    short nb_valeur_total;
    short *table_nb_croissant;
    table_nb_croissant = calloc (nb_valeur, sizeof(short));
    if (table_nb_croissant == NULL) return;
    nb_valeur_total = nb_valeur;
    for (cpt_nb = 0 ;
            cpt_nb < nb_valeur_total ;
            cpt_nb ++)
        *(table_nb_croissant + cpt_nb) = cpt_nb;
    for (cpt_nb = 0 ;
            cpt_nb < nb_valeur_total ;
            cpt_nb ++)
    {
        nb_aleatoire = random (nb_valeur);
        *(table_nb_aleatoire + cpt_nb) = *(table_nb_croissant + nb_aleatoire);
        for (i = nb_aleatoire ;
                i< (nb_valeur-1) ;
                i++)
            *(table_nb_croissant + i) = *(table_nb_croissant + (i+1));
        nb_valeur --;
    }
    free (table_nb_croissant);
    for (cpt_nb = 0 ;
            cpt_nb < nb_valeur_total ;
            cpt_nb ++)
    {
        *(table_nb_aleatoire + cpt_nb) = *(table_nb_aleatoire + cpt_nb) + 1;
    }
}
