#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>

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
    //d[0]=input[2];
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
    if (appx == 1) return ((a & b) ^ (d ^ (c_in))); //aproximate adder 1
    else if (appx == 2) return ((a & b) ^ d) | (c_in); // appxmt adder 2
    else if (appx == 3) return (~(((a & b) & d) | (c_in & ((a & b) ^ (d))))); // appxmt adder 3
    else if (appx == 4) return ((a & b) ^ (d ^ (c_in))); // appxmt adder 4
    else if (appx == 5) return (c_in & (~((a & b) ^ d))); // appxmt adder M1
    else if (appx == 6) return (~c_in & ((a & b) ^ d)) | (~(a & b) & ~d); // appxmt adder M2
    else if (appx == 7) return (~d & (~(a & b) | ((a & b) & ~c_in))); // appxmt adder M3
    else if (appx == 8) return (c_in & (d | (~(a & b) & ~d))); // appxmt adder M4
    else if (appx == 9) return (d); // appxmt adder M5
    else if (appx == 'a') return (c_in); // appxmt adder AXA1
    else if (appx == 'b') return (~((a & b) ^ d)); // appxmt adder AXA2

    else

      return (c_in & ((a & b) ^ d)) | ((a & b) & d); // exact adder

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

    if (appx == 1) return (c_in); //appx FA 1
    else if (appx == 2) return (((a & b) & d) | (c_in & ((a & b) ^ (d)))); // appxmt FA 2
    else if (appx == 3) return (((a & b) & d) | (c_in & ((a & b) ^ (d)))); // appxmt FA 3
    else if (appx == 4) return (((a & b) & d) | (c_in & ((a & b) ^ (d)))); // exact FA
    else if (appx == 5) return (c_in & ((a & b) ^ d)) | (d & ((a & b) | (~(a & b) & ~c_in))); // appxmt FA M1
    else if (appx == 6) return (c_in & ((a & b) ^ d)) | ((a & b) & d); // appxmt FA M2
    else if (appx == 7) return (d | (((a & b) & ~d) & c_in)); // appxmt FA M3
    else if (appx == 8) return (a & b); // appxmt FA M4
    else if (appx == 9) return ((d & ~c_in) | ((a & b) & ~(d ^ c_in))); // appxmt FA AXA1
    else if (appx == 'a') return (~((((a & b) ^ d) & c_in) | (~(a & b) & ~d))); // appxmt FA AXA1
    else if (appx == 'b') return ((((a & b) ^ d) & c_in) | ((a & b) & d)); // appxmt FA AXA2

    else

      return (c_in & ((a & b) ^ d)) | ((a & b) & d); // appxmt FA AXA3

  }
};
class multiplier_layout8 {
  public:
    And_component Tab_And[8];
  full_adderBlock Tab_FA[56];
  std::bitset < 16 > S; // output

  multiplier_layout8() {

    And_component(); // what the hell ?????
    //full_adderBlock();

  }

