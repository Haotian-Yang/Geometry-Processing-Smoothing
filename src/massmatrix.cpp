#include "massmatrix.h"

void massmatrix(
  const Eigen::MatrixXd & l,
  const Eigen::MatrixXi & F,
  Eigen::DiagonalMatrix<double,Eigen::Dynamic> & M)
{
  // Add your code here
  Eigen::VectorXd diag;
  M.resize(F.maxCoeff() + 1);
  diag.resize(F.maxCoeff() + 1);

  for(int i = 0; i < F.rows(); i ++)
  {
    // get edge length
    double a, b, c;
    a = l(i, 0);
    b = l(i, 1);
    c = l(i, 2);

    // calculate the area(Heron's formula)
    double S = (a + b + c)/2.0;
    double A = sqrt(S*(S - a)*(S - b)*(S - c));
    diag(F(i, 0)) = A / 3.0;
    diag(F(i, 1)) = A / 3.0;
    diag(F(i, 2)) = A / 3.0;
  }
  M.diagonal() = diag;
}
