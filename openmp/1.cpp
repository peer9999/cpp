#include <omp.h>
#include <iostream>

int main()
{
    int value = 123;
    #pragma omp parallel 
    {
        value++;
        #pragma omp critical
        {
            std::cout << value++ << std::endl;
        }
    }
    return 0;
}
