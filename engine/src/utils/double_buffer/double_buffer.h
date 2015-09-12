#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "smart_ptr_utils.h"

template<typename Type>
class DoubleBuffer {

public:

    void setSize(size_t size);

    std::vector<Type>& getBackBuffer();

    void copyBuffer(std::vector<Type>& colorBuffer);
    void swapBuffers();

private:

    std::unique_ptr<std::vector<Type>> frontBuffer;
    std::unique_ptr<std::vector<Type>> backBuffer;

    std::mutex bufferMutex;

};

#include "double_buffer.hpp"
