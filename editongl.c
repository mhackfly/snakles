#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITONGL.H"
#include "SOUREDIT/EDITCHAR.H"
void Afficher_Onglet (OCTET page,OCTET num)
{
    char cptx,cpty;
    char numero;
    switch (num)
    {
    case ONGLET1:
    {
        Cls (page,BOB_BLOC_GRIS);
        Lire_Image_Pcx ("SPRFILES/DATA",page,0,0,MASK_OFF,0,302,319,12);
        Lire_Image_Pcx ("SPRFILES/DATA",page,8,16,MASK_OFF,0,278,304,22);
        numero = 0;
        for (cpty = 0;
                cpty < 8;
                cpty ++)
        {
            for (cptx = 0;
                    cptx < 6;
                    cptx ++)
            {
                numero ++;
                Afficher_Nombre (page,BOB_CHIFFRE,2,numero,
                                 25 + (52 * cptx),
                                 41 + (44 * cpty),
                                 MASK_OFF);
            }
        }
        break;
    }
    case ONGLET2:
    {
        Cls (page,BOB_BLOC_GRIS);
        Lire_Image_Pcx ("SPRFILES/DATA",page,0,0,MASK_OFF,0,316,319,12);
        Lire_Image_Pcx ("SPRFILES/DATA",page,3,14,MASK_OFF,0,264,304,12);
        Lire_Image_Pcx ("SPRFILES/DATA",page,309,28,MASK_OFF,309,0,10,270);
        Lire_Image_Pcx ("SPRFILES/DATA",page,309,299,MASK_OFF,285,0,10,98);
        Afficher_Cadre (page);
        break;
    }
    case ONGLET3:
    {
        Cls (page,BOB_BLOC_GRIS);
        Lire_Image_Pcx ("SPRFILES/DATA",page,0,0,MASK_OFF,0,330,319,12);
        Lire_Image_Pcx ("SPRFILES/DATA",page,3,14,MASK_OFF,0,250,288,12);
        Lire_Image_Pcx ("SPRFILES/DATA",page,309,28,MASK_OFF,273,0,10,88);
        Afficher_Cadre (page);
        break;
    }
    case ONGLET4:
    {
        Cls (page,BOB_BLOC_GRIS);
        Lire_Image_Pcx ("SPRFILES/DATA",page,0,0,MASK_OFF,0,344,319,12);
        Lire_Image_Pcx ("SPRFILES/DATA",page,309,28,MASK_OFF,297,0,10,176);
        Afficher_Cadre (page);
        break;
    }
    case ONGLET5:
    {
        Cls (page,BOB_BLOC_GRIS);
        Lire_Image_Pcx ("SPRFILES/DATA",page,0,0,MASK_OFF,0,358,319,12);
        Lire_Image_Pcx ("SPRFILES/DATA",page,5,15,MASK_OFF,0,234,148,14);
        break;
    }
    case ONGLET6:
    {
        Cls (page,BOB_BLOC_GRIS);
        Lire_Image_Pcx ("SPRFILES/DATA",page,0,0,MASK_OFF,0,372,319,12);
        break;
    }
    case ONGLET7:
    {
        Cls (page,BOB_BLOC_GRIS);
        Lire_Image_Pcx ("SPRFILES/DATA",page,0,0,MASK_OFF,0,386,319,12);
        break;
    }
    }
}
