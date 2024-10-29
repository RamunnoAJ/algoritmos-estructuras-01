#define MAX_COLA 50
#define MAX_PAIS 4
#define MAX_CODIGO 7

typedef struct {
  char pais[MAX_PAIS];
  unsigned int ciudad;
  char codigo[MAX_CODIGO];
  unsigned int volumen;
} TELEMENTOC;

typedef struct {
  TELEMENTOC items[MAX_COLA];
  int pri, ult;
} TCOLA;

void iniciac(TCOLA *cola);
int vaciac(TCOLA cola);
int llenac(TCOLA cola);
void sacac(TCOLA *cola, TELEMENTOC *elem);
void ponec(TCOLA *cola, TELEMENTOC elem);
void consultac(TCOLA cola, TELEMENTOC *elem);
