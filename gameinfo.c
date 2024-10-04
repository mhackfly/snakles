#include "SOURGAME/GAMEGRAP.H"
#include "SOURGAME/GAMEINFO.H"
#include "SOURGAME/GAMECHAR.H"
unsigned long score;
char ntableau;
short temps;
char vies;
void Ini_Score (unsigned long sc)
{
    score = sc;
}
void Dec_Score (unsigned long sc)
{
    score -= sc;
    Aff_Score ();
}
void Inc_Score (unsigned long sc)
{
    score += sc;
    if (score > LIM_SCORE) score = LIM_SCORE;
    Aff_Score ();
}
unsigned long Lir_Score (void)
{
    return (score);
}
void Ini_Tableau (char nt)
{
    ntableau = nt;
}
void Dec_Tableau (char nt)
{
    ntableau -= nt;
    Aff_Tableau ();
}
void Inc_Tableau (char nt)
{
    ntableau += nt;
    if (ntableau > LIM_TABLEAU) ntableau = LIM_TABLEAU;
    Aff_Tableau ();
}
char Lir_Tableau (void)
{
    return (ntableau);
}
void Ini_Temps (short te)
{
    temps = te;
}
void Dec_Temps (short te)
{
    temps -= te;
    Aff_Temps ();
}
void Inc_Temps (short te)
{
    temps += te;
    if (temps > LIM_TEMPS) temps = LIM_TEMPS;
    Aff_Temps ();
}
short Lir_Temps (void)
{
    return (temps);
}
void Ini_Vies (char vi)
{
    vies = vi;
}
void Dec_Vies (char vi)
{
    vies -= vi;
    Aff_Vies ();
}
void Inc_Vies (char vi)
{
    vies += vi;
    if (vies > LIM_VIES) vies = LIM_VIES;
    Aff_Vies ();
}
char Lir_Vies (void)
{
    return (vies);
}
void Aff_Score (void)
{
    Afficher_Nombre (0,BOB_CHIFFRE2,NBU_SCORE,score,XNB_SCORE,Y_INFOS,MASK_OFF);
    Afficher_Nombre (1,BOB_CHIFFRE2,NBU_SCORE,score,XNB_SCORE,Y_INFOS,MASK_OFF);
}
void Aff_Tableau (void)
{
    Afficher_Nombre (0,BOB_CHIFFRE2,NBU_TABLEAU,ntableau,XNB_TABLEAU,Y_INFOS,MASK_OFF);
    Afficher_Nombre (1,BOB_CHIFFRE2,NBU_TABLEAU,ntableau,XNB_TABLEAU,Y_INFOS,MASK_OFF);
}
void Aff_Temps (void)
{
    Afficher_Nombre (0,BOB_CHIFFRE2,NBU_TEMPS,temps,XNB_TEMPS,Y_INFOS,MASK_OFF);
    Afficher_Nombre (1,BOB_CHIFFRE2,NBU_TEMPS,temps,XNB_TEMPS,Y_INFOS,MASK_OFF);
}
void Aff_Vies (void)
{
    Afficher_Nombre (0,BOB_CHIFFRE2,NBU_VIES,vies,XNB_VIES,Y_INFOS,MASK_OFF);
    Afficher_Nombre (1,BOB_CHIFFRE2,NBU_VIES,vies,XNB_VIES,Y_INFOS,MASK_OFF);
}
void Afficher_Infos (void)
{
    Print (0,X_SCORE, Y_INFOS,COLOR_INFOS,0,"SCORE");
    Print (0,X_TABLEAU, Y_INFOS,COLOR_INFOS,0,"TABLEAU");
    Print (0,X_TEMPS, Y_INFOS,COLOR_INFOS,0,"TEMPS");
    Print (0,X_VIES, Y_INFOS,COLOR_INFOS,0,"VIES");
    Print (1,X_SCORE, Y_INFOS,COLOR_INFOS,0,"SCORE");
    Print (1,X_TABLEAU, Y_INFOS,COLOR_INFOS,0,"TABLEAU");
    Print (1,X_TEMPS, Y_INFOS,COLOR_INFOS,0,"TEMPS");
    Print (1,X_VIES, Y_INFOS,COLOR_INFOS,0,"VIES");
    Aff_Score ();
    Aff_Tableau ();
    Aff_Temps ();
    Aff_Vies ();
}
