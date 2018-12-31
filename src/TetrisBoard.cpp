#include <stdlib.h>
#include <time.h>
#include "TetrisBoard.h"


void TetrisBoard::init() {
    srand(time(NULL));

    this->level = 1;
    this->score = 0;
    this->cleared_lines = 0;

    //this can use some explanation
    //To make things simple we see each tetrinom/cluster as a single point(is_center)
    //that has 3 offset blocks
    //we move the center block, just the relative offsets and then HEY we have
    //moved the entire cluster
    //this does mean we have to problem in the cluster some how
    //that is what this is
    //this could also be a file, or some preprocessor macro
    //I have choose it to define it like this beause it was the fastest from
    //a development standpoint 
    //the other solutions require standing up more tech to support it

    //S cluster
    pre_built_clusters[0].tetris_cluster_type = TetrisClusterType::S;

    pre_built_clusters[0].blocks[0].offset_x = -1;
    pre_built_clusters[0].blocks[0].offset_y = 0;

    pre_built_clusters[0].blocks[1].offset_x = 0;
    pre_built_clusters[0].blocks[1].offset_y = 0;

    pre_built_clusters[0].blocks[2].offset_x = 0;
    pre_built_clusters[0].blocks[2].offset_y = -1;

    pre_built_clusters[0].blocks[3].offset_x = 1;
    pre_built_clusters[0].blocks[3].offset_y = -1;

    //Z Cluster
    pre_built_clusters[1].tetris_cluster_type = TetrisClusterType::Z;

    pre_built_clusters[1].blocks[0].offset_x = 1;
    pre_built_clusters[1].blocks[0].offset_y = 0;

    pre_built_clusters[1].blocks[1].offset_x = 0;
    pre_built_clusters[1].blocks[1].offset_y = 0;

    pre_built_clusters[1].blocks[2].offset_x = 0;
    pre_built_clusters[1].blocks[2].offset_y = -1;

    pre_built_clusters[1].blocks[3].offset_x = -1;
    pre_built_clusters[1].blocks[3].offset_y = -1;

    //L Cluster
    pre_built_clusters[2].tetris_cluster_type = TetrisClusterType::L;

    pre_built_clusters[2].blocks[0].offset_x = -1;
    pre_built_clusters[2].blocks[0].offset_y = 0;

    pre_built_clusters[2].blocks[1].offset_x = 0;
    pre_built_clusters[2].blocks[1].offset_y = 0;

    pre_built_clusters[2].blocks[2].offset_x = 1;
    pre_built_clusters[2].blocks[2].offset_y = 0;

    pre_built_clusters[2].blocks[3].offset_x = -1;
    pre_built_clusters[2].blocks[3].offset_y = -1;

    //RevL Cluster
    pre_built_clusters[3].tetris_cluster_type = TetrisClusterType::RevL;

    pre_built_clusters[3].blocks[0].offset_x = -1;
    pre_built_clusters[3].blocks[0].offset_y = 0;

    pre_built_clusters[3].blocks[1].offset_x = 0;
    pre_built_clusters[3].blocks[1].offset_y = 0;

    pre_built_clusters[3].blocks[2].offset_x = 1;
    pre_built_clusters[3].blocks[2].offset_y = 0;

    pre_built_clusters[3].blocks[3].offset_x = 1;
    pre_built_clusters[3].blocks[3].offset_y = -1;

    //Sqaure Cluster
    pre_built_clusters[4].tetris_cluster_type = TetrisClusterType::Sqaure;

    pre_built_clusters[4].blocks[0].offset_x = 0;
    pre_built_clusters[4].blocks[0].offset_y = 0;

    pre_built_clusters[4].blocks[1].offset_x = 1;
    pre_built_clusters[4].blocks[1].offset_y = 0;

    pre_built_clusters[4].blocks[2].offset_x = 0;
    pre_built_clusters[4].blocks[2].offset_y = -1;

    pre_built_clusters[4].blocks[3].offset_x = 1;
    pre_built_clusters[4].blocks[3].offset_y = -1;

    //Line Cluster
    pre_built_clusters[5].tetris_cluster_type = TetrisClusterType::Line;

    pre_built_clusters[5].blocks[0].offset_x = -1;
    pre_built_clusters[5].blocks[0].offset_y = 0;

    pre_built_clusters[5].blocks[1].offset_x = 0;
    pre_built_clusters[5].blocks[1].offset_y = 0;

    pre_built_clusters[5].blocks[2].offset_x = 1;
    pre_built_clusters[5].blocks[2].offset_y = 0;

    pre_built_clusters[5].blocks[3].offset_x = 2;
    pre_built_clusters[5].blocks[3].offset_y = 0;

    //T Cluster
    pre_built_clusters[6].tetris_cluster_type = TetrisClusterType::T;

    pre_built_clusters[6].blocks[0].offset_x = -1;
    pre_built_clusters[6].blocks[0].offset_y = 0;

    pre_built_clusters[6].blocks[1].offset_x = 0;
    pre_built_clusters[6].blocks[1].offset_y = 0;

    pre_built_clusters[6].blocks[2].offset_x = 1;
    pre_built_clusters[6].blocks[2].offset_y = 0;

    pre_built_clusters[6].blocks[3].offset_x = 0;
    pre_built_clusters[6].blocks[3].offset_y = -1;

    this->generateNextCluster();
}

