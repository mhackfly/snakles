#include <DOS.H>
#include <STDIO.H>
#include <STDLIB.H>
#include <STRING.H>
#include "SOURGAME/GAMEGRAP.H"
#define NB_BOB 195
void CopyBuf2Plane (OCTET*,OCTET,short,short,OCTET,OCTET,OCTET);
void CopyPlane2Buf (OCTET*,OCTET,short,short,OCTET,OCTET);
OCTET page_active;
struct bob_infos
{
    OCTET presence;
    OCTET *pointeurbitplan [4];
    OCTET nombrepoint [4];
    OCTET largeur;
    OCTET nombreligne;
};
struct bob_infos bob [NB_BOB];
OCTET Lire_Page (void)
{
    return (page_active);
}
void Activer_Ecran (void)
{
    asm
    {
        mov ax,0x0013;
        int 0x10;
        mov dx,0x3CE;
        mov al,5;
        out dx,al;
        inc dx;
        in al,dx;
        and al,239;
        out dx,al;
        dec dx;
        mov al,6;
        out dx,al;
        inc dx;
        in al,dx;
        and al,253;
        out dx,al;
        mov dx,0x3C4;
        mov al,4;
        out dx,al;
        inc dx;
        in al,dx;
        and al,247;
        or al,4;
        out dx,al;
        mov ax,0xA000;
        mov es,ax;
        xor di,di;
        mov ax,di;
        mov cx,0x8000;
        rep stosw;
        mov dx,0x3D4;
        mov al,9;
        out dx,al;
        inc dx;
        in al,dx;
        and al,112;
        out dx,al;
        dec dx;
        mov al,0x14;
        out dx,al;
        inc dx;
        in al,dx;
        and al,191;
        out dx,al;
        dec dx;
        mov al,0x17;
        out dx,al;
        inc dx;
        in al,dx;
        or al,64;
        out dx,al;
    }
}
void Desactiver_Ecran (void)
{
    union REGS regs;
    regs.x.ax = 0x0003;
    int86(0x10,&regs,&regs);
}
void Afficher_Point (OCTET page,short xpoint,short ypoint,OCTET coul)
{
    short adrpage;
    asm
    {
        push es;
        push di;
        mov adrpage,0xA000;
        mov al,page;
        mov bl,0x0A0;
        or al,al;
        je sauter_page;
        mov bl,0x0A8;
    }
sauter_page:
    asm
    {
        mov byte ptr adrpage + 1,bl;
        mov ax,80;
        mul ypoint;
        mov cx,xpoint;
        mov bx,cx;
        shr bx,1;
        shr bx,1;
        add ax,bx;
        mov di,ax;
        and cl,3;
        mov ah,1;
        shl ah,cl;
        mov al,2;
        mov dx,0x03C4;
        out dx,ax;
        mov ax,adrpage;
        mov es,ax;
        mov al,coul;
        stosb;
        pop di;
        pop es;
    }
}
OCTET Lire_Point (OCTET page,short xpoint,short ypoint)
{
    OCTET couleur_retour;
    short adrpage;
    asm
    {
        push es;
        push di;
        push ds;
        push si;
        mov adrpage,0xA000;
        mov al,page;
        mov bl,0x0A0;
        or al,al;
        je sauter_page;
        mov bl,0x0A8;
    }
sauter_page:
    asm
    {
        mov byte ptr adrpage + 1,bl;
        mov ax,80;
        mul ypoint;
        mov si,xpoint;
        mov cx,si;
        shr si,1;
        shr si,1;
        add si,ax;
        and cl,3;
        mov ah,cl;
        mov al,4;
        mov dx,0x03CE;
        out dx,ax;
        mov ax,adrpage;
        mov es,ax;
        mov al,es:[si];
        mov couleur_retour,al;
        pop si;
        pop ds;
        pop di;
        pop es;
    }
    return (couleur_retour);
}
void Afficher_Page (OCTET page)
{
    page_active = page;
    asm
    {
        mov al,page;
        or al,al;
        je sauter_page;
        mov al,0x80;
    }
sauter_page:
    asm
    {
        mov dx,0x3D4;
        mov ah,al;
        mov al,0x0C;
        out dx,ax;
        mov dx,0x3DA;
    }
boucle_balayage:
    asm
    {
        in al,dx;
        test al,8;
        jne boucle_balayage;
    }
boucle_faisceau:
    asm
    {
        in al,dx;
        test al,8;
        je boucle_faisceau;
    }
}
void Tracer_Droite (OCTET page,short x,short y,short x2,short y2,OCTET c)
{
    int i, steep = 0, sx, sy, dx, dy, e;
    dx = abs(x2 - x);
    sx = ((x2 - x) > 0) ? 1 : -1;
    dy = abs(y2 - y);
    sy = ((y2 - y) > 0) ? 1 : -1;
    if(dy > dx)
    {
        steep = 1;
        x ^= y;
        y ^= x;
        x ^= y;
        dx ^= dy;
        dy ^= dx;
        dx ^= dy;
        sx ^= sy;
        sy ^= sx;
        sx ^= sy;
    }
    e = 2 * dy - dx;
    for(i = 0; i < dx; i++)
    {
        if(steep)
            Afficher_Point (page,y,x,c);
        else Afficher_Point (page,x,y,c);
        while(e >= 0)
        {
            y += sy;
            e -= 2 * dx;
        }
        x += sx;
        e += 2 * dy;
    }
    Afficher_Point (page,x2,y2,c);
}
void Effacer_Ecran (OCTET pg,OCTET cl)
{
    short cptx;
    short cpty;
    for (cpty=0 ; cpty<LIMITE_Y_ECRAN ; cpty++)
        for (cptx=0 ; cptx<LIMITE_X_ECRAN ; cptx++)
            Afficher_Point (pg,cptx,cpty,cl);
}
void Cls (OCTET page)
{
    char cpty,cptx;
    for (cpty = 0;
            cpty < 40;
            cpty ++)
    {
        for (cptx = 0;
                cptx < 32;
                cptx ++)
            Afficher_Bob (page,BOB_BLOC,cptx * 10,cpty * 10,MASK_OFF);
    }
}
BOOL Lire_Image_Pcx (char *nomfichier,
                     OCTET np,
                     short xec,short yec,
                     OCTET masq,
                     short xfichiermin,short yfichiermin,
                     short xfichiermax,short yfichiermax)
{
    FILE *flux;
    char extension;
    char bufnomfic [13];
    OCTET sortie;
    OCTET octet;
    short j;
    short coul;
    short compteur;
    short xecran = 0;
    short yecran = 0;
    short xfichier = 0;
    short yfichier = 0;
    short largeurfichier;
    short hauteurfichier;
    short largeurfenetre;
    short hauteurfenetre;
    strcpy (bufnomfic,nomfichier);
    strcat (bufnomfic,".PCX");
    flux = fopen (bufnomfic,"rb");
    if (flux == NULL)
    {
        strcpy (bufnomfic,nomfichier);
        strcat (bufnomfic,".SPR");
        flux = fopen (bufnomfic,"rb");
        if (flux == NULL)
            return (FAUX);
        else
            extension = SPR;
    }
    else
        extension = PCX;
    sortie = FAUX;
    largeurfichier = LIMITE_X_ECRAN-1;
    hauteurfichier = LIMITE_Y_ECRAN-1;
    largeurfenetre = xfichiermax;
    hauteurfenetre = yfichiermax;
    xfichiermax += xfichiermin;
    yfichiermax += yfichiermin;
    if (extension == PCX)
        fseek(flux,128,SEEK_SET);
    do
    {
        octet = getc(flux);
        if (octet>191)
        {
            compteur = octet-192;
            octet = getc(flux);
            coul = octet;
        }
        else
        {
            coul = octet;
            compteur = 1;
        }
        for (j=0; j<compteur; j++)
        {
            if ( (xfichier >= xfichiermin) & (xfichier <= xfichiermax) )
                if ( (yfichier >= yfichiermin) & (yfichier <= yfichiermax) )
                {
                    if (xecran+xec<LIMITE_X_ECRAN)
                        if (yecran+yec<LIMITE_Y_ECRAN)
                            if (!( (coul == 255) & (masq == MASK_ON) ))
                                Afficher_Point(np,xecran+xec,yecran+yec,coul);
                    if (xecran>=largeurfenetre)
                    {
                        xecran=-1;
                        yecran++;
                    }
                    if (yecran>hauteurfenetre )
                    {
                        sortie=VRAI;
                        break;
                    }
                    xecran++;
                }
            if (xfichier>=largeurfichier)
            {
                xfichier=-1;
                yfichier++;
            }
            if (yfichier>hauteurfichier )
            {
                sortie=VRAI;
                break;
            }
            xfichier++;
        }
    }
    while (sortie!=VRAI);
    fclose (flux);
    return (VRAI);
}
void Lire_Palette (char *nomfichier)
{
    FILE *flux;
    union REGS reg;
    struct SREGS regs;
    OCTET pal[256][3];
    flux = fopen (nomfichier,"rb");
    if (flux == NULL)
        return;
    fread (&pal[0][0],sizeof(pal),1,flux);
    fclose (flux);
    reg.x.ax = 0x1012;
    regs.es = FP_SEG(pal);
    reg.x.dx = FP_OFF(pal);
    reg.x.bx = 0x0;
    reg.x.cx = 256;
    int86x(0x10, &reg, &reg, &regs);
}
void CopyBuf2Plane (OCTET *bufptr,OCTET verspage,short versx,short versy,
                    OCTET largeur,OCTET hauteur, OCTET bg)
{
    unsigned long buffer;
    buffer = (long)(bufptr);
    asm
    {
        push es;
        push di;
        push ds;
        push si;
        mov ah,0xA0;
        cmp verspage,0;
        je cv0;
        mov ah,0xA8;
    }
cv0:
    asm
    {
        xor al,al;
        mov es,ax;
        mov ax,80;
        mul versy;
        mov di,versx;
        mov cx,di;
        shr di,1;
        shr di,1;
        add di,ax;
        mov ah,1;
        and cl,3;
        shl ah,cl;
        mov dx,0x03c4;
        mov al,0x02;
        out dx,ax;
        mov dh,hauteur;
        mov dl,largeur;
        mov bx,80;
        sub bl,dl;
        xor ch,ch;
        lds si,buffer;
        cmp bg,0;
        jne cv2;
    }
cv1:
    asm
    {
        mov cl,dl;
        rep movsb;
        add di,bx;
        dec dh;
        jne cv1;
        jmp cvend;
    }
cv2:
    asm
    {
        mov cl,dl;
    }
cv3:
    asm
    {
        lodsb;
        cmp al,255;
        je cv5;
        stosb;
        loop cv3;
    }
cv4:
    asm
    {
        add di,bx;
        dec dh;
        jne cv2;
        jmp cvend;
    }
cv5:
    asm
    {
        inc di;
        loop cv3;
        jmp cv4;
    }
cvend:
    asm
    {
        pop si;
        pop ds;
        pop di;
        pop es;
    }
}
void CopyPlane2Buf (OCTET *bufptr,OCTET depage,short dex,short dey,
                    OCTET largeur,OCTET hauteur)
{
    unsigned long buffer;
    buffer = (long)(bufptr);
    asm
    {
        push es;
        push di;
        push ds;
        push si;
        mov ah,0xA0;
        cmp depage,0;
        je cc0;
        mov ah,0xA8;
    }
cc0:
    asm
    {
        xor al,al;
        mov ds,ax;
        mov ax,80;
        mul dey;
        mov si,dex;
        mov cx,si;
        shr si,1;
        shr si,1;
        add si,ax;
        and cl,3;
        mov ah,cl;
        mov al,0x04;
        mov dx,0x03ce;
        out dx,ax;
        mov dh,hauteur;
        mov dl,largeur;
        mov bx,80;
        sub bl,dl;
        xor ch,ch;
        les di,buffer;
    }
cc1:
    asm
    {
        mov cl,dl;
        rep movsb;
        add si,bx;
        dec dh;
        jne cc1;
        pop si;
        pop ds;
        pop di;
        pop es;
    }
}
BOOL Creer_Bob (short num_bob,short largeur,short hauteur)
{
    short taille_bob;
    OCTET *buffer;
    if (bob[num_bob].presence != 1)
    {
        taille_bob = largeur * hauteur;
        buffer = malloc (taille_bob);
        if (buffer == NULL)
            return (FAUX);
        bob[num_bob].presence = 1;
        bob[num_bob].pointeurbitplan[0] = buffer;
        bob[num_bob].largeur = largeur;
        bob[num_bob].nombreligne = hauteur;
    }
    else
        return (FAUX);
    return (VRAI);
}
BOOL Lire_Bob (short num_bob,OCTET page,short x,short y)
{
    OCTET cpt_bitplan;
    OCTET plancour;
    OCTET sb;
    OCTET eb;
    OCTET b;
    OCTET am;
    OCTET largeur;
    OCTET hauteur;
    OCTET *buffer;
    if (bob[num_bob].presence == 1)
    {
        buffer = bob[num_bob].pointeurbitplan[0];
        largeur = bob[num_bob].largeur;
        hauteur = bob[num_bob].nombreligne;
        am = (OCTET)(((x+largeur-1)&~3)-((x+4)&~3)) >>2;
        sb = (OCTET)(x%4);
        eb = (OCTET)((x+largeur-1)%4);
        for (cpt_bitplan = 0;
                cpt_bitplan < 4;
                cpt_bitplan ++)
        {
            plancour = (sb+cpt_bitplan) % 4;
            b = am;
            if (plancour >= sb) ++b;
            if (plancour <= eb) ++b;
            bob[num_bob].pointeurbitplan[cpt_bitplan] = buffer;
            bob[num_bob].nombrepoint [cpt_bitplan] = b;
            CopyPlane2Buf (buffer,
                           page,
                           x+cpt_bitplan,
                           y,
                           b,
                           hauteur);
            buffer += b * hauteur;
        }
    }
    else
        return (FAUX);
    return (VRAI);
}
BOOL Afficher_Bob (OCTET page,short num_bob,short x1,short y1,OCTET masq)
{
    OCTET cpt_plan;
    if (bob[num_bob].presence == 1)
    {
        for (cpt_plan = 0;
                cpt_plan < 4;
                cpt_plan ++)
            CopyBuf2Plane (bob[num_bob].pointeurbitplan[cpt_plan],
                           page,
                           x1 + cpt_plan,
                           y1,
                           bob[num_bob].nombrepoint [cpt_plan],
                           bob[num_bob].nombreligne,
                           masq);
    }
    else
        return (FAUX);
    return (VRAI);
}
BOOL Detruire_Bob (short num_bob)
{
    OCTET *buffer;
    if (bob[num_bob].presence == 1)
    {
        buffer = bob[num_bob].pointeurbitplan[0];
        free (buffer);
        bob[num_bob].presence = 0;
    }
    else
        return (FAUX);
    return (VRAI);
}
void Afficher_Nombre (OCTET pg,OCTET nm,OCTET nu,ULONG nb,short x,short y,
                      OCTET ms)
{
    char buffer[6];
    char cptnb;
    char unite;
    for (cptnb = 0;
            cptnb < nu;
            cptnb ++)
    {
        unite = nb - ( (nb/10)*10 );
        buffer [cptnb] = unite;
        nb /= 10;
    }
    for (cptnb = nu-1;
            cptnb >= 0;
            cptnb --)
    {
        Afficher_Bob (pg,nm + buffer [cptnb],x,y,ms);
        x += 8;
    }
}
void Definir_Bobs (void)
{
    short cpt;
    for (cpt = 0;
            cpt < NB_BOB_BLOC;
            cpt ++)
        Creer_Bob (BOB_BLOC + cpt,BLOC_LONG,BLOC_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_CHIFFRE2;
            cpt ++)
        Creer_Bob (BOB_CHIFFRE2 + cpt,CHIF2_LONG,CHIF2_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_PASTILLE;
            cpt ++)
        Creer_Bob (BOB_PASTILLE + cpt,PASTILLE_LONG,PASTILLE_HAUT);
    Creer_Bob (BOB_FOND,FOND_LONG,FOND_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_BORDURE;
            cpt ++)
        Creer_Bob (BOB_BORDURE + cpt,BORDURE_LONG,BORDURE_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_ROUGE;
            cpt ++)
        Creer_Bob (BOB_SERPENT_ROUGE + cpt,
                   SERPENT_ROUGE_LONG,
                   SERPENT_ROUGE_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_VERT;
            cpt ++)
        Creer_Bob (BOB_SERPENT_VERT + cpt,
                   SERPENT_VERT_LONG,
                   SERPENT_VERT_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_BLEU;
            cpt ++)
        Creer_Bob (BOB_SERPENT_BLEU + cpt,
                   SERPENT_BLEU_LONG,
                   SERPENT_BLEU_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_NOIR;
            cpt ++)
        Creer_Bob (BOB_SERPENT_NOIR + cpt,
                   SERPENT_NOIR_LONG,
                   SERPENT_NOIR_HAUT);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_BLANC;
            cpt ++)
        Creer_Bob (BOB_SERPENT_BLANC + cpt,
                   SERPENT_BLANC_LONG,
                   SERPENT_BLANC_HAUT);
    Afficher_Page (PAGE0);
    Lire_Image_Pcx ("SPRFILES/DATA",PAGE1,0,0,MASK_OFF,0,0,319,399);
    for (cpt = 0;
            cpt < NB_BOB_BLOC;
            cpt ++)
        Lire_Bob (BOB_BLOC + cpt,PAGE1,117 + (cpt * BLOC_LONG),16);
    for (cpt = 0;
            cpt < NB_BOB_CHIFFRE2;
            cpt ++)
        Lire_Bob (BOB_CHIFFRE2 + cpt,PAGE1,2 + (cpt * CHIF2_LONG),27);
    for (cpt = 0;
            cpt < NB_BOB_PASTILLE;
            cpt++)
        Lire_Bob (BOB_PASTILLE + cpt,PAGE1,2 + (cpt * PASTILLE_LONG),2);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_ROUGE;
            cpt ++)
        Lire_Bob (BOB_SERPENT_ROUGE + cpt,PAGE1,
                  2 + (cpt * SERPENT_ROUGE_LONG),48);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_VERT;
            cpt ++)
        Lire_Bob (BOB_SERPENT_VERT + cpt,PAGE1,
                  2 + (cpt * SERPENT_VERT_LONG),60);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_BLEU;
            cpt ++)
        Lire_Bob (BOB_SERPENT_BLEU + cpt,PAGE1,
                  2 + (cpt * SERPENT_BLEU_LONG),72);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_NOIR;
            cpt ++)
        Lire_Bob (BOB_SERPENT_NOIR + cpt,PAGE1,
                  2 + (cpt * SERPENT_NOIR_LONG),84);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_BLANC;
            cpt ++)
        Lire_Bob (BOB_SERPENT_BLANC + cpt,PAGE1,
                  2 + (cpt * SERPENT_BLANC_LONG),96);
}
void Supprimer_Bobs (void)
{
    short cpt;
    for (cpt = 0;
            cpt < NB_BOB_BLOC;
            cpt ++)
        Detruire_Bob (BOB_BLOC + cpt);
    for (cpt = 0;
            cpt < NB_BOB_CHIFFRE2;
            cpt ++)
        Detruire_Bob (BOB_CHIFFRE2 + cpt);
    for (cpt = 0;
            cpt < NB_BOB_PASTILLE;
            cpt ++)
        Detruire_Bob (BOB_PASTILLE + cpt);
    Detruire_Bob (BOB_FOND);
    for (cpt = 0;
            cpt < NB_BOB_BORDURE;
            cpt ++)
        Detruire_Bob (BOB_BORDURE + cpt);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_ROUGE;
            cpt ++)
        Detruire_Bob (BOB_SERPENT_ROUGE + cpt);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_VERT;
            cpt ++)
        Detruire_Bob (BOB_SERPENT_VERT + cpt);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_BLEU;
            cpt ++)
        Detruire_Bob (BOB_SERPENT_BLEU + cpt);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_NOIR;
            cpt ++)
        Detruire_Bob (BOB_SERPENT_NOIR + cpt);
    for (cpt = 0;
            cpt < NB_BOB_SERPENT_BLANC;
            cpt ++)
        Detruire_Bob (BOB_SERPENT_BLANC + cpt);
}
void Wait_Retrace (void)
{
    asm
    {
        mov dx,0x03da;
    }
wait1:
    asm
    {
        in al,dx;
        test al,0x08;
        jnz wait1;
    }
wait2:
    asm
    {
        in al,dx;
        test al,0x08;
        jz wait2;
    }
}
