#define MAXCOLA 5
typedef struct {
  char pais[4];
  int ciudad;
  int volumen;
  char codigo[7];
} TELEMENTOC;
typedef struct {
  TELEMENTOC items[MAXCOLA];
  int pri, ult;
} TCOLA;

void iniciac(TCOLA *c);
int llenac(TCOLA cola);
int vaciac(TCOLA cola);
void sacac(TCOLA *c, TELEMENTOC *e);
void ponec(TCOLA *c, TELEMENTOC elem);
void consultac(TCOLA cola, TELEMENTOC *e);
