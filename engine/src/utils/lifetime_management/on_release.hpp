template <typename F>
OnRelease::OnRelease(F&& releaseFunc_)
: releaseFunc{std::forward<F>(releaseFunc_)}
{
}
