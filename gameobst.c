#include <STDLIB.H>
#include "SOURGAME/GAMESERP.H"
#include "SOURGAME/GAMEGRAP.H"
#include "SOURGAME/GAMETABL.H"
#include "SOURGAME/GAMEINFO.H"
extern OCTET sortie;
void Obst_Fond (void);
void Obst_Bordure (void);
void Obst_Dessin (void);
void Obst_Porte_Blanche_Mobile (void);
void Obst_Porte_Rouge_Fermee (void);
void Obst_Porte_Verte_Fermee (void);
void Obst_Porte_Bleu_Fermee (void);
void Obst_Porte_Rouge_Ouverte (void);
void Obst_Porte_Verte_Ouverte (void);
void Obst_Porte_Bleu_Ouverte (void);
void Obst_Cle_Rouge (void);
void Obst_Cle_Verte (void);
void Obst_Cle_Bleu (void);
void Obst_Boule_Bleu (void);
void Obst_Diamant (void);
void Obst_Boule_Verte (void);
void Obst_Boule_Rouge (void);
void Obst_Etoile_Vie (void);
void Obst_Etoile_Mort (void);
void Obst_Serpent_Souple (void);
void Obst_Serpent_Raide (void);
void Obst_Temps_Plus (void);
void Obst_Temps_Moins (void);
void Obst_Immortalite (void);
void Obst_Mortalite (void);
void Obst_Avance_Lente (void);
void Obst_Avance_Rapide (void);
void Obst_Vitesse_Rapide (void);
void Obst_Vitesse_Moyenne (void);
void Obst_Vitesse_Lente (void);
void Obst_Stop_Serpent_Rouge (void);
void Obst_Stop_Serpent_Vert (void);
void Obst_Stop_Serpent_Bleu (void);
void Obst_Sens_Serpent_Rouge (void);
void Obst_Sens_Serpent_Vert (void);
void Obst_Sens_Serpent_Bleu (void);
void Obst_Vitesse_Serpent_Rouge (void);
void Obst_Vitesse_Serpent_Vert (void);
void Obst_Vitesse_Serpent_Bleu (void);
short *ad_fonct [39] =
{
    (short*)Obst_Fond,
    (short*)Obst_Bordure,
    (short*)Obst_Dessin,
    (short*)Obst_Porte_Blanche_Mobile,
    (short*)Obst_Porte_Rouge_Fermee,
    (short*)Obst_Porte_Verte_Fermee,
    (short*)Obst_Porte_Bleu_Fermee,
    (short*)Obst_Porte_Rouge_Ouverte,
    (short*)Obst_Porte_Verte_Ouverte,
    (short*)Obst_Porte_Bleu_Ouverte,
    (short*)Obst_Cle_Rouge,
    (short*)Obst_Cle_Verte,
    (short*)Obst_Cle_Bleu,
    (short*)Obst_Boule_Bleu,
    (short*)Obst_Diamant,
    (short*)Obst_Boule_Verte,
    (short*)Obst_Boule_Rouge,
    (short*)Obst_Etoile_Vie,
    (short*)Obst_Etoile_Mort,
    (short*)Obst_Serpent_Souple,
    (short*)Obst_Serpent_Raide,
    (short*)Obst_Temps_Plus,
    (short*)Obst_Temps_Moins,
    (short*)Obst_Immortalite,
    (short*)Obst_Mortalite,
    (short*)Obst_Avance_Lente,
    (short*)Obst_Avance_Rapide,
    (short*)Obst_Vitesse_Rapide,
    (short*)Obst_Vitesse_Moyenne,
    (short*)Obst_Vitesse_Lente,
    (short*)Obst_Stop_Serpent_Rouge,
    (short*)Obst_Stop_Serpent_Vert,
    (short*)Obst_Stop_Serpent_Bleu,
    (short*)Obst_Sens_Serpent_Rouge,
    (short*)Obst_Sens_Serpent_Vert,
    (short*)Obst_Sens_Serpent_Bleu,
    (short*)Obst_Vitesse_Serpent_Rouge,
    (short*)Obst_Vitesse_Serpent_Vert,
    (short*)Obst_Vitesse_Serpent_Bleu
};
void Obst_Fond (void)
{
}
void Obst_Bordure (void)
{
    Ecrire_Direction(NIBBLE,0);
}
void Obst_Dessin (void)
{
    Ecrire_Direction(NIBBLE,0);
}
void Obst_Porte_Blanche_Mobile (void)
{
    OCTET dir;
    dir = Lire_Direction(NIBBLE);
    if (Verifier_Porte_Mobile_Tableau (NIBBLE,dir) == ON)
    {
        Afficher_Porte_Mobile_Tableau (NIBBLE,dir);
        Ecrire_Obstacle_Tableau (NIBBLE,dir,OBST_FOND);
        Afficher_Obstacle_Tableau (NIBBLE,dir,BOB_FOND);
    }
    else
        Ecrire_Direction(NIBBLE,0);
}
void Obst_Porte_Rouge_Fermee (void)
{
    Ecrire_Direction(NIBBLE,0);
}
void Obst_Porte_Verte_Fermee (void)
{
    Ecrire_Direction(NIBBLE,0);
}
void Obst_Porte_Bleu_Fermee (void)
{
    Ecrire_Direction(NIBBLE,0);
}
void Obst_Porte_Rouge_Ouverte (void)
{
}
void Obst_Porte_Verte_Ouverte (void)
{
}
void Obst_Porte_Bleu_Ouverte (void)
{
}
void Obst_Cle_Rouge (void)
{
    short x,y;
    short cpt_nb_porte;
    OCTET lecture_obstacle,
          ecriture_obstacle;
    Inc_Score (PT_CLE_ROUGE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt_nb_porte = 0;
            cpt_nb_porte < Lire_Nbporterouge();
            cpt_nb_porte++)
    {
        x = (short)Lire_Xporterouge (cpt_nb_porte) * LG_BOB;
        y = (short)Lire_Yporterouge (cpt_nb_porte) * HT_BOB;
        lecture_obstacle = Lire_Code_Tableau(x,y);
        ecriture_obstacle = (lecture_obstacle == OBST_PORTE_ROUGE_FERMEE) ?
                            OBST_PORTE_ROUGE_OUVERTE : OBST_PORTE_ROUGE_FERMEE;
        Ecrire_Code_Tableau (x,y,ecriture_obstacle);
        Afficher_Bob (0,BOB_PASTILLE + (ecriture_obstacle - 1),x,y,MASK_ON);
        Afficher_Bob (1,BOB_PASTILLE + (ecriture_obstacle - 1),x,y,MASK_ON);
    }
}
void Obst_Cle_Verte (void)
{
    short x,y;
    short cpt_nb_porte;
    OCTET lecture_obstacle,
          ecriture_obstacle;
    Inc_Score (PT_CLE_VERTE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt_nb_porte = 0;
            cpt_nb_porte < Lire_Nbporteverte();
            cpt_nb_porte++)
    {
        x = (short)Lire_Xporteverte (cpt_nb_porte) * LG_BOB;
        y = (short)Lire_Yporteverte (cpt_nb_porte) * HT_BOB;
        lecture_obstacle = Lire_Code_Tableau(x,y);
        ecriture_obstacle = (lecture_obstacle == OBST_PORTE_VERTE_FERMEE) ?
                            OBST_PORTE_VERTE_OUVERTE : OBST_PORTE_VERTE_FERMEE;
        Ecrire_Code_Tableau (x,y,ecriture_obstacle);
        Afficher_Bob (0,BOB_PASTILLE + (ecriture_obstacle - 1),x,y,MASK_ON);
        Afficher_Bob (1,BOB_PASTILLE + (ecriture_obstacle - 1),x,y,MASK_ON);
    }
}
void Obst_Cle_Bleu (void)
{
    short x,y;
    short cpt_nb_porte;
    OCTET lecture_obstacle,
          ecriture_obstacle;
    Inc_Score (PT_CLE_BLEU);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt_nb_porte = 0;
            cpt_nb_porte < Lire_Nbportebleue();
            cpt_nb_porte++)
    {
        x = (short)Lire_Xportebleue (cpt_nb_porte) * LG_BOB;
        y = (short)Lire_Yportebleue (cpt_nb_porte) * HT_BOB;
        lecture_obstacle = Lire_Code_Tableau(x,y);
        ecriture_obstacle = (lecture_obstacle == OBST_PORTE_BLEU_FERMEE) ?
                            OBST_PORTE_BLEU_OUVERTE : OBST_PORTE_BLEU_FERMEE;
        Ecrire_Code_Tableau (x,y,ecriture_obstacle);
        Afficher_Bob (0,BOB_PASTILLE + (ecriture_obstacle - 1),x,y,MASK_ON);
        Afficher_Bob (1,BOB_PASTILLE + (ecriture_obstacle - 1),x,y,MASK_ON);
    }
}
void Obst_Boule_Bleu (void)
{
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Inc_Score (PT_BOULE_BLEU);
    Incrementer_Compteur_Pastille (1);
    if (Lire_Nombre_Pastille() == Lire_Compteur_Pastille())
        sortie = 7;
}
void Obst_Diamant (void)
{
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Inc_Score (Lire_Vlbonus ());
}
void Obst_Boule_Verte (void)
{
    if (Lire_Longueur(NIBBLE) > LG_SERPENT_MINI)
    {
        Inc_Score (PT_BOULE_VERTE);
        Ecrire_Obstacle_Tableau (NIBBLE,
                                 Lire_Direction(NIBBLE),
                                 OBST_FOND);
        Activer_Taille_Moins (NIBBLE);
        Avancer_Serpent (NIBBLE);
    }
}
void Obst_Boule_Rouge (void)
{
    if (Lire_Longueur(NIBBLE) < LG_SERPENT_MAXI)
    {
        Inc_Score (PT_BOULE_ROUGE);
        Ecrire_Obstacle_Tableau (NIBBLE,
                                 Lire_Direction(NIBBLE),
                                 OBST_FOND);
        Activer_Taille_Plus (NIBBLE);
    }
}
void Obst_Etoile_Vie (void)
{
    Inc_Score (PT_ETOILE_VIE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Inc_Vies (1);
}
void Obst_Etoile_Mort (void)
{
    Inc_Score (PT_ETOILE_MORT);
    if (Lire_Mortalite (NIBBLE) == ON)
        sortie = 3;
}
void Obst_Serpent_Souple (void)
{
    Inc_Score (PT_SERPENT_SOUPLE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Activer_Souplesse (NIBBLE);
}
void Obst_Serpent_Raide (void)
{
    Inc_Score (PT_SERPENT_RAIDE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Desactiver_Souplesse (NIBBLE);
}
void Obst_Temps_Plus (void)
{
    Inc_Score (PT_TEMPS_PLUS);
    Inc_Temps (Lire_Temps_Plus ());
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
}
void Obst_Temps_Moins (void)
{
    Inc_Score (PT_TEMPS_MOINS);
    Dec_Temps (Lire_Temps_Moins ());
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
}
void Obst_Immortalite (void)
{
    Inc_Score (PT_IMMORTALITE);
    Ecrire_Obstacle_Tableau (NIBBLE,Lire_Direction(NIBBLE),OBST_FOND);
    Desactiver_Mortalite (NIBBLE);
}
void Obst_Mortalite (void)
{
    Inc_Score (PT_MORTALITE);
    Ecrire_Obstacle_Tableau (NIBBLE,Lire_Direction(NIBBLE),OBST_FOND);
    Activer_Mortalite (NIBBLE);
}
void Obst_Avance_Lente (void)
{
    Inc_Score (PT_AVANCE_LENTE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Desactiver_Fluidite (NIBBLE);
}
void Obst_Avance_Rapide (void)
{
    Inc_Score (PT_AVANCE_RAPIDE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Activer_Fluidite (NIBBLE);
}
void Obst_Vitesse_Rapide (void)
{
    Inc_Score (PT_VITESSE_RAPIDE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Init_Vitesse (NIBBLE,0);
    Init_Compteur_Vitesse (NIBBLE,0);
}
void Obst_Vitesse_Moyenne (void)
{
    Inc_Score (PT_VITESSE_MOYENNE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Init_Vitesse (NIBBLE,1);
    Init_Compteur_Vitesse (NIBBLE,1);
}
void Obst_Vitesse_Lente (void)
{
    Inc_Score (PT_VITESSE_LENTE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    Init_Vitesse (NIBBLE,2);
    Init_Compteur_Vitesse (NIBBLE,2);
}
void Obst_Stop_Serpent_Rouge (void)
{
    OCTET cpt;
    Inc_Score (PT_STOP_SERPENT_ROUGE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 0)
        {
            if (Lire_Compteur_Vitesse (cpt+1) == 255)
                Init_Compteur_Vitesse (cpt+1,Lire_Vitesse (cpt+1));
            else
                Init_Compteur_Vitesse (cpt+1,255);
        }
    }
}
void Obst_Stop_Serpent_Vert (void)
{
    OCTET cpt;
    Inc_Score (PT_STOP_SERPENT_VERT);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 1)
        {
            if (Lire_Compteur_Vitesse (cpt+1) == 255)
                Init_Compteur_Vitesse (cpt+1,Lire_Vitesse (cpt+1));
            else
                Init_Compteur_Vitesse (cpt+1,255);
        }
    }
}
void Obst_Stop_Serpent_Bleu (void)
{
    OCTET cpt;
    Inc_Score (PT_STOP_SERPENT_BLEU);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 2)
        {
            if (Lire_Compteur_Vitesse (cpt+1) == 255)
                Init_Compteur_Vitesse (cpt+1,Lire_Vitesse (cpt+1));
            else
                Init_Compteur_Vitesse (cpt+1,255);
        }
    }
}
void Obst_Sens_Serpent_Rouge (void)
{
    OCTET cpt;
    Inc_Score (PT_SENS_SERPENT_ROUGE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 0)
            Init_Compteur_Tempo_Direction (cpt+1);
    }
}
void Obst_Sens_Serpent_Vert (void)
{
    OCTET cpt;
    Inc_Score (PT_SENS_SERPENT_VERT);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 1)
            Init_Compteur_Tempo_Direction (cpt+1);
    }
}
void Obst_Sens_Serpent_Bleu (void)
{
    OCTET cpt;
    Inc_Score (PT_SENS_SERPENT_BLEU);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 2)
            Init_Compteur_Tempo_Direction (cpt+1);
    }
}
void Obst_Vitesse_Serpent_Rouge (void)
{
    OCTET cpt;
    Inc_Score (PT_VITESSE_SERPENT_ROUGE);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 0)
        {
            Init_Vitesse (cpt+1,random(3));
            Init_Compteur_Vitesse (cpt+1,0);
        }
    }
}
void Obst_Vitesse_Serpent_Vert (void)
{
    OCTET cpt;
    Inc_Score (PT_VITESSE_SERPENT_VERT);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 1)
        {
            Init_Vitesse (cpt+1,random(3));
            Init_Compteur_Vitesse (cpt+1,0);
        }
    }
}
void Obst_Vitesse_Serpent_Bleu (void)
{
    OCTET cpt;
    Inc_Score (PT_VITESSE_SERPENT_BLEU);
    Ecrire_Obstacle_Tableau (NIBBLE,
                             Lire_Direction(NIBBLE),
                             OBST_FOND);
    for (cpt = 0 ;
            cpt < Lire_Nbnibble_X() ;
            cpt ++)
    {
        if (Lire_Clnibble_X (cpt) == 2)
        {
            Init_Vitesse (cpt+1,random(3));
            Init_Compteur_Vitesse (cpt+1,0);
        }
    }
}
