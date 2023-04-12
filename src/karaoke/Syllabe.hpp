#ifndef KARAOKE_SYLLABE_HPP
#define KARAOKE_SYLLABE_HPP

#include <vector>

#include "Letter.hpp"

class Syllabe
{
public:
    Syllabe() = delete;
    Syllabe(Syllabe &&) = default;
    Syllabe(const Syllabe &) = default;
    Syllabe &operator=(Syllabe &&) = default;
    Syllabe &operator=(const Syllabe &) = default;
    ~Syllabe() = default;

    Syllabe(const pugi::xml_node& syllabe_node, const Font& font);

    void set_models(float position);

    const std::vector<Letter>& letters() const;
    const Mat4& model() const;

private:
    std::vector<Letter> m_letters;
    Mat4 m_model;
};

#endif
