#include "header.h"

void initVariable(vector<double>& pi, vector< vector<double> >& thetaInit, vector< vector< vector<double> > >& thetaTrans) {
    //TODO
}

void setSigma(vector< vector<int> >& X, vector < vector< map<int, int> > >& sigma, int trainingNum) {
    //TODO
}

void estep(X, pi, thetaInit, thetaTrans, condProb) {
    //TODO
}
    
vecotr<double> computeLL(X, thetaInit, thetaTrans) {
    //TODO
}

void mstep(pi, thetaInit, thetaTrans, condProb) {
    //TODO
}

void mixMarkov(vector< vector<int> >& X, int trainingNum, int numOfState, 
        int K, vector<double>& pi, vector< vector<double> >& thetaInit,
        vector< vector< vector<double> > >& thetaTrans) {
    vector < vector< map<int, int> > > sigma;
    vector<double> ll_variables(3);
    vector< vector<double> > condProb(trainingNum);
    initVariable(pi, thetaInit, thetaTrans);
    setSigma(X, sigma, trainingNum);

    estep(X, pi, thetaInit, thetaTrans, condProb);
    
    ll_variables = computeLL(X, thetaInit, thetaTrans);
    
    for (iter = 1; iter<= MAX_ITER; ++iter) {
        mstep(pi, thetaInit, thetaTrans, condProb);
        estep(X, pi, thetaInit, thetaTrans, condProb);
        vector<double> new_ll_variables(3);
        new_ll_variables = computeLL(X, thetaInit, thetaTrans);
        
        //check for convergence
        if (new_ll_variables[0] + new_ll_variables[1] + new_ll_variables[2] - (ll_variables[0] + ll_variables[1] + ll_variables[2]) >TOL ) {
            ll_variables = new_ll_variables; 
        } else {
            break;
        }
    }
}
