# 05 – Funktionsprototypen und einheitlicher Header

## Überblick

Für alle geplanten Funktionen werden einheitliche Funktionsprototypen in den jeweiligen Header-Dateien (`.h`) definiert.  

Dadurch wird:

- eine klare Schnittstelle zwischen Modulen geschaffen,
- die Kompilierung strukturiert,
- die Lesbarkeit erhöht,
- und die Wiederverwendbarkeit einzelner Module ermöglicht.

Alle Implementierungen befinden sich in den entsprechenden `.c`-Dateien, während die Prototypen ausschließlich in den Header-Dateien definiert sind.

---

## Grundprinzip

Jede Funktion wird:

- mit eindeutigem Rückgabewert versehen
- mit klar definierten Parametern ausgestattet
- in einem thematisch passenden Modul deklariert
- über Include-Guards abgesichert

Beispiel für einen einheitlichen Header-Aufbau:

```c
#ifndef SIMULATION_H
#define SIMULATION_H

#include "types.h"

void simulate_step(void);

#endif
```

---

## Geplante Funktionsprototypen

### simulation.h

```c
#ifndef SIMULATION_H
#define SIMULATION_H

void simulate_step(void);

#endif
```

**Aufgabe:**
- Steuert einen vollständigen Simulationsschritt
- Koordiniert Ankunft, Abfahrt, Warteschlange und Statistik

---

### parking.h

```c
#ifndef PARKING_H
#define PARKING_H

#include "types.h"

int find_free_slot(void);
void assign_vehicle(int slot, Fahrzeug car);
void free_slot(int slot);
void update_parking_durations(void);

#endif
```

**Aufgabe:**
- Verwaltung der Stellplätze
- Reduktion der Parkdauer
- Freigabe belegter Plätze

---

### queue.h

```c
#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

void queue_init(void);
int queue_is_empty(void);
void queue_enqueue(Fahrzeug car);
Fahrzeug queue_dequeue(void);

#endif
```

**Aufgabe:**
- Verwaltung wartender Fahrzeuge
- FIFO-Prinzip

---

### stats.h

```c
#ifndef STATS_H
#define STATS_H

void stats_update(void);
void stats_print(void);

#endif
```

**Aufgabe:**
- Berechnung statistischer Kennzahlen
- Ausgabe der Simulationsergebnisse

---

### io.h

```c
#ifndef IO_H
#define IO_H

void print_step_output(void);
void print_final_statistics(void);

#endif
```

**Aufgabe:**
- Formatierte Konsolenausgabe
- Trennung von Logik und Darstellung

---

## Einheitlicher Stil

Alle Funktionsprototypen folgen einem einheitlichen Stil:

- Rückgabewert steht am Anfang
- Parameter klar benannt
- Keine unnötigen globalen Variablen
- Thematische Gruppierung pro Modul

Rückgabewerte werden sinnvoll verwendet:

- `void` bei reinen Verarbeitungsfunktionen
- `int` oder `enum` bei Statusrückgaben

---

## Vorteile der Prototyp-Definition

1. Klare Schnittstellen zwischen Modulen  
2. Frühzeitige Erkennung von Typfehlern  
3. Bessere Lesbarkeit der Architektur  
4. Trennung von Deklaration und Implementierung  

---

## Zusammenfassung

Die Definition einheitlicher Funktionsprototypen in separaten Header-Dateien stellt sicher, dass:

- jedes Modul klar definierte Schnittstellen besitzt,
- Abhängigkeiten kontrolliert bleiben,
- und die Gesamtarchitektur strukturiert und wartbar bleibt.

Damit erfüllt die Parkhaus-Simulation die Anforderungen einer modular aufgebauten Softwarearchitektur.