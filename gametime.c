#include <DOS.H>
#include "SOURGAME/GAMEINFO.H"
#include "SOURGAME/GAMETIME.H"
#include "SOURGAME/GAMEGRAP.H"
#define OCTET unsigned char
void Accelerer_Horloge (short);
void Retablir_Horloge (void);
void interrupt far Routine_Timer_Interruption (void);
void (interrupt far *Ancienne_Interruption_Timer)(void);
short result;
short port = 0x3c4;
short commutateur_chrono = OFF;
short compteur_timer = 0;
short vitesse;
short nbrt;
void Top_Retrace (void)
{
    nbrt = 0;
}
short Out_Retrace (void)
{
    return (nbrt);
}
void interrupt far Routine_Timer_Interruption (void)
{
    if (commutateur_chrono == ON)
    {
        nbrt ++;
        compteur_timer ++;
        if (compteur_timer > TEMPO_TIMER)
        {
            result = inport(port);
            Dec_Temps (1);
            outport (port,result);
            compteur_timer = 0;
            Ancienne_Interruption_Timer ();
        }
        else
        {
            enable ();
            (void)outp (0x20,0x20);
        }
    }
    else
    {
        enable ();
        (void)outp (0x20,0x20);
    }
}
void far Installer_Timer_Interruption (void)
{
    disable ();
    Accelerer_Horloge (FREQUENCE);
    Ancienne_Interruption_Timer = getvect (TIMER_INTERRUPTION);
    setvect (TIMER_INTERRUPTION,Routine_Timer_Interruption);
    enable ();
}
void far Desinstaller_Timer_Interruption (void)
{
    commutateur_chrono = OFF;
    disable ();
    Retablir_Horloge ();
    setvect (TIMER_INTERRUPTION,
             Ancienne_Interruption_Timer);
    enable ();
}
void far Activer_Timer (void)
{
    commutateur_chrono = ON;
}
void far Desactiver_Timer (void)
{
    commutateur_chrono = OFF;
}
void Accelerer_Horloge (short freq)
{
    unsigned short tspeed;
    tspeed = 1193180UL / (unsigned short)freq;
    outportb (0x43,0x3c);
    outportb (0x40,tspeed & 0xff);
    outportb (0x40,tspeed >> 8);
}
void Retablir_Horloge (void)
{
    outportb (0x43,0x3c);
    outportb (0x40,0xff);
    outportb (0x40,0xff);
}
void Pause (unsigned short duree)
{
    delay (duree * (FREQUENCE/18.206759) );
}
void Init_Cadence (short vit)
{
    vitesse = vit;
}
short Lire_Cadence (void)
{
    return (vitesse);
}