void TetrisBoard::update(TetrisAction action, int direction) {
    int center_x = this->current_cluster.center_x;
    int center_y = this->current_cluster.center_y;

    //if we "remove" the live cluster this saves us having to write extra code
    //to avoid colliding with itself when we do our collision detection
    for(int i = 0;i<4;i++) {
        int lookup_x = center_x + this->current_cluster.blocks[i].offset_x;
        int lookup_y = center_y + this->current_cluster.blocks[i].offset_y;
        this->current_board[lookup_y][lookup_x] = TetrisClusterType::None;
    }

    bool result;
    switch (action) {
        case TetrisAction::Fall:
        case TetrisAction::Drop:
        case TetrisAction::Move:
            result = this->checkForOverlapAndAtEdge(direction);
        break;

        case TetrisAction::Rotate:
            this->rotateCurrentBlock(direction);
            result = false;
        break;
    }

    //If we have hit the bottom or overlap, we need to write back the old position 
    if(result == true) {
        //need to write back the shape
        for(int i = 0;i<4;i++) {
            int lookup_x = this->current_cluster.center_x + this->current_cluster.blocks[i].offset_x;
            int lookup_y = this->current_cluster.center_y + this->current_cluster.blocks[i].offset_y;
            this->current_board[lookup_y][lookup_x] = this->current_cluster.tetris_cluster_type;
        }

        if(action == TetrisAction::Drop || action == TetrisAction::Fall) {
            //if thiw was on the correct action 
            //then create the new shape
            this->generateNextCluster();
            int cleared_lines = this->checkForFullRows();
            if(cleared_lines != 0) {
                score += (TETRIS_BASE_SCORE[cleared_lines - 1] * level);
                this->cleared_lines += cleared_lines;
                this->level = this->cleared_lines / 10 + 1;
            }
        }
    }
    //and reguardless write back either the new cluster, or writeback the old one
    for(int i = 0;i<4;i++) {
        int lookup_x = this->current_cluster.center_x + this->current_cluster.blocks[i].offset_x;
        int lookup_y = this->current_cluster.center_y + this->current_cluster.blocks[i].offset_y;
        this->current_board[lookup_y][lookup_x] = this->current_cluster.tetris_cluster_type;
    }    
}

bool TetrisBoard::checkForOverlapAndAtEdge(int direction) {
    //if we have hit one of the arrow keys, this will shift us by one to the left or right
    //but wont if we have not hit any key, or a key we dont care about for direction
    int new_x = this->current_cluster.center_x + direction;
    
    //we only pass direction as 0 when we have not hit any key
    //so instead preform the normal case of dropping the block one more case
    int new_y = this->current_cluster.center_y;
    if(direction == 0) {
        new_y = this->current_cluster.center_y - 1;
    }
    bool any_at_zero = false;
    bool is_overlapping = false;

    for(int i = 0;i<4;i++) {
        
        int try_x = new_x + this->current_cluster.blocks[i].offset_x;
        int try_y = new_y + this->current_cluster.blocks[i].offset_y;

        if(try_x < 0 || try_x > 9) {
            //these are bad new points
            //return false, this will not overwrite the old positions 
            //no need to do extra work
            return false;
        }

        if(try_y == -1) {
            any_at_zero = true;
        }
        else if(this->current_board[try_y][try_x] != TetrisClusterType::None) {
            is_overlapping = true;
        }
    }

    if(!any_at_zero && is_overlapping) {
        //this means that it has fallen to a point where it can no longer fall
        //dont write back new position
        return true;
    }

    if(!any_at_zero && !is_overlapping) {
        //The cluster still has space to fall
        //write back new position
        this->current_cluster.center_x = new_x;
        this->current_cluster.center_y = new_y;
        return false;
    }

    return any_at_zero;
}

