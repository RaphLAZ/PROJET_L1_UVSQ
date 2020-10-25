#include "uvsqgraphics.h"
int nbm_allumette, enleve, game;
POINT texte,allumette;


void affiche_une_allumette(POINT p)
{
	POINT p1;
	p1.x = p.x + 30;
	p1.y = 300 + p.y;
	draw_fill_rectangle(p,p1,blanc);
}

void efface_une_allumette(POINT p)
{
	POINT p1;
	p.x += 50*enleve;
	p1.x = p.x + 30;
	p1.y = 300 + p.y;
	draw_fill_rectangle(p,p1,noir);
	draw_rectangle(p,p1,blanc);
}

void affiche_allumette(int N)
{
	POINT centre;
	centre.x = 125; centre.y = 400;
	int i;
	for (i = 0; i < N ; i++)
	{
		affiche_une_allumette(centre);
		centre.x += 50;
		
	}
	nbm_allumette = N;
	tableur_type();
}

void affiche_123()
{
	POINT p1,p2;
	/*Coordonée 1 ==> 200/400x 100/300y
	 *Coordonée 2 ==> 600/800x 100/300y
	 *Coordonée 3 ==> 1000/1200x 100/300y*/
	p1.x = 600; p1.y = 100;
	p2.x = 800; p2.y = 300;
	draw_rectangle(p1,p2,blanc);
	p1.x +=400; p2.x+=400;
	draw_rectangle(p1,p2,blanc);
	p1.x -=800; p2.x -=800;
	draw_rectangle(p1,p2,blanc);
	p1.x +=100; p1.y +=100;
	draw_fill_circle(p1,25,blanc);
	p1.x +=363; p2.x+=337;
	p1.y +=37; p2.y-=137;
	draw_fill_circle(p1,25,blanc);
	draw_fill_circle(p2,25,blanc);
	p1.x +=388; p2.x+=413;
	p1.y +=12; p2.y-=12;
	draw_fill_circle(p1,25,blanc);
	draw_fill_circle(p2,25,blanc);
	p1.x += 50; p1.y -= 50;
	draw_fill_circle(p1,25,blanc);	
}

int get_valeur()
{
	POINT p;
	p = wait_clic();
	if ((200 <= p.x && p.x <= 400) && (100 <= p.y && p.y <= 300))
	{
		return 1;
	}
	else if ((600 <= p.x && p.x <= 800) && (100 <= p.y && p.y <= 300))
	{
		return 2;
	}
	else if ((1000 <= p.x && p.x <= 1200) && (100 <= p.y && p.y <= 300))
	{
		return 3;
	}
	else return 0;
}

void jouer_humain()
{
	int a,i;
	POINT centre;
	centre.x = 125; centre.y = 400;
	a=0;
	while (a == 0)
	{
		a = get_valeur();
		for (i = 0; i < a; i++)
		{
			efface_une_allumette(centre);
			enleve +=1;
		}
		tableur_type();
	}
}

void jouer()
{
	POINT prenom;
	prenom.x = 700; prenom.y = 750;
	int joueur;
	joueur = 0;
	while (game == 0)
	{
		if (joueur == 0)
		{
			aff_pol_centre("JOUEUR 2",50, prenom,noir);
			aff_pol_centre("JOUEUR 1",50, prenom,blanc);
			jouer_humain();
			joueur = 1 - joueur;
		}
		else if (joueur == 1)
		{
			aff_pol_centre("JOUEUR 1",50, prenom,noir);
			aff_pol_centre("JOUEUR 2",50, prenom,blanc);
			jouer_humain();
			joueur = 1 - joueur;
		}
		if (nbm_allumette-enleve == 1)
		{
			if (joueur == 1)
			{
				game = 1;
			}
			else
			{
				game = 2;
			}
		}
		else if (nbm_allumette-enleve < 1)
		{
			if (joueur == 1)
			{
				game = 2;
			}
			else
			{
				game = 1;
			}
		}
	}
}

void tableur_type()
{
	POINT g,d;
	g.x = 260; g.y = 770;
	d.x = 290; d.y = 800;
	texte.x =10; texte.y=800;
	allumette.x = 260; allumette.y =800;
	aff_pol("Nombre allumette =", 24, texte, blanc);
	draw_fill_rectangle(d,g,noir);
	aff_int(nbm_allumette - enleve, 24,allumette, rouge);
}

int main()
{
init_graphics(1400,800);

// Debut du code
POINT a;
enleve = 0; game = 0;
affiche_123();
affiche_allumette(23);
jouer();
fill_screen(noir);
a.x = 700; a.y = 400;
if (game == 1)
{
	aff_pol_centre("JOUEUR 1 est gagnant !",50, a,blanc);
}
else if (game == 2)
{
	aff_pol_centre("JOUEUR 2 est gagnant !",50, a,blanc);
}




// Fin du code

wait_escape();
exit(0);
}
