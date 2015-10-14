template <typename T>
unique_ptr<T> ProjectFile::loadFromFile() const
{
    if (auto project = loadFromFile()) {
        return dynamic_unique_ptr_cast<T>(project);
    }
    return nullptr;
}