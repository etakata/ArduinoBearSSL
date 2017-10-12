#ifndef _BEAR_SSL_CLIENT_
#define _BEAR_SSL_CLIENT_

#include <Arduino.h>
#include <Client.h>

#include "bearssl/bearssl.h"

class BearSSLClient : public Client {

public:
  BearSSLClient(Client& client);
  virtual ~BearSSLClient();

  virtual int connect(IPAddress ip, uint16_t port);
  virtual int connect(const char* host, uint16_t port);
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  virtual int available();
  virtual int read();
  virtual int read(uint8_t *buf, size_t size);
  virtual int peek();
  virtual void flush();
  virtual void stop();
  virtual uint8_t connected();
  virtual operator bool();

  using Print::write;

private:
  int connectSSL(const char* host);
  static int clientRead(void *ctx, unsigned char *buf, size_t len);
  static int clientWrite(void *ctx, const unsigned char *buf, size_t len);

private:
  Client* _client;

  br_ssl_client_context _sc;
  br_x509_minimal_context _xc;
  unsigned char _iobuf[BR_SSL_BUFSIZE_MONO/*BR_SSL_BUFSIZE_BIDI*/];
  br_sslio_context _ioc;
  int _peek;
};

#endif
