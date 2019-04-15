#include <vector>
#include <assert.h>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <cstdlib>
#include <iostream>


using namespace std;

class And_component {

  public:

    std::bitset < 1 > a, b;

  bitset < 1 > And_sfunction() {
    // out = a&b;
    return (a & b);
  }

};

class full_adder {

  public:
    std::bitset < 3 > input;

  full_adder() {

    input = 0;

  }

  std::bitset < 1 > calcul_S() {

    std::bitset < 1 > a; //=input[0];
    std::bitset < 1 > b; //=input[1];
    std::bitset < 1 > c_in; //=input[3];
    a[0] = input[0];
    b[0] = input[1];
    c_in[0] = input[2];
    return ((a ^ b) ^ c_in);

  }

  std::bitset < 1 > calcul_cout() {

    std::bitset < 1 > a; //=input[0];
    std::bitset < 1 > b; //=input[1];
    //std::bitset<1> d;//=input[2];
    std::bitset < 1 > c_in; //=input[3];

    a[0] = input[0];
    b[0] = input[1];
    c_in[0] = input[2];

    return ((a & b) | (c_in & ((a ^ b))));
  }
};

class full_adderBlock {

  public:
    std::bitset < 4 > input;
  int appx;
  //                full_adder FA;
  //                And_component et;

  full_adderBlock() {
    appx = 0;
  }

  std::bitset < 1 > calcul_S() {

    //                    et.a=inputs[0];
    //                    et.b=inputs[1];
    //                    FA.input[0]=et.And_sfunction()[0];
    //                    FA.input[1]=inputs[2];
    //                    FA.input[2]=inputs[3];//cin
    std::bitset < 1 > a; //=input[0];
    std::bitset < 1 > b; //=input[1];
    std::bitset < 1 > d; //=input[2];
    std::bitset < 1 > c_in; //=input[3];
    a[0] = input[0];
    b[0] = input[1];
    d[0] = input[2];
    c_in[0] = input[3];
    //c_in[0]=input[3];
    if (appx == 1) return ((a & b) ^ (d ^ (c_in))); //appx full adder 1
    else if (appx == 2) return ((a & b) ^ d) | (c_in); // appx full adder 2
    else if (appx == 3) return (~(((a & b) & d) | (c_in & ((a & b) ^ (d))))); // appx adder 3

    else

      return ((a & b) ^ (d ^ (c_in))); // exact adder

  }

  std::bitset < 1 > calcul_cout() {

    std::bitset < 1 > a; //=input[0];
    std::bitset < 1 > b; //=input[1];
    std::bitset < 1 > d; //=input[2];
    std::bitset < 1 > c_in; //=input[3];

    a[0] = input[0];
    b[0] = input[1];
    d[0] = input[2];
    c_in[0] = input[3];

    if (appx == 1) return (c_in); //aproximate adder 1
    else if (appx == 2) return (((a & b) & d) | (c_in & ((a & b) ^ (d)))); // appxmt adder 2
    else if (appx == 3) return (((a & b) & d) | (c_in & ((a & b) ^ (d)))); // appxmt adder 3

    else

      return (((a & b) & d) | (c_in & ((a & b) ^ (d))));

  }
};

class full_adderAppx {

  public:
    std::bitset < 3 > input;
  int appx;
  //                full_adder FA;
  //                And_component et;

  full_adderAppx() {
    appx = 0;
  }

  std::bitset < 1 > calcul_S() {

    //                    et.a=inputs[0];
    //                    et.b=inputs[1];
    //                    FA.input[0]=et.And_sfunction()[0];
    //                    FA.input[1]=inputs[2];
    //                    FA.input[2]=inputs[3];//cin
    std::bitset < 1 > a; //=input[0];
    std::bitset < 1 > b; //=input[1];
    std::bitset < 1 > c_in; //=input[3];
    a[0] = input[0];
    b[0] = input[1];
    c_in[0] = input[2];
    //c_in[0]=input[3];
    if (appx == 1) return (a ^ (b ^ (c_in))); //appx InXA1
    else if (appx == 2) return (a ^ b) | (c_in); // appx InXA2
    else if (appx == 3) return (~((a & b) | (c_in & (a ^ b)))); // appx InXA3
    else if (appx == 4) return (a ^ (b ^ (c_in))); // Exact FA
    else if (appx == 5) return (c_in & (~(a ^ b))); // AM1
    else if (appx == 6) return (~c_in & (a ^ b)) | (~a & ~b); // AM2
    else if (appx == 7) return (~b & (~a | (a & ~c_in))); // AM3
    else if (appx == 8) return (c_in & (b | (~a & ~b))); // AM4
    else if (appx == 9) return (b); // AM5
    else if (appx == 'a') return (c_in); // AXA1
    else if (appx == 'b') return (~(a ^ b)); // AXA2
    else

      return (c_in & (a ^ b)) | (a & b); // AXA3

  }

