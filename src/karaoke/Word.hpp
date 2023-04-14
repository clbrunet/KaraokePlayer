#ifndef KARAOKE_WORD_HPP
#define KARAOKE_WORD_HPP

#include <vector>

#include "karaoke/Syllabe.hpp"

class Word
{
public:
    Word() = delete;
    Word(Word &&) = default;
    Word(const Word &) = default;
    Word &operator=(Word &&) = default;
    Word &operator=(const Word &) = default;
    ~Word() = default;

    Word(const pugi::xml_node& word_node, const Font& font);

    void set_models(float local_position);
    void set_timings();

    const std::vector<Syllabe>& syllabes() const;
    int letters_count() const;
    const Mat4& model() const;
    float get_end_second() const;

private:
    std::vector<Syllabe> m_syllabes;
    Mat4 m_model;
};

#endif
