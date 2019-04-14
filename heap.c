#include <iostream>
#include <vector>
#include <assert.h>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <cmath>        // std::abs
#include <iomanip>
#include <string>
#include<bits/stdc++.h>  //conv
//#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <cstdlib>


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
    if (appx == 1) return ((a & b) ^ (d ^ (c_in))); //aproximate adder 1
    else if (appx == 2) return ((a & b) ^ d) | (c_in); // appxmt adder 2
    else if (appx == 3) return (~(((a & b) & d) | (c_in & ((a & b) ^ (d))))); // appxmt adder 3
    else if (appx == 4) return ((a & b) ^ (d ^ (c_in))); // appxmt adder 4
    else if (appx == 5) return (c_in &(~((a & b)^ d))); // appxmt adder M1
    else if (appx == 6) return (~c_in &((a & b)^ d))|(~(a & b) & ~d); // appxmt adder M2
    else if (appx == 7) return (~d&(~(a & b)| ((a & b)&~c_in))); // appxmt adder M3
    else if (appx == 8) return (c_in&(d| (~(a & b)&~d))); // appxmt adder M4
    else if (appx == 9) return (d); // appxmt adder M5
    else if (appx == 'a') return (c_in); // appxmt adder AXA1
    else if (appx == 'b') return (~((a & b)^ d)); // appxmt adder AXA2

    else

      return (c_in &((a & b)^ d))|((a & b) & d); // exact adder

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
    else if (appx == 4) return (((a & b) & d) | (c_in & ((a & b) ^ (d)))); // exact adder
    else if (appx == 5) return (c_in &((a & b)^ d))|(d&((a & b)| (~(a & b)&~c_in))); // appxmt adder M1
    else if (appx == 6) return (c_in &((a & b)^ d))|((a & b) & d); // appxmt adder M2
    else if (appx == 7) return  (d|(((a & b) & ~d)&c_in)); // appxmt adder M3
    else if (appx == 8) return  (a & b); // appxmt adder M4
    else if (appx == 9) return  ((d & ~c_in) | ((a & b) & ~(d ^ c_in))); // appxmt adder AXA1
    else if (appx == 'a') return  (~((((a & b) ^ d) & c_in) | (~(a & b) & ~d))); // appxmt adder AXA1
    else if (appx == 'b') return  ( (((a & b) ^ d) & c_in) |((a & b) & d)); // appxmt adder AXA2

    else

      return (c_in &((a & b)^ d))|((a & b) & d); // appxmt adder AXA3

  }
};


class multiplier_layout8 {
  public:
    And_component Tab_And[8];
  full_adderBlock Tab_FA[56];
  std::bitset < 16 > S; // output

  multiplier_layout8() {

    And_component();

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
class adder8 {
  public:

    full_adder Tab_FA[8];
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
    S[8] = Tab_FA[7].calcul_cout()[0];
    return (S);
  }
};

class adder {
  public:

    //And_component Tab_And [2];
    full_adder Tab_FA2[48];
  std::bitset < 48 > S; // output