  std::bitset < 16 > layout_mult8(std::bitset < 8 > A, std::bitset < 8 > B) {

    //link the components

    Tab_And[0].a[0] = A[0];
    Tab_And[0].b[0] = B[0];

    Tab_And[1].a[0] = A[0];
    Tab_And[1].b[0] = B[1];

    Tab_And[2].a[0] = A[0];
    Tab_And[2].b[0] = B[2];

    Tab_And[3].a[0] = A[0];
    Tab_And[3].b[0] = B[3];

    Tab_And[4].a[0] = A[0];
    Tab_And[4].b[0] = B[4];

    Tab_And[5].a[0] = A[0];
    Tab_And[5].b[0] = B[5];

    Tab_And[6].a[0] = A[0];
    Tab_And[6].b[0] = B[6];

    Tab_And[7].a[0] = A[0];
    Tab_And[7].b[0] = B[7];

    S[0] = Tab_And[0].And_sfunction()[0];

    //-----------------b second line

    Tab_FA[0].input[0] = A[1];
    Tab_FA[0].input[1] = B[0];
    Tab_FA[0].input[2] = Tab_And[1].And_sfunction()[0];
    Tab_FA[0].input[3] = 0;

    Tab_FA[1].input[0] = A[1];
    Tab_FA[1].input[1] = B[1];
    Tab_FA[1].input[2] = Tab_And[2].And_sfunction()[0];
    Tab_FA[1].input[3] = Tab_FA[0].calcul_cout()[0];

    Tab_FA[2].input[0] = A[1];
    Tab_FA[2].input[1] = B[2];
    Tab_FA[2].input[2] = Tab_And[3].And_sfunction()[0];
    Tab_FA[2].input[3] = Tab_FA[1].calcul_cout()[0];

    Tab_FA[3].input[0] = A[1];
    Tab_FA[3].input[1] = B[3];
    Tab_FA[3].input[2] = Tab_And[4].And_sfunction()[0];
    Tab_FA[3].input[3] = Tab_FA[2].calcul_cout()[0];

    Tab_FA[4].input[0] = A[1];
    Tab_FA[4].input[1] = B[4];
    Tab_FA[4].input[2] = Tab_And[5].And_sfunction()[0];
    Tab_FA[4].input[3] = Tab_FA[3].calcul_cout()[0];

    Tab_FA[5].input[0] = A[1];
    Tab_FA[5].input[1] = B[5];
    Tab_FA[5].input[2] = Tab_And[6].And_sfunction()[0];
    Tab_FA[5].input[3] = Tab_FA[4].calcul_cout()[0];

    Tab_FA[6].input[0] = A[1];
    Tab_FA[6].input[1] = B[6];
    Tab_FA[6].input[2] = Tab_And[7].And_sfunction()[0];
    Tab_FA[6].input[3] = Tab_FA[5].calcul_cout()[0];

    Tab_FA[7].input[0] = A[1];
    Tab_FA[7].input[1] = B[7];
    Tab_FA[7].input[2] = 0;
    Tab_FA[7].input[3] = Tab_FA[6].calcul_cout()[0];

    S[1] = Tab_FA[0].calcul_S()[0];

    //-----------------b line 3

    Tab_FA[8].input[0] = A[2];
    Tab_FA[8].input[1] = B[0];
    Tab_FA[8].input[2] = Tab_FA[1].calcul_S()[0];
    Tab_FA[8].input[3] = 0;

    Tab_FA[9].input[0] = A[2];
    Tab_FA[9].input[1] = B[1];
    Tab_FA[9].input[2] = Tab_FA[2].calcul_S()[0];
    Tab_FA[9].input[3] = Tab_FA[8].calcul_cout()[0];

    Tab_FA[10].input[0] = A[2];
    Tab_FA[10].input[1] = B[2];
    Tab_FA[10].input[2] = Tab_FA[3].calcul_S()[0];
    Tab_FA[10].input[3] = Tab_FA[9].calcul_cout()[0];

    Tab_FA[11].input[0] = A[2];
    Tab_FA[11].input[1] = B[3];
    Tab_FA[11].input[2] = Tab_FA[4].calcul_S()[0];
    Tab_FA[11].input[3] = Tab_FA[10].calcul_cout()[0];

    Tab_FA[12].input[0] = A[2];
    Tab_FA[12].input[1] = B[4];
    Tab_FA[12].input[2] = Tab_FA[5].calcul_S()[0];
    Tab_FA[12].input[3] = Tab_FA[11].calcul_cout()[0];

    Tab_FA[13].input[0] = A[2];
    Tab_FA[13].input[1] = B[5];
    Tab_FA[13].input[2] = Tab_FA[6].calcul_S()[0];
    Tab_FA[13].input[3] = Tab_FA[12].calcul_cout()[0];

    Tab_FA[14].input[0] = A[2];
    Tab_FA[14].input[1] = B[6];
    Tab_FA[14].input[2] = Tab_FA[7].calcul_S()[0];
    Tab_FA[14].input[3] = Tab_FA[13].calcul_cout()[0];

    Tab_FA[15].input[0] = A[2];
    Tab_FA[15].input[1] = B[7];
    Tab_FA[15].input[2] = Tab_FA[7].calcul_cout()[0];
    Tab_FA[15].input[3] = Tab_FA[14].calcul_cout()[0];

    S[2] = Tab_FA[8].calcul_S()[0];

    //----------------------line 4

    Tab_FA[16].input[0] = A[3];
    Tab_FA[16].input[1] = B[0];
    Tab_FA[16].input[2] = Tab_FA[9].calcul_S()[0];
    Tab_FA[16].input[3] = 0;

    Tab_FA[17].input[0] = A[3];
    Tab_FA[17].input[1] = B[1];
    Tab_FA[17].input[2] = Tab_FA[10].calcul_S()[0];
    Tab_FA[17].input[3] = Tab_FA[16].calcul_cout()[0];

    Tab_FA[18].input[0] = A[3];
    Tab_FA[18].input[1] = B[2];
    Tab_FA[18].input[2] = Tab_FA[11].calcul_S()[0];
    Tab_FA[18].input[3] = Tab_FA[17].calcul_cout()[0];

    Tab_FA[19].input[0] = A[3];
    Tab_FA[19].input[1] = B[3];
    Tab_FA[19].input[2] = Tab_FA[12].calcul_S()[0];
    Tab_FA[19].input[3] = Tab_FA[18].calcul_cout()[0];

    Tab_FA[20].input[0] = A[3];
    Tab_FA[20].input[1] = B[4];
    Tab_FA[20].input[2] = Tab_FA[13].calcul_S()[0];
    Tab_FA[20].input[3] = Tab_FA[19].calcul_cout()[0];

    Tab_FA[21].input[0] = A[3];
    Tab_FA[21].input[1] = B[5];
    Tab_FA[21].input[2] = Tab_FA[14].calcul_S()[0];
    Tab_FA[21].input[3] = Tab_FA[20].calcul_cout()[0];

    Tab_FA[22].input[0] = A[3];
    Tab_FA[22].input[1] = B[6];
    Tab_FA[22].input[2] = Tab_FA[15].calcul_S()[0];
    Tab_FA[22].input[3] = Tab_FA[21].calcul_cout()[0];

    Tab_FA[23].input[0] = A[3];
    Tab_FA[23].input[1] = B[7];
    Tab_FA[23].input[2] = Tab_FA[15].calcul_cout()[0];
    Tab_FA[23].input[3] = Tab_FA[22].calcul_cout()[0];

    S[3] = Tab_FA[16].calcul_S()[0];

    //------ line 5

    Tab_FA[24].input[0] = A[4];
    Tab_FA[24].input[1] = B[0];
    Tab_FA[24].input[2] = Tab_FA[17].calcul_S()[0];
    Tab_FA[24].input[3] = 0;

    Tab_FA[25].input[0] = A[4];
    Tab_FA[25].input[1] = B[1];
    Tab_FA[25].input[2] = Tab_FA[18].calcul_S()[0];
    Tab_FA[25].input[3] = Tab_FA[24].calcul_cout()[0];

    Tab_FA[26].input[0] = A[4];
    Tab_FA[26].input[1] = B[2];
    Tab_FA[26].input[2] = Tab_FA[19].calcul_S()[0];
    Tab_FA[26].input[3] = Tab_FA[25].calcul_cout()[0];

    Tab_FA[27].input[0] = A[4];
    Tab_FA[27].input[1] = B[3];
    Tab_FA[27].input[2] = Tab_FA[20].calcul_S()[0];
    Tab_FA[27].input[3] = Tab_FA[26].calcul_cout()[0];

    Tab_FA[28].input[0] = A[4];
    Tab_FA[28].input[1] = B[4];
    Tab_FA[28].input[2] = Tab_FA[21].calcul_S()[0];
    Tab_FA[28].input[3] = Tab_FA[27].calcul_cout()[0];

    Tab_FA[29].input[0] = A[4];
    Tab_FA[29].input[1] = B[5];
    Tab_FA[29].input[2] = Tab_FA[22].calcul_S()[0];
    Tab_FA[29].input[3] = Tab_FA[28].calcul_cout()[0];

    Tab_FA[30].input[0] = A[4];
    Tab_FA[30].input[1] = B[6];
    Tab_FA[30].input[2] = Tab_FA[23].calcul_S()[0];
    Tab_FA[30].input[3] = Tab_FA[29].calcul_cout()[0];

    Tab_FA[31].input[0] = A[4];
    Tab_FA[31].input[1] = B[7];
    Tab_FA[31].input[2] = Tab_FA[23].calcul_cout()[0];
    Tab_FA[31].input[3] = Tab_FA[30].calcul_cout()[0];

    S[4] = Tab_FA[24].calcul_S()[0];

    /////////////////////////////////////////------- //------ line 6

    Tab_FA[32].input[0] = A[5];
    Tab_FA[32].input[1] = B[0];
    Tab_FA[32].input[2] = Tab_FA[25].calcul_S()[0];
    Tab_FA[32].input[3] = 0;

    Tab_FA[33].input[0] = A[5];
    Tab_FA[33].input[1] = B[1];
    Tab_FA[33].input[2] = Tab_FA[26].calcul_S()[0];
    Tab_FA[33].input[3] = Tab_FA[32].calcul_cout()[0];

    Tab_FA[34].input[0] = A[5];
    Tab_FA[34].input[1] = B[2];
    Tab_FA[34].input[2] = Tab_FA[27].calcul_S()[0];
    Tab_FA[34].input[3] = Tab_FA[33].calcul_cout()[0];

    Tab_FA[35].input[0] = A[5];
    Tab_FA[35].input[1] = B[3];
    Tab_FA[35].input[2] = Tab_FA[28].calcul_S()[0];
    Tab_FA[35].input[3] = Tab_FA[34].calcul_cout()[0];

    Tab_FA[36].input[0] = A[5];
    Tab_FA[36].input[1] = B[4];
    Tab_FA[36].input[2] = Tab_FA[29].calcul_S()[0];
    Tab_FA[36].input[3] = Tab_FA[35].calcul_cout()[0];

    Tab_FA[37].input[0] = A[5];
    Tab_FA[37].input[1] = B[5];
    Tab_FA[37].input[2] = Tab_FA[30].calcul_S()[0];
    Tab_FA[37].input[3] = Tab_FA[36].calcul_cout()[0];

    Tab_FA[38].input[0] = A[5];
    Tab_FA[38].input[1] = B[6];
    Tab_FA[38].input[2] = Tab_FA[31].calcul_S()[0];
    Tab_FA[38].input[3] = Tab_FA[37].calcul_cout()[0];

    Tab_FA[39].input[0] = A[5];
    Tab_FA[39].input[1] = B[7];
    Tab_FA[39].input[2] = Tab_FA[31].calcul_cout()[0];
    Tab_FA[39].input[3] = Tab_FA[38].calcul_cout()[0];

    S[5] = Tab_FA[32].calcul_S()[0];

    /////////////////////////////////////////------- //------ line 7

    Tab_FA[40].input[0] = A[6];
    Tab_FA[40].input[1] = B[0];
    Tab_FA[40].input[2] = Tab_FA[33].calcul_S()[0];
    Tab_FA[40].input[3] = 0;

    Tab_FA[41].input[0] = A[6];
    Tab_FA[41].input[1] = B[1];
    Tab_FA[41].input[2] = Tab_FA[34].calcul_S()[0];
    Tab_FA[41].input[3] = Tab_FA[40].calcul_cout()[0];

    Tab_FA[42].input[0] = A[6];
    Tab_FA[42].input[1] = B[2];
    Tab_FA[42].input[2] = Tab_FA[35].calcul_S()[0];
    Tab_FA[42].input[3] = Tab_FA[41].calcul_cout()[0];

    Tab_FA[43].input[0] = A[6];
    Tab_FA[43].input[1] = B[3];
    Tab_FA[43].input[2] = Tab_FA[36].calcul_S()[0];
    Tab_FA[43].input[3] = Tab_FA[42].calcul_cout()[0];

    Tab_FA[44].input[0] = A[6];
    Tab_FA[44].input[1] = B[4];
    Tab_FA[44].input[2] = Tab_FA[37].calcul_S()[0];
    Tab_FA[44].input[3] = Tab_FA[43].calcul_cout()[0];

    Tab_FA[45].input[0] = A[6];
    Tab_FA[45].input[1] = B[5];
    Tab_FA[45].input[2] = Tab_FA[38].calcul_S()[0];
    Tab_FA[45].input[3] = Tab_FA[44].calcul_cout()[0];

    Tab_FA[46].input[0] = A[6];
    Tab_FA[46].input[1] = B[6];
    Tab_FA[46].input[2] = Tab_FA[39].calcul_S()[0];
    Tab_FA[46].input[3] = Tab_FA[45].calcul_cout()[0];

    Tab_FA[47].input[0] = A[6];
    Tab_FA[47].input[1] = B[7];
    Tab_FA[47].input[2] = Tab_FA[39].calcul_cout()[0];
    Tab_FA[47].input[3] = Tab_FA[46].calcul_cout()[0];

    S[6] = Tab_FA[40].calcul_S()[0];

    /////////////////////////////////////////------- //------ line 8

    Tab_FA[48].input[0] = A[7];
    Tab_FA[48].input[1] = B[0];
    Tab_FA[48].input[2] = Tab_FA[41].calcul_S()[0];
    Tab_FA[48].input[3] = 0;

    Tab_FA[49].input[0] = A[7];
    Tab_FA[49].input[1] = B[1];
    Tab_FA[49].input[2] = Tab_FA[42].calcul_S()[0];
    Tab_FA[49].input[3] = Tab_FA[48].calcul_cout()[0];

    Tab_FA[50].input[0] = A[7];
    Tab_FA[50].input[1] = B[2];
    Tab_FA[50].input[2] = Tab_FA[43].calcul_S()[0];
    Tab_FA[50].input[3] = Tab_FA[49].calcul_cout()[0];

    Tab_FA[51].input[0] = A[7];
    Tab_FA[51].input[1] = B[3];
    Tab_FA[51].input[2] = Tab_FA[44].calcul_S()[0];
    Tab_FA[51].input[3] = Tab_FA[50].calcul_cout()[0];

    Tab_FA[52].input[0] = A[7];
    Tab_FA[52].input[1] = B[4];
    Tab_FA[52].input[2] = Tab_FA[45].calcul_S()[0];
    Tab_FA[52].input[3] = Tab_FA[51].calcul_cout()[0];

    Tab_FA[53].input[0] = A[7];
    Tab_FA[53].input[1] = B[5];
    Tab_FA[53].input[2] = Tab_FA[46].calcul_S()[0];
    Tab_FA[53].input[3] = Tab_FA[52].calcul_cout()[0];

    Tab_FA[54].input[0] = A[7];
    Tab_FA[54].input[1] = B[6];
    Tab_FA[54].input[2] = Tab_FA[47].calcul_S()[0];
    Tab_FA[54].input[3] = Tab_FA[53].calcul_cout()[0];

    Tab_FA[55].input[0] = A[7];
    Tab_FA[55].input[1] = B[7];
    Tab_FA[55].input[2] = Tab_FA[47].calcul_cout()[0];
    Tab_FA[55].input[3] = Tab_FA[54].calcul_cout()[0];

    S[7] = Tab_FA[48].calcul_S()[0];
    S[8] = Tab_FA[49].calcul_S()[0];
    S[9] = Tab_FA[50].calcul_S()[0];
    S[10] = Tab_FA[51].calcul_S()[0];
    S[11] = Tab_FA[52].calcul_S()[0];
    S[12] = Tab_FA[53].calcul_S()[0];
    S[13] = Tab_FA[54].calcul_S()[0];
    S[14] = Tab_FA[55].calcul_S()[0];
    S[15] = Tab_FA[55].calcul_cout()[0];

    return (S);
  }
};

