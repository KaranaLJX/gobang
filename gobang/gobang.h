#pragma once
#include"stdc++.h"
#include<easyx.h>
#include<conio.h>
#include<unordered_map>
using namespace std;
using p = pair<short, short>;
using ll = long long;
class scoreshape {
public:
    short x, y, x_direct, y_direct, offset;
    scoreshape(short xx, short yy, short xx_direct, short yy_direct, short _offset) :
        x(xx), y(yy), x_direct(xx_direct), y_direct(yy_direct), offset(_offset)
    {}
    //这里
    scoreshape() = default;
    bool inequal(short xx, short yy, short xx_direct, short yy_direct) const {
        if (xx_direct == x_direct && yy_direct == y_direct) {
            int resx = (xx - x) * x_direct - offset;
            int resy = (yy - y) * y_direct - offset;
            if (x_direct == 0)
                return xx == x && resy >= 0 && resy <5;
            if (y_direct == 0)
                return yy == y && resx >= 0 && resx <5;
            return resx >= 0 && resx <5 && resy >= 0 && resy <5;
        }
        else
            return false;
    }
    bool in(short xx, short yy) const {
        int resx = (xx - x) * x_direct - offset;
        int resy = (yy - y) * y_direct - offset;
        if (x_direct == 0)
            return xx == x && resy >= 0 && resy <5;
        if (y_direct == 0)
            return yy == y && resx >= 0 && resx < 5;
        else
            return resx >= 0 && resx < 5 && resy >= 0 && resy < 5;

    }
};
class gobang {
public:
    static const int col= 15, gridwidth = 40, radis = 16;
    static const int graphwidth = gridwidth * col;
    static const int MAXSCORE = 99999999;
    static const int RATIO = 1;
    static const int DEPTH = 3;
    static const  unordered_map<string, int> score_type;
    bool iswin;
    bool isaiwin;
    bool aiturn;
    bool cal_score_win;
    list<p> aiChesspoint;
    list<p> humanChesspoint;
    p nextpoint;
    p lastpoint;
    bitset<col + 1> aichess[col + 1];
    bitset<col + 1> humanchess[col + 1];
    gobang();
    bool winGame(bool isai,short x,short y);
    int negmax(bool isai, int depth, int alpha, int beta, p mylastpoint);
    int evaluate(bool isai);
    ll cal_score(short m, short n, short x_decrict, 
        short y_derice,list<pair<ll,scoreshape>>& vec,bool isai);
                    


};


/**
 判断是否递归结束（有人赢了或者到达递归深度0）
    如果递归结束
        返回评分值
    否则
        从最新的落点开始bfs
        for each 候选节点x：
            如果isai
                将x加入aiChess
            否则
                将x加入humanchess
            将x加入allchess
            value=-negmax(!isai,depth-1,-beta,-alpha);
            回溯恢复：
            如果isai
                将x从aichess删去
            否则
                将x从humanchess删除
            将x从allchess删除
**/



