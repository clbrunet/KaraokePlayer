#ifndef IMAGE_HPP
#define IMAGE_HPP

class Image
{
public:
    Image() = default;
    Image(Image &&) = default;
    Image(const Image &) = default;
    Image &operator=(Image &&) = default;
    Image &operator=(const Image &) = default;
    ~Image();

    Image(const char* path);

    bool load(const char* path);
    unsigned int texture() const;

private:
    int m_width = -1;
    int m_height = -1;
    int m_channels_count = -1;
    unsigned int m_texture = 0;
};

#endif
