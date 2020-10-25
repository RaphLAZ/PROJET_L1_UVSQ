#include "uvsqgraphics.h"

#define lar 1000
#define lng 1000
#define radius 20
#define Nb_balle 100
#define hauteur_raquette 10
#define largeur_raquette 200
#define vie 1
#define hauteur_brique lng/20
#define Nb_brique_ligne 20
#define Nb_brique_colonne 10
#define Nb_ligne 5

int plafond = lng;

struct balle{
	POINT centre;
	int rayon;
	COULEUR coul;
	int dx, dy;
};

typedef struct balle BALLE;

struct raquette{
	POINT centre; // centre de la raquette
	int largeur; // largeur de la raquette
	int hauteur; // hauteur de la raquette
	COULEUR coul; // couleur de la raquette
};

typedef struct raquette RAQUETTE;

struct brique{
	POINT bg; // point en bas à gauche de la brique
	int largeur; // largeur de la brique
	int hauteur; // hauteur de la brique
	COULEUR coul; // couleur de la brique
	int casse;
};

typedef struct brique BRIQUE;

BRIQUE br[Nb_brique_colonne][Nb_brique_ligne];
BALLE b;
RAQUETTE r;

void init_briques(){
	
	BRIQUE brik;
	POINT hd;
	
	brik.largeur = lar/Nb_brique_colonne; // On décide la largeur de nos briques
	brik.hauteur = lng/Nb_brique_ligne; // On décide la hauteur de nos briques
	
	int i,j;
	
	affiche_auto_off();
	
	for (i = 0; i < Nb_brique_colonne; i++){
		for (j = 0; j < Nb_brique_ligne; j++){
			switch (alea_int(4)){ // On met une couleur aléatoire à chaque brique
				case 0:
					brik.coul = red;
					break;
				case 1:
					brik.coul = blue;
					break;
				case 2:
					brik.coul = yellow;
					break;
				default:
					brik.coul = green;
			}
			
			brik.bg.x = (i * brik.largeur) + 5; // On place le point en bas à gauche pour chaque brique
			brik.bg.y = (j * brik.hauteur) + 5;
			
			hd.x = brik.bg.x + brik.largeur - 5; // On place le point en haut à droite pour chaque brique en fonction du point en bas à gauche, on met -5 pour pas que les briques ne soit collées
			hd.y = brik.bg.y + brik.hauteur - 5;
			
			brik.casse = 0; // On indique que les briques ne sont pas cassé
			
			if (j < Nb_brique_ligne - Nb_ligne){
				brik.coul = black;
				brik.casse = 1;
			}
			
			br[i][j] = brik; 
			
			printf("casse de la brique br[%d][%d] = %d \n", i, j, br[i][j].casse);
			draw_fill_rectangle(brik.bg,hd,brik.coul);
			// attendre(10000);			
		}
	}	
	
	affiche_all();
}

int choc_balle_brique(){

	int i,j;
	POINT hd;
	/* Faire le test sur la position x/y et voir si on tape une brique en haut en bas a gauche et a droite au lieu de parcourir une double boucle
	 */
	 
	// test du choc en haut de la balle
	i = (b.centre.x) / (lar/Nb_brique_colonne);
	j = (b.centre.y + radius) / (lng/Nb_brique_ligne);
	
		if(!br[i][j].casse){
			if (br[i][j].coul == b.coul){
				hd.x = br[i][j].bg.x + br[i][j].largeur;
				hd.y = br[i][j].bg.y + br[i][j].hauteur;
				br[i][j].casse = 1;
				draw_fill_rectangle(br[i][j].bg, hd, black);
			}else{
				switch (alea_int(4)){
					case 0:
						b.coul = red;
						break;
					case 1:
						b.coul = blue;
						break;
					case 2:
						b.coul = yellow;
						break;
					default:
						b.coul = green;
				}
			}
			return 1;
		}
		
		// test du choc à gauche de la balle
		i = (b.centre.x - radius) / (lar/Nb_brique_colonne);
		j = (b.centre.y) / (lng/Nb_brique_ligne);
		
		if(!br[i][j].casse){
			if (br[i][j].coul == b.coul){
				hd.x = br[i][j].bg.x + br[i][j].largeur;
				hd.y = br[i][j].bg.y + br[i][j].hauteur;
				br[i][j].casse = 1;
				draw_fill_rectangle(br[i][j].bg, hd, black);
			}else{
				switch (alea_int(4)){
					case 0:
						b.coul = red;
						break;
					case 1:
						b.coul = blue;
						break;
					case 2:
						b.coul = yellow;
						break;
					default:
						b.coul = green;
				}
			}
			return 2;
		}
		
		//test du choc à droite de la balle
		i = (b.centre.x + radius) / (lar/Nb_brique_colonne);
		j = (b.centre.y) / (lng/Nb_brique_ligne);
		
		if (i < Nb_brique_colonne){
			if(!br[i][j].casse){
				if (br[i][j].coul == b.coul){
					hd.x = br[i][j].bg.x + br[i][j].largeur;
					hd.y = br[i][j].bg.y + br[i][j].hauteur;
					br[i][j].casse = 1;
					draw_fill_rectangle(br[i][j].bg, hd, black);
				}else{
					switch (alea_int(4)){
						case 0:
							b.coul = red;
							break;
						case 1:
							b.coul = blue;
							break;
						case 2:
							b.coul = yellow;
							break;
						default:
							b.coul = green;
					}
				}
				return 2;
			}			
		}
		

		
		// test du choc en bas de la balle
		i = (b.centre.x) / (lar/Nb_brique_colonne);
		j = (b.centre.y - radius) / (lng/Nb_brique_ligne);
		
		if(!br[i][j].casse){
			if (br[i][j].coul == b.coul){
				hd.x = br[i][j].bg.x + br[i][j].largeur;
				hd.y = br[i][j].bg.y + br[i][j].hauteur;
				br[i][j].casse = 1;
				draw_fill_rectangle(br[i][j].bg, hd, black);
			}else{
				switch (alea_int(4)){
					case 0:
						b.coul = red;
						break;
					case 1:
						b.coul = blue;
						break;
					case 2:
						b.coul = yellow;
						break;
					default:
						b.coul = green;
				}
			}
			return 1;
		}
	
		return 0;
}

