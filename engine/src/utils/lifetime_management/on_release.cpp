#include "on_release.h"

OnRelease::~OnRelease()
{
    releaseFunc();
}
