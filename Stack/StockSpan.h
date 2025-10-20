#include "Stack.h"
#include <vector>
#include <algorithm> // for std::max

int findLargestSpan(std::vector<int> arr)
{
    VectorStack stkarr;
    int maxSpan = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        while (!stkarr.isEmpty() && arr[stkarr.peek()] <= arr[i]) {
            stkarr.pop();
        }
        int span = stkarr.isEmpty() ? (i + 1) : (i - stkarr.peek());
        maxSpan = std::max(maxSpan, span);
        stkarr.push(i);
    }
    return maxSpan;
}

