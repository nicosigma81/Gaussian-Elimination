#include <iostream>


// Returns true if matrix is nonsingular and false if otherwise
bool reduce_matrix(double* matrix, int m, int n)
{
    // For all pivots M(k, k)
    for (int k = 0; k < m; k++)
    {
        double pivot = matrix[k + m * k];
        
        //swap rows if k == 0
        if (pivot == 0)
        {
            int switch_row = k; // The row that the current row will be swapped with
            
            // Find a row to swap with
            for (int i = 0; i < m; i++)
            {
                if (matrix[i + m * k] != 0)
                {
                    switch_row = i;
                    break;
                }
            }

            // (Slow) swap row k with row 
            for (int j = 0; j < n; j++)
            {
                double temp = matrix[k + m * k];
                matrix[k + m * k] = matrix[switch_row + m * k];
                matrix[switch_row + m * k] = temp;
            }
        }

        // Subtract rows to eliminate
        for (int i = 0; i < m; i++)
        {
            if (i == k) { continue; }
            
            // flag gets set to zero only if every element in a row (except the last 
            // column) is zero. This causes the algorithm to halt
            
            bool flag = 0;
            double to_elim = matrix[i + m * k];
            for (int j = 0; j < n; j++)
            {
                double val = (to_elim / pivot) * matrix[k + m * j];
                matrix[i + m * j] -= val;
                flag = j < m ? flag + matrix[i + m * j] : flag;
            }

            if (!flag) 
            {
                return false;
            }
        }
    }

    // Reduce to RRE
    for (int i = 0; i < m; i++)
    {
        double pivot = matrix[i + m * i];
        for (int j = 0; j < n; j++)
        {
            matrix[i + m * j] = matrix[i + m * j] / pivot;
        }
    }

    return true;
}


int main()
{
    const int m = 3;
    const int n = 4;

    /* 
    Matrix to reduce, listed as { c1, c2, c3, ..., cn } where ci is the ith column.
    
    Examples:
        - nonsingular matrix to try (3x4 augmented): { -2, 3, 1, 1, 0, 2, -1, 1, 3, 4, -1, 13 };
        - singular matrix to try (3x4 augmented): { 1, -1, 2, -2, 1, -1, 3, -2, 3, -2, 3, -7 };
        - can also do gauss-jordan (3x6 augnmented ){ -2, 1, 2, 1, 2, 1, -1, 3, 2, 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    */

    double my_matrix[m * n] = { 1, -1, 2, -2, 1, -1, 3, -2, 3, -2, 3, -7 };

    // Display initial matrix
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << my_matrix[i + m * j] << ", ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "Reduces to:\n"<< std::endl;

    // Find RRE form
    reduce_matrix(my_matrix, m, n);

    // Display reduced matrix
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << my_matrix[i + m * j] << ", ";
        }
        std::cout << std::endl;
    }
}
