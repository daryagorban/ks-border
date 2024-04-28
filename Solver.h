#ifndef SOLVER_H
#define SOLVER_H

#include "Parser.h"
#include<algorithm>
#include<vector>
#include<bits/stdc++.h>

class Solver {

    Parser *parser;

public:

    vector <tuple <double, int, int, int> > DATA; // v:w, v, w, index
    vector <tuple <double, int, int, int> > init_DATA;
    vector <int> INDEX;

    Solver(Parser *parser);
    ~Solver();

    void solve(Parser *parser, int N, int MAX_W);

    tuple<double,double,double,double> highest_border(double lvl, double w, double sum, double border, double& cur_sum, int MAX_W);

};

Solver::Solver(Parser *parser) {

    vector<double> V = parser->get_X();
    vector<double> W = parser->get_Y();

    for (int i = 0; i < V.size(); i++)
    {
        DATA.push_back(make_tuple(V[i]/W[i],V[i],W[i],i));
        INDEX.push_back(0);
    }

    init_DATA = DATA;

}

Solver::~Solver() {

    DATA.clear();

}


tuple<double,double,double,double> Solver::highest_border(double lvl, double w, double sum, double border, double& cur_sum, int MAX_W)
{

    tuple<double,double,double,double> V;
    V = make_tuple(lvl,w,sum,border);

    if (w <= MAX_W && sum > cur_sum)
        cur_sum = sum;

    sort(DATA.begin(),DATA.end(),
         [](auto&v1,auto&v2) {return v1 > v2;});

    if (w >= MAX_W) return make_tuple(lvl,w,sum,0);

    int S = DATA.size();

    lvl++;

    while ( lvl < S &&  w + get<2>(DATA[lvl]) <= MAX_W )
    {
        w += get<2>(DATA[lvl]);
        sum += get<1>(DATA[lvl]);
        lvl++;
    }

    if (lvl < S)
        sum += (MAX_W - w) * get<1>(DATA[lvl]) / get<2>(DATA[lvl]);

    V = make_tuple(get<0>(V),get<1>(V),get<2>(V),sum);

    return V;

}


void Solver::solve(Parser *parser, int N, int MAX_W) {

    int i, j, k, m;
    double new_size = DATA.size(), current_sum = 0;

    sort(DATA.begin(),DATA.end(),
         [](auto&v1,auto&v2) {return v1 > v2;});


    queue< tuple <double,double,double,double> > Q; //lvl, w, cst, bnd

    tuple<double,double,double,double> V1, V2;
    V1 = make_tuple(-1,0,0,0);
    Q.push(V1);

    while (!Q.empty())
    {

        V1 = Q.front();
        Q.pop();

        if (get<0>(V1) == -1) V2 = make_tuple(0,get<1>(V2),get<2>(V2),get<3>(V2));

        if ( get<0>(V1) != new_size - 1 )
        {

            V2 = highest_border(get<0>(V1) + 1,get<1>(V1) + get<2>(DATA[get<0>(V1)]),get<2>(V1) + get<1>(DATA[get<0>(V1)]),get<3>(V2),current_sum, MAX_W);

            if (get<3>(V2) > current_sum)
                Q.push(V2);

            V2 = highest_border(get<0>(V2),get<1>(V1),get<2>(V1),get<3>(V2),current_sum, MAX_W);

            if (get<3>(V2) > current_sum)
                Q.push(V2);

        }

    }


    cout << current_sum << endl;

    return;

}

#endif
