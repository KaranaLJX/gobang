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
    //����
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
 �ж��Ƿ�ݹ����������Ӯ�˻��ߵ���ݹ����0��
    ����ݹ����
        ��������ֵ
    ����
        �����µ���㿪ʼbfs
        for each ��ѡ�ڵ�x��
            ���isai
                ��x����aiChess
            ����
                ��x����humanchess
            ��x����allchess
            value=-negmax(!isai,depth-1,-beta,-alpha);
            ���ݻָ���
            ���isai
                ��x��aichessɾȥ
            ����
                ��x��humanchessɾ��
            ��x��allchessɾ��
**/



