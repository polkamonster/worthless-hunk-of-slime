#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/cstdint.hpp>
#include <boost/multi_array.hpp>

class Partitions
{
public:
    static const boost::uint32_t s_max = 1000;
    
    Partitions(boost::uint32_t p_x) :
        m_lookup(boost::extents[s_max][s_max]),
        m_x(p_x)
    {

        if (p_x < s_max)
        {
            initialize();
            std::cout << "Initialized" << std::endl;
        }
        else
        {
            std::cout << "Sorry! You only paid for numbers less than " << s_max << ".  Insert 25 cents please." << std::endl;
            throw std::runtime_error("Insufficient Funds");
        }

    }
    
    ~Partitions()
    {
    }
    
    boost::uint64_t getResult()
    {
        return calculate(m_x);
    }
private:
    void initialize()
    {
        assert(m_x < s_max);
        for (boost::uint32_t i = 1; i < m_x; ++i)
        {
            for (boost::uint32_t j = 1; j <= i; ++j)
            {
                m_lookup[i][j] = 0;
            }
        }
    }
    
    boost::uint64_t calculate(boost::uint64_t p_x, boost::uint64_t p_y, boost::uint64_t p_z)
    {
        if (p_z == 0)
        {
          //std::cout << "In P(x,y,z), you had z = 0" << std::endl;
            throw std::logic_error("oops");
        }
        else if (p_y == 0)
        {
            //std::cout << "In P(x,y,z), you had y = 0" << std::endl;
            throw std::logic_error("oops");
        } 
        else if (p_y * p_z > p_x)
        {
            //std::cout << "In P(x,y,z), you had yz > x, where x = " << p_x << " y = " << p_y << " z = " << p_z << std::endl;
            throw std::logic_error("oops");
        }
        else if (p_y * p_z == p_x)
        {
            //std::cout << "P(" << p_x << "," << p_y << "," << p_z << ") = " << 1 << std::endl;
            return 1;
        }
        else if (p_y == 1)
        {
            //std::cout << "P(" << p_x << "," << p_y << "," << p_z << ") = " << 1 << std::endl;
            return 1; // NOTE should probably be 1 not x
        }
        else // x > yz, y > 1, z > 0
        {
            boost::uint64_t ret = 0;
            
            const boost::uint64_t newX = p_x - p_y * p_z;
            boost::uint64_t newMaxY = std::min(newX, p_y - 1);
            
            for (boost::uint64_t newY = 1; newY <= newMaxY; ++newY)
            {
                ret += calculate(newX, newY);
            }
            //std::cout << "P(" << p_x << "," << p_y << "," << p_z << ") = " << ret << std::endl;
            return ret;
        }
    }

    boost::uint64_t calculate(boost::uint64_t p_x, boost::uint64_t p_y)
    {
        if (p_y > p_x)
        {
            //std::cout << "In P(x,y), you had y = " << p_y << " > x  = " << p_x << std::endl;
            throw std::logic_error("oops");
        }
        else if (p_y == p_x)
        {
            //std::cout << "P(" << p_x << "," << p_y << ") = " << 1 << std::endl;
            return 1;
        }
        else if (p_y == 1)
        {
            //std::cout << "P(" << p_x << "," << p_y << ") = " << 1 << std::endl;
            return 1;
        }
        else if (m_lookup[p_x][p_y] != 0)
        {
            return m_lookup[p_x][p_y];
        }
        else
        {
            boost::uint64_t ret = 0;
            for (boost::uint64_t z = 1; z <= p_x / p_y; ++z)
            {
                ret += calculate(p_x, p_y, z);
            }
            //std::cout << "P(" << p_x << "," << p_y << ") = " << ret << std::endl;
            m_lookup[p_x][p_y] = ret;
            return ret;
        }
    }

    boost::uint64_t calculate(boost::uint64_t p_x)
    {
        if (p_x == 0)
        {
            return 0;
        }
        else if (p_x == 1)
        {
            return 1;
        }
        else
        {
            boost::uint64_t ret = 0;
            for (boost::uint64_t y = 1; y <= p_x; ++y)
            {
                ret += calculate(p_x, y);
                std::time_t currentTime = std::time(NULL);
                std::cout << "Found P(" << p_x << "," << y << ") at " << std::ctime(&currentTime) << std::endl;
            }
            return ret;
        }
    }
    
private:
    boost::multi_array<boost::uint64_t, 2> m_lookup;
    boost::uint64_t m_x;
};
