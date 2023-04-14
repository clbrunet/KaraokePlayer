#pragma once

class Image
{
public:
    Image() = default;
    Image(Image &&) = delete;
    Image(const Image &) = delete;
    Image &operator=(Image &&) = delete;
    Image &operator=(const Image &) = delete;
    ~Image();

    Image(const char* path);

    bool load(const char* path);
    int width() const;
    int height() const;
    unsigned int texture() const;

private:
    int m_width = -1;
    int m_height = -1;
    int m_channels_count = -1;
    unsigned int m_texture = 0;
};
