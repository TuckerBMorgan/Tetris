#pragma once
#include "Util.h"

enum TetrisClusterType {
    None,
    S,
    Z,
    L,
    RevL,
    Sqaure,
    Line,
    T
};

enum TetrisAction {
    Move,
    Rotate,
    Drop,//drop is the user asking for the block to be dropped as far as it can go
    Fall//Fall is down one
};

struct TetrisBlock {
    int offset_x;
    int offset_y;
    bool is_center;
};

struct TetrisCluster {
    int center_x;
    int center_y;
    TetrisClusterType tetris_cluster_type;
    TetrisBlock blocks[4];
};

static constexpr Color BLOCK_COLORS[8] = {Color{255, 0, 0},
                                          Color{0, 255, 0},
                                          Color{0, 0, 255}, 
                                          Color{255, 0, 128}, 
                                          Color{255, 255, 0}, 
                                          Color{0, 255, 255}, 
                                          Color{128, 0, 255},
                                          Color{255, 128, 255}};

class TetrisBoard {
    public:

        void init();
        //returns true if the board state was updated, false otherwise
        bool update(TetrisAction action, int direction);
        TetrisClusterType getIndex(int x, int y);

    private:
        void generateNextCluster();
        bool checkForOverlapAndAtEdge(int direction);
        void rotateCurrentBlock(int direction);

        //we can copy a random element from this array and have our new block!
        TetrisCluster pre_built_clusters[7];
        TetrisClusterType current_board[28][10];
        TetrisCluster current_cluster;
        int frame_count;
        int frame_threshold;
};