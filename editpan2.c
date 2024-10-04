#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITONGL.H"
void Rechercher_Portes (void);
extern OCTET buftab1_sans_cadre [BUFSIZE_SANS_CADRE];
OCTET new_numero_pastille;
OCTET old_numero_pastille;
OCTET backup_new_numero_pastille;
OCTET Numero_Pastille (void)
{
    return (new_numero_pastille);
}
void Panneau_2 (void)
{
    short nbpastilles;
    OCTET page;
    Lire_Tableau (Lire_Tableau_Encours());
    Lire_Buftab_Sans_Cadre (buftab1_sans_cadre);
    Save_Undo ();
    Load_Undo ();
    Ecrire_Panneau_Encours (Lire_Panneau_Demande () );
    Ecrire_Panneau_Demande (0);
    page = (Lire_Page () == 0) ? 1 : 0;
    Afficher_Onglet (page,ONGLET2);
    Afficher_Nombre (page,BOB_CHIFFRE,2,0,310,13,MASK_OFF);
    Afficher_Nombre (page,BOB_CHIFFRE,2,0,310,20,MASK_OFF);
    Changer_Page (page);
    Activer_Zone_Croix (5,31,305,393);
    Afficher_Cases (buftab1_sans_cadre,BOB_PASTILLE-1,1,1,43,33);
    new_numero_pastille = 1;
    old_numero_pastille = 1;
    Selection_Pastille (new_numero_pastille,ON);
    Initialiser_Outils ();
    do
    {
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),3,14,306,26) == ON)
        {
            new_numero_pastille = (X_Fleche () + 5 ) / 8;
            if (new_numero_pastille != old_numero_pastille)
            {
                if ( (new_numero_pastille >=1) & (new_numero_pastille <= MAX_PASTILLE) )
                {
                    Selection_Pastille (old_numero_pastille,OFF);
                    Selection_Pastille (new_numero_pastille,ON);
                    old_numero_pastille = new_numero_pastille;
                    WAIT_NO_CLIC;
                    Ecrire_Panneau_Demande (0);
                }
                else
                    new_numero_pastille = old_numero_pastille;
            }
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),5,31,305,393) == ON)
        {
            Appeler_Outils ();
        }
        if ( Test_Zone (X_Fleche (),Y_Fleche (),5,31,305,393) == ON)
        {
            if (Clic_Souris () == CLIC_DROITE)
            {
                backup_new_numero_pastille = new_numero_pastille;
                new_numero_pastille = 0;
                Appeler_Outils ();
                new_numero_pastille = backup_new_numero_pastille;
            }
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,28,319,397) == ON )
        {
            Traiter_Outils ();
        }
        if (X_Case () != 0)
            Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,X_Case (),310,13,MASK_OFF);
        if (Y_Case () != 0)
            Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,Y_Case (),310,20,MASK_OFF);
    }
    while (Lire_Panneau_Demande () == 0);
    Desactiver_Zone_Croix ();
    Ecrire_Buftab_Sans_Cadre (buftab1_sans_cadre);
    Verifier_Corriger_Dessin ();
    Rechercher_Portes ();
    nbpastilles = Totaliser_Pastilles (OBST_BOULE_BLEU);
    Ecrire_Nombre_Pastille (nbpastilles);
    Convertir_Structure_Buffer ();
    Rechercher_Conflit_Serpents_Bord ();
    Convertir_Buffer_Structure ();
    Sauver_Tableau (Lire_Tableau_Encours ());
}
void Rechercher_Portes (void)
{
    OCTET cpt_x;
    OCTET cpt_y;
    OCTET pastille;
    short nb_porte;
    Ecrire_Nbporterouge (0);
    Ecrire_Nbporteverte (0);
    Ecrire_Nbportebleue (0);
    for (cpt_y = 1;
            cpt_y <= 33;
            cpt_y ++)
    {
        for (cpt_x = 1;
                cpt_x <= 43;
                cpt_x ++)
        {
            pastille = Lire_Case (buftab1_sans_cadre,cpt_x,cpt_y);
            if ( (pastille == OBST_PORTE_ROUGE_FERMEE ) |
                    (pastille == OBST_PORTE_ROUGE_OUVERTE) )
            {
                nb_porte = Lire_Nbporterouge ();
                Ecrire_Xporterouge (nb_porte,cpt_x);
                Ecrire_Yporterouge (nb_porte,cpt_y);
                nb_porte ++;
                Ecrire_Nbporterouge (nb_porte);
            }
            if ( (pastille == OBST_PORTE_VERTE_FERMEE ) |
                    (pastille == OBST_PORTE_VERTE_OUVERTE) )
            {
                nb_porte = Lire_Nbporteverte ();
                Ecrire_Xporteverte (nb_porte,cpt_x);
                Ecrire_Yporteverte (nb_porte,cpt_y);
                nb_porte ++;
                Ecrire_Nbporteverte (nb_porte);
            }
            if ( (pastille == OBST_PORTE_BLEU_FERMEE ) |
                    (pastille == OBST_PORTE_BLEU_OUVERTE) )
            {
                nb_porte = Lire_Nbportebleue ();
                Ecrire_Xportebleue (nb_porte,cpt_x);
                Ecrire_Yportebleue (nb_porte,cpt_y);
                nb_porte ++;
                Ecrire_Nbportebleue (nb_porte);
            }
        }
    }
}
