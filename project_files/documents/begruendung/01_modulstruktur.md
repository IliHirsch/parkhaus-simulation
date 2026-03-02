# 01 – Modulstruktur

## Überblick

Die Parkhaus-Simulation wurde modular aufgebaut, um eine klare Trennung der Verantwortlichkeiten zu erreichen. Jede funktionale Einheit des Programms ist in ein eigenes Modul ausgelagert. Dadurch wird die Wartbarkeit erhöht, die Erweiterbarkeit verbessert und die Abhängigkeit zwischen einzelnen Programmteilen reduziert.

Die Projektstruktur gliedert sich in folgende Hauptbestandteile:

- `main`
- `simulation`
- `parking`
- `queue`
- `stats`
- `io`
- `config`
- `types`
- `rng`

Jedes Modul besteht aus einer Header-Datei (`.h`) und einer zugehörigen Implementierungsdatei (`.c`).

---

## Ziel der Modularisierung

Die Modularisierung verfolgt folgende Ziele:

1. **Trennung von Logikbereichen**
   - Parklogik
   - Warteschlangenverwaltung
   - Statistikberechnung
   - Ein-/Ausgabe
   - Konfiguration

2. **Reduzierung von Kopplung**
   Module kommunizieren ausschließlich über definierte Funktionsschnittstellen.

3. **Erhöhte Übersichtlichkeit**
   Jede Datei erfüllt eine klar definierte Aufgabe.

4. **Bessere Testbarkeit**
   Einzelne Module können isoliert getestet werden.

---

## Beschreibung der Module

### `main`
- Programmeinstiegspunkt
- Initialisiert die Simulation
- Startet die Zeitschritt-Simulation

---

### `simulation`
- Steuert den Ablauf eines einzelnen Simulationsschrittes
- Koordiniert:
  - Abfahrten
  - Ankünfte
  - Warteschlangenverarbeitung
  - Statistikaktualisierung

Dieses Modul fungiert als zentrale Steuerlogik.

---

### `parking`
- Verwaltet die Stellplätze
- Prüft freie Plätze
- Weist Fahrzeuge zu
- Gibt Plätze frei
- Aktualisiert Parkdauer

Dieses Modul kapselt sämtliche Parkplatzlogik.

---

### `queue`
- Implementiert die Warteschlange
- FIFO-Struktur
- Einfügen und Entfernen von Fahrzeugen

Dadurch bleibt die Wartelogik vollständig vom Parkplatzmanagement getrennt.

---

### `stats`
- Erfasst statistische Kennzahlen
- Berechnet Auslastung
- Speichert Simulationsmetriken

Dieses Modul enthält keine Logik zur Ausgabe, sondern ausschließlich zur Berechnung.

---

### `io`
- Zuständig für Konsolenausgabe
- Formatiert Statistiken
- Trennt Darstellung von Berechnung

---

### `config`
- Enthält globale Konstanten
  - Anzahl Stellplätze
  - Simulationsdauer
  - Wahrscheinlichkeiten

Konfigurationswerte sind zentral definiert und nicht im Code verteilt.

---

### `types`
- Enthält zentrale Datentypdefinitionen
  - `struct Fahrzeug`
  - Enums für Statuscodes

Dient der einheitlichen Typdefinition im gesamten Projekt.

---

### `rng`
- Kapselt Zufallszahlengenerierung
- Ermöglicht zentrale Kontrolle der Zufallslogik

---

## Strukturprinzip

Die gewählte Struktur folgt dem Prinzip der **Single Responsibility**:

> Jedes Modul übernimmt genau eine klar definierte Aufgabe.

Dadurch wird vermieden:
- doppelte Logik
- unübersichtlicher Code
- starke Modulabhängigkeiten

---

## Zusammenfassung

Die modulare Struktur ermöglicht eine klare Trennung zwischen:

- Steuerlogik (`simulation`)
- Zustandsverwaltung (`parking`, `queue`)
- Statistik (`stats`)
- Darstellung (`io`)
- Konfiguration (`config`)

Diese Architektur bildet eine stabile Grundlage für die Implementierung der Parkhaus-Simulation und erleichtert spätere Erweiterungen oder Anpassungen.