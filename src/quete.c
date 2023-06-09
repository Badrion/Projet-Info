#include "quete.h"

void ecran_Fin_Radeau(){
  
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
        sprintf(pQuete->dialogue, " *brr brr*");
        break;
      case 1:
        sprintf(pQuete->dialogue, " ??? : Salut c'est le radeau, je t'attendais...");
        break;
      case 2:
        sprintf(pQuete->dialogue, " UN RADEAU? : Tu peux me réparer? je t'aiderai à partir d'ici.");
        break;
      case 3:
        sprintf(pQuete->dialogue, " RADEAU? : Pour commencer, il me faudrait 15 ▂ bâtons. \n (req: 🪓Hache + 🌳arbre)");
        pQuete->etape = 1;
        break;
      // 4: QUETE 1
    
      case 5:
        sprintf(pQuete->dialogue, " RADEAU : Il faut attacher tous ces bâtons, trouve-moi de la corde. \n (à échanger)");
        pQuete->etape = 2;
        break;      
      // 6: QUETE 2
    
      case 7:
        sprintf(pQuete->dialogue, " RADEAU : Bon, on voit le bout dit donc, mon mât est encore utilisable \n alors si tu pouvais me trouver une voile se serai parfait.");
        pQuete->etape = 3;
        break; 
      // 8: QUETE 3
    
      case 9:
        sprintf(pQuete->dialogue, " RADEAU : Ce n’est pas tout mais je suis sur qu'avant de partir tu as \n un compagnon de fortune qui rêverait de venir avec toi.");
        break; 
      // 10: ATTENTE DE PAUL ETAPE 4
  }
}

void quete_Radeau(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe, int e_Paul){
  
  if(pQuete->e_Dialogue != 4 && pQuete->e_Dialogue != 6 && pQuete->e_Dialogue != 8 && pQuete->e_Dialogue != 10 ){
    dialogue_Radeau(pQuete);
    pQuete->e_Dialogue += 1;
  }
  else if(pQuete->e_Dialogue == 10){
      if(e_Paul != 4){
        sprintf(pQuete->dialogue, " RADEAU : Il te manque un compagnon non?");
      }
      else{
        pQuete->etape = 4;
      }
  }
  else{
    switch(pQuete->etape){
      case 1:
        quete_Radeau_1(pJoueur, pQuete, pListe);
        break;
      case 2:
        quete_Radeau_2(pJoueur, pQuete, pListe);
        break;
      case 3:
        quete_Radeau_3(pJoueur, pQuete, pListe);
        break;
    }
  }
}


void quete_Radeau_1(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe){ //si le joueur veut finir la quete.
  //condition de quête
  if(pListe->baton.nb >= 15){ // a remodifier
    pListe->baton.nb -= 16; // a remodifier
    ramasserObjet(&pListe->baton, pJoueur);
    
    sprintf(pQuete->dialogue, " *Tu as réparé le radeau à 25%%* \n RADEAU : Merci! Mais ce ne sera pas suffisant...");
    
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue, " RADEAU : Il me faut 15 bâtons, Il n'y en a pas assez.");
  }
}

void quete_Radeau_2(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe){ 
  if(pListe->corde.nb >= 2){
    pListe->corde.nb -= 3;
    ramasserObjet(&pListe->corde, pJoueur);
    
    sprintf(pQuete->dialogue, " *Tu as réparé le radeau 50%% *,\n RADEAU : Je me sens beaucoup mieux dejà, je pourrais presque flotter.");
    
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue, " RADEAU : Il faut 2 cordes, Il n'y en a pas assez.");
  }
}

void quete_Radeau_3(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe){ 
  if(pListe->voile.nb >= 1){
    pListe->voile.nb -= 2;
    ramasserObjet(&pListe->voile, pJoueur);
    
    sprintf(pQuete->dialogue, " *Tu as réparé le radeau à 75%% *\n RADEAU : JE SUIS COMME NEUF, ça faisait longtemps !");
    
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue, " RADEAU : Il me faut une voile.");
  }
}



// quete paul

void dialogue_Paul(Quete* pQuete){
  switch(pQuete->e_Dialogue){
      case 0:
        sprintf(pQuete->dialogue, " ??? : Une personne vivante ici !"); 
        break;
      case 1:
        sprintf(pQuete->dialogue, " ??? : Je ne me suis pas présenté, je m'appelle PAUL,\n je vis ici depuis maintenant 2 ans ahah.\n Si seulement il existait un moyen de partir... J'ai pas raison la team?");
        break;
      case 2:
        sprintf(pQuete->dialogue, " PAUL : Tu sais maintenant que tu es là, je suis sûr qu'on va s'en sortir. \n Pour survivre ici, tu vas avoir besoin d'autre chose que tes mains.");
        break;
      case 3:
        sprintf(pQuete->dialogue, " PAUL : T'inquiète avec ça, les arbres et les rochers ne te ferons plus obstacle.");
        pQuete->etape = 1;
        break;
      // 4: QUETE 1

      // 5: ATTENTE DU RADEAU 6
    
      case 6:
        sprintf(pQuete->dialogue, " PAUL : Quoi? Tu as besoin de deux cordes? Ouais je peux te faire ça.\n Ramène-moi 10 cailloux et jte fais ça ");
        pQuete->etape = 2;
        break;      
      // 7: QUETE 2

      // 8: ATTENTE DU RADEAU 8
    
      case 9:
        sprintf(pQuete->dialogue, " PAUL : une voile? Avec ce qu'il y a sur cette île à part avec des feuilles...\n Tu peux me ramener 12 feuilles ouuuuu. ");
          pQuete->etape = 3;
          break; 
      // 10: QUETE 3

      // 11: ATTENTE DU RADEAU 10
    
      case 12:
        sprintf(pQuete->dialogue, " PAUL : !!!\n Un bateau ici? Tu me prank là 🤙🤙");
          break; 
      case 13:
        sprintf(pQuete->dialogue, " PAUL :  Je te suis, je ne te croirais pas tant que je ne l'aurais\n pas vu de mes propres yeux. ");
        pQuete->etape = 4;
        break; 
      // 14: QUETE 4
  }
}


