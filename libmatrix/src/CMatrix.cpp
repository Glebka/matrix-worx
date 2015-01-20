#include "CMatrix.hpp"

CMatrix::CMatrix( size_t rows, size_t cols )
{
    mMatrix = gsl_matrix_calloc( rows, cols );
    /// TODO: check nullptr and throw exception;
}

CMatrix::CMatrix( const CMatrix& other )
{
    mMatrix = gsl_matrix_alloc( other.rows(), other.cols() );
    gsl_matrix_memcpy( mMatrix, other.mMatrix );
    ///TODO: check GSL_SUCCESS or throw exception
}

CMatrix& CMatrix::operator=( const CMatrix& other )
{
    if ( this != &other )
    {
        if ( rows() != other.rows() || cols() != other.cols() )
        {
            gsl_matrix* newMatrix = gsl_matrix_alloc( other.rows(), other.cols() );
            gsl_matrix_memcpy( newMatrix, other.mMatrix );
            ///TODO: check GSL_SUCCESS or throw exception
            gsl_matrix_free( mMatrix );
            mMatrix = newMatrix;
        }
        else
        {
            gsl_matrix_memcpy( mMatrix, other.mMatrix );
            ///TODO: check GSL_SUCCESS or throw exception
        }
    }
    return *this;
}

CMatrix::~CMatrix( void )
{
    gsl_matrix_free( mMatrix );
}

size_t CMatrix::rows( void ) const
{
    return mMatrix->size1;
}

size_t CMatrix::cols() const
{
    return mMatrix->size2;
}

double CMatrix::get( size_t rowIndex, size_t columnIndex ) const
{
    return gsl_matrix_get( mMatrix, rowIndex, columnIndex );
}

void CMatrix::set( size_t rowIndex, size_t columnIndex, double value )
{
    gsl_matrix_set( mMatrix, rowIndex, columnIndex, value );
}

const double& CMatrix::operator()( size_t rowIndex, size_t columnIndex ) const
{
    return *gsl_matrix_const_ptr( mMatrix, rowIndex, columnIndex );
}

double& CMatrix::operator()( size_t rowIndex, size_t columnIndex )
{
    return *gsl_matrix_ptr( mMatrix, rowIndex, columnIndex );
}

