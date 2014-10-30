#include "consts.h"
using namespace consts;

#include<iostream>
#include<cmath>

using namespace std;

int main() {
  
  cout << scientific;
  cout << "ref_time: " << (ref_time=sqrt(ref_mass/ref_energy)*ref_length) << endl;
  cout << "ref_hbar: " << (ref_hbar=1.057472E-34/ref_energy/ref_time) << endl;
  cout << "ref_k:    " << (ref_k=1.38065E-23/ref_energy*ref_temp) << endl;
  
return 0;
}