//
float exhaustive(multiplier_layout8 multiplier, int table_index[56]) {

  std::bitset < 16 > S;
  unsigned char ka, kb;
  int i, j;
  float sum, err, sum_MRE;
  float MED, r, rr, MRE, Res; //mean error
  float out;

  r = 0; //counter
  sum = 0;
  sum_MRE = 0;
  Res = 0;
  rr = 0;
  err = 0; //total number of errors by circuit k

  //affect the implementations
  for (i = 0; i < 56; i++) {
    multiplier.Tab_FA[i].appx = table_index[i];
  }

  for (ka = 0; ka < 255; ka++) // all combinations of inputs

  {

    for (kb = 0; kb < 255; kb++) {

      //  A=ka;
      //   B=kb;
      r++;

      S = multiplier.layout_mult8(ka, kb); // layout_mult8(A,B);
      out = (float) S.to_ulong();
      sum += abs(ka * kb - out);
      if ((ka * kb) != 0) {
        Res = (abs(ka * kb - out));
        Res /= (ka * kb);
        sum_MRE += Res;
        rr++;
      }
    }
  }
  MED = sum / (r + 1); //mean error
  //MRE = sum_MRE/(rr+1);   //mean relative error
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
  int len = 56;
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
  int len = 56;
  int i;
  float MED = 0;
  multiplier_layout8 multiplier;
  int table_index[56];
  for (i = 0; i < 56; i++) {
    table_index[i] = chromosome[i] - '0';
  }

  MED = (float) exhaustive(multiplier, table_index);
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
