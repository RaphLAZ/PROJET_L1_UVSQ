#include "uvsqgraphics.h"
#define LARGEUR_ECRAN 1000
#define HAUTEUR_ECRAN 1000


void afficher_cadran(){
	int rayon = HAUTEUR_ECRAN / 2;
	POINT centre;
	centre.x = LARGEUR_ECRAN / 2;
	centre.y = HAUTEUR_ECRAN / 2;
	draw_circle(centre, rayon, white);
	
	int i;
	POINT c;
	for(i = 0; i < 12; i++){
		c.x = centre.x + 0.95 * rayon * cosf(M_PI / 2 - i * M_PI / 6) - 5;
		c.y = centre.y + 0.95 * rayon * sinf(M_PI / 2 - i * M_PI / 6) + 15;
		if((11 + i) % 12 + 1 > 9)
			c.x -= 5;
		aff_int((11 + i) % 12 + 1, 20, c, blue);
	}
}

void afficher_aiguille_heure(int h){
	int rayon = HAUTEUR_ECRAN / 3;
	POINT centre;
	centre.x = LARGEUR_ECRAN / 2;
	centre.y = HAUTEUR_ECRAN / 2;
	
	POINT P = centre;
	P.x += rayon * cosf(M_PI / 2 - h * M_PI / 6);
	P.y += rayon * sinf(M_PI / 2 - h * M_PI / 6);
	
	draw_line(centre, P, green);
}

void afficher_aiguille_minute(int m){
	int rayon = HAUTEUR_ECRAN / 2.3;
	POINT centre;
	centre.x = LARGEUR_ECRAN / 2;
	centre.y = HAUTEUR_ECRAN / 2;
	
	POINT P = centre;
	P.x += rayon * cosf(M_PI / 2 - m * M_PI / 30);
	P.y += rayon * sinf(M_PI / 2 - m * M_PI / 30);
	
	draw_line(centre, P, blue);
}

void afficher_aiguille_seconde(int s){
	int rayon = HAUTEUR_ECRAN / 2;
	POINT centre;	
	centre.x = LARGEUR_ECRAN / 2;
	centre.y = HAUTEUR_ECRAN / 2;
	
	POINT P = centre;
	P.x += rayon * cosf(M_PI / 2 - s * M_PI / 30);
	P.y += rayon * sinf(M_PI / 2 - s * M_PI / 30);
	
	draw_line(centre, P, red);
}

void afficher_aiguilles(int h, int m, int s){
	afficher_aiguille_heure(h);
	afficher_aiguille_minute(m);
	afficher_aiguille_seconde(s);
}



int main()
{
	init_graphics(LARGEUR_ECRAN, HAUTEUR_ECRAN);
	
	
	int s, m, h = 0;
	
	while(1)
	{
		affiche_auto_off();
		h = heure();
		m = minute();
		s = seconde();
		fill_screen(black);
		afficher_cadran();
		afficher_aiguilles(h, m, s);
		affiche_all();
		attendre(1000);
		
	}
	
	wait_escape();
	exit(0);
}


