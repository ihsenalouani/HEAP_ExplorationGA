// C++ program to create target string, starting from
// random string using Genetic Algorithm
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cmath>        // std::abs
#include <bits/stdc++.h>

using namespace std;

class And_component{

    public:

    std::bitset<1> a,b;

    bitset<1> And_sfunction(){
       // out = a&b;
        return(a&b);
    }

};

class full_adder {

	public:
		std::bitset<3> input;

		full_adder(){

                    input= 0;

		}


		std::bitset<1> calcul_S(){

			std::bitset<1> a;//=input[0];
			std::bitset<1> b;//=input[1];
			std::bitset<1> c_in;//=input[3];
			a[0]= input[0];
			b[0]=input[1];
			c_in[0]=input[2];
		 return((a^b)^c_in);

		}

		std::bitset<1> calcul_cout(){

			std::bitset<1> a;//=input[0];
			std::bitset<1> b;//=input[1];
			//std::bitset<1> d;//=input[2];
			std::bitset<1> c_in;//=input[3];

			a[0]= input[0];
			b[0]=input[1];
			//d[0]=input[2];
			c_in[0]=input[2];

			return((a&b)|(c_in&((a^b))));

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
class multiplier_layout8{
public:
And_component Tab_And [8];
full_adderBlock Tab_FA[56];
std::bitset<16> S; // output

multiplier_layout8(){

    And_component(); // what the hell ?????
    //full_adderBlock();

    }

std::bitset<16> layout_mult8(std::bitset<8> A, std::bitset<8> B ){


//link the components

Tab_And[0].a[0]=A[0];
Tab_And[0].b[0]=B[0];


Tab_And[1].a[0]=A[0];
Tab_And[1].b[0]=B[1];


Tab_And[2].a[0]=A[0];
Tab_And[2].b[0]=B[2];


Tab_And[3].a[0]=A[0];
Tab_And[3].b[0]=B[3];


Tab_And[4].a[0]=A[0];
Tab_And[4].b[0]=B[4];


Tab_And[5].a[0]=A[0];
Tab_And[5].b[0]=B[5];


Tab_And[6].a[0]=A[0];
Tab_And[6].b[0]=B[6];


Tab_And[7].a[0]=A[0];
Tab_And[7].b[0]=B[7];


S[0]= Tab_And[0].And_sfunction()[0];

//-----------------b second line


Tab_FA[0].input[0] =A[1];
Tab_FA[0].input[1] =B[0];
Tab_FA[0].input[2] =Tab_And[1].And_sfunction()[0];
Tab_FA[0].input[3] =0;


Tab_FA[1].input[0] =A[1];
Tab_FA[1].input[1] =B[1];
Tab_FA[1].input[2] =Tab_And[2].And_sfunction()[0];
Tab_FA[1].input[3] =Tab_FA[0].calcul_cout()[0];

Tab_FA[2].input[0] =A[1];
Tab_FA[2].input[1] =B[2];
Tab_FA[2].input[2] =Tab_And[3].And_sfunction()[0];
Tab_FA[2].input[3] =Tab_FA[1].calcul_cout()[0];

Tab_FA[3].input[0] =A[1];
Tab_FA[3].input[1] =B[3];
Tab_FA[3].input[2] =Tab_And[4].And_sfunction()[0];
Tab_FA[3].input[3] =Tab_FA[2].calcul_cout()[0];


Tab_FA[4].input[0] =A[1];
Tab_FA[4].input[1] =B[4];
Tab_FA[4].input[2] =Tab_And[5].And_sfunction()[0];
Tab_FA[4].input[3] =Tab_FA[3].calcul_cout()[0];


Tab_FA[5].input[0] =A[1];
Tab_FA[5].input[1] =B[5];
Tab_FA[5].input[2] =Tab_And[6].And_sfunction()[0];
Tab_FA[5].input[3] =Tab_FA[4].calcul_cout()[0];


Tab_FA[6].input[0] =A[1];
Tab_FA[6].input[1] =B[6];
Tab_FA[6].input[2] =Tab_And[7].And_sfunction()[0];
Tab_FA[6].input[3] =Tab_FA[5].calcul_cout()[0];

Tab_FA[7].input[0] =A[1];
Tab_FA[7].input[1] =B[7];
Tab_FA[7].input[2] =0;
Tab_FA[7].input[3] =Tab_FA[6].calcul_cout()[0];


S[1]= Tab_FA[0].calcul_S()[0];

//-----------------b line 3



Tab_FA[8].input[0] =A[2];
Tab_FA[8].input[1] =B[0];
Tab_FA[8].input[2] =Tab_FA[1].calcul_S()[0];
Tab_FA[8].input[3] =0;


Tab_FA[9].input[0] =A[2];
Tab_FA[9].input[1] =B[1];
Tab_FA[9].input[2] =Tab_FA[2].calcul_S()[0];
Tab_FA[9].input[3] =Tab_FA[8].calcul_cout()[0];

Tab_FA[10].input[0] =A[2];
Tab_FA[10].input[1] =B[2];
Tab_FA[10].input[2] =Tab_FA[3].calcul_S()[0];
Tab_FA[10].input[3] =Tab_FA[9].calcul_cout()[0];

Tab_FA[11].input[0] =A[2];
Tab_FA[11].input[1] =B[3];
Tab_FA[11].input[2] =Tab_FA[4].calcul_S()[0];
Tab_FA[11].input[3] =Tab_FA[10].calcul_cout()[0];


Tab_FA[12].input[0] =A[2];
Tab_FA[12].input[1] =B[4];
Tab_FA[12].input[2] =Tab_FA[5].calcul_S()[0];
Tab_FA[12].input[3] =Tab_FA[11].calcul_cout()[0];


Tab_FA[13].input[0] =A[2];
Tab_FA[13].input[1] =B[5];
Tab_FA[13].input[2] =Tab_FA[6].calcul_S()[0];
Tab_FA[13].input[3] =Tab_FA[12].calcul_cout()[0];


Tab_FA[14].input[0] =A[2];
Tab_FA[14].input[1] =B[6];
Tab_FA[14].input[2] =Tab_FA[7].calcul_S()[0];
Tab_FA[14].input[3] =Tab_FA[13].calcul_cout()[0];

Tab_FA[15].input[0] =A[2];
Tab_FA[15].input[1] =B[7];
Tab_FA[15].input[2] =Tab_FA[7].calcul_cout()[0];
Tab_FA[15].input[3] =Tab_FA[14].calcul_cout()[0];



S[2]=Tab_FA[8].calcul_S()[0];

//----------------------line 4



Tab_FA[16].input[0] =A[3];
Tab_FA[16].input[1] =B[0];
Tab_FA[16].input[2] =Tab_FA[9].calcul_S()[0];
Tab_FA[16].input[3] =0;


Tab_FA[17].input[0] =A[3];
Tab_FA[17].input[1] =B[1];
Tab_FA[17].input[2] =Tab_FA[10].calcul_S()[0];
Tab_FA[17].input[3] =Tab_FA[16].calcul_cout()[0];

Tab_FA[18].input[0] =A[3];
Tab_FA[18].input[1] =B[2];
Tab_FA[18].input[2] =Tab_FA[11].calcul_S()[0];
Tab_FA[18].input[3] =Tab_FA[17].calcul_cout()[0];

Tab_FA[19].input[0] =A[3];
Tab_FA[19].input[1] =B[3];
Tab_FA[19].input[2] =Tab_FA[12].calcul_S()[0];
Tab_FA[19].input[3] =Tab_FA[18].calcul_cout()[0];


Tab_FA[20].input[0] =A[3];
Tab_FA[20].input[1] =B[4];
Tab_FA[20].input[2] =Tab_FA[13].calcul_S()[0];
Tab_FA[20].input[3] =Tab_FA[19].calcul_cout()[0];


Tab_FA[21].input[0] =A[3];
Tab_FA[21].input[1] =B[5];
Tab_FA[21].input[2] =Tab_FA[14].calcul_S()[0];
Tab_FA[21].input[3] =Tab_FA[20].calcul_cout()[0];


Tab_FA[22].input[0] =A[3];
Tab_FA[22].input[1] =B[6];
Tab_FA[22].input[2] =Tab_FA[15].calcul_S()[0];
Tab_FA[22].input[3] =Tab_FA[21].calcul_cout()[0];

Tab_FA[23].input[0] =A[3];
Tab_FA[23].input[1] =B[7];
Tab_FA[23].input[2] =Tab_FA[15].calcul_cout()[0];
Tab_FA[23].input[3] =Tab_FA[22].calcul_cout()[0];



S[3]=Tab_FA[16].calcul_S()[0];

//------ line 5




Tab_FA[24].input[0] =A[4];
Tab_FA[24].input[1] =B[0];
Tab_FA[24].input[2] =Tab_FA[17].calcul_S()[0];
Tab_FA[24].input[3] =0;


Tab_FA[25].input[0] =A[4];
Tab_FA[25].input[1] =B[1];
Tab_FA[25].input[2] =Tab_FA[18].calcul_S()[0];
Tab_FA[25].input[3] =Tab_FA[24].calcul_cout()[0];

Tab_FA[26].input[0] =A[4];
Tab_FA[26].input[1] =B[2];
Tab_FA[26].input[2] =Tab_FA[19].calcul_S()[0];
Tab_FA[26].input[3] =Tab_FA[25].calcul_cout()[0];

Tab_FA[27].input[0] =A[4];
Tab_FA[27].input[1] =B[3];
Tab_FA[27].input[2] =Tab_FA[20].calcul_S()[0];
Tab_FA[27].input[3] =Tab_FA[26].calcul_cout()[0];


Tab_FA[28].input[0] =A[4];
Tab_FA[28].input[1] =B[4];
Tab_FA[28].input[2] =Tab_FA[21].calcul_S()[0];
Tab_FA[28].input[3] =Tab_FA[27].calcul_cout()[0];


Tab_FA[29].input[0] =A[4];
Tab_FA[29].input[1] =B[5];
Tab_FA[29].input[2] =Tab_FA[22].calcul_S()[0];
Tab_FA[29].input[3] =Tab_FA[28].calcul_cout()[0];


Tab_FA[30].input[0] =A[4];
Tab_FA[30].input[1] =B[6];
Tab_FA[30].input[2] =Tab_FA[23].calcul_S()[0];
Tab_FA[30].input[3] =Tab_FA[29].calcul_cout()[0];

Tab_FA[31].input[0] =A[4];
Tab_FA[31].input[1] =B[7];
Tab_FA[31].input[2] =Tab_FA[23].calcul_cout()[0];
Tab_FA[31].input[3] =Tab_FA[30].calcul_cout()[0];



S[4]=Tab_FA[24].calcul_S()[0];

/////////////////////////////////////////------- //------ line 6


Tab_FA[32].input[0] =A[5];
Tab_FA[32].input[1] =B[0];
Tab_FA[32].input[2] =Tab_FA[25].calcul_S()[0];
Tab_FA[32].input[3] =0;


Tab_FA[33].input[0] =A[5];
Tab_FA[33].input[1] =B[1];
Tab_FA[33].input[2] =Tab_FA[26].calcul_S()[0];
Tab_FA[33].input[3] =Tab_FA[32].calcul_cout()[0];

Tab_FA[34].input[0] =A[5];
Tab_FA[34].input[1] =B[2];
Tab_FA[34].input[2] =Tab_FA[27].calcul_S()[0];
Tab_FA[34].input[3] =Tab_FA[33].calcul_cout()[0];

Tab_FA[35].input[0] =A[5];
Tab_FA[35].input[1] =B[3];
Tab_FA[35].input[2] =Tab_FA[28].calcul_S()[0];
Tab_FA[35].input[3] =Tab_FA[34].calcul_cout()[0];


Tab_FA[36].input[0] =A[5];
Tab_FA[36].input[1] =B[4];
Tab_FA[36].input[2] =Tab_FA[29].calcul_S()[0];
Tab_FA[36].input[3] =Tab_FA[35].calcul_cout()[0];


Tab_FA[37].input[0] =A[5];
Tab_FA[37].input[1] =B[5];
Tab_FA[37].input[2] =Tab_FA[30].calcul_S()[0];
Tab_FA[37].input[3] =Tab_FA[36].calcul_cout()[0];


Tab_FA[38].input[0] =A[5];
Tab_FA[38].input[1] =B[6];
Tab_FA[38].input[2] =Tab_FA[31].calcul_S()[0];
Tab_FA[38].input[3] =Tab_FA[37].calcul_cout()[0];

Tab_FA[39].input[0] =A[5];
Tab_FA[39].input[1] =B[7];
Tab_FA[39].input[2] =Tab_FA[31].calcul_cout()[0];
Tab_FA[39].input[3] =Tab_FA[38].calcul_cout()[0];



S[5]=Tab_FA[32].calcul_S()[0];



/////////////////////////////////////////------- //------ line 7


Tab_FA[40].input[0] =A[6];
Tab_FA[40].input[1] =B[0];
Tab_FA[40].input[2] =Tab_FA[33].calcul_S()[0];
Tab_FA[40].input[3] =0;


Tab_FA[41].input[0] =A[6];
Tab_FA[41].input[1] =B[1];
Tab_FA[41].input[2] =Tab_FA[34].calcul_S()[0];
Tab_FA[41].input[3] =Tab_FA[40].calcul_cout()[0];

Tab_FA[42].input[0] =A[6];
Tab_FA[42].input[1] =B[2];
Tab_FA[42].input[2] =Tab_FA[35].calcul_S()[0];
Tab_FA[42].input[3] =Tab_FA[41].calcul_cout()[0];

Tab_FA[43].input[0] =A[6];
Tab_FA[43].input[1] =B[3];
Tab_FA[43].input[2] =Tab_FA[36].calcul_S()[0];
Tab_FA[43].input[3] =Tab_FA[42].calcul_cout()[0];


Tab_FA[44].input[0] =A[6];
Tab_FA[44].input[1] =B[4];
Tab_FA[44].input[2] =Tab_FA[37].calcul_S()[0];
Tab_FA[44].input[3] =Tab_FA[43].calcul_cout()[0];


Tab_FA[45].input[0] =A[6];
Tab_FA[45].input[1] =B[5];
Tab_FA[45].input[2] =Tab_FA[38].calcul_S()[0];
Tab_FA[45].input[3] =Tab_FA[44].calcul_cout()[0];


Tab_FA[46].input[0] =A[6];
Tab_FA[46].input[1] =B[6];
Tab_FA[46].input[2] =Tab_FA[39].calcul_S()[0];
Tab_FA[46].input[3] =Tab_FA[45].calcul_cout()[0];

Tab_FA[47].input[0] =A[6];
Tab_FA[47].input[1] =B[7];
Tab_FA[47].input[2] =Tab_FA[39].calcul_cout()[0];
Tab_FA[47].input[3] =Tab_FA[46].calcul_cout()[0];



S[6]=Tab_FA[40].calcul_S()[0];



/////////////////////////////////////////------- //------ line 8


Tab_FA[48].input[0] =A[7];
Tab_FA[48].input[1] =B[0];
Tab_FA[48].input[2] =Tab_FA[41].calcul_S()[0];
Tab_FA[48].input[3] =0;


Tab_FA[49].input[0] =A[7];
Tab_FA[49].input[1] =B[1];
Tab_FA[49].input[2] =Tab_FA[42].calcul_S()[0];
Tab_FA[49].input[3] =Tab_FA[48].calcul_cout()[0];

Tab_FA[50].input[0] =A[7];
Tab_FA[50].input[1] =B[2];
Tab_FA[50].input[2] =Tab_FA[43].calcul_S()[0];
Tab_FA[50].input[3] =Tab_FA[49].calcul_cout()[0];

Tab_FA[51].input[0] =A[7];
Tab_FA[51].input[1] =B[3];
Tab_FA[51].input[2] =Tab_FA[44].calcul_S()[0];
Tab_FA[51].input[3] =Tab_FA[50].calcul_cout()[0];


Tab_FA[52].input[0] =A[7];
Tab_FA[52].input[1] =B[4];
Tab_FA[52].input[2] =Tab_FA[45].calcul_S()[0];
Tab_FA[52].input[3] =Tab_FA[51].calcul_cout()[0];


Tab_FA[53].input[0] =A[7];
Tab_FA[53].input[1] =B[5];
Tab_FA[53].input[2] =Tab_FA[46].calcul_S()[0];
Tab_FA[53].input[3] =Tab_FA[52].calcul_cout()[0];


Tab_FA[54].input[0] =A[7];
Tab_FA[54].input[1] =B[6];
Tab_FA[54].input[2] =Tab_FA[47].calcul_S()[0];
Tab_FA[54].input[3] =Tab_FA[53].calcul_cout()[0];

Tab_FA[55].input[0] =A[7];
Tab_FA[55].input[1] =B[7];
Tab_FA[55].input[2] =Tab_FA[47].calcul_cout()[0];
Tab_FA[55].input[3] =Tab_FA[54].calcul_cout()[0];



S[7]=Tab_FA[48].calcul_S()[0];
S[8]=Tab_FA[49].calcul_S()[0];
S[9]=Tab_FA[50].calcul_S()[0];
S[10]=Tab_FA[51].calcul_S()[0];
S[11]=Tab_FA[52].calcul_S()[0];
S[12]=Tab_FA[53].calcul_S()[0];
S[13]=Tab_FA[54].calcul_S()[0];
S[14]=Tab_FA[55].calcul_S()[0];
S[15]=Tab_FA[55].calcul_cout()[0];

return(S);
}
};


//
float exhaustive(multiplier_layout8 multiplier, int table_index[56]){

                std::bitset<16> S;
                unsigned char ka,kb;
                int i,j;
                float sum,err,sum_MRE;
                float Me,r,rr,MRE,Res; //mean error
                float out;
int i0, i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55;

              r=0;//counter
              sum=0;
              sum_MRE=0;
              Res=0;
              rr=0;
              err=0; //total number of errors by circuit k

   /* i0 = 1;
    i1 = 'c';
    i2 = 'b';
    i3 = 'c';
    i4 = 2;
    i5 = 5;
    i6 = 2;
    i7 = 'c';
    i8 = 6;
    i9 = 'b';
    i10 = 1;
    i11 = 2;
    i12 = 'c';
    i13 = 2;
    i14 = 8;
    i15 = 'b';
    i16 = 6;
    i17 = 2;
    i18 = 1;
    i19 = 2;
    i20 = 1;
    i21 = 2;
    i22 = 'a';
    i23 = 2;
    i24 = 1;
    i25 = 1;
    i26 = 1;
    i27 = 1;
    i28 = 1;
    i29 = 2;
 */   i30 = 2;
    i31 = 1;
    i32 = 1;
    i33 = 1;
    i34 = 1;
    i35 = 1;
    i36 = 1;
    i37 = 2;
    i38 = 1;
    i39 = 2;
    i40 = 1;
    i41 = 1;
    i42 = 1;
    i43 = 1;
    i44 = 1;
    i45 = 2;
    i46 = 2;
    i47 = 2;
    i48 = 1;
    i49 = 1;
    i50 = 1;
    i51 = 1;
    i52 = 1;
    i53 = 1;
    i54 = 2;
    i55 = 2;

             /* multiplier.Tab_FA[0].appx=i0;
              multiplier.Tab_FA[1].appx=i1;
              multiplier.Tab_FA[2].appx=i2;
              multiplier.Tab_FA[3].appx=i3;
              multiplier.Tab_FA[4].appx=i4;
              multiplier.Tab_FA[5].appx=i5;
              multiplier.Tab_FA[6].appx=i6;
              multiplier.Tab_FA[7].appx=i7;
              multiplier.Tab_FA[8].appx=i8;
              multiplier.Tab_FA[9].appx=i9;
              multiplier.Tab_FA[10].appx=i10;
              multiplier.Tab_FA[11].appx=i11;
              multiplier.Tab_FA[12].appx=i12;
              multiplier.Tab_FA[13].appx=i13;
              multiplier.Tab_FA[14].appx=i14;
              multiplier.Tab_FA[15].appx=i15;
              multiplier.Tab_FA[16].appx=i16;
              multiplier.Tab_FA[17].appx=i17;
              multiplier.Tab_FA[18].appx=i18;
              multiplier.Tab_FA[19].appx=i19;
              multiplier.Tab_FA[20].appx=i20;
              multiplier.Tab_FA[21].appx=i21;
              multiplier.Tab_FA[22].appx=i22;
              multiplier.Tab_FA[23].appx=i23;
              multiplier.Tab_FA[24].appx=i24;
              multiplier.Tab_FA[25].appx=i25;
              multiplier.Tab_FA[26].appx=i26;
              multiplier.Tab_FA[27].appx=i27;
              multiplier.Tab_FA[28].appx=i28;
              multiplier.Tab_FA[29].appx=i29; */
              multiplier.Tab_FA[30].appx=i30;
              multiplier.Tab_FA[31].appx=i31;
              multiplier.Tab_FA[32].appx=i32;
              multiplier.Tab_FA[33].appx=i33;
              multiplier.Tab_FA[34].appx=i34;
              multiplier.Tab_FA[35].appx=i35;
              multiplier.Tab_FA[36].appx=i36;
              multiplier.Tab_FA[37].appx=i37;
              multiplier.Tab_FA[38].appx=i38;
              multiplier.Tab_FA[39].appx=i39;
              multiplier.Tab_FA[40].appx=i40;
              multiplier.Tab_FA[41].appx=i41;
              multiplier.Tab_FA[42].appx=i42;
              multiplier.Tab_FA[43].appx=i43;
              multiplier.Tab_FA[44].appx=i44;
              multiplier.Tab_FA[45].appx=i45;
              multiplier.Tab_FA[46].appx=i46;
              multiplier.Tab_FA[47].appx=i47;
              multiplier.Tab_FA[48].appx=i48;
              multiplier.Tab_FA[49].appx=i49;
              multiplier.Tab_FA[50].appx=i50;
              multiplier.Tab_FA[51].appx=i51;
              multiplier.Tab_FA[52].appx=i52;
              multiplier.Tab_FA[53].appx=i53;
              multiplier.Tab_FA[54].appx=i54;
              multiplier.Tab_FA[55].appx=i55;

  //affect the implementations
         for (i=0;i<56;i++)
         {
              multiplier.Tab_FA[i].appx=table_index[i];
         }

 for(ka=0;ka<255;ka++)// all combinations of inputs

    {

 for(kb=0;kb<255;kb++)
    {

   //  A=ka;
  //   B=kb;
     r++;

S= multiplier.layout_mult8(ka,kb);// layout_mult8(A,B);
out= (float)S.to_ulong();
sum+= abs(ka*kb-out);
if ((ka*kb)!=0)
{
Res = (abs(ka*kb-out));
Res /= (ka*kb);
sum_MRE+= Res;
rr++;
}
 }
 }
    Me=sum/(r+1);//mean error
   //MRE = sum_MRE/(rr+1);   //mean relative error
    return Me;
}






// Number of individuals in each generation
#define POPULATION_SIZE 100

// Valid Genes
const string GENES = "12356789abc";


// Function to generate random numbers in given range
int random_num(int start, int end)
{
	int range = (end-start)+1;
	int random_int = start+(rand()%range);
	return random_int;
}

// Create random genes for mutation
char mutated_genes()
{
	int len = GENES.size();
	int r = random_num(0, len-1);
	return GENES[r];
}

// create chromosome or string of genes
string create_gnome()
{
	////int len = TARGET.size();
	int len = 56;
	string gnome = "";
	for(int i = 0;i<len;i++)
		gnome += mutated_genes();
	return gnome;
}

// Class representing individual in population
class Individual
{
public:
	string chromosome;
	float fitness;
	Individual(string chromosome);
	Individual mate(Individual parent2);
	float cal_fitness();
};

Individual::Individual(string chromosome)
{
	this->chromosome = chromosome;
	fitness = cal_fitness();
};

// Perform mating and produce new offspring
Individual Individual::mate(Individual par2)
{
	// chromosome for offspring
	string child_chromosome = "";

	int len = chromosome.size();
	for(int i = 0;i<len;i++)
	{
		// random probability
		float p = random_num(0, 100)/100;

		// if prob is less than 0.45, insert gene
		// from parent 1
		if(p < 0.45)
			child_chromosome += chromosome[i];

		// if prob is between 0.45 and 0.90, insert
		// gene from parent 2
		else if(p < 0.80)
			child_chromosome += par2.chromosome[i];

		// otherwise insert random gene(mutate),
		// for maintaining diversity
		else
			child_chromosome += mutated_genes();
	}

	// create new Individual(offspring) using
	// generated chromosome for offspring
	return Individual(child_chromosome);
};


// Calculate fittness score, it is the number of
// characters in string which differ from target
// string.
float Individual::cal_fitness()
{
	////int len = TARGET.size();
	int len = 56;
	int i;
	float fitness = 0;
    multiplier_layout8 multiplier8;
 	int table_index[56];
    		for(i=0;i<56;i++){
    		 table_index[i] =chromosome[i] - '0';
    		}

		fitness = (float)exhaustive(multiplier8,table_index);
	//	cout<<fitness<<endl;

	return fitness;
};

// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
	return ind1.fitness < ind2.fitness;
}

// Driver code
int main()
{
	srand((unsigned)(time(0)));

	// current generation
	int generation = 0;

	vector<Individual> population;
	bool found = false;

	// create initial population
	for(int i = 0;i<POPULATION_SIZE;i++)
	{
		string gnome = create_gnome();
		population.push_back(Individual(gnome));
	}

	while(! found)
	{
		// sort the population in increasing order of fitness score
		sort(population.begin(), population.end());

		// if the individual having lowest fitness score ie.
		// 0 then we know that we have reached to the target
		// and break the loop
		if(population[0].fitness <= 0)     //condition to break the loop
		{
			found = true;
			break;
		}

		// Otherwise generate new offsprings for new generation
		vector<Individual> new_generation;

		// Perform Elitism, that mean 10% of fittest population
		// goes to the next generation
		int s = (10*POPULATION_SIZE)/100;
		for(int i = 0;i<s;i++)
			new_generation.push_back(population[i]);

		// From 50% of fittest population, Individuals
		// will mate to produce offspring
		s = (90*POPULATION_SIZE)/100;
		for(int i = 0;i<s;i++)
		{
			int len = population.size();
			int r = random_num(0, 60);
			Individual parent1 = population[r];
			r = random_num(0, 60);
			Individual parent2 = population[r];
			Individual offspring = parent1.mate(parent2);
			new_generation.push_back(offspring);
		}
		population = new_generation;
		cout<< "Generation: " << generation << "\t";
		cout<< "Config: "<< population[0].chromosome <<"\t";
		cout<< "Fitness: "<< population[0].fitness << "\n";

		generation++;
	}
	cout<< "Generation: " << generation << "\t";
	cout<< "Config: "<< population[0].chromosome <<"\t";
	cout<< "Fitness: "<< population[0].fitness << "\n";
}

