#include <STDLIB.H>
#include "SOURGAME/GAMESERP.H"
#include "SOURGAME/GAMEGRAP.H"
#include "SOURGAME/GAMETABL.H"
#include "SOURGAME/GAMECLAV.H"
#include "SOURGAME/GAMETIME.H"
#include "SOURGAME/GAMEINFO.H"
extern short *ad_fonct [];
OCTET sortie;
OCTET Animer_Serpents (OCTET *info_page)
{
    short lire_cadence;
    char page_ok;
    short retrace;
    OCTET page;
    OCTET obstacle;
    OCTET direction;
    OCTET cpt_nibble;
    OCTET vitesse_encours;
    short *adresse_fonction;
    sortie = 0;
    page = *info_page;
    Activer_Timer ();
    do
    {
        Init_Cadence (0);
        Top_Retrace ();
        if (Lire_Compteur_Vitesse(NIBBLE) == 0)
        {
            vitesse_encours = 1;
            direction = Determiner_Direction ();
            Ecrire_Direction (NIBBLE,direction);
            if (direction != 0)
            {
                if (Lire_Souplesse(NIBBLE) == OFF)
                    if (Lire_Obstacle_Serpent(NIBBLE,
                                              Lire_Direction(NIBBLE))==NIBBLE)
                        if (Tester_Coords_Tete_Queue (NIBBLE,
                                                      Lire_Direction(NIBBLE))==0)
                        {
                            if (Lire_Mortalite (NIBBLE) == ON)
                                sortie = 2;
                            else
                                Ecrire_Direction (NIBBLE,0);
                        }
                if (Determiner_Obstacle (NIBBLE,
                                         Lire_Direction (NIBBLE)) == OBST_NIBBLEX)
                {
                    if (Lire_Mortalite(NIBBLE) == ON)
                        sortie = 4;
                    else
                        Ecrire_Direction (NIBBLE,0);
                }
                if (Lire_Direction (NIBBLE) != 0)
                {
                    obstacle = Lire_Obstacle_Tableau (NIBBLE,direction);
                    if (obstacle != OBST_FOND)
                    {
                        adresse_fonction = ad_fonct [obstacle];
                        asm call adresse_fonction;
                    }
                }
            }
        }
        Effacer_Serpent (page,NIBBLE,BOB_FOND,BOB_PASTILLE+1);
        if ( (Lire_Direction (NIBBLE) != 0) & (vitesse_encours == 1) )
        {
            Avancer_Serpent (NIBBLE);
            vitesse_encours = 0;
        }
        Afficher_Serpent (page,NIBBLE,BOB_SERPENT_NOIR +
                          (Lire_Mortalite (NIBBLE) * NB_BOB_SERPENT_NOIR) );
        Sauver_Donnees_Serpent (NIBBLE,page);
        Decrementer_Compteur_Vitesse (NIBBLE);
        if (sortie == 0)
        {
            for (cpt_nibble = 1;
                    cpt_nibble <= Lire_Nbnibble_X ();
                    cpt_nibble++)
            {
                if (Lire_Compteur_Vitesse(cpt_nibble) == 0)
                {
                    if (Lire_Direction(cpt_nibble)==0)
                        Ecrire_Direction(cpt_nibble,
                                         Choisir_Direction_NibbleX (cpt_nibble,
                                                 Lire_Direction_Tete(cpt_nibble)));
                    if (Lire_Compteur_Tempo_Direction(cpt_nibble) == 0)
                        Ecrire_Direction(cpt_nibble,random (4)+1);
                    Decrementer_Compteur_Tempo_Direction (cpt_nibble);
                    if (Lire_Direction(cpt_nibble) != 0)
                    {
                        if (Lire_Obstacle_Serpent(cpt_nibble,
                                                  Lire_Direction(cpt_nibble)) == NIBBLE)
                        {
                            if (Lire_Mortalite (NIBBLE) == ON)
                                sortie = 5;
                            else
                                Ecrire_Direction (cpt_nibble,0);
                        }
                        obstacle = Lire_Obstacle_Serpent(cpt_nibble,
                                                         Lire_Direction(cpt_nibble));
                        if ( (obstacle != cpt_nibble) &
                                (obstacle !=0) &
                                (obstacle != CODE_SERPENT_FOND) )
                            Ecrire_Direction(cpt_nibble,0);
                        obstacle = Lire_Obstacle_Tableau(cpt_nibble,Lire_Direction(cpt_nibble));
                        if ( (obstacle >= OBST_BORDURE) &
                                (obstacle <= OBST_PORTE_BLEU_FERMEE) )
                            Ecrire_Direction(cpt_nibble,0);
                    }
                }
                Effacer_Serpent (page,cpt_nibble,BOB_FOND,BOB_PASTILLE+1);
                if (Lire_Direction(cpt_nibble) !=0)
                    if (Lire_Compteur_Vitesse(cpt_nibble) ==0)
                        Avancer_Serpent (cpt_nibble);
                Sauver_Donnees_Serpent (cpt_nibble,page);
                Afficher_Serpent (
                    page,cpt_nibble,BOB_SERPENT_ROUGE +
                    (Lire_Clnibble_X (cpt_nibble-1) * NB_BOB_SERPENT_ROUGE)
                );
                if ( Lire_Compteur_Vitesse(cpt_nibble) != 255)
                    Decrementer_Compteur_Vitesse (cpt_nibble);
            }
        }
        else
        {
            for (cpt_nibble = 1;
                    cpt_nibble <= Lire_Nbnibble_X();
                    cpt_nibble ++)
            {
                Effacer_Serpent (page,cpt_nibble,BOB_FOND,BOB_PASTILLE+1);
                Afficher_Serpent (page,
                                  cpt_nibble,
                                  BOB_SERPENT_ROUGE +
                                  (Lire_Clnibble_X(cpt_nibble-1)*
                                   NB_BOB_SERPENT_ROUGE));
            }
        }
        if ( (Lire_Action_Touche (ECHAP) == 1) & (sortie ==0) ) sortie = 1;
        if ( (Lire_Action_Touche (TOUCHE_P) == 1) & (sortie ==0) ) sortie = 9;
        if ( Lir_Temps () <= 0 )
        {
            Ini_Temps (0);
            Aff_Temps ();
            sortie = 8;
        }
        retrace = Out_Retrace ();
        Afficher_Page (page);
        page = (page == 0) ? 1 : 0;
    }
    while (sortie == 0);
    page = (page == 0) ? 1 : 0;
    *info_page = page;
    Desactiver_Timer ();
    return (sortie);
}
