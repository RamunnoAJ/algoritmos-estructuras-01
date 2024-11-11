#define MAX 50

typedef struct {
  unsigned int codigo;
  int cant_pedida; // Más conveniente usar unsigned int. Ídem demás campos
                   // enteros positivos.
  int hora_pedido;
  int hora_entrega;
} TELEMENTOC;

// Bien.
typedef struct {
  TELEMENTOC items[MAX];
  int pri, ult;
} TCOLAC;

void iniciac(TCOLAC *c);
int vaciac(TCOLAC c);
int llena(TCOLAC c);
void ponec(TCOLAC *c, TELEMENTOC elem);
void sacac(TCOLAC *c, TELEMENTOC *elem);
void consultac(TCOLAC c, TELEMENTOC *elem);
