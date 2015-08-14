#include "node_socket.h"

NodeSocket::NodeSocket(boost::uuids::uuid nodeUuid, string socketName)
: nodeUuid(nodeUuid)
, socketName(socketName)
{
}
