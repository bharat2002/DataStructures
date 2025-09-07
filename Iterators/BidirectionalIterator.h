template <typename T>
class BidirectionalIterator {
public:
    virtual bool hasNext() const = 0;
    virtual T& next() = 0;
    virtual bool hasPrevious() const = 0;
    virtual T& previous() = 0;
    virtual ~BidirectionalIterator() = default;
};