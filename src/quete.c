#include "quete.h"

void ecran_Fin_Radeau(){
  
}

void res_Quete(Quete* pQuete){
  res_Entitee(&(pQuete->npc));
  pQuete->etape = 0;
  pQuete->e_Dialogue = -1;
  sprintf(pQuete->dialogue, "");
}

void quete_Radeau_1(Quete* pQuete, ListeObj* pListe){ //si le joueur veut finir la quete.

  if(pListe->baton.nb >= 1){
    pListe->baton.nb -= 1;
    pQuete->etape += 1;
    pQuete->e_Dialogue += 1;
    sprintf(pQuete->dialogue, "*Tu as réparé le radeau à 25%%* \nRADEAU : Merci mais ce ne sera pas suffisant...");
  }
  else{
    sprintf(pQuete->dialogue, "RADEAU : Il me faut 15 bâtons, Il n'y en a pas assez.");
  }
}

void quete_Radeau_2(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->corde.nb >= 2){
    pListe->corde.nb -= 2;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Tu as réparé le radeau 50\% *,\n RADEAU : Je me sens beaucoup mieux dejà, je pourrais presque flotter.");
  }
  else{
    sprintf(pQuete->dialogue, "RADEAU : Il faut 2 cordes, Il n'y en a pas assez.");
  }
}

void quete_Radeau_3(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->voile.nb >= 1){
    pListe->voile.nb -= 1;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Tu as réparé le radeau à 75\% *\n RADEAU : JE SUIS COMME NEUF, ça faisait longtemps !");
  }
  else{
    sprintf(pQuete->dialogue, "RADEAU : Il me faut une voile.");
  }
}

void quete_Radeau_4(Quete* pQuete, ListeObj* pListe){ 
  ecran_Fin_Radeau();
}

void quete_DialogueR(Quete* pQuete){
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
        sprintf(pQuete->dialogue, "RADEAU : Il faut attacher tous ces bâtons, trouve-moi de la corde. \n (req : à échanger)");
          break;      
      case 6:
        sprintf(pQuete->dialogue, "");
            break;
    
      case 7:
        sprintf(pQuete->dialogue, "RADEAU : Bon, on voit le bout dit donc, mon mât est encore utilisable \n alors si tu pouvais me trouver une voile ce serai parfait.");
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
    pQuete->e_Dialogue += 1;
    quete_DialogueR(pQuete);
  }
  if(pQuete->e_Dialogue == 4 || pQuete->e_Dialogue == 6 || pQuete->e_Dialogue == 8){
    switch(pQuete->etape){
      case 1:
          quete_Radeau_1(pQuete, pListe);
          //pQuete->e_Dialogue += 1;
        break;
      case 2:
          quete_Radeau_2(pQuete, pListe);
          pQuete->e_Dialogue += 1;
        break;
        case 3:
          quete_Radeau_3(pQuete, pListe);
          pQuete->e_Dialogue += 1;
        break;
      case 4:
          quete_Radeau_4(pQuete, pListe);
          pQuete->e_Dialogue += 1;
        break;    
    }
  }
}

// quete paul

void quete_Paul_1(Quete* pQuete, ListeObj* pListe){ //si le joueur veut finir la quete.
  if(pListe->pioche == 0){
    pListe->pioche.nb += 1;
  }
  if(pListe->hache == 0){
    pListe->hache.nb += 1;
  }
  pQuete->etape += 1;
  pQuete->e_Dialogue += 1;
  sprintf(pQuete->dialogue, "*Ta relation avec Paul a augmenté ! (25\%)* \n PAUL : Ce n’est pas grand-chose mais ça devrait pouvoir t'aider.");
}

void quete_Paul_2(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->caillou.nb >= 10){ //remplacer avec viande de poule si fais 
    pListe->caillou.nb -= 10;
    pListe->caillou.nb += 2;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Ta relation avec Paul a augmenté ! (50\%)*,\n PAUL : Voilà ta corde, tu vas faire quoi avec ça ?");
  }
  else{
    sprintf(pQuete->dialogue, "PAUL : C'est 10 cailloux contre la corde, reviens avec.");
  }
}

void quete_Paul_3(Quete* pQuete, ListeObj* pListe){ 
  if(pListe->feuille.nb >= 12){
    pListe->feuille.nb -= 12;
    pListe->voile.nb += 1;
    pQuete->etape += 1;
    sprintf(pQuete->dialogue, "*Ta relation avec Paul a augmenté ! (75\%) *\n PAUL : Il faudrait que tu m'explique un jour... \n (tu as reçu une voile)");
  }
  else{
    sprintf(pQuete->dialogue,"PAUL : 12 feuilles pour que je puisse faire cette voile.");
  }
}

void quete_Paul_4(Quete* pQuete, ListeObj* pListe){ 
  paul_Fin();
}

void quete_DialogueP(Quete* pQuete){
  switch(pQuete->e_Dialogue){
      case 0:
        sprintf(pQuete->dialogue, "??? : Une personne vivante ici !");
        break;
      case 1:
        sprintf(pQuete->dialogue, "??? : Je me suis pas présenté, je m'appelle PAUL, je vis ici depuis \n maintenant 2 ans, ");
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
        sprintf(pQuete->dialogue, "RADEAU : Il faut attacher tous ces bâtons, trouve-moi de la corde. \n (req : à échanger)");
          break;      
      case 6:
        sprintf(pQuete->dialogue, "");
            break;
    
      case 7:
        sprintf(pQuete->dialogue, "RADEAU : Bon, on voit le bout dit donc, mon mât est encore utilisable \n alors si tu pouvais me trouver une voile ce serai parfait.");
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

void quete_Paul(Quete* pQuete, ListeObj* pListe){
  
  if(pQuete->e_Dialogue != 4 && pQuete->e_Dialogue != 6 && pQuete->e_Dialogue != 8 && pQuete->e_Dialogue != 10 ){
    pQuete->e_Dialogue += 1;
    quete_DialogueP(pQuete);
  }
  if(pQuete->e_Dialogue == 4 || pQuete->e_Dialogue == 6 || pQuete->e_Dialogue == 8){
    switch(pQuete->etape){
      case 1:
          quete_Paul_1(pQuete, pListe);
          //pQuete->e_Dialogue += 1;
        break;
      case 2:
          quete_Paul_2(pQuete, pListe);
          pQuete->e_Dialogue += 1;
        break;
        case 3:
          quete_Paul_3(pQuete, pListe);
          pQuete->e_Dialogue += 1;
        break;
      case 4:
          quete_Paul_4(pQuete, pListe);
          pQuete->e_Dialogue += 1;
        break;    
    }
  }
}

