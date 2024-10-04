#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITBOIT.H"
void Panneau_8 (void)
{
    OCTET reponse;
    OCTET page;
    Ecrire_Panneau_Encours (Lire_Panneau_Demande () );
    Ecrire_Panneau_Demande (0);
    page = (Lire_Page () == 0) ? 1 : 0;
    Cls (page,BOB_BLOC_NOIR);
    Changer_Page (page);
    Afficher_Boite_Message (page,INFO09);
    reponse = RIEN;
    do
    {
        if ( Test_Option (INFO09_OUI) == ON )
        {
            reponse = OUI;
            Option (OFF,page,INFO09_OUI);
            WAIT_NO_CLIC;
            Option (ON,page,INFO09_OUI);
        }
        if ( Test_Option (INFO09_NON) == ON )
        {
            reponse = NON;
            Option (OFF,page,INFO09_NON);
            WAIT_NO_CLIC;
            Option (ON,page,INFO09_NON);
        }
    }
    while (reponse == RIEN);
    if (reponse == OUI) Ecrire_Panneau_Demande (9);
    if (reponse == NON) Ecrire_Panneau_Demande (1);
    Effacer_Boite (page);
}
