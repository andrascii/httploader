#pragma once

#include "requester.h"

namespace CrawlerEngine {

class IDownloadHandler {
 public:
  virtual ~IDownloadHandler() = default;

  virtual void handle_request(RequesterSharedPtr requester) = 0;
  virtual void stop_request_handling(RequesterSharedPtr requester) = 0;

  virtual void set_pause_range(int from, int to) = 0;
  virtual void reset_pause_range() = 0;

  virtual void set_timeout(int msecs) = 0;

  virtual void set_max_redirects(int redirects) = 0;

  virtual void set_max_parallel_connections(int connections) = 0;

  virtual void set_user_agent(const QByteArray& user_agent) = 0;

  virtual void reset_proxy() = 0;
  virtual void set_proxy(
    const QString& proxy_host_name,
    int proxy_port,
    const QString& proxy_user,
    const QString& proxy_password) = 0;

  virtual QObject* qobject() = 0;
};

}
