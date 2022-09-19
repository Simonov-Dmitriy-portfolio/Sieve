//UTF-8

#include "sieve.h"

#include <assert.h>

Sieve::Sieve(uint32 last_basic_prime) : m_sieve_numbers({1}), m_basic_primes({2}), m_primorial(2)
{
  if (last_basic_prime <= 2)
    return;

  //Следующий шаг не включён в цикл, поскольку следующее базовое простое число (3)
  //за пределами примориала (2)
  m_sieve_numbers.push_back(5);
  m_basic_primes.push_back(3);
  m_primorial = 6;

  uint32 cur_basic_prime = 3;

  //Строим решето, наращивая в цикле базовые простые числа
  while (cur_basic_prime < last_basic_prime)
  {
    std::vector<uint32> tmp;

    //Первое число в фильтре всегда 1, второе является следующим базовым простым числом
    assert(m_sieve_numbers[0] == 1);
    cur_basic_prime = m_sieve_numbers[1];

    m_basic_primes.push_back(cur_basic_prime);

    //По результатам предыдущего этапа уже можем определить, сколько чисел останется после фильтрации на текущем шаге
    //по формуле q(n) = (q(n - 1) * p(n) - q(n - 1)
    //q(n) - количество чисел после фильтрации на шаге n
    //p(n) - новое базовое простое число на шаге n
    //То есть мы размножаем полученные на предыдущем этапе числа в соответствии с расширением примориала,
    //и дополнительно отфильтровываем числа, кратные новому простому числу (включая само это число),
    //причём все возможные множители нового простого числа внутри нового примориала - это опять же числа,
    //полученные на предыдущем этапе
    tmp.reserve(m_basic_primes.size() * (cur_basic_prime - 1));

    auto tmp_primorial = m_primorial;
    m_primorial *= cur_basic_prime;

    size_t fi = 0;
    auto next_prime_factor = m_sieve_numbers[fi]; //первый сомножитель для нового базового простого числа (1)

    for (uint32 base = 0; base < m_primorial; base += tmp_primorial)
    {
      for (size_t i = 0; i < m_sieve_numbers.size(); ++i)
      {
        auto maybe_prime = base + m_sieve_numbers[i];
        if (fi < m_sieve_numbers.size() && maybe_prime == cur_basic_prime * next_prime_factor)
        {
          //Отфильтровываем (не добавляем) кратное нового простого числа
          //Фиксируем следующий сомножитель нового простого числа
          next_prime_factor = m_sieve_numbers[++fi];
        }
        else
        {
          assert(tmp.size() < m_sieve_numbers.size() * (cur_basic_prime - 1));
          tmp.push_back(maybe_prime);
        }
      }
    }
    assert(tmp.size() == m_sieve_numbers.size() * (cur_basic_prime - 1));
    m_sieve_numbers = std::move(tmp);
  }
}
