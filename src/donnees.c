#include "donnees.h"


unsigned long getTimeMicros(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000000) + (tv.tv_usec/1);
} 

int percent(int nb, int percent){
  return nb * percent / 100;
}

int alea(int min, int max){
  return (rand() % (max - min)) + min;
}


void generateMap(Map* pMap){
  srand(time(NULL));
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  

  for (int y = 0; y < pDonnees_Map->height; y++) {
    for (int x = 0; x < pDonnees_Map->width; x++) {
      if((x < alea(2, 4) || pDonnees_Map->width - x < alea(2, 4)) || (y < alea(2, 4)|| pDonnees_Map->height - y < alea(2, 4))){
        pDonnees_Map->tab[x][y].biome = DEEP_WATER;
        pDonnees_Map->tab[x][y].ressource = WAVE;
      }
      else if((x < alea(4, 9) || pDonnees_Map->width - x < alea(4, 9)) || (y < alea(4, 9)|| pDonnees_Map->height - y < alea(4, 9))){
        pDonnees_Map->tab[x][y].biome = WATER;
        pDonnees_Map->tab[x][y].ressource = WAVE;
      }
      else if((x < alea(12, 15) || pDonnees_Map->width - x < alea(12, 15)) || (y < alea(12, 15) || pDonnees_Map->height - y < alea(12, 15))){
        pDonnees_Map->tab[x][y].biome = SAND;
        if( !(rand() % 200)){
          pDonnees_Map->tab[x][y].ressource = COCO;
        }
      }
      else{
        pDonnees_Map->tab[x][y].biome = GRASS;
        if( !(rand() % 25)){
          pDonnees_Map->tab[x][y].ressource = TREE;
        }
        if( !(rand() % 100)){
          pDonnees_Map->tab[x][y].ressource = ROCHER;
        }
        if( !(rand() % 150)){
          pDonnees_Map->tab[x][y].ressource = COCO;
        }
        if( !(rand() % 80)){
          pDonnees_Map->tab[x][y].ressource = LEAF;
        }
        if( !(rand() % 110)){
          pDonnees_Map->tab[x][y].ressource = BATON;
        }
        if( !(rand() % 110)){
          pDonnees_Map->tab[x][y].ressource = CAILLOU;
        }
      }

      pAffichage_Map->tab[x][y].isLoaded = 0;
      
    }// x
  }// y

  pDonnees_Map->tab[alea(10, 13)][alea(20, 70)].ressource = PNG_BOAT;
  pDonnees_Map->tab[alea(20, 40)][alea(20, 40)].ressource = PNG_PAUL;
  pDonnees_Map->tab[alea(40, 83)][alea(10, 20)].ressource = HACHE;
  pDonnees_Map->tab[alea(60, 90)][alea(60, 80)].ressource = PIOCHE;
  
}

void createBouton(Map* pMap, int coordX, int coordY, int heigh, int width, int h_Affichage, Ressource ressource, Brush brush, char text[30]){
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;

  int len = strlen(text);
  int espace = 0;
  if(width != len){
    espace = (width - len) / 2;
  }
  int ch = 0;
  
  for (int y = 0; y < heigh; y++) {
    for (int x = 0; x < width; x++) {
      pDonnees_Map->tab[x + coordX][y + coordY].biome = BOUTON;
      pDonnees_Map->tab[x + coordX][y + coordY].ressource = ressource;
      
      pAffichage_Map->tab[x + coordX][y + coordY].brush = brush;
      if(y == h_Affichage && (x >= espace + (len % 2) && x < width - espace || width == len)){          
        sprintf(pAffichage_Map->tab[x + coordX][y + coordY].caractere, "%c ", text[ch]);
        ch++;
      }
      else{
        sprintf(pAffichage_Map->tab[x + coordX][y + coordY].caractere, "  ");
      }
    }
  }
}

