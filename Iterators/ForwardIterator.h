template <typename T>
class ForwardIterator {

public:
    // ForwardIterator(T* start) : current(start) {}
    virtual bool hasNext() const = 0;
    virtual T& next() = 0;
    virtual ~ForwardIterator() = default;
};