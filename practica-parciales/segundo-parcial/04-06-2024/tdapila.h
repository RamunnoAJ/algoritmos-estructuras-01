#define MAX_PILA 50

typedef struct {
  int legajo;
  int antiguedad;
} TELEMENTOP;

typedef struct {
  TELEMENTOP vp[MAX_PILA];
  int tope;
} TPILA;

void iniciap(TPILA *p);
int vaciap(TPILA p);
int llenap(TPILA p);
void ponep(TPILA *p, TELEMENTOP elem);
void sacap(TPILA *p, TELEMENTOP *elem);
void consultap(TPILA p, TELEMENTOP *elem);
