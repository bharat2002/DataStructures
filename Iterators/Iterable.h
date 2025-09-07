template <typename T, typename Iter>
class Iterable {
public:
    virtual Iter* begin() = 0;
    virtual Iter* end() = 0;
    virtual Iter* createIterator() = 0;
};  