  std::bitset < 1 > calcul_cout() {

    std::bitset < 1 > a; //=input[0];
    std::bitset < 1 > b; //=input[1];
    std::bitset < 1 > c_in; //=input[3];

    a[0] = input[0];
    b[0] = input[1];
    c_in[0] = input[2];

    if (appx == 1) return (c_in); //aproximate adder 1
    else if (appx == 2) return ((a & b) | (c_in & (a ^ b))); // appxmt adder 2
    else if (appx == 3) return ((a & b) | (c_in & (a ^ b))); // appxmt adder 3
    else if (appx == 4) return ((a & b) | (c_in & (a ^ b))); // exact adder
    else if (appx == 5) return (c_in & (a ^ b)) | (b & (a | (~a & ~c_in))); // appxmt adder M1
    else if (appx == 6) return (c_in & (a ^ b)) | (a & b); // appxmt adder M2
    else if (appx == 7) return (b) | ((a & ~b) & c_in); // appxmt adder M3
    else if (appx == 8) return (a); // appxmt adder M4
    else if (appx == 9) return (a); // appxmt adder M5
    else if (appx == 'a') return (~(((a ^ b) & c_in) | (~a & ~b))); // appxmt adder AXA1
    else if (appx == 'b') return (((a ^ b) & c_in) | (a & b)); // appxmt adder AXA2
    else

      return (c_in & (a ^ b)) | (a & b); // appxmt adder AXA3

  }
};

class adder8 {
  public:

    full_adderAppx Tab_FA[8];
  std::bitset < 8 > S; // output

  std::bitset < 8 > layout_add8(std::bitset < 8 > A, std::bitset < 8 > B) {
    Tab_FA[0].input[0] = A[0];
    Tab_FA[0].input[1] = B[0];
    Tab_FA[0].input[2] = 0;
    S[0] = Tab_FA[0].calcul_S()[0];

    Tab_FA[1].input[0] = A[1];
    Tab_FA[1].input[1] = B[1];
    Tab_FA[1].input[2] = Tab_FA[0].calcul_cout()[0];
    S[1] = Tab_FA[1].calcul_S()[0];

    Tab_FA[2].input[0] = A[2];
    Tab_FA[2].input[1] = B[2];
    Tab_FA[2].input[2] = Tab_FA[1].calcul_cout()[0];
    S[2] = Tab_FA[2].calcul_S()[0];

    Tab_FA[3].input[0] = A[3];
    Tab_FA[3].input[1] = B[3];
    Tab_FA[3].input[2] = Tab_FA[2].calcul_cout()[0];
    S[3] = Tab_FA[3].calcul_S()[0];

    Tab_FA[4].input[0] = A[4];
    Tab_FA[4].input[1] = B[4];
    Tab_FA[4].input[2] = Tab_FA[3].calcul_cout()[0];
    S[4] = Tab_FA[4].calcul_S()[0];

    Tab_FA[5].input[0] = A[5];
    Tab_FA[5].input[1] = B[5];
    Tab_FA[5].input[2] = Tab_FA[4].calcul_cout()[0];
    S[5] = Tab_FA[5].calcul_S()[0];

    Tab_FA[6].input[0] = A[6];
    Tab_FA[6].input[1] = B[6];
    Tab_FA[6].input[2] = Tab_FA[5].calcul_cout()[0];
    S[6] = Tab_FA[6].calcul_S()[0];

    Tab_FA[7].input[0] = A[7];
    Tab_FA[7].input[1] = B[7];
    Tab_FA[7].input[2] = Tab_FA[6].calcul_cout()[0];
    S[7] = Tab_FA[7].calcul_S()[0];
    // S[8] = Tab_FA[7].calcul_cout()[0];
    return (S);
  }
};

