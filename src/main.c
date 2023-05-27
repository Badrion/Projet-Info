#include "main.h"


//
//INIT DES STRUCTURES
//

Info_Fenetre* init_Info_Fenetre(){
  
  Info_Fenetre* pFenetre = NULL;
  if( !(pFenetre = malloc(sizeof(Info_Fenetre)))){
    printf("Erreur malloc Info_Fenetre");
    exit(5);
  }
  
  pFenetre->pWin = NULL;

  pFenetre->ecran = ACCUEIL;

  pFenetre->camJeu = constructor_Info_Cam(16*2, 9*2); //la caméra est en 16/9 du coup (48/27)
  pFenetre->camAccueil = constructor_Info_Cam(16*2, 9*2);

  pFenetre->initialTime = 0;
  pFenetre->startTime = 0;
  pFenetre->endTime = 0;
  pFenetre->frameTime = 0;
  
  pFenetre->fps = 2;

  return pFenetre;
}

Info_Jeu* init_Info_Jeu(){

  Info_Jeu* pJeu = NULL;
  if( !(pJeu = malloc(sizeof(Info_Jeu)))){
    printf("Erreur malloc Info_Jeu");
    exit(6);
  }

  pJeu->pJoueur = init_Entitee();
  // ! \\ déplacement en fonction d'une donnée de temps: toutes les 0.5 seconde

  if( !(pJeu->pQ_Radeau = malloc(sizeof(Quete)))){
    printf("Erreur malloc pQ_Radeau");
    exit(7);
  }
  if( !(pJeu->pQ_Survivant = malloc(sizeof(Quete)))){
    printf("Erreur malloc pQ_Survivant");
    exit(7);
  }

  pJeu->listeObj = init_ListeObj();
  
  pJeu->mapJeu = constructor_Map(70, 60);
  pJeu->mapAccueil = constructor_Map(16*2, 9*2);
  createMapAccueil(pJeu->mapAccueil);
  loadMapPrint(pJeu->mapAccueil);
  pJeu->mapOcean = constructor_Map(16*2, 9*2);
  createMapOcean(pJeu->mapOcean);
  pJeu->mapMort = constructor_Map(16*2, 9*2);
  
  

  pJeu->enJeu = 0;
  pJeu->score = 0;
  pJeu->temps = 0;
  
  pJeu->event = 0;

  return pJeu;
}


//
//RESET DES STRUCTURES
//

void res_Info_Jeu(Info_Jeu* pJeu){  
  
  pJeu->pJoueur->initial.x = 10;
  pJeu->pJoueur->initial.y = 10;
  pJeu->pJoueur->coordonnees.x = pJeu->pJoueur->initial.x;
  pJeu->pJoueur->coordonnees.y = pJeu->pJoueur->initial.y;

  pJeu->pJoueur->pvActuelle = 100;
  pJeu->pJoueur->vie = 2;

  res_Quete(pJeu->pQ_Radeau);
  res_Quete(pJeu->pQ_Survivant);


  pJeu->listeObj = init_ListeObj();

  pJeu->pJoueur->T_intervalleDeplacement = 500000; // Temps nécessaire entre chaques déplacement (1s = 1 000 000) 

  pJeu->enJeu = 1;
  pJeu->score = 0;
  
  pJeu->event = 0;
}

void debutJeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  res_Info_Jeu(pJeu);
  pFenetre->ecran = JEU;

  // Début du temps du jeu
  pFenetre->initialTime = getTimeMicros();
  pFenetre->startTime = getTimeMicros();
  pFenetre->endTime = getTimeMicros();
  
  pJeu->listeObj = init_ListeObj();

  res_Donnees_Map_tab(pJeu->mapJeu->pDonnees);
  res_Affichage_Map_tab(pJeu->mapJeu->pAffichage);
  
  generateMap(pJeu->mapJeu);
  loadMapPrint(pJeu->mapJeu);

}

void reprendreJeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  // charge la derniere partie en cour
  res_Info_Jeu(pJeu);
  pFenetre->ecran = JEU;

  pJeu->listeObj = init_ListeObj();
  
  generateMap(pJeu->mapJeu);
  loadMapPrint(pJeu->mapJeu);
}


//
//AUTRES FONCTIONS
//

void init_Curses(Info_Fenetre* pFenetre){
  printf("Locale: %s\n", setlocale(LC_ALL, "en_US.UTF-8"));
  
  if( !(pFenetre->pWin = initscr())){
    printf("Erreur lors de initscr() !");
    exit(1);
  }

  // Paramétrage de la récupération des touches
  noecho();
  curs_set(0);
  if(nodelay(pFenetre->pWin, TRUE) == ERR){
    printf("erreur lors de l'activation de nodelay");
    endwin();
    exit(4);
  }

    
  // Création des couleurs
  start_color();
  init_Brush();
}

void freeGame(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  echo();
  endwin();

  free(pFenetre->camJeu); 
  free_Map(pJeu->mapJeu);
  free(pFenetre->camAccueil); 
  free_Map(pJeu->mapAccueil);
  free_Map(pJeu->mapOcean);
  free_Map(pJeu->mapMort);
 
  free(pJeu->pJoueur);
  free(pJeu->pQ_Radeau);
  free(pJeu->pQ_Survivant);
  
  free(pFenetre);
  free(pJeu);
}



