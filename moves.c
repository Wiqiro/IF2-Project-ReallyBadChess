#include <game.h>


bool collisionTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;
    int dx, dy;

    if (move_x == 0) {
        dx = 0;
    } else { 
        dx = move_x/abs(move_x);
    }

    if (move_y == 0) {
        dy = 0;
    } else {
        dy = move_y/abs(move_y);
    }

    int i=0;
        while (i+1 < fmax(abs(move_x),abs(move_y)) && board[start_pos.x+dx*(i+1)][start_pos.y+dy*(i+1)].type == empty) {
        i++;
    }
    if (i == fmax(abs(move_x),abs(move_y))-1) {
        return true; //returns true if the way is free (if there is only empty squares in the path of the bishop)
    } else {
        return false;
    }
}

bool moveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    switch (board[start_pos.x][start_pos.y].type) {
    case pawn:
        return pawnMoveTest(board, size, start_pos, targ_pos);
        break;
    case bishop:
        return bishopMoveTest(board, size, start_pos, targ_pos);
        break;
    case knight:
        return knightMoveTest(board, size, start_pos, targ_pos);
        break;
    case rook:
        return rookMoveTest(board, size, start_pos, targ_pos);
        break;
    case queen:
        return queenMoveTest(board, size, start_pos, targ_pos);
        break;
    case king:
        return kingMoveTest(board, size, start_pos, targ_pos);
        break;
    
    default:
        return false;
        break;
    }
}

bool pawnMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;

    if ((board[start_pos.x][start_pos.y].color == black && move_y == 1) || (board[start_pos.x][start_pos.y].color == white && move_y == -1)) {
        if (move_x == 0 && board[targ_pos.x][targ_pos.y].type == empty) {
            return true;
        } else if (abs(move_x) == 1 && board[targ_pos.x][targ_pos.y].type != empty) {
            return true;
        }

    } else if (move_x == 0 && ((board[start_pos.x][start_pos.y].color == black && targ_pos.y == 3) || (board[start_pos.x][start_pos.y].color == white && targ_pos.y == size-4))) {
        return true;
    }

    return false;
}

bool bishopMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    if (abs(targ_pos.x-start_pos.x) == abs(targ_pos.y-start_pos.y)) {
        return collisionTest(board, size, start_pos, targ_pos);
    } else {
        return false;
    }
}

bool knightMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {
    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;

    if ((abs(move_x) == 2 && abs(move_y) == 1) || (abs(move_x) == 1 && abs(move_y) == 2)) {
        return true;
    } else {
        return false;
    }
}

bool rookMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    if (targ_pos.x-start_pos.x == 0 || targ_pos.y-start_pos.y == 0) {
        return collisionTest(board, size, start_pos, targ_pos);
    } else {
        return false;
    }
}

bool queenMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    if (abs(targ_pos.x-start_pos.x) == abs(targ_pos.y-start_pos.y) || targ_pos.x-start_pos.x == 0 || targ_pos.y-start_pos.y == 0) {
        return collisionTest(board, size, start_pos, targ_pos);
    } else {
        return false;
    }
}

bool kingMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {
    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;

    if (abs(move_x) > 1 || abs(move_y) > 1) {
        return false;
    } else {
        return true;
    }
}

bool checkTest(Square** board, int size, Coords piece_pos, Color piece_color) {
    bool check = false;
    Coords test_pos;
    test_pos.y = 0;
    while (test_pos.y < size && check == false) {
        test_pos.x = 0;
        while (test_pos.x < size && check == false) {
            if (board[test_pos.x][test_pos.y].type != empty && board[test_pos.x][test_pos.y].type != king && (board[test_pos.x][test_pos.y].color != piece_color)) {
                check = moveTest(board, size, test_pos, piece_pos);
            }
            test_pos.x++;
        }
        test_pos.y++;
    }
    return check;
}

bool RescueTest(Square** board, int size, Coords start_pos,  Coords king_pos) {

    Color kingcolor = board[king_pos.x][king_pos.y].color;
    int move_x = king_pos.x-start_pos.x;
    int move_y = king_pos.y-start_pos.y;
    int dx, dy;

    if (move_x == 0) {
        dx = 0;
    } else {
        dx = move_x/abs(move_x);
    }
    if (move_y == 0) {
        dy = 0;
    } else {
        dy = move_y/abs(move_y);
    }

    int i=0;
    bool rescue = false;
    Coords test_coords = start_pos;
    
    while (i < (int)fmax(abs(move_x),abs(move_y)) && (rescue = checkTest(board, size, test_coords, !kingcolor)) == false) {
        test_coords.x += dx;
        test_coords.y += dy;
        i++;
    }

    return rescue;
}

bool checkMateTest(Square** board, int size, Coords king_pos) {
    bool checkmate = true;
    Coords test_coords;
    test_coords.x = king_pos.x-1;

    Color kingcolor = board[king_pos.x][king_pos.y].color;

    while (test_coords.x <= king_pos.x+1 && checkmate == true) {
        test_coords.y = king_pos.y-1;
        while (test_coords.y <= king_pos.y+1 && checkmate == true) {
            if (test_coords.x >= 0 && test_coords.x < size && test_coords.y >= 0 && test_coords.y < size) {
                
                if (board[test_coords.x][test_coords.y].color != kingcolor || board[test_coords.x][test_coords.y].type == empty) {
                    checkmate = checkTest(board, size, test_coords, kingcolor);
                }
            }
            test_coords.y++;
        }
        test_coords.x++;
    }
    if (checkmate == true) {
        bool already_tested = false;
        for (test_coords.y = 0; test_coords.y < size; test_coords.y++) {
            for (test_coords.x = 0; test_coords.x < size; test_coords.x++) {
                if (board[test_coords.x][test_coords.y].type != empty && board[test_coords.x][test_coords.y].color != kingcolor && moveTest(board, size, test_coords, king_pos) == true) {
                    if (already_tested == true) {
                        checkmate = false;
                    } else if (board[test_coords.x][test_coords.y].type == bishop || board[test_coords.x][test_coords.y].type == rook || board[test_coords.x][test_coords.y].type == queen) {
                        checkmate = !RescueTest(board, size, test_coords, king_pos);
                        already_tested = true;
                    } else {
                        checkmate = !checkTest(board, size, test_coords, !kingcolor);
                        already_tested = true;
                    }
                }
            }
        }
    }
    return checkmate;
}

void moveExecute(Square** board, int size, Coords start_pos, Coords targ_pos) {
    board[targ_pos.x][targ_pos.y] = board[start_pos.x][start_pos.y];
    board[start_pos.x][start_pos.y].type = empty;
}

bool checkTestAfterMove(Square** board, int size, Coords start_pos, Coords targ_pos, Coords king_pos, Color kingcolor) {

    Square startpiece = board[start_pos.x][start_pos.y];
    Square targpiece = board[targ_pos.x][targ_pos.y];
    moveExecute(board, size, start_pos, targ_pos);
    bool check = checkTest(board, size, king_pos, kingcolor);

    board[start_pos.x][start_pos.y] = startpiece;
    board[targ_pos.x][targ_pos.y] = targpiece;

    return check;
}