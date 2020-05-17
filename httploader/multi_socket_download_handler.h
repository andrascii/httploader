#pragma once

#include "idownload_handler.h"

namespace HttpLoader {

struct DownloadResponse;
class RandomIntervalRangeTimer;

class MultiSocketDownloadHandler : public QObject, public IDownloadHandler {
  Q_OBJECT

 public:
  MultiSocketDownloadHandler();

  Q_INVOKABLE virtual void setPauseRange(int from, int to) override;
  Q_INVOKABLE virtual void resetPauseRange() override;
  Q_INVOKABLE virtual void setMaxRedirects(int redirects) override;
  Q_INVOKABLE virtual void setMaxParallelConnections(int connections) override;
  Q_INVOKABLE virtual void handleRequest(RequesterSharedPtr requester) override;

 protected:
  int maxRedirectsToProcess() const noexcept;
  int maxParrallelConnections() const noexcept;
  void removeRequesterFromQueue(RequesterSharedPtr requester);

 protected slots:
  void proxyAuthenticationRequired() const;

 private slots:
  void onTimerTicked();

 private:
  virtual void load(RequesterSharedPtr requester) = 0;
  virtual std::shared_ptr<DownloadResponse> responseFor(int requestId) = 0;
  virtual void pauseRequesters(const QList<Requester*>& requesterToPause) = 0;
  virtual void unpauseRequesters(const QList<Requester*>& requesterToUnpause) = 0;
  virtual void resetRequesters(const QList<Requester*>& requesterToReset) = 0;

 private:
  RandomIntervalRangeTimer* m_randomIntervalRangeTimer;
  std::deque<RequesterSharedPtr> m_requesterQueue;
  int m_maxRedirects;
  int m_maxParallelConnections;
};

}  // namespace HttpLoader
