#include "resolvererror.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

<<<<<<< HEAD
ResolverError::ResolverError(int gai_errno) : gai_errno(gai_errno) {}

const char *ResolverError::what() const noexcept {
  return gai_strerror(gai_errno);
}
=======
ResolverError::ResolverError(int gai_errno): gai_errno(gai_errno) {}

const char* ResolverError::what() const noexcept { return gai_strerror(gai_errno); }
>>>>>>> origin/Server-Branch

ResolverError::~ResolverError() {}
