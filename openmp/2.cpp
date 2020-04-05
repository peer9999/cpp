#include <omp.h>
#include <iostream>

int main()
{
    int value = 123;
    #pragma omp parallel num_threads(5)
    {
        value++;
        #pragma omp critical
        {
            std::cout << value++ << std::endl;
        }
    }
    return 0;
}
