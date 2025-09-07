template<typename T>
class InsertionInterface {
public:
    virtual void addFirst(T val) = 0;
    virtual void addLast(T val) = 0;
    virtual void addAt(T index, T val) = 0;
    virtual ~InsertionInterface() {}
};