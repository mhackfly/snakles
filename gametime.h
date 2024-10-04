#define OFF 0
#define ON 1
#define FREQUENCE 50
#define TEMPO_TIMER 50
#define TIMER_INTERRUPTION 8
void far Installer_Timer_Interruption (void);
void far Desinstaller_Timer_Interruption (void);
void far Activer_Timer (void);
void far Desactiver_Timer (void);
void Pause (unsigned short);
void Init_Cadence (short);
short Lire_Cadence (void);
void Top_Retrace (void);
short Out_Retrace (void);
