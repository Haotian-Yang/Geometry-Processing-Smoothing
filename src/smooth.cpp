#include "smooth.h"
#include "cotmatrix.h"
#include "massmatrix.h"
#include <Eigen/SparseCholesky>
#include <igl/edge_lengths.h>

using namespace Eigen;

void smooth(
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & F,
    const Eigen::MatrixXd & G,
    double lambda,
    Eigen::MatrixXd & U)
{

  // calculate the length of all edges
  Eigen::MatrixXd l;
  igl::edge_lengths(V, F, l);

  // construct the mass matrix
  Eigen::DiagonalMatrix<double,Eigen::Dynamic> M;
  massmatrix(l, F, M);

  // construct the cot Laplacian
  Eigen::SparseMatrix<double> L;
  cotmatrix(l, F, L);


  Eigen::SparseMatrix<double> A = -lambda * L;
  for(int i = 0; i < M.rows(); i++) {
  	A.coeffRef(i, i) += M.diagonal()(i);
  }

  Eigen::SimplicialLDLT<Eigen::SparseMatrix<double> > solver;
  solver.compute(A);
  U = solver.solve(M * G);
} 
