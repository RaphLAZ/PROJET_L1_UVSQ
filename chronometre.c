#include "uvsqgraphics.h"
#define LARGEUR_ECRAN 900
#define HAUTEUR_ECRAN 600
#define PI 3.14159


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




void transforme(int a, int segments[7]){
	int i;
	for(i = 0; i < 7; i++) // cela revient à créer le chiffre 8
		segments[i] = 1;
		
	if(a == 1 || a == 4)
		segments[0] = 0; // segment horizontal du haut
	if(a == 0 || a == 1 || a == 7)
		segments[1] = 0; // segment horizontal du milieu
	if(a == 1 || a == 4 || a == 7)
		segments[2] = 0; // segment horizontal du bas
	if(a == 1 || a == 2 || a == 3 || a == 7)
		segments[3] = 0; // segment vertical en haut à gauche
	if(a == 1 || a == 3 || a == 4 || a == 5 || a == 7 || a == 9)
		segments[4] = 0; // segment vertical en bas à gauche
	if(a == 5 || a == 6)
		segments[5] = 0; // segment vertical en haut à droite
	if(a == 2)
		segments[6] = 0; // segment vertical en haut à droite
}

void dessine_chiffre(int segments[], POINT pos[]){
	int i;
	for(i = 0; i < 7; i++)
		if(segments[i]){ // TRUE fera dessiner le segment
			if(i < 3) // les 3 segments horizontaux
				draw_line(pos[i], pos[i + 3], white);
			else
				if(i < 5) // les 2 segments verticaux à gauche
					draw_line(pos[i - 3], pos[i - 2], white);
				else // les 2 segments verticaux à droite
					draw_line(pos[i - 2], pos[i - 1], white);
		}
}

void afficher_dizaine_heure(int segments[]){
	POINT pos[6]; // par ordre croissant : du haut vers le bas à gauche, puis à droite 
	
	pos[0].x = pos[1].x = pos[2].x = 9 * LARGEUR_ECRAN / 40;
	pos[3].x = pos[4].x = pos[5].x = 11 * LARGEUR_ECRAN / 40;
	pos[0].y = pos[3].y = HAUTEUR_ECRAN / 4;
	pos[1].y = pos[4].y = pos[0].y - LARGEUR_ECRAN / 20;
	pos[2].y = pos[5].y = pos[1].y - LARGEUR_ECRAN / 20;

	dessine_chiffre(segments, pos);
}

void afficher_unite_heure(int segments[]){
	POINT pos[6]; 
	
	pos[0].x = pos[1].x = pos[2].x = 13 * LARGEUR_ECRAN / 40;
	pos[3].x = pos[4].x = pos[5].x = 15 * LARGEUR_ECRAN / 40;
	pos[0].y = pos[3].y = HAUTEUR_ECRAN / 4;
	pos[1].y = pos[4].y = pos[0].y - LARGEUR_ECRAN / 20;
	pos[2].y = pos[5].y = pos[1].y - LARGEUR_ECRAN / 20;

	dessine_chiffre(segments, pos);
}

void afficher_dizaine_minute(int segments[]){
	POINT pos[6]; 
	
	pos[0].x = pos[1].x = pos[2].x = 17 * LARGEUR_ECRAN / 40;
	pos[3].x = pos[4].x = pos[5].x = 19 * LARGEUR_ECRAN / 40;
	pos[0].y = pos[3].y = HAUTEUR_ECRAN / 4;
	pos[1].y = pos[4].y = pos[0].y - LARGEUR_ECRAN / 20;
	pos[2].y = pos[5].y = pos[1].y - LARGEUR_ECRAN / 20;

	dessine_chiffre(segments, pos);
}

void afficher_unite_minute(int segments[]){
	POINT pos[6]; 
	
	pos[0].x = pos[1].x = pos[2].x = 21 * LARGEUR_ECRAN / 40;
	pos[3].x = pos[4].x = pos[5].x = 23 * LARGEUR_ECRAN / 40;
	pos[0].y = pos[3].y = HAUTEUR_ECRAN / 4;
	pos[1].y = pos[4].y = pos[0].y - LARGEUR_ECRAN / 20;
	pos[2].y = pos[5].y = pos[1].y - LARGEUR_ECRAN / 20;

	dessine_chiffre(segments, pos);
}

