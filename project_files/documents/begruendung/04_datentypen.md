# 04 – Datentypen und Strukturen

## Überblick

Für die Umsetzung der Parkhaus-Simulation wurden eigene Datentypen und Strukturen definiert, um den Simulationszustand strukturiert und nachvollziehbar abzubilden.

Die Verwendung eigener `struct`-Typen und `enum`-Definitionen erhöht die Lesbarkeit des Codes, reduziert Fehlerquellen und sorgt für eine klare Modellierung der realen Problemstellung.

---

## Zentrale Struktur: Fahrzeug

Zur Modellierung eines einzelnen Fahrzeugs wird eine eigene Struktur verwendet:

```c
typedef struct {
    int id;
    int parkdauer;
    int einfahrtszeit;
} Fahrzeug;
```

### Begründung

- **id**  
  Eindeutige Identifikation des Fahrzeugs innerhalb der Simulation.

- **parkdauer**  
  Speichert die verbleibende Parkdauer in Zeitschritten.  
  Wird in jedem Simulationsschritt reduziert.

- **einfahrtszeit**  
  Ermöglicht die spätere Berechnung von Wartezeit oder Aufenthaltsdauer.

Die Bündelung dieser Werte in einer Struktur verhindert lose Variablen und sorgt für eine klare Zusammengehörigkeit der Fahrzeugdaten.

---

## Struktur zur Parkplatzverwaltung

Die Stellplätze werden als Array verwaltet:

```c
Fahrzeug parkplaetze[MAX_STELLPLAETZE];
```

Zusätzlich wird über eine Belegungsinformation gesteuert, ob ein Platz aktuell belegt ist.

### Begründung

- Direkter Zugriff über Index
- Effiziente Iteration bei Abfahrtsprüfung
- Konstante Speichergröße
- Einfache Implementierung ohne dynamische Speicherverwaltung

Da die Anzahl der Stellplätze konstant ist, ist eine statische Array-Struktur ausreichend und effizient.

---

## Warteschlange (Queue)

Für wartende Fahrzeuge wird eine eigene Datenstruktur verwendet:

```c
typedef struct {
    Fahrzeug daten[MAX_QUEUE];
    int front;
    int rear;
} Queue;
```

### Begründung

- FIFO-Prinzip (First-In-First-Out)
- Trennung zwischen Parkplatzverwaltung und Wartelogik
- Klare Zuständigkeit im `queue`-Modul

Die Queue ist notwendig, da bei fehlenden Stellplätzen Fahrzeuge nicht verworfen, sondern zwischengespeichert werden.

---

## Statuscodes (Enum)

Zur einheitlichen Rückmeldung von Funktionen werden Statuscodes verwendet:

```c
typedef enum {
    SIM_OK,
    SIM_QUEUE,
    SIM_ERROR
} SimStatus;
```

### Begründung

- Vermeidung von „magischen Zahlen“
- Bessere Lesbarkeit
- Klare Unterscheidung von Erfolgs- und Sonderfällen

Enums erhöhen die Typensicherheit und machen Rückgabewerte eindeutig interpretierbar.

---

## Konfigurationskonstanten

Globale Konstanten werden zentral in `config.h` definiert:

```c
#define MAX_STELLPLAETZE 50
#define MAX_QUEUE 100
#define SIM_DAUER 1000
```

### Begründung

- Vermeidung harter Kodierung im Programm
- Einfache Anpassbarkeit der Simulation
- Zentrale Verwaltung aller Parameter

---

## Wahl der Datentypen

Es werden überwiegend folgende Grundtypen verwendet:

- `int` für Zähler, Zeitangaben und Indizes
- `enum` für Statuswerte
- `struct` zur Modellierung komplexer Einheiten

Auf dynamische Speicherverwaltung (`malloc`) wird bewusst verzichtet, da:

- maximale Größen bekannt sind
- Speicherbedarf gering ist
- Fehlerquellen reduziert werden

---

## Zusammenfassung

Die gewählten Datentypen und Strukturen bilden die reale Problemstellung der Parkhaus-Simulation strukturiert ab.

Durch die Verwendung eigener `struct`- und `enum`-Typen wird:

- die Lesbarkeit erhöht,
- die Wartbarkeit verbessert,
- die Fehleranfälligkeit reduziert,
- und eine klare Trennung der Zuständigkeiten erreicht.

Die Datenstruktur ist damit stabil, nachvollziehbar und für die geplante Simulation ausreichend dimensioniert.