float exhaustive(adder8 add, int table_index[8]) {

  //    std::ofstream results;
  //  results.open ("results_distributions.txt");

  std::bitset < 8 > A; //input A
  std::bitset < 8 > B; //input B
  std::bitset < 8 > S, Scor; // output

  int ka, kb, err, p, r;
  float MED, MRD, NMED, sum, sum_rel, k; //mean error
  int i0, i1, i2, i3, i4, i5, i6, i7, j, i;
  int out, tab[9];
  for (j = 0; j < 9; j++) {
    tab[j] = 0;
  }

  /*    i0 = 1;
      i1 = 1;
      i2 = 1;
      i3 = 1;
      i4 = 1;
      i5 = 1;
      i6 = 1;
      i7 = 1; */

  r = 0; //counter
  k = 0;
  sum = 0;
  sum_rel = 0;
  err = 0; //total number of errors by circuit k
  MED = 0;
  MRD = 0;
  NMED = 0;

  //affect the implementations
  /*  add.Tab_FA[0].appx=i0;
    add.Tab_FA[1].appx=i1;
    add.Tab_FA[2].appx=i2;
    add.Tab_FA[3].appx=i3;
    add.Tab_FA[4].appx=i4;
    add.Tab_FA[5].appx=i5;
    add.Tab_FA[6].appx=i6;
    add.Tab_FA[7].appx=i7;*/
  for (i = 0; i < 8; i++) {
    add.Tab_FA[i].appx = table_index[i];
  }

  for (ka = 0; ka < 128; ka++) { // all combinations of inputs{

    for (kb = 0; kb < 128; kb++) {
      A = ka;
      B = kb;
      r++;

      S = add.layout_add8(A, B); // layout_mult2(A,B);

      out = (int) S.to_ulong();
      sum += abs((ka + kb) - out);

      //results<<A.to_ulong() <<" + "<<B.to_ulong()<<"= "<<out<<"    "<<ka+kb<< "\n";
      /*if (ka+kb != 0){sum_rel+= abs(ka+kb-out)/(ka+kb);
      k++;}
      if(abs(ka+kb-out)!=0) //there is an error
      {
          err++;
          Scor=ka+kb;//correct output

          for(p=0;p<9;p++)
          {
              if(Scor[p]!=S[p])
              {
                  tab[p]++;
              }
          }
          //results<<"correct="<<ka*kb<<"   error="<<out[r]<< " \n";
          }*/
    }

  }
  MED = sum / (r + 1);

  return MED;
}

# define POPSIZE 100

const string GENES = "12356789abc";

int random_num(int start, int end) {
  int range = (end - start) + 1;
  int random_int = start + (rand() % range);
  return random_int;
}

char mutated_genes() {
  int len = GENES.size();
  int r = random_num(0, len - 1);
  return GENES[r];
}

string create_gnome() {
  int len = 8;
  string gnome = "";
  for (int i = 0; i < len; i++)
    gnome += mutated_genes();
  return gnome;
}

class Individual {
  public:
    string chromosome;
  float MED;
  Individual(string chromosome);
  Individual mate(Individual parent2);
  float cal_MED();
};

Individual::Individual(string chromosome) {
  this -> chromosome = chromosome;
  MED = cal_MED();
};

Individual Individual::mate(Individual par2) {
  string child_chromosome = "";

  int len = chromosome.size();
  for (int i = 0; i < len; i++) {
    float p = random_num(0, 100) / 100;

    if (p < 0.45)
      child_chromosome += chromosome[i];

    else if (p < 0.90)
      child_chromosome += par2.chromosome[i];

    else
      child_chromosome += mutated_genes();
  }

  return Individual(child_chromosome);
};

float Individual::cal_MED() {
  int len = 8;
  int i;
  float MED = 0;
  adder8 add;
  int table_index[8];
  for (i = 0; i < 8; i++) {
    table_index[i] = chromosome[i] - '0';
  }

  MED = (float) exhaustive(add, table_index);
  //	cout<<MED<<endl;

  return MED;
};

bool operator < (const Individual & ind1,
  const Individual & ind2) {
  return ind1.MED < ind2.MED;
}

int main() {
  srand((unsigned)(time(0)));

  vector < Individual > population;
  bool found = false;

  for (int i = 0; i < POPSIZE; i++) {
    string gnome = create_gnome();
    population.push_back(Individual(gnome));
  }

  while (!found) {
    sort(population.begin(), population.end());

    if (population[0].MED <= 0) //condition to break the loop
    {
      found = true;
      break;
    }

    vector < Individual > new_generation;

    int s = (10 * POPSIZE) / 100;
    for (int i = 0; i < s; i++)
      new_generation.push_back(population[i]);

    s = (90 * POPSIZE) / 100;
    for (int i = 0; i < s; i++) {
      int len = population.size();
      int r = random_num(0, 50);
      Individual parent1 = population[r];
      r = random_num(0, 50);
      Individual parent2 = population[r];
      Individual offspring = parent1.mate(parent2);
      new_generation.push_back(offspring);
    }
    population = new_generation;
    cout << "Configuration: " << population[0].chromosome << "\t";
    cout << "MED: " << population[0].MED << "\n";

  }
  cout << "Configuration: " << population[0].chromosome << "\t";
  cout << "MED: " << population[0].MED << "\n";
}