void afficher_dizaine_seconde(int segments[]){
	POINT pos[6]; 
	
	pos[0].x = pos[1].x = pos[2].x = 25 * LARGEUR_ECRAN / 40;
	pos[3].x = pos[4].x = pos[5].x = 27 * LARGEUR_ECRAN / 40;
	pos[0].y = pos[3].y = HAUTEUR_ECRAN / 4;
	pos[1].y = pos[4].y = pos[0].y - LARGEUR_ECRAN / 20;
	pos[2].y = pos[5].y = pos[1].y - LARGEUR_ECRAN / 20;

	dessine_chiffre(segments, pos);
}

void afficher_unite_seconde(int segments[]){
	POINT pos[6]; 
	
	pos[0].x = pos[1].x = pos[2].x = 29 * LARGEUR_ECRAN / 40;
	pos[3].x = pos[4].x = pos[5].x = 31 * LARGEUR_ECRAN / 40;
	pos[0].y = pos[3].y = HAUTEUR_ECRAN / 4;
	pos[1].y = pos[4].y = pos[0].y - LARGEUR_ECRAN / 20;
	pos[2].y = pos[5].y = pos[1].y - LARGEUR_ECRAN / 20;

	dessine_chiffre(segments, pos);
}

void deux_points(){
	POINT p1, p2;
	
	p1.x = p2.x = 2 * LARGEUR_ECRAN / 5;
	p1.y = HAUTEUR_ECRAN / 5;
	p2.y = HAUTEUR_ECRAN / 6;
	draw_fill_circle(p1, 2, white);
	draw_fill_circle(p2, 2, white);
	
	p1.x = p2.x = 3 * LARGEUR_ECRAN / 5;
	draw_fill_circle(p1, 2, white);
	draw_fill_circle(p2, 2, white);
}

void afficher_digitale(int h, int m, int s){
	int segments[7];
	
	if(s % 2)
		deux_points();
		
	transforme(h / 10, segments);
	afficher_dizaine_heure(segments);
	transforme(h % 10, segments);
	afficher_unite_heure(segments);
	
	transforme(m / 10, segments);
	afficher_dizaine_minute(segments);
	transforme(m % 10, segments);
	afficher_unite_minute(segments);
	
	transforme(s / 10, segments);
	afficher_dizaine_seconde(segments);
	transforme(s % 10, segments);
	afficher_unite_seconde(segments);
}

struct chrono { int h; int m; int s;};
typedef struct chrono CHRONO;

void afficher_bouton()
{
	POINT p1,p2;
	p1.x=p1.y=0;
	p2.x=p2.y=30;
	draw_fill_rectangle(p1,p2,rouge);
}

CHRONO init_chronometre()
{
	CHRONO c;
	c.h = c.m = c.s = 0;
	return c;
}
void afficher_chrono(CHRONO c)
{
	afficher_digitale(c.h, c.m, c.s);
}


void affiche_bouton_start()
{
	POINT p1,p2,p3;
	p1.x=0;p1.y=HAUTEUR_ECRAN-1;
	p2.x=90; p2.y=p1.y-20;
	draw_rectangle(p1,p2,rouge);
	p3.x=p1.x;p3.y=p1.y+2;
	aff_pol("start/stop",18,p3,blanc);
}
void affiche_bouton_tour()
{
	POINT p1,p2,p3;
	p1.x=0;p1.y=HAUTEUR_ECRAN-22;
	p2.x=90; p2.y=p1.y-20;
	draw_rectangle(p1,p2,vert);
	p3.x=p1.x+30;p3.y=p1.y+2;
	aff_pol("tour",18,p3,blanc);
	}
	
	



int main()
{
	init_graphics(LARGEUR_ECRAN, HAUTEUR_ECRAN);
	affiche_auto_off();
	
	int s, m, h = 0;
	POINT p;
	
	while(1){
		p=wait_clic();
		afficher_bouton();
		affiche_bouton_start();
		affiche_bouton_tour();
		if ((p.x<80) && (p.y>(HAUTEUR_ECRAN-20)))
		{
			chrono_start();
		}
		h = heure();
		m = minute();
		s = seconde();
		fill_screen(black);
		afficher_cadran();
		afficher_aiguilles(h, m, s);
		afficher_digitale(h, m, s);
		affiche_all();
		attendre(250);
		
	}
	
	wait_escape();
	exit(0);
}


