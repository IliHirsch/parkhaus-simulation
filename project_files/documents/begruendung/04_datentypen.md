# Übersicht zu den festgelegten Datentypen und Strukturen

## Ziel der Typdefinitionen

Alle zentralen Datentypen der Simulation sind in der Datei `types.h`
gebündelt. Dadurch:

-   existiert **eine einheitliche, zentrale Definition** aller
    Strukturen,
-   werden **Mehrfachdefinitionen und Inkonsistenzen vermieden**,
-   bleiben die einzelnen Module logisch getrennt,
-   können sich die Module über klar definierte Datentypen austauschen.

Die Strukturierung folgt dem Prinzip:\
**Datenmodelle werden getrennt von der Logik definiert.**

------------------------------------------------------------------------

## Überblick über die verwendeten Datentypen

### 1. `SimStatus` (enum)

``` c
typedef enum {
    SIM_OK = 0,
    SIM_KFZ_WARTEN,
    SIM_ERR_INPUT
} SimStatus;
```

**Begründung:**

-   Vermeidet „magische Zahlen" als Rückgabewerte.
-   Erhöht Lesbarkeit und Wartbarkeit.
-   Ermöglicht saubere Statusrückgaben bei Funktionen wie
    `parking_handle_arrival()`.

------------------------------------------------------------------------

### 2. `Vehicle`

``` c
typedef struct {
    unsigned int id;
    int restparkdauer;
    int einfahrtzeit;
} Vehicle;
```

**Begründung:**

Ein Fahrzeug ist die zentrale Entität der Simulation.

-   `id` → eindeutige Identifikation
-   `restparkdauer` → wird pro Zeitschritt reduziert
-   `einfahrtzeit` → notwendig zur Berechnung der Wartezeit

Die Struktur ist bewusst kompakt gehalten und enthält nur
simulationsrelevante Informationen.

------------------------------------------------------------------------

### 3. `ParkingSlot`

``` c
typedef struct {
    bool belegt;
    Vehicle fahrzeug;
} ParkingSlot;
```

**Begründung:**

Ein Stellplatz kapselt:

-   Belegungszustand (`belegt`)
-   Das zugehörige Fahrzeug

Diese Struktur trennt klar: - Parkhaus (Sammlung von Slots) -
Fahrzeugdaten

------------------------------------------------------------------------

### 4. `ParkingLot`

``` c
typedef struct {
    ParkingSlot* slots;
    size_t kapazitaet;
    size_t belegte_plaetze;
} ParkingLot;
```

**Begründung:**

Das Parkhaus wird als **dynamisch allokiertes Array von Stellplätzen**
umgesetzt.

-   `slots` → dynamischer Speicher (`malloc`)
-   `kapazitaet` → feste Anzahl Stellplätze
-   `belegte_plaetze` → schneller Zugriff auf aktuelle Belegung

Vorteile dieser Struktur:

-   O(1) Zugriff auf Belegungsgrad
-   einfache Iteration über Slots
-   klare Trennung von Struktur und Logik

------------------------------------------------------------------------

### 5. `QueueNode`

``` c
typedef struct QueueNode {
    Vehicle fahrzeug;
    struct QueueNode* next;
} QueueNode;
```

**Begründung:**

Für die Warteschlange wird eine **einfach verkettete Liste** verwendet.

-   Jeder Knoten enthält genau ein Fahrzeug.
-   `next` zeigt auf das nächste Element.

Dies ermöglicht:

-   dynamisches Wachstum der Warteschlange
-   FIFO-Verhalten ohne Verschieben von Array-Inhalten
-   saubere Speicherverwaltung (`malloc` / `free`)

------------------------------------------------------------------------

### 6. `Queue`

``` c
typedef struct {
    QueueNode* head;
    QueueNode* tail;
    size_t size;
} Queue;
```

**Begründung:**

Die Queue kapselt:

-   `head` → erstes Element
-   `tail` → letztes Element
-   `size` → aktuelle Länge

Vorteile:

-   `push` und `pop` in O(1)
-   einfache Leerprüfung
-   keine Traversierung zur Längenbestimmung nötig

------------------------------------------------------------------------

### 7. `Stats`

Die `Stats`-Struktur enthält:

-   **Step-Zähler**
-   **Momentanwerte**
-   **Aggregierte Werte**
-   **Samples für Mittelwerte**

**Begründung:**

Alle statistischen Werte werden zentral gesammelt, um:

-   Berechnungen konsistent zu halten
-   doppelte Logik zu vermeiden
-   eine klare Trennung zwischen Simulation und Statistik zu
    gewährleisten

Step-Werte werden pro Zeitschritt zurückgesetzt, Aggregate über die
gesamte Simulation fortgeschrieben.

------------------------------------------------------------------------

## Designentscheidungen

### Verwendung von `struct` statt globaler Variablen

Alle Zustände (Parkhaus, Queue, Stats, Config) werden explizit
übergeben.

Vorteile:

-   bessere Testbarkeit
-   keine versteckten Seiteneffekte
-   klarer Datenfluss

------------------------------------------------------------------------

### Dynamische Speicherverwaltung

-   `ParkingLot` → dynamisches Array
-   `Queue` → dynamische Knoten

Begründung:

-   Kapazität ist zur Laufzeit bekannt
-   Warteschlange kann dynamisch wachsen
-   entspricht Anforderungen an dynamische Speicherverwaltung

------------------------------------------------------------------------

### Trennung von Daten und Verhalten

-   `types.h` enthält ausschließlich Datendefinitionen
-   Keine Logik
-   Keine Funktionsimplementierungen

Dies verhindert zyklische Abhängigkeiten und Vermischung von Struktur
und Algorithmus.

------------------------------------------------------------------------

## Zusammenfassung

Die festgelegten Datentypen modellieren:

-   Fahrzeuge als Entitäten
-   Stellplätze als Zustandscontainer
-   das Parkhaus als dynamische Struktur
-   die Warteschlange als FIFO-Datenstruktur
-   Statistiken als aggregierte Auswertungseinheit

Die gewählte Struktur sorgt für:

-   klare Verantwortlichkeiten
-   gute Erweiterbarkeit
-   saubere Speicherverwaltung
-   nachvollziehbare Datenflüsse zwischen den Modulen