  std::bitset < 48 > layout_add48(std::bitset < 48 > A, std::bitset < 48 > B) {
    Tab_FA2[0].input[0] = A[0];
    Tab_FA2[0].input[1] = B[0];
    Tab_FA2[0].input[2] = 0;
    S[0] = Tab_FA2[0].calcul_S()[0];
    Tab_FA2[1].input[0] = A[1];
    Tab_FA2[1].input[1] = B[1];
    Tab_FA2[1].input[2] = Tab_FA2[0].calcul_cout()[0];
    S[1] = Tab_FA2[1].calcul_S()[0];
    Tab_FA2[2].input[0] = A[2];
    Tab_FA2[2].input[1] = B[2];
    Tab_FA2[2].input[2] = Tab_FA2[1].calcul_cout()[0];
    S[2] = Tab_FA2[2].calcul_S()[0];
    Tab_FA2[3].input[0] = A[3];
    Tab_FA2[3].input[1] = B[3];
    Tab_FA2[3].input[2] = Tab_FA2[2].calcul_cout()[0];
    S[3] = Tab_FA2[3].calcul_S()[0];

    Tab_FA2[4].input[0] = A[4];
    Tab_FA2[4].input[1] = B[4];
    Tab_FA2[4].input[2] = Tab_FA2[3].calcul_cout()[0];
    S[4] = Tab_FA2[4].calcul_S()[0];

    Tab_FA2[5].input[0] = A[5];
    Tab_FA2[5].input[1] = B[5];
    Tab_FA2[5].input[2] = Tab_FA2[4].calcul_cout()[0];
    S[5] = Tab_FA2[5].calcul_S()[0];

    Tab_FA2[6].input[0] = A[6];
    Tab_FA2[6].input[1] = B[6];
    Tab_FA2[6].input[2] = Tab_FA2[5].calcul_cout()[0];
    S[6] = Tab_FA2[6].calcul_S()[0];

    Tab_FA2[7].input[0] = A[7];
    Tab_FA2[7].input[1] = B[7];
    Tab_FA2[7].input[2] = Tab_FA2[6].calcul_cout()[0];
    S[7] = Tab_FA2[7].calcul_S()[0];

    Tab_FA2[8].input[0] = A[8];
    Tab_FA2[8].input[1] = B[8];
    Tab_FA2[8].input[2] = Tab_FA2[7].calcul_cout()[0];
    S[8] = Tab_FA2[8].calcul_S()[0];

    Tab_FA2[9].input[0] = A[9];
    Tab_FA2[9].input[1] = B[9];
    Tab_FA2[9].input[2] = Tab_FA2[8].calcul_cout()[0];
    S[9] = Tab_FA2[9].calcul_S()[0];

    Tab_FA2[10].input[0] = A[10];
    Tab_FA2[10].input[1] = B[10];
    Tab_FA2[10].input[2] = Tab_FA2[9].calcul_cout()[0];
    S[10] = Tab_FA2[10].calcul_S()[0];

    Tab_FA2[11].input[0] = A[11];
    Tab_FA2[11].input[1] = B[11];
    Tab_FA2[11].input[2] = Tab_FA2[10].calcul_cout()[0];
    S[11] = Tab_FA2[11].calcul_S()[0];

    Tab_FA2[12].input[0] = A[12];
    Tab_FA2[12].input[1] = B[12];
    Tab_FA2[12].input[2] = Tab_FA2[11].calcul_cout()[0];
    S[12] = Tab_FA2[12].calcul_S()[0];

    Tab_FA2[13].input[0] = A[13];
    Tab_FA2[13].input[1] = B[13];
    Tab_FA2[13].input[2] = Tab_FA2[12].calcul_cout()[0];
    S[13] = Tab_FA2[13].calcul_S()[0];

    Tab_FA2[14].input[0] = A[14];
    Tab_FA2[14].input[1] = B[14];
    Tab_FA2[14].input[2] = Tab_FA2[13].calcul_cout()[0];
    S[14] = Tab_FA2[14].calcul_S()[0];

    Tab_FA2[15].input[0] = A[15];
    Tab_FA2[15].input[1] = B[15];
    Tab_FA2[15].input[2] = Tab_FA2[14].calcul_cout()[0];
    S[15] = Tab_FA2[15].calcul_S()[0];

    Tab_FA2[16].input[0] = A[16];
    Tab_FA2[16].input[1] = B[16];
    Tab_FA2[16].input[2] = Tab_FA2[15].calcul_cout()[0];
    S[16] = Tab_FA2[16].calcul_S()[0];

    Tab_FA2[17].input[0] = A[17];
    Tab_FA2[17].input[1] = B[17];
    Tab_FA2[17].input[2] = Tab_FA2[16].calcul_cout()[0];
    S[17] = Tab_FA2[17].calcul_S()[0];

    Tab_FA2[18].input[0] = A[18];
    Tab_FA2[18].input[1] = B[18];
    Tab_FA2[18].input[2] = Tab_FA2[17].calcul_cout()[0];
    S[18] = Tab_FA2[18].calcul_S()[0];

    Tab_FA2[19].input[0] = A[19];
    Tab_FA2[19].input[1] = B[19];
    Tab_FA2[19].input[2] = Tab_FA2[18].calcul_cout()[0];
    S[19] = Tab_FA2[19].calcul_S()[0];

    Tab_FA2[20].input[0] = A[20];
    Tab_FA2[20].input[1] = B[20];
    Tab_FA2[20].input[2] = Tab_FA2[19].calcul_cout()[0];
    S[20] = Tab_FA2[20].calcul_S()[0];

    Tab_FA2[21].input[0] = A[21];
    Tab_FA2[21].input[1] = B[21];
    Tab_FA2[21].input[2] = Tab_FA2[20].calcul_cout()[0];
    S[21] = Tab_FA2[21].calcul_S()[0];

    Tab_FA2[22].input[0] = A[22];
    Tab_FA2[22].input[1] = B[22];
    Tab_FA2[22].input[2] = Tab_FA2[21].calcul_cout()[0];
    S[22] = Tab_FA2[22].calcul_S()[0];

    Tab_FA2[23].input[0] = A[23];
    Tab_FA2[23].input[1] = B[23];
    Tab_FA2[23].input[2] = Tab_FA2[22].calcul_cout()[0];
    S[23] = Tab_FA2[23].calcul_S()[0];

    Tab_FA2[24].input[0] = A[24];
    Tab_FA2[24].input[1] = B[24];
    Tab_FA2[24].input[2] = Tab_FA2[23].calcul_cout()[0];
    S[24] = Tab_FA2[24].calcul_S()[0];

    Tab_FA2[25].input[0] = A[25];
    Tab_FA2[25].input[1] = B[25];
    Tab_FA2[25].input[2] = Tab_FA2[24].calcul_cout()[0];
    S[25] = Tab_FA2[25].calcul_S()[0];

    Tab_FA2[26].input[0] = A[26];
    Tab_FA2[26].input[1] = B[26];
    Tab_FA2[26].input[2] = Tab_FA2[25].calcul_cout()[0];
    S[26] = Tab_FA2[26].calcul_S()[0];

    Tab_FA2[27].input[0] = A[27];
    Tab_FA2[27].input[1] = B[27];
    Tab_FA2[27].input[2] = Tab_FA2[26].calcul_cout()[0];
    S[27] = Tab_FA2[27].calcul_S()[0];

    Tab_FA2[28].input[0] = A[28];
    Tab_FA2[28].input[1] = B[28];
    Tab_FA2[28].input[2] = Tab_FA2[27].calcul_cout()[0];
    S[28] = Tab_FA2[28].calcul_S()[0];

    Tab_FA2[29].input[0] = A[29];
    Tab_FA2[29].input[1] = B[29];
    Tab_FA2[29].input[2] = Tab_FA2[28].calcul_cout()[0];
    S[29] = Tab_FA2[29].calcul_S()[0];

    Tab_FA2[30].input[0] = A[30];
    Tab_FA2[30].input[1] = B[30];
    Tab_FA2[30].input[2] = Tab_FA2[29].calcul_cout()[0];
    S[30] = Tab_FA2[30].calcul_S()[0];

    Tab_FA2[31].input[0] = A[31];
    Tab_FA2[31].input[1] = B[31];
    Tab_FA2[31].input[2] = Tab_FA2[30].calcul_cout()[0];
    S[31] = Tab_FA2[31].calcul_S()[0];

    Tab_FA2[32].input[0] = A[32];
    Tab_FA2[32].input[1] = B[32];
    Tab_FA2[32].input[2] = Tab_FA2[31].calcul_cout()[0];
    S[32] = Tab_FA2[32].calcul_S()[0];

    Tab_FA2[33].input[0] = A[33];
    Tab_FA2[33].input[1] = B[33];
    Tab_FA2[33].input[2] = Tab_FA2[32].calcul_cout()[0];
    S[33] = Tab_FA2[33].calcul_S()[0];

    Tab_FA2[34].input[0] = A[34];
    Tab_FA2[34].input[1] = B[34];
    Tab_FA2[34].input[2] = Tab_FA2[33].calcul_cout()[0];
    S[34] = Tab_FA2[34].calcul_S()[0];

    Tab_FA2[35].input[0] = A[35];
    Tab_FA2[35].input[1] = B[35];
    Tab_FA2[35].input[2] = Tab_FA2[34].calcul_cout()[0];
    S[35] = Tab_FA2[35].calcul_S()[0];

    Tab_FA2[36].input[0] = A[36];
    Tab_FA2[36].input[1] = B[36];
    Tab_FA2[36].input[2] = Tab_FA2[35].calcul_cout()[0];
    S[36] = Tab_FA2[36].calcul_S()[0];

    Tab_FA2[37].input[0] = A[37];
    Tab_FA2[37].input[1] = B[37];
    Tab_FA2[37].input[2] = Tab_FA2[36].calcul_cout()[0];
    S[37] = Tab_FA2[37].calcul_S()[0];

    Tab_FA2[38].input[0] = A[38];
    Tab_FA2[38].input[1] = B[38];
    Tab_FA2[38].input[2] = Tab_FA2[37].calcul_cout()[0];
    S[38] = Tab_FA2[38].calcul_S()[0];

    Tab_FA2[39].input[0] = A[39];
    Tab_FA2[39].input[1] = B[39];
    Tab_FA2[39].input[2] = Tab_FA2[38].calcul_cout()[0];
    S[39] = Tab_FA2[39].calcul_S()[0];

    Tab_FA2[40].input[0] = A[40];
    Tab_FA2[40].input[1] = B[40];
    Tab_FA2[40].input[2] = Tab_FA2[39].calcul_cout()[0];
    S[40] = Tab_FA2[40].calcul_S()[0];

    Tab_FA2[41].input[0] = A[41];
    Tab_FA2[41].input[1] = B[41];
    Tab_FA2[41].input[2] = Tab_FA2[40].calcul_cout()[0];
    S[41] = Tab_FA2[41].calcul_S()[0];

    Tab_FA2[42].input[0] = A[42];
    Tab_FA2[42].input[1] = B[42];
    Tab_FA2[42].input[2] = Tab_FA2[41].calcul_cout()[0];
    S[42] = Tab_FA2[42].calcul_S()[0];

    Tab_FA2[43].input[0] = A[43];
    Tab_FA2[43].input[1] = B[43];
    Tab_FA2[43].input[2] = Tab_FA2[42].calcul_cout()[0];
    S[43] = Tab_FA2[43].calcul_S()[0];

    Tab_FA2[44].input[0] = A[44];
    Tab_FA2[44].input[1] = B[44];
    Tab_FA2[44].input[2] = Tab_FA2[43].calcul_cout()[0];
    S[44] = Tab_FA2[44].calcul_S()[0];

    Tab_FA2[45].input[0] = A[45];
    Tab_FA2[45].input[1] = B[45];
    Tab_FA2[45].input[2] = Tab_FA2[44].calcul_cout()[0];
    S[45] = Tab_FA2[45].calcul_S()[0];

    Tab_FA2[46].input[0] = A[46];
    Tab_FA2[46].input[1] = B[46];
    Tab_FA2[46].input[2] = Tab_FA2[45].calcul_cout()[0];
    S[46] = Tab_FA2[46].calcul_S()[0];

    Tab_FA2[47].input[0] = A[47];
    Tab_FA2[47].input[1] = B[47];
    Tab_FA2[47].input[2] = Tab_FA2[46].calcul_cout()[0];
    S[47] = Tab_FA2[47].calcul_S()[0];

    return (S);
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
    if (appx == 1) return (a ^ (b ^ (c_in))); //aproximate adder 1
    else if (appx == 2) return (a ^ b) | (c_in); // appxmt adder 2
    else if (appx == 3) return (~((a & b) | (c_in & (a^ b)))); // appxmt adder 3

    else

      return (a ^ (b ^ (c_in))); // exact adder

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

    else

      return ((a & b) | (c_in & (a ^ b)));

  }
};

class adder8bits {
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
std::bitset<8> Add8(std::bitset<8> A,std::bitset<8> B){

          //    std::ofstream results;
            //  results.open ("results_distributions.txt");

              adder8bits add;
              int x=1;
             //   std::bitset<8> A;//input A
    	//	std::bitset<8> B;//input B
    		std::bitset<8> S,Scor; // output
                int i0, i1,i2,i3,i4,i5,i6,i7,j,i;


                i0 = 4;
                i1 = 4;
                i2 = 4;
                i3 = 4;
                i4 = 4;
                i5 = 4;
                i6 = 4;
                i7 = 4;

  //affect the implementations
              add.Tab_FA[0].appx=i0;
              add.Tab_FA[1].appx=i1;
              add.Tab_FA[2].appx=i2;
              add.Tab_FA[3].appx=i3;
              add.Tab_FA[4].appx=i4;
              add.Tab_FA[5].appx=i5;
              add.Tab_FA[6].appx=i6;
              add.Tab_FA[7].appx=i7;



    /*  for (i=0;i<8;i++)
         {
              add.Tab_FA[i].appx=x;
         } */

S= add.layout_add8(A,B);// layout_mult2(A,B);


return S;
}



std::bitset < 16 > multiply8x8(std::bitset < 8 > A, std::bitset < 8 > B, int x) {
  multiplier_layout8 multiplier;
  std::bitset < 16 > S;
  int SS, i, j;
  int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18, i19, i20, i21, i22, i23, i24, i25, i26, i27, i28, i29, i30, i31, i32, i33, i34, i35, i36, i37, i38, i39, i40, i41, i42, i43, i44, i45, i46, i47, i48, i49, i50, i51, i52, i53, i54, i55;

  unsigned short table_index[56];
  if (x == 'h') {
                        i0=3;
                        i1='a';
                        i2=6;
                        i3=2;
                        i4=9;
                        i5=7;
                        i6=1;
                        i7='c';
                        i8=6;
                        i9='a';
                        i10=2;
                        i11=6;
                        i12=1;
                        i13='b';
                        i14='c';
                        i15='b';
                        i16=1;
                        i17=1;
                        i18=9;
                        i19='c';
                        i20=6;
                        i21=6;
                        i22=6;          //3a62971c6a261bcb119c66621c7a52b512127c982797288211858222
                        i23=2;
                        i24=1;
                        i25='c';
                        i26=7;
                        i27='a';
                        i28=5;
                        i29=2;
                        i30='b';
                        i31=5;
                        i32=1;        // 12836363c591a3727799b77c28a2a9976aac2288355a898811132222
                        i33=2;
                        i34=1;
                        i35=2;
                        i36=7;
                        i37='c';
                        i38=9;
                        i39=8;
                        i40=2;
                        i41=7;
                        i42=9;
                        i43=7;
                        i44=2;
                        i45=8;
                        i46=8;
                        i47=2;
                        i48=1;       //c2836363cb91a3727599a67c28a2a9976aac2288355a898811132222
                        i49=1;
                        i50=8;
                        i51=5;
                        i52=8;
                        i53=2;
                        i54=2;
                        i55=2;

    multiplier.Tab_FA[0].appx = i0;
    multiplier.Tab_FA[1].appx = i1;
    multiplier.Tab_FA[2].appx = i2;
    multiplier.Tab_FA[3].appx = i3;
    multiplier.Tab_FA[4].appx = i4;
    multiplier.Tab_FA[5].appx = i5;
    multiplier.Tab_FA[6].appx = i6;
    multiplier.Tab_FA[7].appx = i7;
    multiplier.Tab_FA[8].appx = i8;
    multiplier.Tab_FA[9].appx = i9;
    multiplier.Tab_FA[10].appx = i10;
    multiplier.Tab_FA[11].appx = i11;
    multiplier.Tab_FA[12].appx = i12;
    multiplier.Tab_FA[13].appx = i13;
    multiplier.Tab_FA[14].appx = i14;
    multiplier.Tab_FA[15].appx = i15;
    multiplier.Tab_FA[16].appx = i16;
    multiplier.Tab_FA[17].appx = i17;
    multiplier.Tab_FA[18].appx = i18;
    multiplier.Tab_FA[19].appx = i19;
    multiplier.Tab_FA[20].appx = i20;
    multiplier.Tab_FA[21].appx = i21;
    multiplier.Tab_FA[22].appx = i22;
    multiplier.Tab_FA[23].appx = i23;
    multiplier.Tab_FA[24].appx = i24;
    multiplier.Tab_FA[25].appx = i25;
    multiplier.Tab_FA[26].appx = i26;
    multiplier.Tab_FA[27].appx = i27;
    multiplier.Tab_FA[28].appx = i28;
    multiplier.Tab_FA[29].appx = i29;
    multiplier.Tab_FA[30].appx = i30;
    multiplier.Tab_FA[31].appx = i31;
    multiplier.Tab_FA[32].appx = i32;
    multiplier.Tab_FA[33].appx = i33;
    multiplier.Tab_FA[34].appx = i34;
    multiplier.Tab_FA[35].appx = i35;
    multiplier.Tab_FA[36].appx = i36;
    multiplier.Tab_FA[37].appx = i37;
    multiplier.Tab_FA[38].appx = i38;
    multiplier.Tab_FA[39].appx = i39;
    multiplier.Tab_FA[40].appx = i40;
    multiplier.Tab_FA[41].appx = i41;
    multiplier.Tab_FA[42].appx = i42;
    multiplier.Tab_FA[43].appx = i43;
    multiplier.Tab_FA[44].appx = i44;
    multiplier.Tab_FA[45].appx = i45;
    multiplier.Tab_FA[46].appx = i46;
    multiplier.Tab_FA[47].appx = i47;
    multiplier.Tab_FA[48].appx = i48;
    multiplier.Tab_FA[49].appx = i49;
    multiplier.Tab_FA[50].appx = i50;
    multiplier.Tab_FA[51].appx = i51;
    multiplier.Tab_FA[52].appx = i52;
    multiplier.Tab_FA[53].appx = i53;
    multiplier.Tab_FA[54].appx = i54;
    multiplier.Tab_FA[55].appx = i55;
  } else {
    for (j = 0; j < 56; j++) {
      table_index[j] = x;
    }

    for (i = 0; i < 56; i++) {
      multiplier.Tab_FA[i].appx = table_index[i];
    }

  }

  S = multiplier.layout_mult8(A, B); // layout_mult2(A,B);
  //SS=(int)(S.to_ulong());
  return S;
}

std::bitset < 48 > multiply24x24(std::bitset < 24 > A, std::bitset < 24 > B) {

  std::string AA1;
  std::string AA2;
  std::string AA3;
  std::string BB1;
  std::string BB2;
  std::string BB3;
  std::bitset < 8 > A1, A2, A3, B1, B2, B3;

  string A1B1;
  string A2B1;
  string A3B1;
  string A1B2;
  string A2B2;
  string A3B2;
  string A1B3;
  string A2B3;
  string A3B3;

  std::bitset < 48 > CC; // output
  adder add48;

  std::string AA = A.to_string();
  std::string BB = B.to_string();
  AA3 = AA.substr(0, 8);
  AA2 = AA.substr(8, 8);
  AA1 = AA.substr(16, 8);

  BB3 = BB.substr(0, 8);
  BB2 = BB.substr(8, 8);
  BB1 = BB.substr(16, 8);

  A1 = std::bitset < 8 > (AA1);
  A2 = std::bitset < 8 > (AA2);
  A3 = std::bitset < 8 > (AA3);
  B1 = std::bitset < 8 > (BB1);
  B2 = std::bitset < 8 > (BB2);
  B3 = std::bitset < 8 > (BB3);

  A1B1 = multiply8x8(A1, B1, 'h').to_string();
  A2B1 = multiply8x8(A2, B1, 'h').to_string();
  A3B1 = multiply8x8(A3, B1, 'h').to_string();

  A1B2 = multiply8x8(A1, B2, 'h').to_string();
  A2B2 = multiply8x8(A2, B2, 'h').to_string();
  A3B2 = multiply8x8(A3, B2, 'h').to_string();

  A1B3 = multiply8x8(A1, B3, 'h').to_string();
  A2B3 = multiply8x8(A2, B3, 'h').to_string();
  A3B3 = multiply8x8(A3, B3, 'h').to_string();

  /*
  cout<<"AA = "<< AA <<endl;
  cout<<"BB = "<< BB <<endl;
  cout<<"AA1 = "<< AA1 <<endl;
  cout<<"AA2 = "<< AA2 <<endl;
  cout<<"AA3 = "<< AA3 <<endl;
  cout<<"BB1 = "<< BB1 <<endl;
  cout<<"BB2 = "<< BB2 <<endl;
  cout<<"BB3 = "<< BB3 <<endl;
  cout<<"A1 = "<< A1 <<endl;
  cout<<"A2 = "<< A2 <<endl;
  cout<<"A3 = "<< A3 <<endl;
  cout<<"B1 = "<< B1 <<endl;
  cout<<"B2 = "<< B2 <<endl;
  cout<<"B3 = "<< B3 <<endl;
  cout<<"A1B1 = "<< A1B1 <<endl;
  cout<<"A2B1 = "<< A2B1 <<endl;
  cout<<"A3B1 = "<< A3B1 <<endl;
  cout<<"A1B2 = "<< A1B2 <<endl;
  cout<<"A2B2 = "<< A2B2 <<endl;
  cout<<"A3B2 = "<< A3B2 <<endl;
  cout<<"A1B3 = "<< A1B3 <<endl;
  cout<<"A2B3 = "<< A2B3 <<endl;
  cout<<"A3B3 = "<< A3B3 <<endl; */

  A1B1 = A1B1.insert(0, "00000000000000000000000000000000"); //32
  //cout<<"A1B1 = "<<A1B1<<endl;
  A2B1 = A2B1.insert(16, "00000000"); //8
  A2B1 = A2B1.insert(0, "000000000000000000000000"); //24
  //cout<<"A2B1 = "<<A2B1<<endl;
  A3B1 = A3B1.insert(16, "0000000000000000");
  A3B1 = A3B1.insert(0, "0000000000000000");
  //cout<<"A3B1 = "<<A3B1<<endl;
  A1B2 = A1B2.insert(16, "00000000");
  A1B2 = A1B2.insert(0, "000000000000000000000000");
  //cout<<"A1B2 = "<<A1B2<<endl;
  A2B2 = A2B2.insert(16, "0000000000000000");
  A2B2 = A2B2.insert(0, "0000000000000000");
  //cout<<"A2B2 = "<<A2B2<<endl;
  A3B2 = A3B2.insert(16, "000000000000000000000000");
  A3B2 = A3B2.insert(0, "00000000");
  //cout<<"A3B2 = "<<A3B2<<endl;
  A1B3 = A1B3.insert(16, "0000000000000000");
  A1B3 = A1B3.insert(0, "0000000000000000");
  //cout<<"A1B3 = "<<A1B3<<endl;
  A2B3 = A2B3.insert(16, "000000000000000000000000");
  A2B3 = A2B3.insert(0, "00000000");
  //cout<<"A2B3 = "<<A2B3<<endl;
  A3B3 = A3B3.insert(16, "00000000000000000000000000000000");
  //cout<<"A3B3 = "<<A3B3<<endl;

  std::bitset < 48 > A1xB1 = std::bitset < 48 > (A1B1);
  std::bitset < 48 > A2xB1 = std::bitset < 48 > (A2B1);
  std::bitset < 48 > A3xB1 = std::bitset < 48 > (A3B1);
  std::bitset < 48 > A1xB2 = std::bitset < 48 > (A1B2);
  std::bitset < 48 > A2xB2 = std::bitset < 48 > (A2B2);
  std::bitset < 48 > A3xB2 = std::bitset < 48 > (A3B2);
  std::bitset < 48 > A1xB3 = std::bitset < 48 > (A1B3);
  std::bitset < 48 > A2xB3 = std::bitset < 48 > (A2B3);
  std::bitset < 48 > A3xB3 = std::bitset < 48 > (A3B3);

  CC = add48.layout_add48(A1xB1, A2xB1);
  CC = add48.layout_add48(CC, A3xB1);
  CC = add48.layout_add48(CC, A1xB2);
  CC = add48.layout_add48(CC, A2xB2);
  CC = add48.layout_add48(CC, A3xB2);
  CC = add48.layout_add48(CC, A1xB3);
  CC = add48.layout_add48(CC, A2xB3);
  CC = add48.layout_add48(CC, A3xB3);
 // cout << "CC = " << CC << endl;
 // string C = CC.to_string();
  return (CC);
}

std::bitset < 8 > subtracter8(std::bitset < 8 > A, std::bitset < 8 > B) {
  std::bitset < 8 > S;
  S = Add8(A, ~B);
  S = Add8(S, 1);
  return (S);
}

// Convert the 32-bit binary encoding into hexadecimal
int Binary2Hex(std::string Binary) {
  std::bitset < 32 > set(Binary);
  int hex = set.to_ulong();

  return hex;
}

// Convert the 32-bit binary into the decimal
float GetFloat32(std::string Binary) {
  int HexNumber = Binary2Hex(Binary);

  bool negative = !!(HexNumber & 0x80000000);
  int exponent = (HexNumber & 0x7f800000) >> 23;
  int sign = negative ? -1 : 1;

  // Subtract 127 from the exponent
  exponent -= 127;

  // Convert the mantissa into decimal using the
  // last 23 bits
  int power = -1;
  float total = 0.0;
  for (int i = 0; i < 23; i++) {
    int c = Binary[i + 9] - '0';
    total += (float) c * (float) pow(2.0, power);
    power--;
  }
  total += 1.0;

  float value = sign * (float) pow(2.0, exponent) * total;

  return value;
}

// Get 32-bit IEEE 754 format of the decimal value
string GetBinary32(float value) {
  union {
    float input; // assumes sizeof(float) == sizeof(int)
    int output;
  }
  data;

  data.input = value;

  std::bitset < sizeof(float) * CHAR_BIT > bits(data.output);

  std::string mystring = bits.to_string < char,
    std::char_traits < char > ,
    std::allocator < char > > ();

  return mystring;
}

string rounding(string Binary, int p)
{
 std::bitset < 48 > B ;
adder add48;
// cout<< Binary <<endl;
if(Binary[p] == '0'){Binary = Binary.substr(0,p+1);
Binary = Binary.substr(0,p+1);
// cout<<"Binary ="<< Binary<<endl;
B = std::bitset < 48 > (Binary);
B = add48.layout_add48(B, 1);
Binary = B.to_string();
Binary = Binary.substr(25,23);
}
else{
if(Binary[p+1] == '0'){Binary = Binary.substr(0,p+1);}
int l;
l = Binary.length();
 if (Binary[p+1] == '1'){
 Binary = Binary.substr(0,p+1);
// cout<<"Binary ="<< Binary<<endl;
B = std::bitset < 48 > (Binary);
B = add48.layout_add48(B, 1);
Binary = B.to_string();
Binary = Binary.substr(25,23);
//cout<<Binary <<endl;
 }
}

return Binary;
}
float heap(float n, float m) {

  float CC;
  if ((n==0)|(m==0)) {CC = 0;}
else{
  string A = GetBinary32(n);
  //cout << "A= " << A << endl;
  string B = GetBinary32(m);
  //cout << "B= " << B << endl;
  std::bitset < 1 > signA = std::bitset < 1 > (A[0]);

  std::bitset < 1 > signB = std::bitset < 1 > (B[0]);

  std::bitset < 1 > signAxB = signA ^ signB;

  string sign = signAxB.to_string();

  string exponentA = A.substr(1, 8);

  string exponentB = B.substr(1, 8);
  // add exponent
  adder8 add;
  std::bitset < 8 > S_exponent = Add8(std::bitset < 8 > (exponentA), std::bitset < 8 > (exponentB));
  std::bitset < 8 > Bias = 127;
  S_exponent = subtracter8(S_exponent, Bias);
  //cout << "exponent " << S_exponent << endl;
  string C = "1";
  string D = "1";

  string mantissaA = A.substr(9, 23);
  string mantissaB = B.substr(9, 23);
  //cout << "mantissaA " << mantissaA << endl;
  //cout << "mantissaB " << mantissaB << endl;
  //Normalization
  string Nor_mantissa_A = C.append(mantissaA);
  string Nor_mantissa_B = D.append(mantissaB);
  //
  std::bitset < 48 > S_mantissa = multiply24x24(std::bitset < 24 > (Nor_mantissa_A), std::bitset < 24 > (Nor_mantissa_B));

  string S_mantissaaa = S_mantissa.to_string();
 // cout << "mantissa =  " << S_mantissaaa << endl;
  //add rounding building bloc
  //string S_mantiss(S_mantissaaa, 1, 23);
  string S_mantiss;
  //adjust exponent
  if (S_mantissaaa[0] == '0') {
    S_mantiss = S_mantissaaa.substr(2, 46);
   //   cout << "mantissa1 =  " << S_mantiss << endl;
    S_mantiss = rounding(S_mantiss, 22);
  } else {
    S_mantiss = S_mantissaaa.substr(1, 47);
     S_mantiss = rounding(S_mantiss, 22);

    std::bitset < 8 > FF = 1;
    S_exponent = Add8(S_exponent, FF);
  }
  string S;
  string S_exp = S_exponent.to_string();
  //collect all results to get 32bits
  S.append(sign);
  S.append(S_exponent.to_string());
  S.append(S_mantiss);
//  cout<<"S = "<<S<<endl;
float NaN;
  //Special cases
  if (S_mantiss == "00000000000000000000000"){
     if (S_exponent.to_string() == "00000000"){CC = 0;}
     else if ((S_exp == "11111111")&(sign == "0")){CC = INFINITY;}
     else if ((S_exp == "11111111")&(sign == "1")){CC = -INFINITY;}}
 else if (S_exp == "11111111"){C = NaN;}

CC = GetFloat32(S);

if (abs(CC) > 3.4e38){cout<< "out of range!"<<endl;
CC = INFINITY;}
else if (abs(CC) < 1.74594e-38){
CC = 0;
cout<< "out of range!"<<endl;}}
  return CC;
}

int main()
{
    int i;
    string mantissa[25];
    string FP32[25];
    string A0 [25], A1[25], A2[25];
    string Fixed_man[75];
    float A[25] = {0.0409432 ,0.0408633,0.0406245,0.0402297,0.0396835,0.0408633,0.0407835,0.0405453,0.0401512,0.039606,0.0406245,0.0405453,0.0403084,0.0399167,0.0393746,0.0402297,0.0401512,0.0399167,0.0395288,0.038992,0.0396835,0.039606,0.0393746,0.038992,0.0384625};
    for (i = 0; i < 25; i++) {
        FP32[i] = GetBinary32(A[i]);
        mantissa[i] = FP32[i].substr(9, 23);
        mantissa[i] = mantissa[i].insert(0,"1");
        A2[i] = mantissa[i].substr(0, 8);
        A1[i] = mantissa[i].substr(8, 8);
        A0[i] = mantissa[i].substr(16, 8);
        //cout <<"a2=" << A2[i] <<endl;
        //cout <<"a1="<< A1[i] <<endl;
        //cout <<"a0="<< A0[i] <<endl;

    }
    for (i = 0; i < 25; i++) {
         Fixed_man[i] =  A2[i];
    }
      for (i = 25; i < 50; i++) {
         Fixed_man[i] =  A1[i-25];
    }
        for (i = 50; i < 75; i++) {
         Fixed_man[i] =  A0[i-50];
    }
    std::sort(Fixed_man, Fixed_man+75);


}