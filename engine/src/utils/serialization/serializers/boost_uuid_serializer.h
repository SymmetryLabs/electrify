// See: http://stackoverflow.com/a/27009935/216311

#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace cereal
{
    
    template <class Archive> inline
    std::string save_minimal(const Archive& ar, const boost::uuids::uuid& uuid)
    {
        return boost::lexical_cast<std::string>(uuid);
    }

    template <class Archive> inline
    void load_minimal(Archive& ar, boost::uuids::uuid& uuid, const std::string& value)
    {
        uuid = boost::lexical_cast<boost::uuids::uuid>(value);
    }

} // namespace cereal