int TetrisBoard::checkForFullRows() {
    int cleared_lines = 0;
    int row_count = 0;
    //for each row
    for(int y = 0;y<28;y++) {
        row_count = 0;
        //count a full row 
        for(int x = 0;x<10;x++) {
            if(this->current_board[y][x] != TetrisClusterType::None) {
                row_count+=1;
            }
        }
        //if it is all full
        if(row_count == 10) {
            cleared_lines += 1;
            //CLEAR THE ROW
            for(int x = 0;x<10;x++) {
                this->current_board[y][x] = TetrisClusterType::None;
            }

            //shifting the rows above the one we cleared
            for(int up_y = y + 1;up_y<28;up_y++) {
                for(int x = 0;x<10;x++){
                    this->current_board[up_y - 1][x] = this->current_board[up_y][x];
                    this->current_board[up_y][x] = TetrisClusterType::None;
                }
            }
            //since we shifted all the rows down one, we have to also walk back the y counter, to catch the row
            //above the one we just cleared
            y -=1;
        }
    }
    return cleared_lines;
}

void TetrisBoard::rotateCurrentBlock(int direction) {
    //This is what I would call a straight HACK that I am doing because guess what it WORKS!
    if(this->current_cluster.tetris_cluster_type == TetrisClusterType::Sqaure) {
        return;
    }
    //we need to store them
    //so that way if all four pass we can just set
    //otherwise we discard
    //the other way of doing this would be to regenerate the points
    //after we see then pass them one by one
    int possible_new_offsets[4][2];
    bool any_fail = false;
    for(int i = 0;i<4;i++) {
        //0 is x position, which we write y into
        //1 in y position, which we write x into
        //doing this will preform the first step of the 90 degree rotation
        possible_new_offsets[i][0] = this->current_cluster.blocks[i].offset_y;
        possible_new_offsets[i][1] = this->current_cluster.blocks[i].offset_x;

        //this is a simple way of preforming a 90 degree rotation depending on the way in which you do it
        if(direction == -1) {
            possible_new_offsets[i][0] *= -1;
        }
        else if(direction == 1) {
            possible_new_offsets[i][1] *= -1;
        }

        int test_x = this->current_cluster.center_x + possible_new_offsets[i][0];
        int test_y = this->current_cluster.center_y + possible_new_offsets[i][1];

        if(test_x < 0 || test_x > 9) {
            //the rotation rotated out of the left-right bounds
            any_fail = true;
        }
        else if(test_y < 0 || test_y > 27) {
            any_fail = true;
        }
        else if(this->current_board[test_y][test_x] != TetrisClusterType::None) {
            any_fail = true;
        }
    }

    if(!any_fail) {
        //if we had no fail conditions write back the rotated posistions 
        for(int i = 0;i<4;i++) {
            this->current_cluster.blocks[i].offset_x = possible_new_offsets[i][0];
            this->current_cluster.blocks[i].offset_y = possible_new_offsets[i][1];
        }
    }
}

int TetrisBoard::getScore() {
    return this->score;
}

int TetrisBoard::getLevel() {
    return this->level;
}

int TetrisBoard::getLinesCleared() {
    return this->cleared_lines;
}

TetrisClusterType TetrisBoard::getIndex(int x, int y) {
    return current_board[y][x];
}

void TetrisBoard::generateNextCluster() {
    //random value of TetrisClusterType
    //Create new cluster 
    int whichOne = rand() % 7;
    this->current_cluster = this->pre_built_clusters[whichOne];
    //mid top of the board
    this->current_cluster.center_x = 5;
    this->current_cluster.center_y = 27;
}  