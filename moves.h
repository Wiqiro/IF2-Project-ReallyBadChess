Bool Move(**case board, int size, int startx, int starty, int targx, int targy); //envoie vers le mouvcheck 

Bool PawnMove(**case board, int size, int startx, int starty, int targx, int targy);

Bool BishopMove(**case board, int size, int startx, int starty, int targx, int targy);

Bool KnightMove(**case board, int size, int startx, int starty, int targx, int targy);

Bool RookMove(**case board, int size, int startx, int starty, int targx, int targy);

Bool QueenMove(**case board, int size, int startx, int starty, int targx, int targy);

Bool KingMove(**case board, int size, int startx, int starty, int targx, int targy); // séparer toute les fonctions en fonction check et executer le mouv. 
//kingmove scan all the board
// make 14 bool
// 