#define COLOR_INFOS 107
#define COLOR_NBINFOS 240
#define Y_INFOS 391
#define X_SCORE 0
#define XNB_SCORE 45
#define NBU_SCORE 6
#define LIM_SCORE 999999L
#define X_TABLEAU 101
#define XNB_TABLEAU 162
#define NBU_TABLEAU 2
#define LIM_TABLEAU 99
#define X_TEMPS 186
#define XNB_TEMPS 231
#define NBU_TEMPS 3
#define LIM_TEMPS 999
#define X_VIES 263
#define XNB_VIES 300
#define NBU_VIES 2
#define LIM_VIES 99
void Afficher_Infos (void);
void Ini_Score (unsigned long);
void Dec_Score (unsigned long);
void Inc_Score (unsigned long);
unsigned long Lir_Score (void);
void Ini_Tableau (char);
void Dec_Tableau (char);
void Inc_Tableau (char);
char Lir_Tableau (void);
void Ini_Temps (short);
void Dec_Temps (short);
void Inc_Temps (short);
short Lir_Temps (void);
void Ini_Vies (char);
void Dec_Vies (char);
void Inc_Vies (char);
char Lir_Vies (void);
void Aff_Score (void);
void Aff_Tableau (void);
void Aff_Temps (void);
void Aff_Vies (void);
