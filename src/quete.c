#include "quete.h"

void ecran_Fin_Radeau(){
  
}

void paul_Fin(){
  
}



void res_Quete(Quete* pQuete){
  res_Entitee(&(pQuete->npc));
  pQuete->etape = 0;
  pQuete->e_Dialogue = 0;
  sprintf(pQuete->dialogue, "");
}



void dialogue_Radeau(Quete* pQuete){
  switch(pQuete->e_Dialogue){
      case 0:
        sprintf(pQuete->dialogue, "*brr brr*");
        break;
      case 1:
        sprintf(pQuete->dialogue, "??? : Salut c'est le radeau, je t'attendais...");
        break;
      case 2:
        sprintf(pQuete->dialogue, "UN RADEAU? : Tu peux me réparer? je t'aiderai à partir d'ici.");
        break;
      case 3:
        sprintf(pQuete->dialogue, "RADEAU? : Pour commencer, il me faudrait 15 ▂ bâtons. \n (req: 🪓Hache + 🌳arbre)");
        pQuete->etape = 1;
        break;
      case 4:
        sprintf(pQuete->dialogue, "");
        break;
    
      case 5:
        sprintf(pQuete->dialogue, "RADEAU : Il faut attacher tous ces bâtons, trouve-moi de la corde. \n (reqis : à échanger)");
          break;      
      case 6:
        sprintf(pQuete->dialogue, "");
            break;
    
      case 7:
        sprintf(pQuete->dialogue, "RADEAU : Bon, on voit le bout dit donc, mon mât est encore utilisable \n alors si tu pouvais me trouver une voile se serai parfait.");
          break; 
      case 8:
        sprintf(pQuete->dialogue, "");
          break; 
    
      case 9:
        sprintf(pQuete->dialogue, "RADEAU : Ce n’est pas tout mais je suis sur qu'avant de partir tu as \n un compagnon de fortune qui rêverait de venir avec toi.");
          break; 
      case 10:
        sprintf(pQuete->dialogue, "");
          break;
  }
}

void quete_Radeau(Quete* pQuete, ListeObj* pListe){
  
  if(pQuete->e_Dialogue != 4 && pQuete->e_Dialogue != 6 && pQuete->e_Dialogue != 8 && pQuete->e_Dialogue != 10 ){
    dialogue_Radeau(pQuete);
    pQuete->e_Dialogue += 1;
  }
  else{
    switch(pQuete->etape){
      case 1:
          quete_Radeau_1(pQuete, pListe);
        break;
      case 2:
          quete_Radeau_2(pQuete, pListe);
          
        break;
        case 3:
          quete_Radeau_3(pQuete, pListe);
          
        break;
      case 4:
          quete_Radeau_4(pQuete, pListe);
          
        break;    
    }
  }
}


void quete_Radeau_1(Quete* pQuete, ListeObj* pListe){ //si le joueur veut finir la quete.
  //condition de quête
  if(pListe->baton.nb >= 1){ // a remodifier
    pListe->baton.nb -= 1; // a remodifier
    
    pQuete->etape += 1;
    pQuete->e_Dialogue += 1;
    sprintf(pQuete->dialogue, "*Tu as réparé le radeau à 25%%* \nRADEAU : Merci! Mais ce ne sera pas suffisant...");
  }
  else{
    sprintf(pQuete->dialogue, "RADEAU : Il me faut 15 bâtons, Il n'y en a pas assez.");
  }
}

void quete_Radeau_2(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->corde.nb >= 2){
    pListe->corde.nb -= 2;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Tu as réparé le radeau 50%% *,\n RADEAU : Je me sens beaucoup mieux dejà, je pourrais presque flotter.");
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue, "RADEAU : Il faut 2 cordes, Il n'y en a pas assez.");
  }
}

void quete_Radeau_3(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->voile.nb >= 1){
    pListe->voile.nb -= 1;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Tu as réparé le radeau à 75%% *\n RADEAU : JE SUIS COMME NEUF, ça faisait longtemps !");
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue, "RADEAU : Il me faut une voile.");
  }
}

void quete_Radeau_4(Quete* pQuete, ListeObj* pListe){ 
  ecran_Fin_Radeau();
  pQuete->e_Dialogue += 1;
}


// quete paul