void createMapAccueil(Map* pMap){
  srand(time(NULL));
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  
  for (int y = 0; y < pDonnees_Map->height; y++) {
    for (int x = 0; x < pDonnees_Map->width; x++) {
      if((x < percent(pDonnees_Map->width, 20))){
        pDonnees_Map->tab[x][y].biome = DEEP_WATER;
        pDonnees_Map->tab[x][y].ressource = WAVE;
      }
      else if((x < percent(pDonnees_Map->width, 28) || pDonnees_Map->width - x < percent(pDonnees_Map->width, 7)) || (y < percent(pDonnees_Map->height, 7) || pDonnees_Map->height - y < percent(pDonnees_Map->height, 7))){
        pDonnees_Map->tab[x][y].biome = WATER;
        pDonnees_Map->tab[x][y].ressource = WAVE;

      }
      else if((x < percent(pDonnees_Map->width, 35) || pDonnees_Map->width - x < percent(pDonnees_Map->width, 15)) || (y < percent(pDonnees_Map->height, 15) || pDonnees_Map->height - y < percent(pDonnees_Map->height, 15))){
        pDonnees_Map->tab[x][y].biome = SAND;
        if( !(rand() % 50)){
          pDonnees_Map->tab[x][y].ressource = LEAF;
        }
      }
      else{
        pDonnees_Map->tab[x][y].biome = GRASS;
        if( !(rand() % 20)){
          pDonnees_Map->tab[x][y].ressource = TREE;
        }
      }      
    }// x
  }// y

  createBouton(pMap, percent(pDonnees_Map->width, 65) - 7, 3, 3, 14, 1, NOUVEAU_JEU, BRUSH_NOUVEAU_JEU, "NOUVEAU JEU");
  createBouton(pMap, percent(pDonnees_Map->width, 65) - 7, 7, 3, 14, 1, REPRENDRE_JEU, BRUSH_REPRENDRE_JEU, "REPRENDRE JEU");
  createBouton(pMap, percent(pDonnees_Map->width, 65) - 7, 12, 3, 14, 1, QUITTER_JEU, BRUSH_QUITTER_JEU, "QUITER LE JEU");

  createBouton(pMap, 2, 1, 1, 1, 0, TOUCHE, BRUSH_TOUCHE, "Z");
  createBouton(pMap, 1, 2, 1, 1, 0, TOUCHE, BRUSH_TOUCHE, "Q");
  createBouton(pMap, 2, 2, 1, 1, 0, TOUCHE, BRUSH_TOUCHE, "S");
  createBouton(pMap, 3, 2, 1, 1, 0, TOUCHE, BRUSH_TOUCHE, "D");
  
  createBouton(pMap, 2, 5, 1, 1, 0, TOUCHE, BRUSH_TOUCHE, "E");
  createBouton(pMap, 0, 6, 1, 7, 0, TOUCHE, BRUSH_TOUCHE, "INTERAC");

  createBouton(pMap, 2, 8, 1, 1, 0, TOUCHE, BRUSH_TOUCHE, "A");
  createBouton(pMap, 0, 9, 1, 7, 0, TOUCHE, BRUSH_TOUCHE, "ACCUEIL");

  //createBouton(pMap, 2, 12, 1, 1, 0, TOUCHE, BRUSH_TOUCHE, "I");
  //createBouton(pMap, 1, 13, 1, 3, 0, TOUCHE, BRUSH_TOUCHE, "INV");
}


void createMapOcean(Map* pMap){
  srand(time(NULL));
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  
  for (int y = 0; y < pDonnees_Map->height; y++) {
    for (int x = 0; x < pDonnees_Map->width; x++) {
      pDonnees_Map->tab[x][y].biome = WATER;

      if( !(rand() % 50)){
        sprintf(pAffichage_Map->tab[x][y].caractere, "🌊");
      }
          
    }// x
  }// y

}


void createMapMort(Map* pMap){
  srand(time(NULL));
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  
  for (int y = 0; y < pDonnees_Map->height; y++) {
    for (int x = 0; x < pDonnees_Map->width; x++) {
      pDonnees_Map->tab[x][y].biome = WATER;

      if( !(rand() % 5)){
        sprintf(pAffichage_Map->tab[x][y].caractere, "💀");
      }
          
    }// x
  }// y

}


void createMapPaul(Map* pMap){
  srand(time(NULL));
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  
  for (int y = 0; y < pDonnees_Map->height; y++) {
    for (int x = 0; x < pDonnees_Map->width; x++) {
      pDonnees_Map->tab[x][y].biome = WATER;

      if( !(rand() % 50)){
        sprintf(pAffichage_Map->tab[x][y].caractere, "🌴");
      }
          
    }// x
  }// y

}


void res_Obj(Obj* pObj){
  pObj->id_Obj = O_VIDE;
  pObj->nb_Max = 0;
  pObj->nb = 0;
  pObj->placeinv = -1;
  sprintf(pObj->nom, "VIDE");
  sprintf(pObj->symbole, "V");

  //res_BuffObj(&(pObj->buffObj)); (pas encore de stats pr les objets)
}

Obj constructor_Obj(Id_Obj O_nom, int nb_Max, char nom[30], char symbole[10]){
  Obj objet;
  res_Obj(&objet);
  objet.nb_Max = nb_Max;
  objet.id_Obj = O_nom;
  
  sprintf(objet.nom, "%s", nom);
  sprintf(objet.symbole, "%s", symbole);
  
  return objet;  
}

ListeObj init_ListeObj(){
  ListeObj listObj;

  listObj.coco = constructor_Obj(O_COCO, 10, "Coco", "🥥");
  listObj.baton = constructor_Obj(O_BATON, 20, "Baton", "▂");
  listObj.feuille = constructor_Obj(O_FEUILLE, 30, "Feuille", "🍃");
  listObj.caillou = constructor_Obj(O_CAILLOU, 20, "Caillou", "☁");

  listObj.corde = constructor_Obj(O_CORDE, 2, "Corde", "➰");
  listObj.voile = constructor_Obj(O_VOILE, 1, "Voile", "🏴");
  
  listObj.hache = constructor_Obj(O_HACHE, 1, "Hache", "🪓");
  listObj.pioche = constructor_Obj(O_PIOCHE, 1, "Pioche", "⛏");

  return listObj;
}

