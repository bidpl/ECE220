/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA,double *matrixB,double *matrixC,int m,int k,int n)
{
//YOUR CODE HERE
    for(int rowC = 0; rowC < m; rowC++) {
        for(int colC = 0; colC<n; colC++) {
            double sum = 0;

            for(int i = 0; i < k; i++) {
                sum += matrixA[rowC*k + i] * matrixB[i*n + colC];
            }

            matrixC[rowC*n + colC] = sum;
        }
    }
}

