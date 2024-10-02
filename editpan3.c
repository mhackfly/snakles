#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITBOIT.H"
#include "SOUREDIT/EDITONGL.H"
void Afficher_Serpents_Ecran (void);
void Saisir_Parametres_Serpents (void);
void Rechercher_Croisement_Serpents (void);
void Effacer_Serpents (void);
extern OCTET buftab1_sans_cadre [BUFSIZE_SANS_CADRE];
extern OCTET buftab2_sans_cadre [BUFSIZE_SANS_CADRE];
extern char incx [5];
extern char incy [5];
OCTET new_num_serpent;
OCTET old_num_serpent;
void Panneau_3 (void)
{
    OCTET nb_serpent;
    OCTET page;
    OCTET element;
    Lire_Tableau ( Lire_Tableau_Encours() );
    Lire_Buftab_Sans_Cadre (buftab1_sans_cadre);
    Convertir_Structure_Buffer ();
    Ecrire_Panneau_Encours (Lire_Panneau_Demande () );
    Ecrire_Panneau_Demande (0);
    page = (Lire_Page () == 0) ? 1 : 0;
    Afficher_Onglet (page,ONGLET3);
    Afficher_Nombre (page,BOB_CHIFFRE,2,0,310,13,MASK_OFF);
    Afficher_Nombre (page,BOB_CHIFFRE,2,0,310,20,MASK_OFF);
    Changer_Page (page);
    Afficher_Nombre(Lire_Page(),BOB_CHIFFRE,2,
                    (Lire_Lgnibble () == 0) ? Lire_Nbnibble_X():
                    Lire_Nbnibble_X()+1,
                    310,101,MASK_OFF);
    Activer_Zone_Croix (5,31,305,393);
    Afficher_Serpents_Ecran ();
    new_num_serpent = 1;
    old_num_serpent = 1;
    Selection_Pastille (new_num_serpent,ON);
    do
    {
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),3,14,306,26) == ON)
        {
            new_num_serpent = (X_Fleche () + 5 ) / 8;
            if (new_num_serpent != old_num_serpent)
            {
                if ( (new_num_serpent >=1) & (new_num_serpent <= NB_ELEMENT_ESQUISSE_SERPENT) )
                {
                    Selection_Pastille (old_num_serpent,OFF);
                    Selection_Pastille (new_num_serpent,ON);
                    old_num_serpent = new_num_serpent;
                    WAIT_NO_CLIC;
                    Ecrire_Panneau_Demande (0);
                }
                else
                    new_num_serpent = old_num_serpent;
            }
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),5,31,305,393) == ON)
        {
            if (Lire_Case(buftab2_sans_cadre,X_Case(),Y_Case()) != new_num_serpent)
            {
                element = Lire_Case(buftab1_sans_cadre,X_Case(),Y_Case());
                if ( !( (element >= 1) & (element <= 6) ) )
                {
                    Ecrire_Case (buftab2_sans_cadre,new_num_serpent,X_Case (),
                                 Y_Case ());
                    Souris (OFF);
                    Afficher_Case (BOB_SERPENTS,new_num_serpent,X_Case (),
                                   Y_Case ());
                    Souris (ON);
                }
            }
        }
        if ( Test_Zone (X_Fleche (),Y_Fleche (),5,31,305,393) == ON)
        {
            if (Clic_Souris () == CLIC_DROITE)
            {
                if (Lire_Case(buftab2_sans_cadre,X_Case(),Y_Case()) != 0)
                {
                    Ecrire_Case (buftab2_sans_cadre,0,X_Case (),Y_Case ());
                    element = Lire_Case(buftab1_sans_cadre,X_Case (),Y_Case ());
                    Souris (OFF);
                    Afficher_Case (BOB_PASTILLE,element,X_Case (),Y_Case ());
                    Souris (ON);
                }
            }
        }
        if (X_Case () != 0)
            Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,X_Case (),310,13,MASK_OFF);
        if (Y_Case () != 0)
            Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,Y_Case (),310,20,MASK_OFF);
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,86,319,99) == ON )
        {
            Option (OFF,Lire_Page (),309,86,319,99);
            WAIT_NO_CLIC;
            Convertir_Buffer_Structure ();
            Rechercher_Croisement_Serpents ();
            nb_serpent = Convertir_Buffer_Structure ();
            Souris (OFF);
            Afficher_Nombre(Lire_Page(),
                            BOB_CHIFFRE,2,
                            nb_serpent,
                            310,101,
                            MASK_OFF);
            Souris (ON);
            Convertir_Structure_Buffer ();
            Afficher_Serpents_Ecran ();
            Option (ON,Lire_Page (),309,86,319,99);
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,51,319,85) == ON )
        {
            Option (OFF,Lire_Page (),309,51,319,85);
            WAIT_NO_CLIC;
            Saisir_Parametres_Serpents ();
            Option (ON,Lire_Page (),309,51,319,85);
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,28,319,50) == ON )
        {
            Option (OFF,Lire_Page (),309,28,319,50);
            WAIT_NO_CLIC;
            Effacer_Serpents ();
            Option (ON,Lire_Page (),309,28,319,50);
        }
    }
    while (Lire_Panneau_Demande () == 0);
    Desactiver_Zone_Croix ();
    Convertir_Buffer_Structure ();
    Rechercher_Croisement_Serpents ();
    nb_serpent = Convertir_Buffer_Structure ();
    Afficher_Nombre(Lire_Page(),
                    BOB_CHIFFRE,2,
                    nb_serpent,
                    310,101,
                    MASK_OFF);
    Convertir_Structure_Buffer ();
    Afficher_Serpents_Ecran ();
    Sauver_Tableau (Lire_Tableau_Encours ());
}
void Saisir_Parametres_Serpents (void)
{
    OCTET sortie;
    OCTET page;
    OCTET nb_serpent;
    OCTET cpt_serpent;
    OCTET x_clic;
    OCTET y_clic;
    short val_tempo;
    page = Lire_Page ();
    Convertir_Buffer_Structure ();
    Rechercher_Croisement_Serpents ();
    nb_serpent = Convertir_Buffer_Structure ();
    Afficher_Nombre(page,BOB_CHIFFRE,2,
                    nb_serpent,310,101,MASK_OFF);
    Convertir_Structure_Buffer ();
    Afficher_Serpents_Ecran ();
    if (nb_serpent == 0) return;
    sortie = OFF;
    WAIT_CLIC_GAUCHE;
    WAIT_NO_CLIC;
    x_clic = X_Case ();
    y_clic = Y_Case ();
    if ( (x_clic < 1) | (x_clic > 43) | (y_clic < 1) | (y_clic >33) )
    {
        Ecrire_Panneau_Demande (0);
        return;
    }
    if ( (Lire_Xnibble () == x_clic) &
            (Lire_Ynibble () == y_clic) )
    {
        Afficher_Boite_Message (page,INFO03);
        if (Lire_Vtnibble () == 0) Option (OFF,page,INFO03_R);
        if (Lire_Vtnibble () == 1) Option (OFF,page,INFO03_N);
        if (Lire_Vtnibble () == 2) Option (OFF,page,INFO03_L);
        if (Lire_Spnibble () == 1) Option (OFF,page,INFO03_SO1);
        if (Lire_Spnibble () == 0) Option (OFF,page,INFO03_SO2);
        if (Lire_Mtnibble () == 1) Option (OFF,page,INFO03_MO1);
        if (Lire_Mtnibble () == 0) Option (OFF,page,INFO03_MO2);
        if (Lire_Flnibble () == 1) Option (OFF,page,INFO03_FL1);
        if (Lire_Flnibble () == 0) Option (OFF,page,INFO03_FL2);
        do
        {
            if ( Test_Option (INFO03_R) == ON )
            {
                Option (OFF,page,INFO03_R);
                Option (ON,page,INFO03_N);
                Option (ON,page,INFO03_L);
                WAIT_NO_CLIC;
                Ecrire_Vtnibble (0);
            }
            if ( Test_Option (INFO03_N) == ON )
            {
                Option (ON,page,INFO03_R);
                Option (OFF,page,INFO03_N);
                Option (ON,page,INFO03_L);
                WAIT_NO_CLIC;
                Ecrire_Vtnibble (1);
            }
            if ( Test_Option (INFO03_L) == ON )
            {
                Option (ON,page,INFO03_R);
                Option (ON,page,INFO03_N);
                Option (OFF,page,INFO03_L);
                WAIT_NO_CLIC;
                Ecrire_Vtnibble (2);
            }
            if ( Test_Option (INFO03_SO1) == ON )
            {
                Option (OFF,page,INFO03_SO1);
                Option (ON,page,INFO03_SO2);
                WAIT_NO_CLIC;
                Ecrire_Spnibble (1);
            }
            if ( Test_Option (INFO03_SO2) == ON )
            {
                Option (OFF,page,INFO03_SO2);
                Option (ON,page,INFO03_SO1);
                WAIT_NO_CLIC;
                Ecrire_Spnibble (0);
            }
            if ( Test_Option (INFO03_MO1) == ON )
            {
                Option (OFF,page,INFO03_MO1);
                Option (ON,page,INFO03_MO2);
                WAIT_NO_CLIC;
                Ecrire_Mtnibble (1);
            }
            if ( Test_Option (INFO03_MO2) == ON )
            {
                Option (OFF,page,INFO03_MO2);
                Option (ON,page,INFO03_MO1);
                WAIT_NO_CLIC;
                Ecrire_Mtnibble (0);
            }
            if ( Test_Option (INFO03_FL1) == ON )
            {
                Option (OFF,page,INFO03_FL1);
                Option (ON,page,INFO03_FL2);
                WAIT_NO_CLIC;
                Ecrire_Flnibble (1);
            }
            if ( Test_Option (INFO03_FL2) == ON )
            {
                Option (OFF,page,INFO03_FL2);
                Option (ON,page,INFO03_FL1);
                WAIT_NO_CLIC;
                Ecrire_Flnibble (0);
            }
            if ( Test_Option (INFO03_OK) == ON )
            {
                sortie = ON;
                Option (OFF,page,INFO03_OK);
                WAIT_NO_CLIC;
                Option (ON,page,INFO03_OK);
            }
        }
        while (sortie == OFF);
        Effacer_Boite (page);
    }
    for (cpt_serpent = 0;
            cpt_serpent < Lire_Nbnibble_X ();
            cpt_serpent ++)
    {
        if ( (Lire_Xnibble_X (cpt_serpent) == x_clic) &
                (Lire_Ynibble_X (cpt_serpent) == y_clic) )
        {
            Afficher_Boite_Message (page,INFO02);
            if (Lire_Vtnibble_X (cpt_serpent)==0) Option (OFF,page,INFO02_R);
            if (Lire_Vtnibble_X (cpt_serpent)==1) Option (OFF,page,INFO02_N);
            if (Lire_Vtnibble_X (cpt_serpent)==2) Option (OFF,page,INFO02_L);
            if (Lire_Vtnibble_X (cpt_serpent)==255) Option (OFF,page,INFO02_A);
            Nombre_Option (INFO02_NB,page,INFO02_LGNB,
                           Lire_Tpnibble_X (cpt_serpent));
            do
            {
                if ( Test_Option (INFO02_R) == ON )
                {
                    Option (OFF,page,INFO02_R);
                    Option (ON,page,INFO02_N);
                    Option (ON,page,INFO02_L);
                    Option (ON,page,INFO02_A);
                    WAIT_NO_CLIC;
                    Ecrire_Vtnibble_X (cpt_serpent,0);
                }
                if ( Test_Option (INFO02_N) == ON )
                {
                    Option (ON,page,INFO02_R);
                    Option (OFF,page,INFO02_N);
                    Option (ON,page,INFO02_L);
                    Option (ON,page,INFO02_A);
                    WAIT_NO_CLIC;
                    Ecrire_Vtnibble_X (cpt_serpent,1);
                }
                if ( Test_Option (INFO02_L) == ON )
                {
                    Option (ON,page,INFO02_R);
                    Option (ON,page,INFO02_N);
                    Option (OFF,page,INFO02_L);
                    Option (ON,page,INFO02_A);
                    WAIT_NO_CLIC;
                    Ecrire_Vtnibble_X (cpt_serpent,2);
                }
                if ( Test_Option (INFO02_A) == ON )
                {
                    Option (ON,page,INFO02_R);
                    Option (ON,page,INFO02_N);
                    Option (ON,page,INFO02_L);
                    Option (OFF,page,INFO02_A);
                    WAIT_NO_CLIC;
                    Ecrire_Vtnibble_X (cpt_serpent,255);
                }
                if ( Test_Option (INFO02_GAUCHE) == ON )
                {
                    val_tempo = Traiter_Fleche (page,DEC,
                                                Lire_Tpnibble_X (cpt_serpent),
                                                INFO02_MIN,
                                                INFO02_MAX,
                                                INFO02_GAUCHE,
                                                INFO02_NB,
                                                INFO02_LGNB);
                    Ecrire_Tpnibble_X (cpt_serpent,val_tempo);
                }
                if ( Test_Option (INFO02_DROITE) == ON )
                {
                    val_tempo = Traiter_Fleche (page,INC,
                                                Lire_Tpnibble_X (cpt_serpent),
                                                INFO02_MIN,
                                                INFO02_MAX,
                                                INFO02_DROITE,
                                                INFO02_NB,
                                                INFO02_LGNB);
                    Ecrire_Tpnibble_X (cpt_serpent,val_tempo);
                }
                if ( Test_Option (INFO02_OK) == ON )
                {
                    sortie = ON;
                    Option (OFF,page,INFO02_OK);
                    WAIT_NO_CLIC;
                    Option (ON,page,INFO02_OK);
                }
            }
            while (sortie == OFF);
            Effacer_Boite (page);
        }
    }
    Ecrire_Panneau_Demande (0);
}
void Afficher_Serpents_Ecran (void)
{
    OCTET cpt_x;
    OCTET cpt_y;
    short x_bob;
    short y_bob;
    OCTET forme;
    Souris (OFF);
    for (cpt_y = 1;
            cpt_y <= 33;
            cpt_y ++)
    {
        for (cpt_x = 1;
                cpt_x <= 43;
                cpt_x ++)
        {
            x_bob = X_TAB_PASTILLES_SERPENTS + ( (cpt_x - 1) * SERPENT_LONG );
            y_bob = Y_TAB_PASTILLES_SERPENTS + ( (cpt_y - 1) * SERPENT_HAUT );
            forme = Lire_Case (buftab2_sans_cadre,cpt_x,cpt_y);
            if (forme != 0)
            {
                Afficher_Bob (Lire_Page (),FOND_1,x_bob,y_bob,MASK_ON);
                Afficher_Bob (Lire_Page(),forme + (BOB_SERPENTS - 1),
                              x_bob,y_bob,MASK_ON);
            }
            else
            {
                forme = Lire_Case (buftab1_sans_cadre,cpt_x,cpt_y);
                if (forme != 0)
                {
                    Afficher_Bob (Lire_Page (),FOND_1,x_bob,y_bob,MASK_ON);
                    Afficher_Bob (Lire_Page (),forme + (BOB_PASTILLE - 1),
                                  x_bob,y_bob,MASK_ON);
                }
                else
                    Afficher_Bob (Lire_Page (),FOND_1,x_bob,y_bob,MASK_ON);
            }
        }
    }
    Souris (ON);
}
void Rechercher_Croisement_Serpents (void)
{
    OCTET position_x [NB_SERPENT_RVB * (LG_SERPENTS+2)];
    OCTET position_y [NB_SERPENT_RVB * (LG_SERPENTS+2)];
    short cpt_position_test;
    short cpt_positions;
    short nb_position;
    OCTET x,y;
    OCTET cptnb_serpent_rvb;
    OCTET cptlg_serpent_rvb;
    OCTET dr_serpent_rvb;
    OCTET lg_serpent_rvb;
    OCTET nb_serpent_rvb;
    nb_serpent_rvb = Lire_Nbnibble_X ();
    if (nb_serpent_rvb == 0) return;
    cpt_positions = 0;
    for (cptnb_serpent_rvb = 0;
            cptnb_serpent_rvb < nb_serpent_rvb;
            cptnb_serpent_rvb ++)
    {
        x = Lire_Xnibble_X (cptnb_serpent_rvb);
        y = Lire_Ynibble_X (cptnb_serpent_rvb);
        position_x [cpt_positions] = x;
        position_y [cpt_positions] = y;
        cpt_positions ++;
        lg_serpent_rvb = Lire_Lgnibble_X (cptnb_serpent_rvb);
        dr_serpent_rvb = Lire_Drnibble_X (cptnb_serpent_rvb);
        for (cptlg_serpent_rvb = 0;
                cptlg_serpent_rvb < lg_serpent_rvb;
                cptlg_serpent_rvb ++)
        {
            x += incx [dr_serpent_rvb];
            y += incy [dr_serpent_rvb];
            position_x [cpt_positions] = x;
            position_y [cpt_positions] = y;
            cpt_positions ++;
        }
        x += incx [dr_serpent_rvb];
        y += incy [dr_serpent_rvb];
        position_x [cpt_positions] = x;
        position_y [cpt_positions] = y;
        cpt_positions ++;
    }
    nb_position = cpt_positions;
    for (cpt_position_test = 0;
            cpt_position_test < nb_position;
            cpt_position_test ++)
    {
        for (cpt_positions = 0;
                cpt_positions < nb_position;
                cpt_positions ++)
        {
            if (cpt_position_test != cpt_positions)
            {
                x = position_x [cpt_position_test];
                y = position_y [cpt_position_test];
                if ( (x==position_x[cpt_positions]) & (y==position_y [cpt_positions]) )
                    Ecrire_Case (buftab2_sans_cadre,0,x,y);
            }
        }
    }
}
void Effacer_Serpents (void)
{
    OCTET page;
    OCTET nb_serpent;
    OCTET lg_serpent;
    OCTET cpt_serpent;
    OCTET reponse;
    OCTET x,y;
    page = Lire_Page ();
    Convertir_Buffer_Structure ();
    Rechercher_Croisement_Serpents ();
    nb_serpent = Convertir_Buffer_Structure ();
    Afficher_Nombre(page,BOB_CHIFFRE,2,
                    nb_serpent,310,101,MASK_OFF);
    Convertir_Structure_Buffer ();
    Afficher_Serpents_Ecran ();
    if (nb_serpent == 0) return;
    Afficher_Boite_Message (page,INFO06);
    reponse = RIEN;
    do
    {
        if ( Test_Option (INFO06_OUI) == ON )
        {
            reponse = OUI;
            Option (OFF,page,INFO06_OUI);
            WAIT_NO_CLIC;
            Option (ON,page,INFO06_OUI);
        }
        if ( Test_Option (INFO06_NON) == ON )
        {
            reponse = NON;
            Option (OFF,page,INFO06_NON);
            WAIT_NO_CLIC;
            Option (ON,page,INFO06_NON);
        }
    }
    while (reponse == RIEN);
    Effacer_Boite (page);
    if (reponse == OUI)
    {
        lg_serpent = Lire_Lgnibble ();
        if (lg_serpent != 0)
        {
            x = Lire_Xnibble ();
            y = Lire_Ynibble ();
            Ecrire_Case (buftab2_sans_cadre,0,x,y);
        }
        nb_serpent = Lire_Nbnibble_X ();
        for (cpt_serpent = 0;
                cpt_serpent < nb_serpent;
                cpt_serpent ++)
        {
            x = Lire_Xnibble_X (cpt_serpent);
            y = Lire_Ynibble_X (cpt_serpent);
            Ecrire_Case (buftab2_sans_cadre,0,x,y);
        }
        nb_serpent = Convertir_Buffer_Structure ();
        Afficher_Nombre(page,BOB_CHIFFRE,2,
                        nb_serpent,310,101,MASK_OFF);
        Convertir_Structure_Buffer ();
        Afficher_Serpents_Ecran ();
    }
    Ecrire_Panneau_Demande (0);
}