void dialogue_Paul(Quete* pQuete){
  switch(pQuete->e_Dialogue){
      case 0:
        sprintf(pQuete->dialogue, "??? : Une personne vivante ici !");
        break;
      case 1:
        sprintf(pQuete->dialogue, "??? : Je ne me suis pas présenté, je m'appelle PAUL, je vis ici depuis \n maintenant 2 ans. Si seulement il existait un moyen de partir...");
        break;
      case 2:
        sprintf(pQuete->dialogue, "PAUL : Tu sais maintenant que tu es là, je suis sûr qu'on va s'en sortir. \n Pour survivre ici, tu vas avoir besoin d'autre chose que tes mains.");
        break;
      case 3:
        sprintf(pQuete->dialogue, "PAUL : Avec ça, les arbres et les rochers ne te ferons plus obstacle.");
        pQuete->etape = 1;
        break;
      case 4:
        sprintf(pQuete->dialogue, "");
        break;
    
      case 6:
        sprintf(pQuete->dialogue, "PAUL : Tu as besoin de deux cordes?\n Ouais je peux te faire ça, ramène-moi 10 cailloux, je te fais ça.");
          break;      
      case 7:
        sprintf(pQuete->dialogue, "");
            break;
    
      case 9:
        sprintf(pQuete->dialogue, "PAUL : une voile? Avec ce qu'il y a sur cette île à part avec des feuilles,\n Je ne vois pas comment je pourrais en fabriquer. Ramène-moi 12 feuilles. ");
          break; 
      case 10:
        sprintf(pQuete->dialogue, "");
          break; 
    
      case 12:
        sprintf(pQuete->dialogue, "PAUL : !!!\n Un bateau ici? ");
          break; 
      case 13:
        sprintf(pQuete->dialogue, "PAUL :  Je te suis, je ne te croirais pas tant que je ne l'aurais\n pas vu de mes propres yeux. ");
          break; 
      case 14:
        sprintf(pQuete->dialogue, "");
          break;
  }
}


void quete_Paul(Quete* pQuete, ListeObj* pListe, int eDQuete_Radeau){
  if(pQuete->e_Dialogue != 4 && pQuete->e_Dialogue != 5 &&  pQuete->e_Dialogue != 7 && pQuete->e_Dialogue != 8 && pQuete->e_Dialogue != 10 && pQuete->e_Dialogue != 11 && pQuete->e_Dialogue != 14 ){
    dialogue_Paul(pQuete);
    pQuete->e_Dialogue += 1;
  }
  else{
    if(pQuete->e_Dialogue == 5 && eDQuete_Radeau != 6){
      sprintf(pQuete->dialogue, "PAUL : Reviens me voir si tu as besoin de quelque chose !");
      
    }
    else if(pQuete->e_Dialogue == 7 && eDQuete_Radeau != 8){
      sprintf(pQuete->dialogue, "PAUL : De la corde ahah, après tout c'est un élément essentiel pour \n construire des trucs, si tu as besoin d'un truc dis-le-moi ! ");
     
    }
    else if(eDQuete_Radeau == 9 && eDQuete_Radeau != 10){
      sprintf(pQuete->dialogue, "PAUL : Une voile ? Tu comptes partir de cette île? nan je rigole... \n... Mais imagine quand même.");
    }
    else{
      switch(pQuete->etape){
        case 1:
            quete_Paul_1(pQuete, pListe);
            //pQuete->e_Dialogue += 1;
          break;
        case 2:
            quete_Paul_2(pQuete, pListe);
          break;
          case 3:
            quete_Paul_3(pQuete, pListe);
          break;
        case 4:
            quete_Paul_4(pQuete, pListe);
          break;  
      }
    }
  }
}


void quete_Paul_1(Quete* pQuete, ListeObj* pListe){ //si le joueur veut finir la quete.
  if(pListe->pioche.nb == 0){
    pListe->pioche.nb += 1;
  }
  if(pListe->hache.nb == 0){
    pListe->hache.nb += 1;
  }
  pQuete->etape += 1;
  pQuete->e_Dialogue += 1;
  sprintf(pQuete->dialogue, "*Ta relation avec Paul a augmenté ! (25%%)* \n PAUL : Ce n’est pas grand-chose mais ça devrait pouvoir t'aider.");
}

void quete_Paul_2(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->caillou.nb >= 1){ //remplacer avec viande de poule si fais 
    pListe->caillou.nb -= 1;// a remodifier
    pListe->corde.nb += 2;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Ta relation avec Paul a augmenté ! (50%%) (tu as reçu une HACHE et une PIOCHE)*,\n PAUL : Voilà ta corde, tu vas faire quoi avec ça ?");
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue, "PAUL : C'est 10 cailloux contre la corde, reviens avec.");
  }
}

void quete_Paul_3(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->feuille.nb >= 1){ // a remodifier
    pListe->feuille.nb -= 1;// a remodifier
    pListe->voile.nb += 1;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Ta relation avec Paul a augmenté ! (75%%) *\n PAUL : Il faudrait que tu m'expliques un jour... \n (tu as reçu une voile)");
  pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue,"PAUL : 12 feuilles pour que je puisse faire cette voile.");
  }
}

void quete_Paul_4(Quete* pQuete, ListeObj* pListe){ 
  paul_Fin();
}