void affiche_jeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  Info_Cam* pCam = NULL;
  Map* pMap = NULL;
  
  switch(pFenetre->ecran){
    case ACCUEIL:
      pCam = pFenetre->camAccueil;
      pMap = pJeu->mapAccueil;
      break;
    case JEU:
      pCam = pFenetre->camJeu;
      pMap = pJeu->mapJeu;
      break;
    case OCEAN:
      pCam = pFenetre->camAccueil;
      pMap = pJeu->mapOcean;
      break;
    case MORT:
      pCam = pFenetre->camAccueil;
      pMap = pJeu->mapMort;
      break;
  }

  if(pFenetre->ecran == OCEAN){
    Coordonnees coord;
    coord.x = 16; coord.y = 9;
    printFin_Radeau(coord, pMap->pAffichage, pCam);
  }
  else{
    // actualise la partie affichage de la map
    loadCamPrint(pJeu->pJoueur->coordonnees, pMap, pCam);
    printCam(pJeu->pJoueur->coordonnees, pMap->pAffichage, pCam);
    
    
    if(pFenetre->ecran == JEU){
      printStat(pFenetre, pJeu, 7);
      printDialogue(pFenetre, pJeu, 6);
      
      if(pJeu->pQ_Survivant->etape == 1){ // doit etre a 4
        attron(COLOR_PAIR(pMap->pAffichage->tab[pJeu->pJoueur->derniereCoordonnees.x][pJeu->pJoueur->derniereCoordonnees.y].brush));
        mvprintw((pJeu->pJoueur->derniereCoordonnees.y - pFenetre->camJeu->yCam) + 1, (pJeu->pJoueur->derniereCoordonnees.x - pFenetre->camJeu->xCam) *2 + 1, "🕺");
        attroff(COLOR_PAIR(pMap->pAffichage->tab[pJeu->pJoueur->derniereCoordonnees.x][pJeu->pJoueur->derniereCoordonnees.y].brush));
      }
    }
  }

  gestionFps(pFenetre);
  refresh();

}

void printStat(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height){
  int colonne = pFenetre->camJeu->width*2 + 2;
  int ligne = 0;
  
  move(ligne, colonne); 

  for(int i = 1; i < height; i++){
    mvprintw(ligne + i, colonne + 1, "                 ");
  }
  
  attron(COLOR_PAIR(BRUSH_STAT));
  ligne++;

  mvprintw(ligne, colonne + 1, "Timer: %05ld", pJeu->temps);
  ligne += 2;

  mvprintw(ligne, colonne + 1, "Score: %05d", pJeu->score);
  ligne +=2;

  mvprintw(ligne, colonne + 1, "PV: %03d", pJeu->pJoueur->pvActuelle);
  ligne += 2;


  attroff(COLOR_PAIR(BRUSH_STAT));


  // encadré
  move(0, colonne - 1);
  printw("╦");
  for(int i = 0; i<16; i++){
    printw("═");
  }
  printw("╗");
  
  for(int i = 1; i<height; i++){
    mvprintw(i, colonne+16, "║");
  }

  move(ligne, colonne - 1);
  printw("╠");
  for(int i = 0; i<16; i++){
    printw("═");
  }
  printw("╝");
  
}


void printDialogue(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height){
  int colonne = 0;
  int ligne = pFenetre->camJeu->height + 1;
  
  move(ligne + 1, colonne + 1); 

  printw("                                                                                \n");
  printw("                                                                                \n");
  printw("                                                                                \n");
  printw("                                                                                \n");
  printw("                                                                                \n");

  move(ligne + 1, colonne + 1);
  attron(COLOR_PAIR(BRUSH_D_RADEAU));
  printw("%s\n", pJeu->pQ_Radeau->dialogue);
  attroff(COLOR_PAIR(BRUSH_D_RADEAU));
  
  move(ligne + 3, colonne + 1);
  attron(COLOR_PAIR(BRUSH_D_PAUL));
  printw("%s", pJeu->pQ_Survivant->dialogue);
  attroff(COLOR_PAIR(BRUSH_D_PAUL));


  // encadré
  move(ligne, 0);
  printw("╠");
  mvprintw(ligne, colonne + 82, "╣");
  for(int i = 1; i<height; i++){
    mvprintw(ligne + i, colonne, "║");
    mvprintw(ligne + i, colonne + 82, "║");
  }

  move(ligne + height, 0);
  printw("╚");
  for(int i = 0; i<81; i++){
    printw("═");
  }
  printw("╝");
}


void gestionFps(Info_Fenetre* pFenetre){
  // gestion des fps
  pFenetre->endTime   = getTimeMicros();
  pFenetre->frameTime = pFenetre->endTime - pFenetre->startTime; 
  pFenetre->startTime = pFenetre->endTime;
  // Wait to achieve 60FPS
  
  if(pFenetre->frameTime <= (1000000/pFenetre->fps)){
    usleep((1000000/pFenetre->fps) - pFenetre->frameTime);
  }
}




int main(int argc, char* argv[]){
  
  
  // structures réunissants les informations importantes du programme
  Info_Fenetre* pFenetre = init_Info_Fenetre();
  Info_Jeu* pJeu = init_Info_Jeu();  

  // active les fonctionnalitées de curses
  init_Curses(pFenetre);

  // charge les infos de base avant chages partie (dont la map)
  res_Info_Jeu(pJeu); 

  
  //affiche la map entière
  //printMap(pJeu->mapJeu->pAffichage);


  while(pJeu->enJeu){// boucle du jeu

    pJeu->temps = (pFenetre->endTime - pFenetre->initialTime) / 1000000;
    faim(pJeu->pJoueur, pJeu->temps);
    death(pJeu->pJoueur, pJeu, pFenetre);
    limiteScore(pJeu, pFenetre);
    
    action(pFenetre, pJeu);

    affiche_jeu(pFenetre, pJeu);
    //printw("\n*Orientation du joueur: %d", pJeu->pJoueur->regard);

    //test();
    
    //usleep(1000000);

  }


  // DESALLOCATION
  
  freeGame(pFenetre, pJeu);
  
  return 0;
}
