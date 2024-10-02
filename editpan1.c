#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITONGL.H"
#include "SOUREDIT/EDITBOIT.H"
void Afficher_Numero (short,short,short);
short Tester_Zone_Tableaux (void);
void Option_Lire_Tableau (void);
void Option_Initialiser_Tableau (void);
void Option_Copier_Tableau (void);
void Option_Permuter_Tableau (void);
void Option_Verifier_Tableau (void);
void Option_About (void);
void Panneau_1 (void)
{
    short cpt;
    OCTET page;
    Ecrire_Panneau_Encours (Lire_Panneau_Demande () );
    Ecrire_Panneau_Demande (0);
    page = (Lire_Page () == 0) ? 1 : 0;
    Afficher_Onglet (page,ONGLET1);
    for (cpt = 1 ; cpt <= 48 ; cpt ++) Afficher_Mini_Tableau (page,cpt);
    Changer_Page (page);
    Afficher_Numero (Lire_Tableau_Encours (),X1_NUM_CHARGER,Y1_NUM_CHARGER);
    do
    {
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_CHARGER,
                             Y_MIN_CHARGER,
                             X_MAX_CHARGER,
                             Y_MAX_CHARGER) == ON)
            Option_Lire_Tableau ();
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_INITIALISER,
                             Y_MIN_INITIALISER,
                             X_MAX_INITIALISER,
                             Y_MAX_INITIALISER) == ON)
            Option_Initialiser_Tableau ();
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_COPIER,
                             Y_MIN_COPIER,
                             X_MAX_COPIER,
                             Y_MAX_COPIER) == ON)
            Option_Copier_Tableau ();
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_PERMUTER,
                             Y_MIN_PERMUTER,
                             X_MAX_PERMUTER,
                             Y_MAX_PERMUTER) == ON)
            Option_Permuter_Tableau ();
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_VERIFIER,
                             Y_MIN_VERIFIER,
                             X_MAX_VERIFIER,
                             Y_MAX_VERIFIER) == ON)
            Option_Verifier_Tableau ();
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_ANALYSER,
                             Y_MIN_ANALYSER,
                             X_MAX_ANALYSER,
                             Y_MAX_ANALYSER) == ON)
            Option_About ();
    }
    while (Lire_Panneau_Demande () == 0);
}
void Afficher_Numero (short numero,short x,short y)
{
    Souris (OFF);
    Afficher_Nombre (Lire_Page (),BOB_CHIFFRE,2,numero,x,y,MASK_OFF);
    Souris (ON);
}
short Tester_Zone_Tableaux (void)
{
    short rep;
    OCTET tabx;
    OCTET taby;
    OCTET cptx;
    OCTET cpty;
    tabx = OFF;
    taby = OFF;
    for (cptx = 0;
            cptx <= 5;
            cptx ++)
    {
        if ( X_Fleche () >= (X_TABLEAUX + (cptx * X_ECART)) )
        {
            if ( X_Fleche () <= (X_TABLEAUX + (cptx * X_ECART) + LG_TABLEAU) )
            {
                tabx = ON;
                break;
            }
        }
    }
    for (cpty = 0;
            cpty <= 7;
            cpty ++)
    {
        if ( Y_Fleche () >= (Y_TABLEAUX + (cpty * Y_ECART)) )
        {
            if ( Y_Fleche () <= (Y_TABLEAUX + (cpty * Y_ECART) + HT_TABLEAU) )
            {
                taby = ON;
                break;
            }
        }
    }
    if ( (tabx == ON) & (taby == ON) )
        rep = (NB_TABLEAU_X * cpty) + (cptx + 1);
    else
        rep = 0;
    return (rep);
}
void Option_Lire_Tableau (void)
{
    short num_tableau;
    num_tableau = 0;
    Option (OFF,Lire_Page (),X_MIN_CHARGER,Y_MIN_CHARGER,
            X_MAX_CHARGER,Y_MAX_CHARGER);
    WAIT_NO_CLIC;
    do
    {
        if (Clic_Souris () == CLIC_GAUCHE)
            num_tableau = Tester_Zone_Tableaux ();
    }
    while ( num_tableau == 0 );
    WAIT_NO_CLIC;
    Option (ON,Lire_Page (),X_MIN_CHARGER,Y_MIN_CHARGER,
            X_MAX_CHARGER,Y_MAX_CHARGER);
    Ecrire_Tableau_Encours (num_tableau);
    Afficher_Numero (num_tableau,X1_NUM_CHARGER,Y1_NUM_CHARGER);
    Ecrire_Panneau_Demande (0);
}
void Option_Initialiser_Tableau (void)
{
    OCTET page;
    short num_tableau;
    OCTET reponse;
    num_tableau = 0;
    page = Lire_Page ();
    Option (OFF,page,X_MIN_INITIALISER,Y_MIN_INITIALISER,
            X_MAX_INITIALISER,Y_MAX_INITIALISER);
    WAIT_NO_CLIC;
    do
    {
        if (Clic_Souris () == CLIC_GAUCHE)
            num_tableau = Tester_Zone_Tableaux ();
    }
    while ( num_tableau == 0 );
    WAIT_NO_CLIC;
    Option (ON,page,X_MIN_INITIALISER,Y_MIN_INITIALISER,
            X_MAX_INITIALISER,Y_MAX_INITIALISER);
    Afficher_Numero (num_tableau,X1_NUM_INITIALISER,Y1_NUM_INITIALISER);
    Afficher_Boite_Message (page,INFO01);
    Nombre_Option (INFO01_NB,page,2,num_tableau);
    reponse = RIEN;
    do
    {
        if ( Test_Option (INFO01_OUI) == ON )
        {
            reponse = OUI;
            Option (OFF,page,INFO01_OUI);
            WAIT_NO_CLIC;
            Option (ON,page,INFO01_OUI);
        }
        if ( Test_Option (INFO01_NON) == ON )
        {
            reponse = NON;
            Option (OFF,page,INFO01_NON);
            WAIT_NO_CLIC;
            Option (ON,page,INFO01_NON);
        }
    }
    while (reponse == RIEN);
    Effacer_Boite (page);
    if (reponse == OUI)
    {
        Initialiser_Tableau (num_tableau);
        Souris (OFF);
        Afficher_Mini_Tableau (page,num_tableau);
        Souris (ON);
    }
    Ecrire_Panneau_Demande (0);
}
void Option_Copier_Tableau (void)
{
    OCTET page;
    OCTET reponse;
    short tab1;
    short tab2;
    tab1 = 0;
    tab2 = 0;
    page = Lire_Page ();
    Option (OFF,page,X_MIN_COPIER,Y_MIN_COPIER,
            X_MAX_COPIER,Y_MAX_COPIER);
    WAIT_NO_CLIC;
    do
    {
        if (Clic_Souris () == CLIC_GAUCHE)
            tab1 = Tester_Zone_Tableaux ();
    }
    while ( tab1 == 0 );
    WAIT_NO_CLIC;
    Option (ON,page,X_MIN_COPIER,Y_MIN_COPIER,
            X_MAX_COPIER,Y_MAX_COPIER);
    Afficher_Numero (tab1,X1_NUM_COPIER,Y1_NUM_COPIER);
    Option (OFF,page,X_MIN_COPIER,Y_MIN_COPIER,
            X_MAX_COPIER,Y_MAX_COPIER);
    WAIT_NO_CLIC;
    do
    {
        if (Clic_Souris () == CLIC_GAUCHE)
            tab2 = Tester_Zone_Tableaux ();
    }
    while ( (tab2 == 0) | (tab2 == tab1) );
    WAIT_NO_CLIC;
    Option (ON,page,X_MIN_COPIER,Y_MIN_COPIER,
            X_MAX_COPIER,Y_MAX_COPIER);
    Afficher_Numero (tab2,X2_NUM_COPIER,Y2_NUM_COPIER);
    Afficher_Boite_Message (page,INFO01);
    Nombre_Option (INFO01_NB,page,2,tab2);
    reponse = RIEN;
    do
    {
        if ( Test_Option (INFO01_OUI) == ON )
        {
            reponse = OUI;
            Option (OFF,page,INFO01_OUI);
            WAIT_NO_CLIC;
            Option (ON,page,INFO01_OUI);
        }
        if ( Test_Option (INFO01_NON) == ON )
        {
            reponse = NON;
            Option (OFF,page,INFO01_NON);
            WAIT_NO_CLIC;
            Option (ON,page,INFO01_NON);
        }
    }
    while (reponse == RIEN);
    Effacer_Boite (page);
    if (reponse == OUI)
    {
        Copier_Tableau (tab1,tab2);
        Souris (OFF);
        Afficher_Mini_Tableau (page,
                               tab2);
        Souris (ON);
    }
    Ecrire_Panneau_Demande (0);
}
void Option_Permuter_Tableau (void)
{
    short tab1;
    short tab2;
    tab1 = 0;
    tab2 = 0;
    Option (OFF,Lire_Page (),X_MIN_PERMUTER,Y_MIN_PERMUTER,
            X_MAX_PERMUTER,Y_MAX_PERMUTER);
    WAIT_NO_CLIC;
    do
    {
        if (Clic_Souris () == CLIC_GAUCHE)
            tab1 = Tester_Zone_Tableaux ();
    }
    while ( tab1 == 0 );
    WAIT_NO_CLIC;
    Option (ON,Lire_Page (),X_MIN_PERMUTER,Y_MIN_PERMUTER,
            X_MAX_PERMUTER,Y_MAX_PERMUTER);
    Afficher_Numero (tab1,X1_NUM_PERMUTER,Y1_NUM_PERMUTER);
    Option (OFF,Lire_Page (),X_MIN_PERMUTER,Y_MIN_PERMUTER,
            X_MAX_PERMUTER,Y_MAX_PERMUTER);
    WAIT_NO_CLIC;
    do
    {
        if (Clic_Souris () == CLIC_GAUCHE)
            tab2 = Tester_Zone_Tableaux ();
    }
    while ( (tab2 == 0) | (tab2 == tab1) );
    WAIT_NO_CLIC;
    Option (ON,Lire_Page (),X_MIN_PERMUTER,Y_MIN_PERMUTER,
            X_MAX_PERMUTER,Y_MAX_PERMUTER);
    Afficher_Numero (tab2,X2_NUM_PERMUTER,Y2_NUM_PERMUTER);
    Permuter_Tableau (tab1,tab2);
    Souris (OFF);
    Afficher_Mini_Tableau (Lire_Page (),
                           tab1);
    Afficher_Mini_Tableau (Lire_Page (),
                           tab2);
    Souris (ON);
    Ecrire_Panneau_Demande (0);
}
void Option_Verifier_Tableau (void)
{
    OCTET page;
    BOOL etat;
    OCTET sortie;
    short num_tableau;
    num_tableau = 0;
    sortie = OFF;
    page = Lire_Page ();
    Option (OFF,page,X_MIN_VERIFIER,Y_MIN_VERIFIER,
            X_MAX_VERIFIER,Y_MAX_VERIFIER);
    WAIT_NO_CLIC;
    do
    {
        if (Clic_Souris () == CLIC_GAUCHE)
            num_tableau = Tester_Zone_Tableaux ();
    }
    while ( num_tableau == 0 );
    WAIT_NO_CLIC;
    Option (ON,page,X_MIN_VERIFIER,Y_MIN_VERIFIER,
            X_MAX_VERIFIER,Y_MAX_VERIFIER);
    Afficher_Numero (num_tableau,X1_NUM_VERIFIER,Y1_NUM_VERIFIER);
    etat = Verifier_Jouabilite_Tableau (num_tableau);
    if (etat == VRAI)
    {
        Afficher_Boite_Message (page,INFO11);
        do
        {
            if ( Test_Option (INFO11_OK) == ON )
            {
                sortie = ON;
                Option (OFF,page,INFO11_OK);
                WAIT_NO_CLIC;
                Option (ON,page,INFO11_OK);
            }
        }
        while (sortie == OFF);
    }
    else
    {
        Afficher_Boite_Message (page,INFO12);
        do
        {
            if ( Test_Option (INFO12_OK) == ON )
            {
                sortie = ON;
                Option (OFF,page,INFO12_OK);
                WAIT_NO_CLIC;
                Option (ON,page,INFO12_OK);
            }
        }
        while (sortie == OFF);
    }
    Effacer_Boite (page);
    Ecrire_Panneau_Demande (0);
}
void Option_About (void)
{
    OCTET sortie;
    OCTET page;
    sortie = OFF;
    page = Lire_Page ();
    Option (OFF,page,X_MIN_ANALYSER,Y_MIN_ANALYSER,
            X_MAX_ANALYSER,Y_MAX_ANALYSER);
    WAIT_NO_CLIC;
    Option (ON,page,X_MIN_ANALYSER,Y_MIN_ANALYSER,
            X_MAX_ANALYSER,Y_MAX_ANALYSER);
    Afficher_Boite_Message (page,INFO13);
    do
    {
        if ( Test_Option (INFO13_OK) == ON )
        {
            sortie = ON;
            Option (OFF,page,INFO13_OK);
            WAIT_NO_CLIC;
            Option (ON,page,INFO13_OK);
        }
    }
    while (sortie == OFF);
    Effacer_Boite (page);
    Ecrire_Panneau_Demande (0);
}
