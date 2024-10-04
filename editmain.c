#include <STDIO.H>
#include <CONIO.H>
#include <TIME.H>
#include <STRING.H>
#include <STDLIB.H>
#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITBOIT.H"
#include "SOUREDIT/EDITCHAR.H"
void Panneau_1 (void);
void Panneau_2 (void);
void Panneau_3 (void);
void Panneau_4 (void);
void Panneau_5 (void);
void Panneau_6 (void);
void Panneau_7 (void);
void Panneau_8 (void);
extern char NOM_TABLEAU [];
void main (int argc,char *argv [])
{
    BOOL etat;
    if (argc != 2)
    {
        printf ("Erreur d'appel.\n");
        exit (0);
    }
    Activer_Ecran ();
    Afficher_Page (0);
    Lire_Palette ("SPRFILES/COULEURS.PAL");
    Definir_Bobs ();
    if (Activer_Souris () == FAUX)
    {
        Supprimer_Bobs ();
        Desactiver_Ecran ();
        printf ("Pas de souris ou pas de driver souris installe.\n");
        printf ("<Appuyer sur une touche>\n");
        getch();
        exit (EXIT_SUCCESS);
    }
    Sauver_Fond ();
    Afficher_Souris ();
    etat = Verifier_Repertoire_Tableaux (PAGE0,argv[1]);
    if (etat == FAUX)
    {
        Supprimer_Bobs ();
        Desactiver_Souris ();
        Desactiver_Ecran ();
        exit (EXIT_SUCCESS);
    }
    strcpy (NOM_TABLEAU,argv[1]);
    strcat (NOM_TABLEAU,"/level");
    Afficher_Boite_Message (PAGE0,INFO14);
    Verifier_Tableaux (PAGE1);
    Ecrire_Panneau_Demande (1);
    Ecrire_Panneau_Encours (0);
    Ecrire_Tableau_Encours (1);
    Effacer_Boite (PAGE0);
    Cls (PAGE1,BOB_BLOC_NOIR);
    randomize();
    do
    {
        if (Lire_Panneau_Demande () == 1) Panneau_1 ();
        if (Lire_Panneau_Demande () == 2) Panneau_2 ();
        if (Lire_Panneau_Demande () == 3) Panneau_3 ();
        if (Lire_Panneau_Demande () == 4) Panneau_4 ();
        if (Lire_Panneau_Demande () == 5) Panneau_5 ();
        if (Lire_Panneau_Demande () == 6) Panneau_6 ();
        if (Lire_Panneau_Demande () == 7) Panneau_7 ();
        if (Lire_Panneau_Demande () == 8) Panneau_8 ();
    }
    while (Lire_Panneau_Demande () != 9);
    Supprimer_Bobs ();
    Desactiver_Souris ();
    Desactiver_Ecran ();
}
