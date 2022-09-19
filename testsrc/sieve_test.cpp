//UTF-8

#include "sieve/sieve.h"
#include <iostream>
#include <random>
#include <ctime>
#include <assert.h>

int main()
{
  std::cout
    << "Sieve test" << std::endl
    << "last basic prime 19" << std::endl;

  Sieve sieve(19);

  auto interval = sieve.interval();
  auto& basic_primes = sieve.basic_primes();

  assert(interval == 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19);

  assert((basic_primes == std::vector<uint32>{2, 3, 5, 7, 11, 13, 17, 19 }));

  //Убедимся, что числа из решета, сдвинутые на произвольное количество интервалов, не делятся на базовые простые,
  //а остальные делятся на одно из них
  std::default_random_engine dre(time(0));
  std::uniform_int_distribution<uint32> dist;

  uint64 base = (uint64)(dist(dre)) * interval;

  auto sni = sieve.cbegin();
  auto sieve_num = base + *sni;

  uint64 rem;

  for (auto num = base; num < base + interval; ++num)
  {
    for (auto basic_prime: basic_primes)
    {
      rem = num % basic_prime;
      if (rem == 0)
        break;
    }
    if (rem == 0) //Число поделилось на базовое простое, значит оно отфильтровано
      assert(num < sieve_num);
    else
    {
      assert(num == sieve_num);
      if (++sni != sieve.cend())
      {
        //Числа в решете отсортированы по возрастанию
        assert(*sni > *(sni - 1));
        sieve_num = base + *sni;
      }
    }
  }

  assert(sni == sieve.cend());

  std::cout
    << sieve.size() << " / " << interval << " ~ " << sieve.size() * 100 / interval << "% left in sieve" << std::endl
    << "ok" << std::endl;

  return 0;
}
