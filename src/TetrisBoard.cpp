#include <stdlib.h>
#include <time.h>
#include "TetrisBoard.h"


void TetrisBoard::init() {
    this->frame_count = 0;
    this->frame_threshold = 1000;
    srand(time(NULL));



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
    preBuiltClusters[0].tetrisClusterType = TetrisClusterType::S;

    preBuiltClusters[0].blocks[0].is_center = false;
    preBuiltClusters[0].blocks[0].offset_x = -1;
    preBuiltClusters[0].blocks[0].offset_y = 0;

    preBuiltClusters[0].blocks[1].is_center = true;
    preBuiltClusters[0].blocks[1].offset_x = 0;
    preBuiltClusters[0].blocks[1].offset_y = 0;

    preBuiltClusters[0].blocks[2].is_center = false;
    preBuiltClusters[0].blocks[2].offset_x = 0;
    preBuiltClusters[0].blocks[2].offset_y = -1;

    preBuiltClusters[0].blocks[3].is_center = false;
    preBuiltClusters[0].blocks[3].offset_x = 1;
    preBuiltClusters[0].blocks[3].offset_y = -1;

    //Z Cluster
    preBuiltClusters[1].tetrisClusterType = TetrisClusterType::Z;

    preBuiltClusters[1].blocks[0].is_center = false;
    preBuiltClusters[1].blocks[0].offset_x = 1;
    preBuiltClusters[1].blocks[0].offset_y = 0;

    preBuiltClusters[1].blocks[1].is_center = true;
    preBuiltClusters[1].blocks[1].offset_x = 0;
    preBuiltClusters[1].blocks[1].offset_y = 0;

    preBuiltClusters[1].blocks[2].is_center = false;
    preBuiltClusters[1].blocks[2].offset_x = 0;
    preBuiltClusters[1].blocks[2].offset_y = -1;

    preBuiltClusters[1].blocks[3].is_center = false;
    preBuiltClusters[1].blocks[3].offset_x = -1;
    preBuiltClusters[1].blocks[3].offset_y = -1;

    //L Cluster
    preBuiltClusters[2].tetrisClusterType = TetrisClusterType::L;

    preBuiltClusters[2].blocks[0].is_center = false;
    preBuiltClusters[2].blocks[0].offset_x = 0;
    preBuiltClusters[2].blocks[0].offset_y = 0;

    preBuiltClusters[2].blocks[1].is_center = true;
    preBuiltClusters[2].blocks[1].offset_x = 0;
    preBuiltClusters[2].blocks[1].offset_y = -1;

    preBuiltClusters[2].blocks[2].is_center = false;
    preBuiltClusters[2].blocks[2].offset_x = 0;
    preBuiltClusters[2].blocks[2].offset_y = -2;

    preBuiltClusters[2].blocks[3].is_center = false;
    preBuiltClusters[2].blocks[3].offset_x = 1;
    preBuiltClusters[2].blocks[3].offset_y = -2;

    //RevL Cluster
    preBuiltClusters[3].tetrisClusterType = TetrisClusterType::RevL;

    preBuiltClusters[3].blocks[0].is_center = false;
    preBuiltClusters[3].blocks[0].offset_x = 0;
    preBuiltClusters[3].blocks[0].offset_y = 0;

    preBuiltClusters[3].blocks[1].is_center = true;
    preBuiltClusters[3].blocks[1].offset_x = 0;
    preBuiltClusters[3].blocks[1].offset_y = -1;

    preBuiltClusters[3].blocks[2].is_center = false;
    preBuiltClusters[3].blocks[2].offset_x = 0;
    preBuiltClusters[3].blocks[2].offset_y = -2;

    preBuiltClusters[3].blocks[3].is_center = false;
    preBuiltClusters[3].blocks[3].offset_x = -1;
    preBuiltClusters[3].blocks[3].offset_y = -2;

    //Sqaure Cluster
    preBuiltClusters[4].tetrisClusterType = TetrisClusterType::Sqaure;
    preBuiltClusters[4].blocks[0].is_center = false;
    preBuiltClusters[4].blocks[0].offset_x = 0;
    preBuiltClusters[4].blocks[0].offset_y = 0;

    preBuiltClusters[4].blocks[1].is_center = true;
    preBuiltClusters[4].blocks[1].offset_x = 1;
    preBuiltClusters[4].blocks[1].offset_y = 0;

    preBuiltClusters[4].blocks[2].is_center = false;
    preBuiltClusters[4].blocks[2].offset_x = 0;
    preBuiltClusters[4].blocks[2].offset_y = -1;

    preBuiltClusters[4].blocks[3].is_center = false;
    preBuiltClusters[4].blocks[3].offset_x = 1;
    preBuiltClusters[4].blocks[3].offset_y = -1;

    //Line Cluster
    preBuiltClusters[5].tetrisClusterType = TetrisClusterType::Line;
    preBuiltClusters[5].blocks[0].is_center = false;
    preBuiltClusters[5].blocks[0].offset_x = 0;
    preBuiltClusters[5].blocks[0].offset_y = 0;

    preBuiltClusters[5].blocks[1].is_center = true;
    preBuiltClusters[5].blocks[1].offset_x = 0;
    preBuiltClusters[5].blocks[1].offset_y = -1;

    preBuiltClusters[5].blocks[2].is_center = false;
    preBuiltClusters[5].blocks[2].offset_x = 0;
    preBuiltClusters[5].blocks[2].offset_y = -2;

    preBuiltClusters[5].blocks[3].is_center = false;
    preBuiltClusters[5].blocks[3].offset_x = 0;
    preBuiltClusters[5].blocks[3].offset_y = -3;

    //T Cluster
    preBuiltClusters[6].tetrisClusterType = TetrisClusterType::T;
    preBuiltClusters[6].blocks[0].is_center = false;
    preBuiltClusters[6].blocks[0].offset_x = -1;
    preBuiltClusters[6].blocks[0].offset_y = 0;

    preBuiltClusters[6].blocks[1].is_center = true;
    preBuiltClusters[6].blocks[1].offset_x = 0;
    preBuiltClusters[6].blocks[1].offset_y = 0;

    preBuiltClusters[6].blocks[2].is_center = false;
    preBuiltClusters[6].blocks[2].offset_x = 1;
    preBuiltClusters[6].blocks[2].offset_y = 0;

    preBuiltClusters[6].blocks[3].is_center = false;
    preBuiltClusters[6].blocks[3].offset_x = 0;
    preBuiltClusters[6].blocks[3].offset_y = -1;

    this->generateNextCluster();
}

