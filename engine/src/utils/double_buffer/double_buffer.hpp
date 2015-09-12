template<typename Type>
void DoubleBuffer<Type>::setSize(size_t size)
{
    frontBuffer = std::make_unique<std::vector<Type>>(size);
    backBuffer = std::make_unique<std::vector<Type>>(size);
}

template<typename Type>
std::vector<Type>& DoubleBuffer<Type>::getBackBuffer()
{
    return *backBuffer.get();
}

template<typename Type>
void DoubleBuffer<Type>::copyBuffer(std::vector<Type>& buffer)
{
    std::lock_guard<std::mutex> lock {bufferMutex};

    buffer = *frontBuffer;
}

template<typename Type>
void DoubleBuffer<Type>::swapBuffers()
{
    std::lock_guard<std::mutex> lock {bufferMutex};

    swap(backBuffer, frontBuffer);
}
