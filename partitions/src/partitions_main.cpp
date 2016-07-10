#include "partitions.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Hey! gimme one numba" << std::endl;
        return 0;
    }

    
    boost::uint64_t x = std::atoi(argv[1]);
    Partitions partitions(x);
    boost::uint64_t answer = partitions.getResult();
         
    std::cout << "P(" << x << ") is ... " << answer << std::endl;
    
    return 0;
}