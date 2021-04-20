#include "cotmatrix.h"

double cot(double a, double b, double c)
{

  // calculate the area
  double S = (a + b + c)/2.0;
  double A = sqrt(S*(S - a)*(S - b)*(S - c));

  // calculate the cot
  double cos_A = (-a*a + b*b + c*c)/(2.0*b*c);
  double sin_A = 2.0 * A / (b * c);
  return cos_A/sin_A;
}


void cotmatrix(
  const Eigen::MatrixXd & l,
  const Eigen::MatrixXi & F,
  Eigen::SparseMatrix<double> & L)
{
   // Add your code here
  typedef Eigen::Triplet<double> T;
  std::vector<T> tripletList;
  int n = F.maxCoeff() + 1;
  tripletList.reserve(n*12);
  L.resize(n, n);

  for (int i = 0; i < F.rows(); i++) {
    // get the edge legth
    double a = l(i, 0); 
    double b = l(i, 1); 
    double c = l(i, 2); 

    // get the vertices
    int A = F(i, 0);
    int B = F(i, 1);
    int C = F(i, 2);

    // calculate the cot
    double cot_A = cot(a, b, c);
    double cot_B = cot(b, c, a);
    double cot_C = cot(c, a, b);

    tripletList.push_back(T(A, B, cot_C / 2.0));
    tripletList.push_back(T(B, A, cot_C / 2.0));
    tripletList.push_back(T(B, C, cot_A / 2.0));
    tripletList.push_back(T(C, B, cot_A / 2.0));
    tripletList.push_back(T(C, A, cot_B / 2.0));
    tripletList.push_back(T(A, C, cot_B / 2.0));
    
    tripletList.push_back(T(A, A, -cot_C / 2.0));
    tripletList.push_back(T(B, B, -cot_C / 2.0));
    tripletList.push_back(T(B, B, -cot_A / 2.0));
    tripletList.push_back(T(C, C, -cot_A / 2.0));
    tripletList.push_back(T(A, A, -cot_B / 2.0));
    tripletList.push_back(T(C, C, -cot_B / 2.0));
  }

  L.setFromTriplets(tripletList.begin(), tripletList.end());
}
