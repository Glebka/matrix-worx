#ifndef CMATRIX_HPP
#define CMATRIX_HPP

#include "matrix_export.h"
#include <gsl/gsl_matrix.h>

class MATRIX_EXPORT CMatrix
{
public:
    CMatrix( size_t rows, size_t cols );
    CMatrix( const CMatrix& other );
    CMatrix& operator=( const CMatrix& other );

    ~CMatrix( void );

    size_t rows( void ) const;
    size_t cols( void ) const;

    double get( size_t rowIndex, size_t columnIndex ) const;
    void set( size_t rowIndex, size_t columnIndex, double value );

    const double& operator()( size_t rowIndex, size_t columnIndex ) const;
    double& operator()( size_t rowIndex, size_t columnIndex );

private:
    gsl_matrix* mMatrix;
};

#endif // CMATRIX_HPP
