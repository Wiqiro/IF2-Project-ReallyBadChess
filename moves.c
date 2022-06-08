#include <game.h>


bool CollisionTest(square** board, int size, coords startpos, coords targpos) {

    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;
    int dx, dy;

    if (movex == 0) {
        dx = 0;
    } else { 
        dx = movex/abs(movex);
    }

    if (movey == 0) {
        dy = 0;
    } else {
        dy = movey/abs(movey);
    }

    int i=0;
        while (i+1 < fmax(abs(movex),abs(movey)) && board[startpos.x+dx*(i+1)][startpos.y+dy*(i+1)].type == empty) {
        i++;
    }
    if (i == fmax(abs(movex),abs(movey))-1) {
        return true; //returns true if the way is free (if there is only empty squares in the path of the bishop)
    } else {
        return false;
    }
}

bool MoveTest(square** board, int size, coords startpos, coords targpos) {

    switch (board[startpos.x][startpos.y].type) {
    case pawn:
        return PawnMoveTest(board, size, startpos, targpos);
        break;
    case bishop:
        return BishopMoveTest(board, size, startpos, targpos);
        break;
    case knight:
        return KnightMoveTest(board, size, startpos, targpos);
        break;
    case rook:
        return RookMoveTest(board, size, startpos, targpos);
        break;
    case queen:
        return QueenMoveTest(board, size, startpos, targpos);
        break;
    case king:
        return KingMoveTest(board, size, startpos, targpos);
        break;
    
    default:
        return false;
        break;
    }
}

bool PawnMoveTest(square** board, int size, coords startpos, coords targpos) {

    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;

    if ((board[startpos.x][startpos.y].color == black && movey == 1) || (board[startpos.x][startpos.y].color == white && movey == -1)) {
        if (movex == 0 && board[targpos.x][targpos.y].type == empty) {
            return true;
        } else if (abs(movex) == 1 && board[targpos.x][targpos.y].type != empty) {
            return true;
        }

    } else if (movex == 0 && ((board[startpos.x][startpos.y].color == black && targpos.y == 3) || (board[startpos.x][startpos.y].color == white && targpos.y == size-4))) {
        return true;
    }

    return false;
}

bool BishopMoveTest(square** board, int size, coords startpos, coords targpos) {

    if (abs(targpos.x-startpos.x) == abs(targpos.y-startpos.y)) {
        return CollisionTest(board, size, startpos, targpos);
    } else {
        return false;
    }
}

bool KnightMoveTest(square** board, int size, coords startpos, coords targpos) {
    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;

    if ((abs(movex) == 2 && abs(movey) == 1) || (abs(movex) == 1 && abs(movey) == 2)) {
        return true;
    } else {
        return false;
    }
}

bool RookMoveTest(square** board, int size, coords startpos, coords targpos) {

    if (targpos.x-startpos.x == 0 || targpos.y-startpos.y == 0) {
        return CollisionTest(board, size, startpos, targpos);
    } else {
        return false;
    }
}

bool QueenMoveTest(square** board, int size, coords startpos, coords targpos) {

    if (abs(targpos.x-startpos.x) == abs(targpos.y-startpos.y) || targpos.x-startpos.x == 0 || targpos.y-startpos.y == 0) {
        return CollisionTest(board, size, startpos, targpos);
    } else {
        return false;
    }
}

bool KingMoveTest(square** board, int size, coords startpos, coords targpos) {
    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;

    if (abs(movex) > 1 || abs(movey) > 1) {
        return false;
    } else {
        return true;
    }
}

bool CheckTest(square** board, int size, coords piecepos, color piececolor) {
    bool check = false;
    coords testpos;
    testpos.y = 0;
    while (testpos.y < size && check == false) {
        testpos.x = 0;
        while (testpos.x < size && check == false) {
            if (board[testpos.x][testpos.y].type != empty && board[testpos.x][testpos.y].type != king && (board[testpos.x][testpos.y].color != piececolor)) {
                check = MoveTest(board, size, testpos, piecepos);
            }
            testpos.x++;
        }
        testpos.y++;
    }
    return check;
}

bool RescueTest(square** board, int size, coords startpos,  coords kingpos) {

    color kingcolor = board[kingpos.x][kingpos.y].color;
    int movex = kingpos.x-startpos.x;
    int movey = kingpos.y-startpos.y;
    int dx, dy;

    if (movex == 0) {
        dx = 0;
    } else {
        dx = movex/abs(movex);
    }
    if (movey == 0) {
        dy = 0;
    } else {
        dy = movey/abs(movey);
    }

    int i=0;
    bool rescue = false;
    coords testcoords = startpos;
    
    while (i < (int)fmax(abs(movex),abs(movey)) && (rescue = CheckTest(board, size, testcoords, !kingcolor)) == false) {
        testcoords.x += dx;
        testcoords.y += dy;
        i++;
    }

    return rescue;
}

bool CheckMateTest(square** board, int size, coords kingpos) {
    bool checkmate = true;
    coords testcoords;
    testcoords.x = kingpos.x-1;

    color kingcolor = board[kingpos.x][kingpos.y].color;

    while (testcoords.x <= kingpos.x+1 && checkmate == true) {
        testcoords.y = kingpos.y-1;
        while (testcoords.y <= kingpos.y+1 && checkmate == true) {
            if (testcoords.x >= 0 && testcoords.x < size && testcoords.y >= 0 && testcoords.y < size) {
                
                if (board[testcoords.x][testcoords.y].color != kingcolor || board[testcoords.x][testcoords.y].type == empty) {
                    checkmate = CheckTest(board, size, testcoords, kingcolor);
                }
            }
            testcoords.y++;
        }
        testcoords.x++;
    }
    if (checkmate == true) {
        bool already_tested = false;
        for (testcoords.y = 0; testcoords.y < size; testcoords.y++) {
            for (testcoords.x = 0; testcoords.x < size; testcoords.x++) {
                if (board[testcoords.x][testcoords.y].type != empty && board[testcoords.x][testcoords.y].color != kingcolor && MoveTest(board, size, testcoords, kingpos) == true) {
                    if (already_tested == true) {
                        checkmate = false;
                    } else if (board[testcoords.x][testcoords.y].type == bishop || board[testcoords.x][testcoords.y].type == rook || board[testcoords.x][testcoords.y].type == queen) {
                        checkmate = !RescueTest(board, size, testcoords, kingpos);
                        already_tested = true;
                    } else {
                        checkmate = !CheckTest(board, size, testcoords, !kingcolor);
                        already_tested = true;
                    }
                }
            }
        }
    }
    return checkmate;
}

void MoveExecute(square** board, int size, coords startpos, coords targpos) {
    board[targpos.x][targpos.y] = board[startpos.x][startpos.y];
    board[startpos.x][startpos.y].type = empty;
}

bool CheckTestAfterMove(square** board, int size, coords startpos, coords targpos, coords kingpos, color kingcolor) {

    square startpiece = board[startpos.x][startpos.y];
    square targpiece = board[targpos.x][targpos.y];
    MoveExecute(board, size, startpos, targpos);
    bool check = CheckTest(board, size, kingpos, kingcolor);

    board[startpos.x][startpos.y] = startpiece;
    board[targpos.x][targpos.y] = targpiece;

    return check;
}