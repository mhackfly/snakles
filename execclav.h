#define OCTET unsigned char
#define OFF 0
#define ON 1
#define CLAVIER_INTERRUPTION 9
#define ECHAP 1
#define ESPACE 57
#define ENTREE 28
#define CTRL 29
#define TAB 15
#define SHIFT 42
#define ALT 56
#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define F7 65
#define F8 66
#define F9 67
#define F10 68
#define F11 87
#define F12 88
#define FLECHE_DROITE 77
#define FLECHE_GAUCHE 75
#define FLECHE_BAS 80
#define FLECHE_HAUT 72
#define TOUCHE_A 16
#define TOUCHE_B 48
#define TOUCHE_C 46
#define TOUCHE_D 32
#define TOUCHE_E 18
#define TOUCHE_F 33
#define TOUCHE_G 34
#define TOUCHE_H 35
#define TOUCHE_I 23
#define TOUCHE_J 36
#define TOUCHE_K 37
#define TOUCHE L 38
#define TOUCHE_M 39
#define TOUCHE_N 49
#define TOUCHE_O 24
#define TOUCHE_P 25
#define TOUCHE_Q 30
#define TOUCHE_R 19
#define TOUCHE_S 31
#define TOUCHE_T 20
#define TOUCHE_U 21
#define TOUCHE_V 47
#define TOUCHE_W 44
#define TOUCHE_X 45
#define TOUCHE_Y 20
#define TOUCHE_Z 16
void far Installer_Clavier_Interruption (void);
void far Desinstaller_Clavier_Interruption (void);
char far Lire_Code_Touche (void);
char far Lire_Action_Touche (char);
