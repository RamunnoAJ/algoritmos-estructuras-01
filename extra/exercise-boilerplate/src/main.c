#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct stat st = {0};

int createCExercise();
int createCProgram();
int createDirectory(char name[]);
void createFile(char name[], char extension[], char content[]);
void menu(int *op);
char *readFile(char fileName[]);

int main() {
  int op, error;
  do {
    menu(&op);
    switch (op) {
    case 1:
      error = createCExercise();
      if (error) {
        return 1;
      }
      break;
    case 2:
      error = createCProgram();
      if (error) {
        return 1;
      }
      break;
    default:
      printf("Saliendo del programa...\n");
      break;
    }
  } while (op < 0 || op > 2);

  return 0;
}

int createDirectory(char name[]) {
  if (stat(name, &st) == -1) {
    mkdir(name, 0700);
    return 0;
  }

  return 1;
}

void createFile(char name[], char extension[], char content[]) {
  FILE *fptr;
  fptr = fopen(strcat(name, extension), "w");
  fprintf(fptr, "%s", content);
  fclose(fptr);
}

int createCExercise() {
  char directoryName[32];
  char mainFileName[10] = "solucion";
  char markdownFileName[15] = "enunciado";
  int hasTextfile;

  char *mainContent = readFile("/usr/local/share/cbpc/assets/solucion.txt");
  char *markdownContent =
      readFile("/usr/local/share/cbpc/assets/enunciado.txt");

  int totalLengthMainFile = strlen(directoryName) + strlen(mainFileName) + 2;
  char *filePathMainFile = (char *)malloc(totalLengthMainFile);

  if (filePathMainFile == 0) {
    return 1;
  }

  int totalLengthMDFile = strlen(directoryName) + strlen(markdownFileName) + 2;
  char *filePathMDFile = (char *)malloc(totalLengthMDFile);

  if (filePathMDFile == 0) {
    return 1;
  }

  printf("¿Tiene archivo de texto?\n");
  printf("0) No\n");
  printf("1) Si\n");
  printf("Ingrese una opción: ");
  scanf("%d", &hasTextfile);

  printf("Ingrese el nombre del directorio: ");
  scanf("%s", directoryName);
  if (createDirectory(directoryName)) {
    return 1;
  }

  strcpy(filePathMainFile, directoryName);
  strcpy(filePathMDFile, directoryName);
  strcat(filePathMainFile, "/");
  strcat(filePathMDFile, "/");
  strcat(filePathMainFile, mainFileName);
  strcat(filePathMDFile, markdownFileName);

  if (hasTextfile) {
    char filePathTextFile[64];
    char textFileName[32];

    printf("Ingrese el nombre del archivo de texto: ");
    scanf("%s", textFileName);

    strcpy(filePathTextFile, directoryName);
    strcat(filePathTextFile, "/");
    strcat(filePathTextFile, textFileName);

    createFile(filePathTextFile, ".txt", "");
  }

  createFile(filePathMainFile, ".c", mainContent);
  createFile(filePathMDFile, ".md", markdownContent);
  free(filePathMDFile);
  free(filePathMainFile);
  return 0;
}

int createCProgram() {
  char directoryName[32];
  char mainFileName[10] = "main";
  char *mainContent = readFile("/usr/local/share/cbpc/assets/solucion.txt");
  char *mainContentWithFile =
      readFile("/usr/local/share/cbpc/assets/solucion_con_texto.txt");
  int hasTextfile;

  int totalLengthMainFile = strlen(directoryName) + strlen(mainFileName) + 2;
  char *filePathMainFile = (char *)malloc(totalLengthMainFile);

  if (filePathMainFile == 0) {
    return 1;
  }

  printf("¿Tiene archivo de texto?\n");
  printf("0) No\n");
  printf("1) Si\n");
  printf("Ingrese una opción: ");
  scanf("%d", &hasTextfile);

  printf("Ingresa el nombre del directorio: ");
  scanf("%s", directoryName);
  if (createDirectory(directoryName)) {
    return 1;
  }

  strcpy(filePathMainFile, directoryName);
  strcat(filePathMainFile, "/");
  strcat(filePathMainFile, mainFileName);

  if (hasTextfile) {
    char filePathTextFile[64];
    char textFileName[32];

    printf("Ingrese el nombre del archivo de texto: ");
    scanf("%s", textFileName);

    strcpy(filePathTextFile, directoryName);
    strcat(filePathTextFile, "/");
    strcat(filePathTextFile, textFileName);

    createFile(filePathTextFile, ".txt", "");
  }

  createFile(filePathMainFile, ".c", mainContent);
  free(filePathMainFile);
  return 0;
}

void menu(int *op) {
  printf("Menu de opciones\n");
  printf("1) C - Ejercicio\n");
  printf("2) C - Programa\n");
  printf("0) Salir\n");

  do {
    printf("Ingrese una opción: ");
    scanf("%d", op);
  } while (*op < 0 || *op > 2);
}

char *readFile(char fileName[]) {
  FILE *fptr = fopen(fileName, "r");

  if (fptr == NULL) {
    printf("Error abriendo el archivo\n");
    return NULL;
  }

  fseek(fptr, 0, SEEK_END);
  long fileSize = ftell(fptr);
  rewind(fptr);

  char *content = (char *)malloc(fileSize + 1);

  if (content == NULL) {
    printf("Error de malloc\n");
    fclose(fptr);
    return NULL;
  }

  fread(content, sizeof(char), fileSize, fptr);
  content[fileSize] = '\0';
  fclose(fptr);

  return content;
}
