#pragma once

#include <functional>
#include <string>

#include "envoy/buffer/buffer.h"
#include "envoy/common/pure.h"
#include "envoy/http/codes.h"
#include "envoy/network/listen_socket.h"

namespace Envoy {
namespace Server {

/**
 * Global admin HTTP endpoint for the server.
 */
class Admin {
public:
  virtual ~Admin() {}

  /**
   * Callback for admin URL handlers.
   * @param url supplies the URL prefix to install the handler for.
   * @param response supplies the buffer to fill in with the response body.
   * @return Http::Code the response code.
   */
  typedef std::function<Http::Code(const std::string& url, Buffer::Instance& response)> HandlerCb;

  /**
   * Add an admin handler.
   * @param prefix supplies the URL prefix to handle.
   * @param help_text supplies the help text for the handler.
   * @param callback supplies the callback to invoke when the prefix matches.
   * @param removable if true allows the handler to be removed via removeHandler.
   * @return bool true if the handler was added, false if it was not added.
   */
  virtual bool addHandler(const std::string& prefix, const std::string& help_text,
                          HandlerCb callback, bool removable) PURE;

  /**
   * Remove an admin handler if it is removable.
   * @param prefix supplies the URL prefix of the handler to delete.
   * @return bool true if the handler was removed, false if it was not removed.
   */
  virtual bool removeHandler(const std::string& prefix) PURE;

  /**
   * Obtain socket the admin endpoint is bound to.
   * @return Network::ListenSocket& socket reference.
   */
  virtual const Network::ListenSocket& socket() PURE;
};

} // namespace Server
} // namespace Envoy