bool TetrisBoard::update(int direction) {
    if(this->frame_count % this->frame_threshold == 0) {
        int center_x = this->currentCluster.center_x;
        int center_y = this->currentCluster.center_y;

        //if we "remove" the live cluster this saves us having to write extra code
        //to avoid colliding with itself when we do our collision dections
        for(int i = 0;i<4;i++) {
            int lookup_x = center_x + this->currentCluster.blocks[i].offset_x;
            int lookup_y = center_y + this->currentCluster.blocks[i].offset_y;
            this->currentBoard[lookup_y][lookup_x] =  TetrisClusterType::None;
        }

        bool result = this->checkForOverlapAndAtEdge(direction);
        
        if(result == true) {
            //need to write back the shape
            for(int i = 0;i<4;i++) {
                int lookup_x = this->currentCluster.center_x + this->currentCluster.blocks[i].offset_x;
                int lookup_y = this->currentCluster.center_y + this->currentCluster.blocks[i].offset_y;
                this->currentBoard[lookup_y][lookup_x] = this->currentCluster.tetrisClusterType;
            }
            this->generateNextCluster();
        }

        for(int i = 0;i<4;i++) {
            int lookup_x = this->currentCluster.center_x + this->currentCluster.blocks[i].offset_x;
            int lookup_y = this->currentCluster.center_y + this->currentCluster.blocks[i].offset_y;
            this->currentBoard[lookup_y][lookup_x] = this->currentCluster.tetrisClusterType;
        }
        this->frame_count = 0;
        return true;
    }

    this->frame_count+=1;

    return false;
}

bool TetrisBoard::checkForOverlapAndAtEdge(int direction) {
    //if we have hit one of the arrow keys, this will shift us by one to the left or right
    //but wont if we have not hit any key, or a key we dont care about for direction
    int new_x = this->currentCluster.center_x + direction;
    
    //we only pass direction as 0 when we have not hit any key
    //so instead preform the normal case of dropping the block one more case
    int new_y = this->currentCluster.center_y;
    if(direction == 0) {
        new_y = this->currentCluster.center_y - 1;
    }
    bool anyAtZero = false;
    bool isOverlapping = false;

    for(int i = 0;i<4;i++) {
        
        int try_x = new_x + this->currentCluster.blocks[i].offset_x;
        int try_y = new_y + this->currentCluster.blocks[i].offset_y;

        if(try_x < 0 || try_x > 9) {
            //these are bad new points
            //return false, this will not overwrite the old positions 
            //no need to do extra work
            return false;
        }

        if(try_y == 0) {
            anyAtZero = true;
        }
        if(this->currentBoard[try_y][try_x] != TetrisClusterType::None) {
            isOverlapping = true;
        }
    }

    if(anyAtZero && !isOverlapping) {
        //this means that is has gotten to the bottom of the boarad
        //write back new position
        this->currentCluster.center_x = new_x;
        this->currentCluster.center_y = new_y;
        return true;
    }

    if(!anyAtZero && isOverlapping) {
        //this means that it has fallen to a point where it can no longer fall
        //dont write back new position
        return true;
    }

    if(!anyAtZero && !isOverlapping) {
        //The cluster still has space to fall
        //write back new position
        this->currentCluster.center_x = new_x;
        this->currentCluster.center_y = new_y;
        return false;
    }

    return anyAtZero;
}

void TetrisBoard::rotateCurrentBlock(int direction) {
    for(int i = 0;i<4;i++) {
        int old_x = this->currentCluster.blocks[i].offset_x;
        int old_y = this->currentCluster.blocks[i].offset_y;

        //I THINK THIS IS THE RIGHT WAY, I HAVE NO FUCKING IDEA AHHH
        this->currentCluster.blocks[i].offset_y = old_x * direction;
        this->currentCluster.blocks[i].offset_x = old_y * direction;
    }
}

TetrisClusterType TetrisBoard::getIndex(int x, int y) {
    return currentBoard[y][x];
}

void TetrisBoard::generateNextCluster() {
    //random value of TetrisClusterType
    //Create new cluster 
    int whichOne = rand() % 7;
    this->currentCluster = this->preBuiltClusters[whichOne];
    this->currentCluster.center_x = 5;
    this->currentCluster.center_y = 27;
}  