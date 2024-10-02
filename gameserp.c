#include <DOS.H>
#include <STDLIB.H>
#include "SOURGAME/GAMESERP.H"
#include "SOURGAME/GAMEGRAP.H"
#include "SOURGAME/GAMETABL.H"
#include "SOURGAME/GAMECLAV.H"
#include "SOURGAME/GAMETIME.H"
void Init_Serpent (OCTET,OCTET,OCTET,OCTET,OCTET,
                   OCTET,OCTET,OCTET,OCTET,short);
void Avancer_Queue_Buffers (OCTET ns);
void Avancer_Tete_Buffers (OCTET ns,OCTET dt);
OCTET Lire_Code_Serpent (short,short);
void Ecrire_Code_Serpent (short,short,OCTET);
OCTET Verifier_Direction (OCTET);
OCTET backup_direction = 0;
struct serpent
{
    OCTET formes[LG_SERPENT_MAXI+2];
    short xtete;
    short ytete;
    short xqueue;
    short yqueue;
    OCTET vitesse;
    OCTET cpt_vitesse;
    OCTET longueur;
    OCTET direction;
    OCTET souplesse;
    OCTET mortalite;
    OCTET fluidite;
    short tempo_direction;
    short cpt_tempo_direction;
    OCTET taille;
};
OCTET bufferserpent [X_MAX*Y_MAX];
OCTET dirinverse [5] = {0,2,1,4,3};
struct serpent infoserpent [NB_SERPENT];
struct serpent backupinfoserpent [2][NB_SERPENT];
char offx[24] = {1,1,0,0,-1,1,-1,-1,0,0,1,-1,0,0,-1,1,0,0,0,0,-1,1,0,0};
char offy[24] = {0,0,1,-1,0,0,0,0,1,-1,0,0,1,1,0,0,-1,1,-1,-1,0,0,1,-1};
char corps[4][4]= { {-4,-1,-3,-2},{-1,-4,-3,-2},{-2,-3,-4,-1},{-2,-3,-1,-4} };
OCTET dirtete[24]= {0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,3,0,0,0,0,0,4};
OCTET dir_bord[5][3] = { {0,0,0},{1,3,4},{2,3,4},{3,2,1},{4,2,1} };
OCTET dir_1_nibble2 [5] = {0,4,4,2,2};
OCTET dir_2_nibble2 [5] = {0,3,3,1,1};
void Activer_Taille_Plus (OCTET ns)
{
    infoserpent[ns].taille = TAILLE_PLUS;
}
void Activer_Taille_Moins (OCTET ns)
{
    infoserpent[ns].taille = TAILLE_MOINS;
}
void Desactiver_Taille (OCTET ns)
{
    infoserpent[ns].taille = TAILLE_NULLE;
}
char Lire_Taille (OCTET ns)
{
    return (infoserpent[ns].taille);
}
void Activer_Souplesse (OCTET ns)
{
    infoserpent[ns].souplesse = ON;
}
void Desactiver_Souplesse (OCTET ns)
{
    infoserpent[ns].souplesse = OFF;
}
OCTET Lire_Souplesse (OCTET ns)
{
    return (infoserpent[ns].souplesse);
}
OCTET Lire_Mortalite (OCTET ns)
{
    return (infoserpent[ns].mortalite);
}
void Activer_Mortalite (OCTET ns)
{
    infoserpent[ns].mortalite = ON;
}
void Desactiver_Mortalite (OCTET ns)
{
    infoserpent[ns].mortalite = OFF;
}
OCTET Lire_Fluidite (OCTET ns)
{
    return (infoserpent[ns].fluidite);
}
void Activer_Fluidite (OCTET ns)
{
    infoserpent[ns].fluidite = ON;
}
void Desactiver_Fluidite (OCTET ns)
{
    infoserpent[ns].fluidite = OFF;
}
OCTET Lire_Longueur (OCTET ns)
{
    return (infoserpent[ns].longueur);
}
void Init_Vitesse (OCTET ns,OCTET vt)
{
    infoserpent[ns].vitesse = vt;
}
OCTET Lire_Vitesse (OCTET ns)
{
    return (infoserpent[ns].vitesse);
}
void Init_Compteur_Vitesse (OCTET ns,OCTET vt)
{
    infoserpent[ns].cpt_vitesse = vt;
}
OCTET Lire_Compteur_Vitesse (OCTET ns)
{
    return(infoserpent[ns].cpt_vitesse);
}
void Decrementer_Compteur_Vitesse (OCTET ns)
{
    if (infoserpent[ns].cpt_vitesse == 0) infoserpent[ns].cpt_vitesse = infoserpent[ns].vitesse;
    else infoserpent[ns].cpt_vitesse --;
}
void Init_Compteur_Tempo_Direction (OCTET ns)
{
    infoserpent[ns].cpt_tempo_direction = 0;
}
short Lire_Compteur_Tempo_Direction (OCTET ns)
{
    return (infoserpent[ns].cpt_tempo_direction);
}
void Decrementer_Compteur_Tempo_Direction (OCTET ns)
{
    if (infoserpent[ns].cpt_tempo_direction == 0)
        infoserpent[ns].cpt_tempo_direction = infoserpent[ns].tempo_direction;
    else
        infoserpent[ns].cpt_tempo_direction --;
}
void Init_Serpent (OCTET ns,OCTET dt,OCTET xt,OCTET yt,OCTET lg,
                   OCTET sp,OCTET vt,OCTET mt,OCTET fl,short tp)
{
    short xq,yq;
    OCTET cptlg;
    OCTET numtete;
    numtete=(dt*5)+(dt-1);
    infoserpent[ns].formes[0] = numtete-5;
    infoserpent[ns].formes[lg+1] = numtete;
    for (cptlg = 1;
            cptlg <= lg;
            cptlg++)
        infoserpent[ns].formes[cptlg]=numtete-4;
    infoserpent[ns].xtete=(xt*LG_BOB);
    infoserpent[ns].ytete=(yt*HT_BOB);
    infoserpent[ns].xqueue=(xt*LG_BOB)+((lg+1)*(offx[numtete-1]*LG_BOB));
    infoserpent[ns].yqueue=(yt*HT_BOB)+((lg+1)*(offy[numtete-1]*HT_BOB));
    infoserpent[ns].longueur = lg;
    xq = infoserpent[ns].xqueue;
    yq = infoserpent[ns].yqueue;
    for (cptlg = 0;
            cptlg <= lg+1;
            cptlg++)
    {
        Ecrire_Code_Serpent (xq,yq,ns);
        xq += (offx[ infoserpent[ns].formes[cptlg] ]*LG_BOB);
        yq += (offy[ infoserpent[ns].formes[cptlg] ]*HT_BOB);
    }
    infoserpent[ns].taille = TAILLE_NULLE;
    infoserpent[ns].direction = dt;
    infoserpent[ns].souplesse = sp;
    infoserpent[ns].vitesse = vt;
    infoserpent[ns].cpt_vitesse = vt;
    infoserpent[ns].tempo_direction = tp;
    infoserpent[ns].cpt_tempo_direction = tp;
    infoserpent[ns].mortalite = mt;
    infoserpent[ns].fluidite = fl;
}
void Init_Tous_Serpents (void)
{
    OCTET cpt_nibble_x;
    Init_Serpent (NIBBLE,
                  Lire_Drnibble(),
                  Lire_Xnibble (),
                  Lire_Ynibble (),
                  Lire_Lgnibble(),
                  Lire_Spnibble(),
                  Lire_Vtnibble(),
                  Lire_Mtnibble(),
                  Lire_Flnibble(),
                  0);
    for (cpt_nibble_x = 0 ;
            cpt_nibble_x<Lire_Nbnibble_X() ;
            cpt_nibble_x++)
        Init_Serpent (cpt_nibble_x+1,
                      Lire_Drnibble_X (cpt_nibble_x),
                      Lire_Xnibble_X (cpt_nibble_x),
                      Lire_Ynibble_X (cpt_nibble_x),
                      Lire_Lgnibble_X (cpt_nibble_x),
                      0,
                      Lire_Vtnibble_X (cpt_nibble_x),
                      0,
                      0,
                      Lire_Tpnibble_X (cpt_nibble_x));
}
void Avancer_Queue_Buffers (OCTET ns)
{
    OCTET cptlg;
    OCTET valcorps;
    short xs;
    short ys;
    xs = infoserpent[ns].xqueue;
    ys = infoserpent[ns].yqueue;
    Ecrire_Code_Serpent(infoserpent[ns].xqueue,
                        infoserpent[ns].yqueue,
                        CODE_SERPENT_FOND);
    for (cptlg = 0; cptlg <= infoserpent[ns].longueur ; cptlg ++)
    {
        xs += (offx[ infoserpent[ns].formes[cptlg] ]*LG_BOB);
        ys += (offy[ infoserpent[ns].formes[cptlg] ]*HT_BOB);
        Ecrire_Code_Serpent(xs,ys,ns);
    }
    infoserpent[ns].xqueue += offx[infoserpent[ns].formes[0]]*LG_BOB;
    infoserpent[ns].yqueue += offy[infoserpent[ns].formes[0]]*HT_BOB;
    valcorps = infoserpent[ns].formes[2];
    infoserpent[ns].formes[1] = (valcorps/6)*6;
    for (cptlg=0; cptlg<=infoserpent[ns].longueur; cptlg++)
        infoserpent[ns].formes[cptlg] = infoserpent[ns].formes[cptlg+1];
    infoserpent[ns].longueur --;
}
void Avancer_Tete_Buffers (OCTET ns,OCTET dt)
{
    OCTET longueur;
    OCTET nouvtete;
    OCTET ancitete;
    longueur = infoserpent[ns].longueur;
    nouvtete = (dt*5)+(dt-1);
    ancitete = infoserpent[ns].formes[longueur+1];
    infoserpent[ns].xtete += offx[nouvtete]*LG_BOB;
    infoserpent[ns].ytete += offy[nouvtete]*HT_BOB;
    Ecrire_Code_Serpent(infoserpent[ns].xtete,infoserpent[ns].ytete,ns);
    infoserpent[ns].formes[longueur+2] = nouvtete;
    infoserpent[ns].formes[longueur+1] = ancitete+corps[(ancitete-5)/6][dt-1];
    infoserpent[ns].longueur ++;
}
void Avancer_Serpent (OCTET ns)
{
    if (Lire_Taille(ns) != TAILLE_PLUS)
        Avancer_Queue_Buffers (ns);
    else
        Desactiver_Taille (ns);
    if (Lire_Taille(ns) != TAILLE_MOINS)
        Avancer_Tete_Buffers (ns,Lire_Direction(ns));
    else
        Desactiver_Taille (ns);
}
void Afficher_Serpent (OCTET pg,OCTET ns,OCTET nm)
{
    OCTET cpt;
    short xb;
    short yb;
    xb = infoserpent[ns].xqueue;
    yb = infoserpent[ns].yqueue;
    for (cpt=0; cpt<=(infoserpent[ns].longueur)+1; cpt++)
    {
        Afficher_Bob (pg,infoserpent[ns].formes[cpt]+nm,xb,yb,MASK_ON);
        xb += (offx[ infoserpent[ns].formes[cpt] ]*LG_BOB);
        yb += (offy[ infoserpent[ns].formes[cpt] ]*HT_BOB);
    }
}
void Afficher_Tous_Serpents (OCTET pg)
{
    OCTET cpt_nibble_x;
    Afficher_Serpent (pg,NIBBLE,BOB_SERPENT_NOIR +
                      (Lire_Mortalite (NIBBLE) * NB_BOB_SERPENT_NOIR) );
    for (cpt_nibble_x = 0 ;
            cpt_nibble_x<Lire_Nbnibble_X() ;
            cpt_nibble_x++)
        Afficher_Serpent (pg,
                          cpt_nibble_x+1,
                          BOB_SERPENT_ROUGE +
                          (Lire_Clnibble_X(cpt_nibble_x)*
                           NB_BOB_SERPENT_ROUGE));
}
void Effacer_Serpent (OCTET pg,OCTET ns,OCTET nm1,OCTET nm2)
{
    OCTET code;
    OCTET cpt;
    short xb;
    short yb;
    xb = backupinfoserpent[pg][ns].xqueue;
    yb = backupinfoserpent[pg][ns].yqueue;
    for (cpt = 0 ; cpt <= (backupinfoserpent[pg][ns].longueur)+1 ; cpt++)
    {
        Afficher_Bob (pg,nm1,xb,yb,MASK_OFF);
        code = Lire_Code_Tableau(xb,yb);
        if (code>=2) Afficher_Bob (pg,nm2+(code-2),xb,yb,MASK_ON);
        xb += (offx[ backupinfoserpent[pg][ns].formes[cpt] ]*LG_BOB);
        yb += (offy[ backupinfoserpent[pg][ns].formes[cpt] ]*HT_BOB);
    }
}
void Effacer_Tous_Serpents (OCTET pg)
{
    OCTET cpt;
    for (cpt = 0;
            cpt <= Lire_Nbnibble_X();
            cpt ++)
        Effacer_Serpent (pg,cpt,
                         BOB_FOND,BOB_PASTILLE+1);
}
void Sauver_Donnees_Serpent (OCTET ns,OCTET pg)
{
    backupinfoserpent[pg][ns] = infoserpent[ns];
}
void Sauver_Toutes_Donnees_Serpent (OCTET pg)
{
    OCTET cpt_nibble_x;
    Sauver_Donnees_Serpent (NIBBLE,pg);
    for (cpt_nibble_x = 0 ;
            cpt_nibble_x < Lire_Nbnibble_X() ;
            cpt_nibble_x ++)
        Sauver_Donnees_Serpent (cpt_nibble_x+1,pg);
}
OCTET Tester_Coords_Tete_Queue (OCTET ns,OCTET dt)
{
    short xt,yt;
    OCTET resul;
    resul = 0;
    xt = infoserpent[ns].xtete + offx[ (dt*5)+(dt-1) ] * LG_BOB;
    yt = infoserpent[ns].ytete + offy[ (dt*5)+(dt-1) ] * HT_BOB;
    if (xt == infoserpent[ns].xqueue)
        if (yt == infoserpent[ns].yqueue)
            resul = 1;
    return (resul);
}
OCTET Choisir_Direction_NibbleX (OCTET ns,OCTET dt)
{
    OCTET direction_possible [3];
    OCTET nb_direction;
    nb_direction = 0;
    if ((Determiner_Obstacle (ns,dir_1_nibble2[dt]) == 0) |
            ( (Lire_Obstacle_Serpent (ns,dir_1_nibble2[dt]) == NIBBLE) &
              (Lire_Mortalite (NIBBLE) == ON) ))
    {
        direction_possible [nb_direction] = dir_1_nibble2[dt];
        nb_direction ++;
    }
    if ((Determiner_Obstacle (ns,dir_2_nibble2[dt]) == 0) |
            ( (Lire_Obstacle_Serpent (ns,dir_2_nibble2[dt]) == NIBBLE) &
              (Lire_Mortalite (NIBBLE) == ON) ))
    {
        direction_possible [nb_direction] = dir_2_nibble2[dt];
        nb_direction ++;
    }
    if (nb_direction == 0) return (dirinverse[dt]);
    return (direction_possible [random(nb_direction)]);
}
OCTET Determiner_Obstacle (OCTET ns,OCTET dt)
{
    char code_sortie;
    OCTET type_obstacle;
    code_sortie = OBST_FOND;
    type_obstacle = Lire_Obstacle_Tableau (ns,dt);
    if ( (type_obstacle >= OBST_BORDURE) &
            (type_obstacle <= OBST_PORTE_BLEU_FERMEE) )
        code_sortie = OBST_MUR;
    type_obstacle = Lire_Obstacle_Serpent (ns,dt);
    if (type_obstacle == 0)
        code_sortie = OBST_NIBBLE;
    if ( (type_obstacle > 0) & (type_obstacle < CODE_SERPENT_FOND) )
        code_sortie = OBST_NIBBLEX;
    return (code_sortie);
}
OCTET Verifier_Impasse (OCTET ns,OCTET dt)
{
    OCTET devant,
          cote1,
          cote2;
    OCTET sortie;
    sortie = 0;
    devant = 0;
    cote1 = 0;
    cote2 = 0;
    if (Determiner_Obstacle (ns,dir_bord[dt][0]) >= 1)
        devant = 1;
    if (Determiner_Obstacle (ns,dir_bord[dt][1]) >= 1)
        cote1 = 1;
    if (Determiner_Obstacle (ns,dir_bord[dt][2]) >= 1)
        cote2 = 1;
    if (devant + cote1 + cote2 == 3)
        sortie = 1;
    return (sortie);
}
OCTET Lire_Obstacle_Tableau (OCTET ns,OCTET dt)
{
    OCTET code;
    short xt,yt;
    xt = infoserpent[ns].xtete + offx[(dt*5)+(dt-1)]*LG_BOB;
    yt = infoserpent[ns].ytete + offy[(dt*5)+(dt-1)]*HT_BOB;
    code = Lire_Code_Tableau(xt,yt);
    return (code);
}
void Ecrire_Obstacle_Tableau (OCTET ns,OCTET dt,OCTET code)
{
    short xt,yt;
    xt = infoserpent[ns].xtete + offx[ (dt*5)+(dt-1) ] * LG_BOB;
    yt = infoserpent[ns].ytete + offy[ (dt*5)+(dt-1) ] * HT_BOB;
    Ecrire_Code_Tableau(xt,yt,code);
}
void Afficher_Obstacle_Tableau (OCTET ns,OCTET dt,OCTET nb)
{
    short xt,yt;
    xt = infoserpent[ns].xtete + offx[(dt*5)+(dt-1)] * LG_BOB;
    yt = infoserpent[ns].ytete + offy[(dt*5)+(dt-1)] * HT_BOB;
    Afficher_Bob (PAGE0,nb,xt,yt,MASK_ON);
    Afficher_Bob (PAGE1,nb,xt,yt,MASK_ON);
}
OCTET Lire_Direction (OCTET ns)
{
    return(infoserpent[ns].direction);
}
void Ecrire_Direction (OCTET ns,OCTET dt)
{
    infoserpent[ns].direction = dt;
}
OCTET Lire_Direction_Tete (OCTET ns)
{
    return (dirtete[ infoserpent[ns].formes[infoserpent[ns].longueur+1] ]);
}
OCTET Lire_Direction_Opposee (OCTET dt)
{
    return (dirinverse[dt]);
}
void Init_Code_Serpent (OCTET c)
{
    short cptbuf;
    for (cptbuf = 0;
            cptbuf<X_MAX*Y_MAX;
            cptbuf++)
        bufferserpent[cptbuf]=c;
}
OCTET Lire_Code_Serpent (short x,short y)
{
    return (bufferserpent[((y/HT_BOB)*X_MAX)+(x/LG_BOB)]);
}
void Ecrire_Code_Serpent (short x,short y,OCTET code)
{
    bufferserpent[((y/HT_BOB)*X_MAX)+(x/LG_BOB)] = code;
}
OCTET Lire_Obstacle_Serpent (OCTET ns,OCTET dt)
{
    OCTET code;
    short xt,yt;
    xt = infoserpent[ns].xtete + offx[(dt*5)+(dt-1)]*LG_BOB;
    yt = infoserpent[ns].ytete + offy[(dt*5)+(dt-1)]*HT_BOB;
    code = bufferserpent[((yt/HT_BOB)*X_MAX)+(xt/LG_BOB)];
    return (code);
}
void Ecrire_Obstacle_Serpent (OCTET ns,OCTET dt,OCTET code)
{
    short xt,yt;
    xt = infoserpent[ns].xtete + offx[ (dt*5)+(dt-1) ] * LG_BOB;
    yt = infoserpent[ns].ytete + offy[ (dt*5)+(dt-1) ] * HT_BOB;
    bufferserpent[((yt/HT_BOB)*X_MAX)+(xt/LG_BOB)] = code;
}
OCTET Verifier_Porte_Mobile_Tableau (OCTET ns,OCTET dt)
{
    OCTET sortie;
    OCTET code_tableau;
    OCTET code_serpent;
    short xt,yt;
    sortie = OFF;
    xt = infoserpent[ns].xtete + (offx[(dt*5)+(dt-1)] * 2) * LG_BOB;
    yt = infoserpent[ns].ytete + (offy[(dt*5)+(dt-1)] * 2) * HT_BOB;
    code_tableau = Lire_Code_Tableau (xt,yt);
    code_serpent = Lire_Code_Serpent (xt,yt);
    if ( (code_tableau == OBST_FOND) & (code_serpent == CODE_SERPENT_FOND) )
        sortie = ON;
    return (sortie);
}
void Afficher_Porte_Mobile_Tableau (OCTET ns,OCTET dt)
{
    short xt,yt;
    xt = infoserpent[ns].xtete + (offx[(dt*5)+(dt-1)] * 2) * LG_BOB;
    yt = infoserpent[ns].ytete + (offy[(dt*5)+(dt-1)] * 2) * HT_BOB;
    Ecrire_Code_Tableau(xt,yt,OBST_PORTE_BLANCHE_MOBILE);
    Afficher_Bob (PAGE0,BOB_PASTILLE + OBST_PORTE_BLANCHE_MOBILE-1,xt,yt,MASK_ON);
    Afficher_Bob (PAGE1,BOB_PASTILLE + OBST_PORTE_BLANCHE_MOBILE-1,xt,yt,MASK_ON);
}
OCTET Determiner_Direction (void)
{
    OCTET nouvelle_direction;
    OCTET direction_verifier;
    direction_verifier = 0;
    nouvelle_direction = Lire_Direction_Touche ();
    if (nouvelle_direction != 0)
    {
        direction_verifier = Verifier_Direction (nouvelle_direction);
        if (direction_verifier == nouvelle_direction)
            backup_direction = 0;
    }
    else
    {
        if (Lire_Fluidite (NIBBLE) == ON)
        {
            if (backup_direction ==
                    Lire_Direction_Opposee (Lire_Direction_Tete (NIBBLE)))
                backup_direction = 0;
            if (backup_direction != 0)
            {
                direction_verifier = Verifier_Direction (backup_direction);
                if (direction_verifier == backup_direction)
                    backup_direction = 0;
            }
            else
                direction_verifier = Lire_Direction_Tete (NIBBLE);
        }
    }
    return (direction_verifier);
}
OCTET Verifier_Direction (OCTET dt)
{
    OCTET valeur1,valeur2;
    OCTET nouvelle_direction;
    nouvelle_direction = dt;
    valeur1 = Lire_Direction_Tete (NIBBLE);
    if (Lire_Souplesse (NIBBLE) == OFF)
        if (Lire_Direction_Opposee (dt) == valeur1)
            nouvelle_direction = valeur1;
    if (Lire_Fluidite (NIBBLE) == ON)
    {
        valeur2 = Determiner_Obstacle (NIBBLE,dt);
        switch (valeur2)
        {
        case OBST_MUR:
        {
            backup_direction = nouvelle_direction;
            nouvelle_direction = valeur1;
            if (Lire_Obstacle_Tableau (NIBBLE,dt) == OBST_PORTE_BLANCHE_MOBILE)
                if (Verifier_Porte_Mobile_Tableau (NIBBLE,dt) == ON)
                    nouvelle_direction = dt;
            break;
        }
        case OBST_NIBBLEX:
        {
            if (Lire_Mortalite (NIBBLE) == OFF)
            {
                backup_direction = nouvelle_direction;
                nouvelle_direction = valeur1;
            }
            break;
        }
        case OBST_NIBBLE:
        {
            if (Lire_Souplesse (NIBBLE) == OFF)
                if (Lire_Mortalite (NIBBLE) == OFF)
                {
                    backup_direction = nouvelle_direction;
                    nouvelle_direction = valeur1;
                }
            break;
        }
        }
    }
    else
    {
        if (Lire_Souplesse (NIBBLE) == OFF)
            if (Lire_Direction_Opposee (dt) == valeur1)
                nouvelle_direction = 0;
    }
    return (nouvelle_direction);
}
void Clignoter_Serpent_Blanc (OCTET page_active,OCTET page_cachee)
{
    char cpt;
    Effacer_Serpent (page_cachee,NIBBLE,
                     BOB_FOND,BOB_PASTILLE+1);
    for (cpt = 0;
            cpt < 10;
            cpt ++)
    {
        Afficher_Page (page_cachee);
        Pause (50);
        Afficher_Page (page_active);
        Pause (50);
    }
    Afficher_Serpent (page_cachee,
                      NIBBLE,BOB_SERPENT_BLANC);
    Afficher_Page (page_active);
}
void Clignoter_Tous_Serpent (OCTET page_active,OCTET page_cachee)
{
    char cpt;
    Afficher_Pastilles (page_cachee,BOB_PASTILLE);
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
