template <typename T>
class DeletionInterface {
public:
    virtual void deleteFirst() = 0;
    virtual void deleteLast() = 0;
    virtual void deleteAt(int index) = 0;
    virtual ~DeletionInterface() {}
};