void quete_Paul(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe, int eDQuete_Radeau){
  if(pQuete->e_Dialogue != 4 && pQuete->e_Dialogue != 5 &&  pQuete->e_Dialogue != 7 && pQuete->e_Dialogue != 8 && pQuete->e_Dialogue != 10 && pQuete->e_Dialogue != 11 && pQuete->e_Dialogue != 14 ){
    dialogue_Paul(pQuete);
    pQuete->e_Dialogue += 1;
  }
  else{
    if(pQuete->e_Dialogue == 5){
      if(eDQuete_Radeau != 6){
        sprintf(pQuete->dialogue, " PAUL : Reviens me voir si tu as besoin de quelque chose !");
      }
      else{
        pQuete->e_Dialogue += 1;
        sprintf(pQuete->dialogue, " PAUL : hmm?");
      }
    }
    else if(pQuete->e_Dialogue == 8){
      if(eDQuete_Radeau != 8){
        sprintf(pQuete->dialogue, " PAUL : De la corde ahah, après tout c'est un élément essentiel pour \n construire des trucs, si tu as besoin d'un truc dis-le-moi ! ");
      }
      else{
        pQuete->e_Dialogue += 1;
        sprintf(pQuete->dialogue, " PAUL : hmm?");
      }
    }
    else if(pQuete->e_Dialogue == 11){
      if(eDQuete_Radeau != 10){
        sprintf(pQuete->dialogue, " PAUL : Une voile ? Tu comptes partir de cette île🤙🤙? nan je rigole... \n ... Mais imagine quand même 💀.");
      }
      else{
        pQuete->e_Dialogue += 1;
        sprintf(pQuete->dialogue, " PAUL : hmm? ");
      }
    }
    else{
      switch(pQuete->etape){
        case 1:
            quete_Paul_1(pJoueur, pQuete, pListe);
          break;
        case 2:
            quete_Paul_2(pJoueur, pQuete, pListe);
          break;
          case 3:
            quete_Paul_3(pJoueur, pQuete, pListe);
          break;
      }
    }
  }
}


void quete_Paul_1(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe){ //si le joueur veut finir la quete.
  if(pListe->pioche.nb == 0){
    ramasserObjet(&pListe->pioche, pJoueur);
  }
  if(pListe->hache.nb == 0){
    ramasserObjet(&pListe->hache, pJoueur);
  }
  
  sprintf(pQuete->dialogue, " *Ta relation avec Paul a augmenté ! (25%%)* (tu as reçu une HACHE et une PIOCHE)*\n PAUL : C'est pas grand-chose mais ça devrait pouvoir t'aider j'ai pas raison 🤙");
  
  pQuete->e_Dialogue += 1;
}

void quete_Paul_2(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe){ 
  if(pListe->caillou.nb >= 10){ //remplacer avec viande de poule si fais 
    pListe->caillou.nb -= 11;// a remodifier
    ramasserObjet(&pListe->caillou, pJoueur);
    ramasserObjet(&pListe->corde, pJoueur);
    ramasserObjet(&pListe->corde, pJoueur);
    
    sprintf(pQuete->dialogue, "* Ta relation avec Paul a augmenté ! (50%%) ,\n PAUL : Voilà ta corde, tu vas faire quoi avec ça ?");
    
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue, " PAUL : C'est 10 cailloux contre la corde, reviens avec.");
  }
}

void quete_Paul_3(Entitee* pJoueur, Quete* pQuete, ListeObj* pListe){ 
  if(pListe->feuille.nb >= 12){ // a remodifier
    pListe->feuille.nb -= 13;// a remodifier
    ramasserObjet(&pListe->feuille, pJoueur);
    ramasserObjet(&pListe->voile, pJoueur);
    
    sprintf(pQuete->dialogue, " *Ta relation avec Paul a augmenté ! (75%%) *\n PAUL : Il faudrait que tu m'expliques un jour... \n (tu as reçu une voile)");
    
    pQuete->e_Dialogue += 1;
  }
  else{
    sprintf(pQuete->dialogue," PAUL : 12 feuilles pour que je puisse faire cette voile.");
  }
}
