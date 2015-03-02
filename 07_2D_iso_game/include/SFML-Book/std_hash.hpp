#include <SFML/System/Vector2.hpp>
#include <unordered_map>

/* add hash on std::pair for unordered_map*/
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
  template<>
  struct hash<sf::Vector2i>
  {
    inline size_t operator()(const sf::Vector2i& v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.x);
      ::hash_combine(seed, v.y);
      return seed;
    }
  };
};


