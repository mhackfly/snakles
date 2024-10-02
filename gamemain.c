#define NB_VIE 5
#include <IO.H>
#include <TIME.H>
#include <CONIO.H>
#include <STDIO.H>
#include <STRING.H>
#include <STDLIB.H>
#include "SOURGAME/GAMECLAV.H"
#include "SOURGAME/GAMEGRAP.H"
#include "SOURGAME/GAMETABL.H"
#include "SOURGAME/GAMESERP.H"
#include "SOURGAME/GAMEANIM.H"
#include "SOURGAME/GAMEINFO.H"
#include "SOURGAME/GAMEBOIT.H"
#include "SOURGAME/GAMETIME.H"
short numero_tableau;
void Lancer_Jeu (void);
extern char NOM_TABLEAU [];
void main (int argc,char *argv [])
{
    if (argc == 3)
    {
        if ( access (argv[1],0) == -1)
        {
            printf ("le repertoire des tableaux n'existe pas.\n");
            exit (0);
        }
        else
        {
            strcpy (NOM_TABLEAU,argv[1]);
            strcat (NOM_TABLEAU,"/level");
            if ( Verifier_Jouabilite_Tableau (atoi ( argv[2] )) == FAUX)
            {
                if (atoi ( argv[2] ) != -1)
                {
                    printf ("numero de tableau inexistant ou tableau incomplet.\n");
                    exit (0);
                }
            }
        }
    }
    else
    {
        printf ("Erreur d'appel.\n");
        exit (0);
    }
    numero_tableau = atoi ( argv[2] );
    Installer_Clavier_Interruption ();
    Installer_Timer_Interruption ();
    Activer_Ecran ();
    Lire_Palette ("SPRFILES/COULEURS.PAL");
    randomize();
    Lancer_Jeu ();
    Desactiver_Ecran ();
    Desinstaller_Timer_Interruption ();
    Desinstaller_Clavier_Interruption ();
}
void Lancer_Jeu (void)
{
    BOOL jouable;
    OCTET stop;
    OCTET fin_partie;
    OCTET fin_tableau;
    OCTET page;
    OCTET page_active;
    OCTET page_cachee;
    char cpttab;
    char buftab [50];
    Definir_Bobs ();
    Ini_Score (0);
    Ini_Vies (NB_VIE-1);
    page_active = PAGE0;
    page_cachee = PAGE1;
    Afficher_Page (page_active);
    if (numero_tableau == -1)
    {
        Trier_Nombre_Aleatoire (buftab,(short)(48));
        cpttab = 0;
    }
    else
    {
        for (cpttab = 0;
                cpttab <= 49;
                cpttab ++)
            buftab [cpttab] = cpttab;
        cpttab = numero_tableau;
    }
    numero_tableau = buftab [cpttab];
    jouable = Verifier_Jouabilite_Tableau (numero_tableau);
    if (jouable == FAUX)
    {
        cpttab = Prochain_Tableau (buftab,&cpttab);
        numero_tableau = buftab [cpttab];
    }
    fin_partie = FAUX;
    jouable = VRAI;
    while ( (jouable == VRAI) & (fin_partie == FAUX) )
    {
        Appeler_Tableau (numero_tableau,page_active,page_cachee);
        Clignoter_Serpent_Blanc (page_active,page_cachee);
        do
        {
            fin_tableau = FAUX;
            page = page_cachee;
            stop = Animer_Serpents (&page);
            page_active = page;
            page_cachee = (page == 0) ? 1 : 0;
            switch (stop)
            {
            case 1 :
            {
                Afficher_Tous_Serpents (page_active);
                Afficher_Boite_Info (page_active,ECHAP);
                do
                {
                    if ( Lire_Code_Touche () == TOUCHE_C )
                    {
                        Effacer_Boite (page_active);
                        break;
                    }
                    if ( Lire_Code_Touche () == TOUCHE_R )
                    {
                        Effacer_Boite (page_active);
                        if (Lir_Vies () > 0)
                        {
                            Dec_Vies (1);
                            Rappeler_Tableau (numero_tableau,page_active,page_cachee);
                            Clignoter_Serpent_Blanc (page_active,page_cachee);
                        }
                        else
                        {
                            fin_tableau = VRAI;
                            fin_partie = VRAI;
                        }
                        break;
                    }
                    if ( Lire_Code_Touche () == TOUCHE_Q )
                    {
                        Effacer_Boite (page_active);
                        fin_tableau = VRAI;
                        fin_partie = VRAI;
                        break;
                    }
                }
                while (1);
                break;
            }
            case 2 :
            {
                Afficher_Tous_Serpents (page_active);
                Clignoter_Tous_Serpent (page_active,page_cachee);
                if (Lir_Vies () > 0)
                {
                    Dec_Vies (1);
                    Rappeler_Tableau (numero_tableau,page_active,page_cachee);
                    Clignoter_Serpent_Blanc (page_active,page_cachee);
                }
                else
                {
                    fin_tableau = VRAI;
                    fin_partie = VRAI;
                }
                break;
            }
            case 3 :
            {
                Afficher_Tous_Serpents (page_active);
                Clignoter_Tous_Serpent (page_active,page_cachee);
                if (Lir_Vies () > 0)
                {
                    Dec_Vies (1);
                    Rappeler_Tableau (numero_tableau,page_active,page_cachee);
                    Clignoter_Serpent_Blanc (page_active,page_cachee);
                }
                else
                {
                    fin_tableau = VRAI;
                    fin_partie = VRAI;
                }
                break;
            }
            case 4 :
            {
                Afficher_Tous_Serpents (page_active);
                Afficher_Serpent (page_active,NIBBLE,BOB_SERPENT_BLANC);
                Clignoter_Tous_Serpent (page_active,page_cachee);
                if (Lir_Vies () > 0)
                {
                    Dec_Vies (1);
                    Rappeler_Tableau (numero_tableau,page_active,page_cachee);
                    Clignoter_Serpent_Blanc (page_active,page_cachee);
                }
                else
                {
                    fin_tableau = VRAI;
                    fin_partie = VRAI;
                }
                break;
            }
            case 5 :
            {
                Afficher_Tous_Serpents (page_active);
                Clignoter_Tous_Serpent (page_active,page_cachee);
                if (Lir_Vies () > 0)
                {
                    Dec_Vies (1);
                    Rappeler_Tableau (numero_tableau,page_active,page_cachee);
                    Clignoter_Serpent_Blanc (page_active,page_cachee);
                }
                else
                {
                    fin_tableau = VRAI;
                    fin_partie = VRAI;
                }
                break;
            }
            case 6 :
            {
                fin_tableau = VRAI;
                fin_partie = VRAI;
                break;
            }
            case 7 :
            {
                Clignoter_Tableau (page_active,page_cachee);
                Afficher_Boite_Info (page_active,BONUS);
                do {}
                while (Lire_Code_Touche () != ESPACE);
                Effacer_Boite (page_active);
                cpttab = Prochain_Tableau (buftab,&cpttab);
                if (cpttab > 48)
                    jouable = FAUX;
                else
                    numero_tableau = buftab [cpttab];
                fin_tableau = VRAI;
                break;
            }
            case 8 :
            {
                Afficher_Tous_Serpents (page_active);
                Clignoter_Tous_Serpent (page_active,page_cachee);
                if (Lir_Vies () > 0)
                {
                    Dec_Vies (1);
                    Rappeler_Tableau (numero_tableau,page_active,page_cachee);
                    Clignoter_Serpent_Blanc (page_active,page_cachee);
                }
                else
                {
                    fin_tableau = VRAI;
                    fin_partie = VRAI;
                }
                break;
            }
            case 9 :
            {
                Afficher_Tous_Serpents (page_active);
                Afficher_Boite_Info (page_active,PAUSE);
                do {}
                while (Lire_Code_Touche () != ESPACE);
                Effacer_Boite (page_active);
                break;
            }
            }
        }
        while (fin_tableau == FAUX);
    }
    Cls (page_active);
    Cls (page_cachee);
    Sauver_Filedata (Lir_Score(),numero_tableau);
    Afficher_Boite_Info (page_active,FIN_PARTIE);
    do {}
    while (Lire_Code_Touche () != ESPACE);
    Effacer_Boite (page_active);
    Supprimer_Bobs ();
}
