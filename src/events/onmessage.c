#include <string.h>

#include "../../include/ws.h"
#include "../../include/json.h"
#include "../../include/utils.h"
#include "../../include/active.h"

enum MESSAGES{
  CONNECTED = -1975448840,
  HEARTBEAT = -1211425067,
  EXIT = 2090237503
};

void onmessage(ws_cli_conn_t* client,
  const unsigned char* msg,
  uint64_t size,
  int type) {
  char* cli = ws_getaddress(client);

  int hashed_msg = (int)hash(msg);
  printf("Received message (%u) from:\t%s\nContents:\t%s\nHashed:\t\t%d\n", size, cli, msg, hashed_msg);

  switch (hashed_msg) {
    case EXIT:
      ws_sendframe_txt(client, "cya");
      ws_close_client(client);
      break;
    case HEARTBEAT:
      ws_sendframe_txt(client, "heartbeat");
      break;
    case CONNECTED:
      int i = 0;
      while (connections[i] != NULL) {
        char* packet;
        sprintf(packet, "%s", connections[i]);
        ws_sendframe_txt(client, packet);
        i += 1;
      }
      break;
    default:
      Envelope envelope;
      int parsed = parse_envelope_json(msg, &envelope);
      if (parsed == 0) {
        printf("Payload.sensorId: %s\n", envelope.payload.sensorId);
        printf("Auth: %s\n", envelope.auth);

        char res_message[32];
        sprintf(res_message, "ok(parse_envelop_json:%d)", SUCCESS);
        ws_sendframe_txt(client, res_message);
        return;
      }

      char res_message[32];
      sprintf(res_message, "error(parse_envelop_json:%d)", parsed);

      ws_sendframe_txt(client, res_message);
      break;
  }

}