BALLE init_balle(){
	
	BALLE b;
	POINT p;
	
	p.x = lar/2;
	p.y = radius + 50;
	
	b.centre = p;
	b.rayon = radius;
	b.coul = white;
	b.dx = b.dy = 1;
	
	return b;
}

void affiche_balle(){
	
	draw_fill_circle(b.centre, b.rayon, b.coul);
}

void efface_balle(){
	
	draw_fill_circle(b.centre, b.rayon, black);
}

BALLE deplace_balle(){

	b.centre.x += b.dx;
	b.centre.y += b.dy;
	
	return b;
}

BALLE rebond_balle(){
	
	if(b.centre.x + radius > lar || b.centre.x - radius < 0){
		b.dx = - b.dx;
	}
	
	if(b.centre.y + radius >= plafond){
		b.dy = - b.dy;
	}
	
	return b;
}

RAQUETTE init_raquette(){
	
	RAQUETTE r;
	
	r.centre.x = lar/2;
	r.centre.y = 5 + hauteur_raquette;
	
	r.largeur = largeur_raquette;
	r.hauteur = hauteur_raquette;
	
	r.coul = white;
	
	return r;
}

void affiche_raquette(){
	
	POINT bg, hd;
	
	bg.x = r.centre.x - r.largeur/2; hd.x = r.centre.x + r.largeur/2;
	bg.y = r.centre.y - r.hauteur/2; hd.y = r.centre.y + r.hauteur/2;
	
	draw_fill_rectangle(bg, hd, r.coul);
}

void efface_raquette(){
	
	POINT bg, hd;
	
	bg.x = r.centre.x - r.largeur/2; hd.x = r.centre.x + r.largeur/2;
	bg.y = r.centre.y - r.hauteur/2; hd.y = r.centre.y + r.hauteur/2;
	
	draw_fill_rectangle(bg, hd, black);
}

RAQUETTE deplace_raquette(){
	
	
	POINT direction;
	
	direction = get_arrow();
	
	if(r.centre.x + 3*direction.x - r.largeur/2 > 0 && r.centre.x + 3*direction.x + r.largeur/2 < lar)
		r.centre.x += 3*direction.x;
	
	return r;
}

int choc_balle_raquette(){
	COULEUR c;
	
	if(b.centre.y - b.rayon == r.centre.y + r.hauteur/2){
		if (b.centre.x >= r.centre.x - r.largeur/2 && b.centre.x <= r.centre.x + r.largeur/2){
			
			c = b.coul;
			b.coul = r.coul;
			r.coul = c;
			
			return 1;
		}	
	}
	
	return 0;
}

int test_en_jeu(){
	
	if(b.centre.y + b.rayon <= 0)
		return 0;
	else
		return 1;
}

int test_fin_de_jeu(){
	
	int i,j,fin;
	
	fin = 1;
	for (i = 0; i < Nb_brique_colonne; i++){
		for (j = 0; j < Nb_brique_ligne; j++){
			if(!br[i][j].casse)
				fin = 0;
		}
	}
	
	return fin;
}
int main(){
	init_graphics(lar,lng);
	
	b = init_balle();
	r = init_raquette();
	
	init_briques();
	
	affiche_auto_off();
	
	int life, choc;
	choc = 0;
	life = vie;

	while(life){
		attendre(0);
		affiche_balle();
		affiche_raquette();
		
		affiche_all();
		
		efface_balle();
		efface_raquette();
		
		b = deplace_balle();
		r = deplace_raquette();
		
		b = rebond_balle(b);
				
		if (choc_balle_raquette()){
			b.dy = - b.dy;
		}
		
		choc = choc_balle_brique();
		
		if(choc == 1){
			b.dy = - b.dy;
		}else if (choc == 2){
			b.dx = - b.dx;
		}
		

		if(!test_en_jeu()){
			life -= 1;
			fill_screen(black);
			b = init_balle();
		}
		
		if(test_fin_de_jeu())
			life = 0;
	}
	
	
	
	wait_escape();
	exit(0);
}
