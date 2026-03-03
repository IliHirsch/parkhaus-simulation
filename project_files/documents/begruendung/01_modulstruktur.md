# Modulstruktur

## Überblick

Die Parkhaus-Simulation ist modular aufgebaut, damit jede Datei eine klar abgegrenzte Aufgabe hat und sich Änderungen (z.B. neue Statistiken oder andere Eingaben) nicht durch das ganze Projekt ziehen. Jedes Modul kapselt einen Funktionsbereich und kommuniziert über saubere Schnittstellen (Header). Dadurch bleibt der Code nachvollziehbar, leichter testbar und besser wartbar.

Die Struktur besteht aus folgenden Modulen:

- `main`
- `simulation`
- `config`
- `parking`
- `queue`
- `stats`
- `io`
- `rng`
- `types`

Jedes Modul ist in `.h` (Schnittstelle) und `.c` (Implementierung/Pseudocode) getrennt.

---

## Ziel der Modularisierung

1. **Klare Verantwortlichkeiten**
   - Eingabe & Validierung der Parameter (`config`)
   - Ablaufsteuerung der Simulation (`simulation`)
   - Parkhauszustand und Ein-/Ausparken (`parking`)
   - Warteschlange für Fahrzeuge (`queue`)
   - Kennzahlen/Statistiken & Ausgabe (`stats`, `io`)
   - Zufallslogik (`rng`)
   - Gemeinsame Datentypen (`types`)

2. **Geringe Kopplung**
   Module greifen nicht “quer” auf interne Details anderer Module zu, sondern nutzen Funktionen und Datentypen über Header.

3. **Nachvollziehbarkeit für Bewertung**
   Die Umsetzung entspricht einem typischen Vorgehen aus der Vorlesung: Datenstrukturen + Funktionsschnittstellen zuerst, Logik in klaren Modulen, Pseudocode in `.c` passend zu Flowcharts.

4. **Erweiterbarkeit**
   Neue Statistiken, andere Ausgabeformate oder alternative Zufallsmodelle können ergänzt werden, ohne den Simulationskern umzubauen.

---

## Beschreibung der Module

### `main`
- Programmeinstiegspunkt.
- Liest Konfiguration über `config_read_from_terminal()`.
- Startet die Simulation über `simulation_run()`.

**Begründung:** `main` bleibt minimal und enthält keine Fachlogik → Einstieg ist sofort verständlich.

---

### `simulation`
- Zentrale Ablaufsteuerung pro Zeitschritt.
- Reihenfolge der Aktionen gemäß Flowchart:
  1) Step-Reset (Stats)  
  2) Abfahrten (Parking)  
  3) Ankunft (RNG + Parking/Queue)  
  4) Queue abarbeiten (Parking + Queue)  
  5) Stats aktualisieren + Ausgabe + Logging

**Begründung:** Trennung zwischen Simulation und parking/queue/stats (Fachlogik). So bleibt der Ablauf an einer Stelle sichtbar.

---

### `config`
- Verantwortlich für **Einlesen und Validieren** der Simulationsparameter aus dem Terminal.
- Stellt `SimConfig` bereit (Kapazität, Parkdauer, Simulationsdauer, Wahrscheinlichkeit, Seed).

**Begründung:** Eingabe/Validierung ist ein eigener Logikblock und soll nicht den Simulationscode “verschmutzen”. Außerdem kann später leicht auf andere Eingabequellen (Datei) umgestellt werden.

---

### `parking`
- Verwaltet das Parkhaus als dynamisch allokiertes Slot-Array (`malloc/free`).
- Sucht freie Plätze, parkt Fahrzeuge ein/aus, reduziert Restparkdauer.
- Behandelt Ankunft: direkt einparken oder in die Queue einreihen.
- Abarbeiten der Queue: FIFO entnehmen und einparken, Wartezeit erfassen.

**Begründung:** Das Parkhaus ist der zentrale Zustand der Simulation. Durch Kapselung bleibt die Speicherverwaltung und Stellplatzlogik konsistent und an einer Stelle.

---

### `queue`
- Implementiert eine **FIFO-Warteschlange** als Linked List.
- Dynamische Speicherverwaltung pro Knoten (`malloc/free`).
- Bietet nur Grundoperationen (init/free/push/pop/is_empty/size).

**Begründung:** Warteschlangenlogik ist unabhängig von der Parklogik. Die klare Schnittstelle verhindert, dass andere Module Knoten direkt manipulieren.

---

### `stats`
- Verwalten und Fortschreiben aller Kennzahlen:
  - Step-Zähler (neu, verlassen, queue->park)
  - Momentanwerte (Belegung, Queue-Länge)
  - Aggregate (Summen, Maxima, Vollauslastung, Mittelwerte)
  - Samples (Wartezeit, Parkdauer, Restparkdauer)
- Gibt Step-Zeilen und Finale Werte auf der Konsole aus.

**Begründung:** Alle Kennzahlen liegen zentral an einem Ort. Dadurch bleibt die Simulation logisch minimal und Statistiken können erweitert werden, ohne andere Module anzufassen.

---

### `io`
- Verantwortlich für **Log-Datei-Ausgabe** (öffnen/schließen/Step-Logging/finales Logging).
- Nutzt `Stats` als Datenquelle, erzeugt aber keine Statistik selbst.

**Begründung:** Persistente Ausgabe (Datei) ist ein eigener Verantwortungsbereich. So kann später z.B. CSV/JSON ergänzt werden, ohne `stats` oder `simulation` umzubauen.

---

### `rng`
- Kapselt Zufallszahlengenerierung (Seed, Zufallsint, Prozent-Chance).
- Sorgt für reproduzierbare Simulation bei gleichem Seed.

**Begründung:** Zufallslogik an einer Stelle verhindert verstreute `rand()`-Nutzung und macht Verhalten kontrollierbar.

---

### `types`
- Enthält **alle zentralen Datentypen** (Vehicle, ParkingSlot, ParkingLot, QueueNode/Queue, Stats, SimStatus).
- Wird von allen Modulen genutzt.

**Begründung:** Einheitliche Definitionen vermeiden Duplikate und Inkonsistenzen. Außerdem bleiben die Header schlanker, weil sie nicht gegenseitig “Typ-Fragmente” nachziehen müssen.

---

## Strukturprinzip

Die Struktur folgt dem Prinzip **Single Responsibility**: jedes Modul hat genau einen klaren Aufgabenbereich. Dadurch entstehen:
- weniger Seiteneffekte,
- klare Schnittstellen,
- einfache Erweiterbarkeit.