void init_Inventaire(Inventaire* pInv, int size){
  pInv->stockagePris = 0;
  pInv->stockageTotal = size;

  for(int n = 0; n<size ; n++){
    res_Obj(&(pInv->inv[n]));
    pInv->inv[n].placeinv = n;
  }
}

Entitee* init_Entitee(){

  Entitee* pEnt = NULL;
  if( !(pEnt = malloc(sizeof(Entitee)))){
    printf("Erreur lors de la création d'une entitée");
    exit(20);
  }
  
  res_Entitee(pEnt);

  return pEnt;
}

void res_Entitee(Entitee* pEnt){
  pEnt->coordonnees.x = 0;
  pEnt->coordonnees.y = 0;
  pEnt->derniereCoordonnees.x = 0;
  pEnt->derniereCoordonnees.y = 0;
  pEnt->initial.x = 0;
  pEnt->initial.y = 0;

  pEnt->regard = DROITE;

  pEnt->T_dernierDeplacement = 0;
  pEnt->T_intervalleDeplacement = 0;
  
  pEnt->pvTotal = 0;
  pEnt->pvActuelle = 0;
  pEnt->atk = 0;
  pEnt->vie = 0;
  
  init_Inventaire(&(pEnt->inventaire), 8);
}


void modifpvA(int dmg_Heal, Entitee* pEntitee){
  pEntitee->pvActuelle += dmg_Heal;
  if(pEntitee->pvActuelle > pEntitee->pvTotal){
    pEntitee->pvActuelle = pEntitee->pvTotal;
  }
  if(pEntitee->pvActuelle < 0){
    //mort(pEntitee);
  }
  
}

void modifpvTT(int dmg_Heal, Entitee* pEntitee){
  pEntitee->pvTotal += dmg_Heal;
  if(pEntitee->pvTotal < pEntitee->pvActuelle){
    pEntitee->pvActuelle = pEntitee->pvTotal;
  }
}


int ramasserObjet(Obj* pObj, Entitee* pJoueur){ //return 0 => pas ramassé return 1 => ramassé
  int estRamasse = 0;
  
  if(pObj->placeinv != -1){
      if(pObj->nb < pObj->nb_Max){
        pObj->nb += 1;

        pJoueur->inventaire.inv[pObj->placeinv] = *pObj;
        estRamasse = 1;
      }
      else{
        //printw("Tu as déjà le nombre maximum pour cette ressource.");
      }
    }
  else{
    for(int n = 0; n < pJoueur->inventaire.stockageTotal && pObj->placeinv == -1; n++){
      if(pJoueur->inventaire.inv[n].id_Obj == O_VIDE ){
        
        pObj->nb += 1;
        pObj->placeinv = n;
        pJoueur->inventaire.stockagePris ++;
        
        pJoueur->inventaire.inv[n] = *pObj;
        estRamasse = 1;
      }
    }
    if(estRamasse == 0){
      //printw("Tu n'as plus de place dans ton inventaire.\n");
    }
  }
  return estRamasse;
}


void afficherStats(Entitee* entitee){
    printf("position x: %d  y: %d\n Pv total %d\n Pv actuelle %d\n Atk %d \n", entitee->coordonnees.x, entitee->coordonnees.y, entitee->pvTotal, entitee->pvActuelle, entitee->atk);
}

void testStats(Entitee* pEntitee){ // on pourra envoyé une entitée plus tard
    printf("test stats. \n");
  res_Entitee(pEntitee);
  printf("initialisez les statistiques\n");
  int x = 0;
  printf("pos x / pos y / pv TT / pv Actuelle / ATK\n");
  scanf("%d", &x);
  pEntitee->coordonnees.x = x;
  scanf("%d", &x);
  pEntitee->coordonnees.y = x;
  scanf("%d", &x);
  pEntitee->pvTotal = x;
  scanf("%d", &x);
  pEntitee->pvActuelle = x;
  scanf("%d", &x);
  pEntitee->atk = x;
  afficherStats(pEntitee);
}

void test(){
  printw("\n");
  
  Obj objet;
  Entitee joueur;
  //sprintf(joueur->inv[n].nom, "Blabla"); exemple de nomage
  res_Entitee(&joueur);
  res_Obj(&objet);
  sprintf(objet.nom, "bonjour");
  objet.id_Obj = O_BATON;
  if(ramasserObjet(&objet, &joueur)){
    printw("ramassé");
    for(int i = 0; i<30; i++){
      printw("\nobjet %d = %s", i, joueur.inventaire.inv[i].nom );
    }
  }
  else{
    printw("pas ramassé");
  }

}
